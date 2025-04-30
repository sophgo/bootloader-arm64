#include "ff_video_encode.hpp"
#include "ff_video_decode.hpp"
#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif
#include <csignal>

static void usage(char *program_name)
{
#ifdef BM_PCIE_MODE
    av_log(NULL, AV_LOG_ERROR, "Usage: \n\t%s <input file> <output file>  encoder framerate bitrate(kbps) isdmabuffer pcie_no_copyback sophon_idx\n", program_name);
    av_log(NULL, AV_LOG_ERROR, "\tencoder: H264 or H265.\n");
    av_log(NULL, AV_LOG_ERROR, "\tisdmabuffer: 1, no memory copy in encoder. Or 0, has memory copy.\n");
    av_log(NULL, AV_LOG_ERROR, "\tpcie_no_copyback: 1, do not copy decoded raw YUV to host. Or 0, copy decoded raw YUV to host.\n");
    av_log(NULL, AV_LOG_ERROR, "\tsophon_idx: bitmain sophon device index.\n");
    av_log(NULL, AV_LOG_ERROR, "Examples:\n");
    av_log(NULL, AV_LOG_ERROR, "\t%s ./file_example_MP4_1920_18MG.mp4 tran5.ts H264 30 3000 1 1 0\n", program_name);
    av_log(NULL, AV_LOG_ERROR, "\t%s ./file_example_MP4_1920_18MG.mp4 tran5.ts H264 30 3000 0 0 0\n", program_name);
    av_log(NULL, AV_LOG_ERROR, "\t%s ./file_example_MP4_1920_18MG.mp4 tran5.ts H264 30 3000 1 0 0\n", program_name);

#else
    av_log(NULL, AV_LOG_ERROR, "Usage: \n\t%s <input file> <output file>  encoder framerate bitrate(kbps) isdmabuffer\n", program_name);
    av_log(NULL, AV_LOG_ERROR, "\tencoder: H264 or H265.\n");
    av_log(NULL, AV_LOG_ERROR, "\tisdmabuffer: 1, no memory copy in encoder. Or 0, has memory copy.\n");
    av_log(NULL, AV_LOG_ERROR, "Examples:\n");
    av_log(NULL, AV_LOG_ERROR, "\t%s ./file_example_MP4_1920_18MG.mp4 tran5.ts H264 30 3000 1\n", program_name);
#endif
}
int quit_flag=0;
void handler(int sig)
{
    quit_flag = 1;
    printf("program will exited \n");
}

int main(int argc, char **argv)
{
    int ret;
    int enccodec_id = AV_CODEC_ID_H264;
    int framerate = 30;
    int bitrate = 3000;
    int is_dma_buffer = false;
    int pcie_no_copyback =0;
    int sophon_idx = 0;
#ifdef WIN32
    clock_t tv1;
    clock_t tv2;
#else
    struct timeval tv1, tv2;
#endif
    signal(SIGINT,handler);
    signal(SIGTERM,handler);

    if (argc < 4) {
        usage(argv[0]);
        return -1;
    }
    if(argc > 3)
    {
        if(strstr(argv[3],"H265") != NULL)
        {
           enccodec_id = AV_CODEC_ID_H265;
        }
    }
    if (argc >4)
    {
        int temp = atoi(argv[4]);
        if(temp >10 && temp <= 60)
        {
             framerate = temp;
        }
        else
        {
            printf("bad frameteate setting \n");
            return 1;
        }
        printf("framerate= %d \n",framerate);
    }
    if (argc >5 )
    {
        int temp = atoi(argv[5]);
        if(temp >500 && temp < 10000)
        {
             bitrate = temp*1000;
        }
        printf("bitrate= %d \n", bitrate);
    }
    if(argc > 6)
    {
        int temp = atoi(argv[6]);
        if(temp == 1)
        {
            is_dma_buffer = true;
        }
        printf("is_dma_buffer= %d \n", is_dma_buffer);
    }
#ifdef BM_PCIE_MODE
    if(argc > 7)
    {
         int temp = atoi(argv[7]);
         if(temp == 1)
             pcie_no_copyback = 1;
         printf("pcie_no_copyback= %d \n", pcie_no_copyback);
    }
    if(argc > 8)
    {
         int temp = atoi(argv[8]);
         if(temp >=0 && temp < 128 )
         {
             sophon_idx = temp;
             printf("sophon_idx=%d \n" ,sophon_idx);
         }
         else
         {
            printf("### sophon_idx is invalid ");
            return 0;
         }
    }
#endif

    VideoDec_FFMPEG reader;

    if(is_dma_buffer)
       ret = reader.openDec(argv[1],9,sophon_idx,pcie_no_copyback);  // in no_copy mode decoder's dma buffer will hold by encoder ref-frame cache
    else
       ret = reader.openDec(argv[1],5,sophon_idx,pcie_no_copyback);
    if(ret < 0 )
    {
        printf("#################open input media failed  ##########\n");
        return -1;
    }
    AVCodecParameters *codec = reader.getCodecPar();
    if(codec->width <= 0 ||codec->height <= 0 || codec->codec_type != AVMEDIA_TYPE_VIDEO)
    {
        printf("#################bad input file no video found ##########\n");
        return -1;
    }

    AVFrame * frame = NULL;
    frame = reader.grabFrame();

    printf("src bitrate=%ld, dst bitrate=%d\n", codec->bit_rate, bitrate);

    VideoEnc_FFMPEG writer;
#ifdef BM_PCIE_MODE
    ret = writer.openEnc(argv[2],enccodec_id, framerate , frame->width, frame->height,
                         frame->format, bitrate, is_dma_buffer, sophon_idx);
#else
    ret = writer.openEnc(argv[2],enccodec_id, framerate , frame->width, frame->height,
                         frame->format, bitrate, is_dma_buffer);
#endif
    if (ret !=0)
    {
        printf("writer.openEnc failed \n ");
        return -1;
    }
    writer.writeAvFrame(frame);
    unsigned int frame_nums = 0;
    int cur = 0;

    //av_log_set_level(AV_LOG_DEBUG);
#ifdef WIN32
    tv1 = clock();
#else
    gettimeofday(&tv1, NULL);
#endif
    while (cur < 1200 && quit_flag==0)
    {
        frame = reader.grabFrame();
        if(!frame)
        {
            printf("no frame ! \n");
            break;
        }
        ret = writer.writeAvFrame(frame);

        if ((frame_nums+1) % 300 == 0)
        {
            unsigned int time;
#ifdef WIN32
            tv2 = clock();
            time = (tv2 - tv1);
#else
            gettimeofday(&tv2, NULL);
            time = (tv2.tv_sec - tv1.tv_sec)*1000 + (tv2.tv_usec - tv1.tv_usec)/1000;
#endif
            printf("current process is %f fps!\n", (frame_nums * 1000.0) / (float)time);
        }
        frame_nums++;
    }
    writer.closeEnc();
    reader.closeDec();
    printf("transcoding finish!\n");
    return 0;
}
