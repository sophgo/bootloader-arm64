#include "ff_video_decode.h"
#include "ff_video_encode.h"
#include "ff_video_filter.h"
extern "C"{
#include <sys/time.h>
#include <csignal>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
}

#define MAX_INST_NUM 256
#define PCIE_MODE_ARG_NUM 5
#define SOC_MODE_ARG_NUM 3
#define PCIE_CARD_NUM 1
#define SET_ALIGNMENT 8
#define ENC_ALIGNMENT 32
pthread_t thread_id[MAX_INST_NUM];
int quit_flag    = 0;
int thread_count = 0;


typedef struct MultiInstTest {
    const char  *src_filename;
    const char  *decoder_name;
    const char  *output_filename;
    const char  *codecer_name;
    int          encode_pixel_format;
    int          sophon_idx;
    int          output_format_mode;
    int          pre_allocation_frame;
    int          is_by_filename;
    int          height;
    int          width;
    int          frame_rate;
    int          bitrate;
    int          is_dma_buffer;
    int          thread_index;
    int          thread_num;
#ifdef BM_PCIE_MODE
    int          zero_copy;
#endif
    unsigned int frame_nums[MAX_INST_NUM];
} THREAD_ARG;

static void usage(char *program_name);
void handler(int sig);
void *startOneInst(void *arg);


int main(int argc, char **argv)
{
    int arg_index = 0;
#ifdef BM_PCIE_MODE
    if(argc > MAX_INST_NUM ){
        printf("The number of threads cannot exceed 256\n");
        return -1;
    }
    printf("This is pcie module\n");

    if(argc < 12){
        usage(argv[0]);
        return -1;
    }
#else
    if(argc > MAX_INST_NUM){
        printf("The number of threads cannot exceed 256\n");
        return -1;
    }
    printf("This is soc module\n");

    if(argc < 10){
        usage(argv[0]);
        return -1;
    }
#endif
    signal(SIGINT,handler);
    signal(SIGTERM,handler);
    THREAD_ARG *thread_arg = (THREAD_ARG *)malloc(sizeof(THREAD_ARG));

    memset(thread_arg,0,sizeof(THREAD_ARG));

    thread_arg->src_filename            = argv[++arg_index];
    thread_arg->output_filename         = argv[++arg_index];
    const char * ch_encode_pixel_format = argv[++arg_index];
    thread_arg->codecer_name            = argv[++arg_index];
    thread_arg->width                   = atoi(argv[++arg_index]);
    thread_arg->height                  = atoi(argv[++arg_index]);
    thread_arg->frame_rate              = atoi(argv[++arg_index]);
    thread_arg->bitrate                 = atoi(argv[++arg_index]);
    thread_arg->thread_num              = atoi(argv[++arg_index]);
#ifdef BM_PCIE_MODE
    thread_arg->zero_copy               = atoi(argv[++arg_index]);
#endif

    if(!thread_arg->src_filename || !ch_encode_pixel_format \
        || !thread_arg->output_filename || !thread_arg->codecer_name){
        usage(argv[0]);
        return -1;
    }

    if(thread_arg->height < 0 ){
        usage(argv[0]);
        return -1;
    }

    if(thread_arg->width < 0 ){
        usage(argv[0]);
        return -1;
    }

    if(thread_arg->frame_rate < 0 ){
        usage(argv[0]);
        return -1;
    }

    if(thread_arg->bitrate > 500 && thread_arg->bitrate <10000 ){
        thread_arg->bitrate = thread_arg->bitrate * 1000;
    }else{
        usage(argv[0]);
        return -1;
    }
    if(thread_arg->thread_num <= 0 ||  thread_arg->thread_num > 256){
        usage(argv[0]);
        return -1;
    }
    if (strcmp(ch_encode_pixel_format, "I420") == 0)
        thread_arg->encode_pixel_format = AV_PIX_FMT_YUV420P;
    else if (strcmp(ch_encode_pixel_format, "NV12") == 0)
        thread_arg->encode_pixel_format = AV_PIX_FMT_NV12;
    else {
        usage(argv[0]);
        return -1;
    }

#ifdef BM_PCIE_MODE
    thread_arg->sophon_idx         = atoi(argv[++arg_index]);
    if(thread_arg->sophon_idx < 0 && thread_arg->sophon_idx > 120){
        usage(argv[0]);
        return -1;
    }
#endif

    int td_index = 0;
 //Initialize multiple threads
    while( thread_arg->thread_num ){
        thread_arg->thread_index = td_index;
        pthread_create(&(thread_id[td_index]), NULL, startOneInst, thread_arg);
        usleep(100000);
        td_index++;
        thread_arg->thread_index = td_index;
        thread_arg->thread_num--;
    }

    td_index = 0;
    while(1){
        if(quit_flag == 1 || !thread_count)
        {
            pthread_join(thread_id[td_index],NULL);
            td_index++;
        }
        if(td_index == thread_arg->thread_index){
            free(thread_arg);
            thread_arg = NULL;
            break;
        }
        usleep(1000 * 500);
    }
    return 0;
}

void *startOneInst(void *arg){
    thread_count++;
    int sophon_idx              = 0;
    THREAD_ARG *thread_arg      = (THREAD_ARG *)arg;
    int index                   = thread_arg->thread_index;
    const char *src_filename    = thread_arg->src_filename;
    //const char *decoder_name    = thread_arg->decoder_name;
    const char *output_filename = thread_arg->output_filename;
    const char *codecer_name    = thread_arg->codecer_name;
    int output_format_mode      = thread_arg->output_format_mode;
    //int pre_allocation_frame    = thread_arg->pre_allocation_frame;
    //int is_by_filename          = thread_arg->is_by_filename;
    int height                  = thread_arg->height;
    int width                   = thread_arg->width;
    int encode_pixel_format     = thread_arg->encode_pixel_format;
    int frame_rate              = thread_arg->frame_rate;
    int bitrate                 = thread_arg->bitrate;
    //int is_dma_buffer           = thread_arg->is_dma_buffer;
#ifdef BM_PCIE_MODE
    int zero_copy               = thread_arg->zero_copy;
    sophon_idx                  = thread_arg->sophon_idx;
#endif
    int ret                     =  0;
    char file_name[256]         = {0};
    struct timeval tv1, tv2;
    unsigned int time;

    width = (width + SET_ALIGNMENT - 1) & ~(SET_ALIGNMENT - 1);
    height = (height + SET_ALIGNMENT - 1) & ~(SET_ALIGNMENT - 1);
    strcpy(file_name,output_filename);
    const char *name_start  = strtok(file_name, ".");
    const char *name_end    = strrchr(output_filename, 46);//ascii '.' = 46
    sprintf(file_name,"%s%d%s",name_start,index,name_end);

    VideoDec_FFMPEG reader;
#ifdef BM_PCIE_MODE
    ret = reader.openDec(src_filename,1,NULL,output_format_mode,2,sophon_idx,zero_copy);
#else
    ret = reader.openDec(src_filename,1,NULL,output_format_mode,2);
#endif
    if(ret < 0 )
    {
        printf("open input media failed\n");
        thread_count--;
        return (void *)-1;
    }

    ffmpegFilterContext filter;
    AVFrame *frame = NULL;
    VideoEnc_FFMPEG writer;

    frame = reader.grabFrame();

    if(encode_pixel_format != AV_PIX_FMT_YUV420P){
     width  = frame->width;
     height = frame->height;
    }
    else{
        av_log(NULL, AV_LOG_INFO, "init filter...\n");

        /* check target width */
        if (width % ENC_ALIGNMENT != 0) {
            int width_align = (width + ENC_ALIGNMENT - 1) & ~(ENC_ALIGNMENT - 1);
            av_log(NULL, AV_LOG_WARNING, "encoder input frame must be %d bytes align, change target width from %d to %d\n", ENC_ALIGNMENT, width, width_align);
            width = width_align;
        }
        initFilter(&filter, frame->width, frame->height, width, height, frame->format, frame_rate, sophon_idx);
 }

#ifdef BM_PCIE_MODE
    ret = writer.openEnc(file_name, codecer_name , 0 , frame_rate , width, height, encode_pixel_format, bitrate, sophon_idx);
#else
    ret = writer.openEnc(file_name, codecer_name , 0 , frame_rate , width, height, encode_pixel_format, bitrate);
#endif
    if (ret !=0 ) {
        av_log(NULL, AV_LOG_ERROR,"writer.openEnc failed\n");
     thread_count--;
        return (void *)-1;
    }
    gettimeofday(&tv1, NULL);
    if(encode_pixel_format == AV_PIX_FMT_YUV420P){

        getFilterFrame(filter, frame, writer.frameWrite);
        av_frame_unref(frame);

        if(!writer.frameWrite){
            printf("no frame ! \n");
            exit(-1);
        }
    }
    if(encode_pixel_format == AV_PIX_FMT_YUV420P){
        writer.writeFrame(writer.frameWrite);
        av_frame_unref(writer.frameWrite);
    }
    else
        writer.writeFrame(frame);
    thread_arg->frame_nums[index]++;

    while(!quit_flag){
        frame = reader.grabFrame();
        if(!frame){
            break;
        }
        if(encode_pixel_format == AV_PIX_FMT_YUV420P){
            getFilterFrame(filter, frame, writer.frameWrite);
            av_frame_unref(frame);
            if(!writer.frameWrite){
                printf("no frame ! \n");
                break;
            }
        }
        if ((thread_arg->frame_nums[index]+1) % 300 == 0){
               gettimeofday(&tv2, NULL);
               time = (tv2.tv_sec - tv1.tv_sec)*1000 + (tv2.tv_usec - tv1.tv_usec)/1000;
               printf("%dth thread process is %5.4f fps!\n", index ,(thread_arg->frame_nums[index] * 1000.0) / (float)time);
        }

        if(encode_pixel_format == AV_PIX_FMT_YUV420P){
            writer.writeFrame(writer.frameWrite);
            av_frame_unref(writer.frameWrite);
        }
        else
            writer.writeFrame(frame);
        thread_arg->frame_nums[index]++;

    }
    gettimeofday(&tv2, NULL);
    time = (tv2.tv_sec - tv1.tv_sec)*1000 + (tv2.tv_usec - tv1.tv_usec)/1000;
    printf("%dth thread Decode %d frame in total, avg: %5.4f, time: %dms!\n", index ,thread_arg->frame_nums[index],(float)thread_arg->frame_nums[index] * 1000 / (float)time, time);

    reader.closeDec();
    deInitFilter(filter);
    writer.closeEnc();
    av_log(NULL, AV_LOG_INFO, "encode finish!\n");
    thread_count--;
    return (void *)0;
}



static void usage(char *program_name)
{
#ifdef BM_PCIE_MODE
    av_log(NULL, AV_LOG_ERROR, "Usage: \n\t%s [src_filename] [output_filename] [encode_pixel_format] [encoder_name] [height] [width] [frame_rate] [bitrate] [thread_num] [zero_copy] [sophon_idx]\n", program_name);
    av_log(NULL, AV_LOG_ERROR, "\t[src_filename]            input file name x.mp4 x.ts...\n");
    av_log(NULL, AV_LOG_ERROR, "\t[output_filename]         encode output file name x.mp4,x.ts...\n");
    av_log(NULL, AV_LOG_ERROR, "\t[encode_pixel_format]     encode format I420.\n");
    av_log(NULL, AV_LOG_ERROR, "\t[encoder_name]            encode h264_bm,hevc_bm,h265_bm\n");
    av_log(NULL, AV_LOG_ERROR, "\t[height]                  encode height.\n");
    av_log(NULL, AV_LOG_ERROR, "\t[width]                   encode width.\n");
    av_log(NULL, AV_LOG_ERROR, "\t[frame_rate]              encode frame_rate.\n");
    av_log(NULL, AV_LOG_ERROR, "\t[bitrate]                 encode bitrate.\n");
    av_log(NULL, AV_LOG_ERROR, "\t[thread_num]              thread num.\n");
    av_log(NULL, AV_LOG_ERROR, "\t[zero_copy ]              0: copy host mem,1: nocopy.\n");
    av_log(NULL, AV_LOG_ERROR, "\t[sophon_idx]              sophon devices idx\n");
    av_log(NULL, AV_LOG_ERROR, "\t%s example.mp4 test.ts I420 h264_bm 800 400 25 3000 3 0 0\n", program_name);

#else
    av_log(NULL, AV_LOG_ERROR, "Usage: \n\t%s [src_filename] [output_filename] [encode_pixel_format] [encoder_name] [height] [width] [frame_rate] [bitrate] [thread_num]...\n", program_name);
    av_log(NULL, AV_LOG_ERROR, "\t[src_filename]            input file name x.mp4 x.ts...\n");
    av_log(NULL, AV_LOG_ERROR, "\t[output_filename]         encode output file name x.mp4,x.ts...\n");
    av_log(NULL, AV_LOG_ERROR, "\t[encode_pixel_format]     encode format I420,NV12\n");
    av_log(NULL, AV_LOG_ERROR, "\t[encoder_name]            h264_bm,hevc_bm,h265_bm\n");
    av_log(NULL, AV_LOG_ERROR, "\t[height]                  encode height.\n");
    av_log(NULL, AV_LOG_ERROR, "\t[width]                   encode width.\n");
    av_log(NULL, AV_LOG_ERROR, "\t[frame_rate]              encode frame_rate.\n");
    av_log(NULL, AV_LOG_ERROR, "\t[bitrate]                 encode bitrate.\n");
    av_log(NULL, AV_LOG_ERROR, "\t[thread_num]              thread num.\n");
    av_log(NULL, AV_LOG_ERROR, "\t%s example.mp4 test.ts I420 h264_bm 1920 1080 25 3000 3\n", program_name);

#endif

}

void handler(int sig)
{
    quit_flag = 1;
    printf("program will exited \n");
}
