
#include <iostream>

extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
}

class VideoDec_FFMPEG
{
public:
    VideoDec_FFMPEG();
    ~VideoDec_FFMPEG();

    int openDec(const char* filename,int extra_frame_buffer_num = 5 ,
                int sophon_idx = 0, int pcie_no_copyback = 0);

    void closeDec();

    AVCodecParameters* getCodecPar();
    AVFrame * grabFrame();

private:
    AVFormatContext   *ifmt_ctx;
    AVCodec           *decoder;
    AVCodecContext    *video_dec_ctx ;
    AVCodecParameters *video_dec_par;

    int width;
    int height;
    int pix_fmt;

    int video_stream_idx;
    AVFrame *frame;
    AVPacket pkt;
    int refcount;

    AVCodec* bm_find_hw_decoder(AVCodecID dec_id)
    {
        AVCodec *decoder = NULL;

        switch (dec_id)
        {
        case AV_CODEC_ID_MJPEG:
            decoder = avcodec_find_decoder_by_name("jpeg_bm");
            break;
        case AV_CODEC_ID_H264:
            decoder = avcodec_find_decoder_by_name("h264_bm");
            break;
        case AV_CODEC_ID_HEVC:
            decoder = avcodec_find_decoder_by_name("hevc_bm");
            break;
        default:
            /* TODO try SW decoder */
            decoder = avcodec_find_decoder(dec_id);
            break;
        }

        return decoder;
    }

    int openCodecContext(int *stream_idx, AVCodecContext **dec_ctx,
                         AVFormatContext *fmt_ctx, enum AVMediaType type,
                         int extra_frame_buffer_num = 5,
                         int sophon_idx = 0,int pcie_no_copyback = 0);
};

VideoDec_FFMPEG::VideoDec_FFMPEG()
{
    ifmt_ctx = NULL;
    video_dec_ctx = NULL;
    video_dec_par = NULL;
    decoder = NULL;

    width   = 0;
    height  = 0;
    pix_fmt = 0;

    video_stream_idx = -1;
    refcount = 1;

    av_init_packet(&pkt);
    pkt.data = NULL;
    pkt.size = 0;


    frame = av_frame_alloc();
}
VideoDec_FFMPEG::~VideoDec_FFMPEG()
{
    printf("#######VideoDec_FFMPEG exit \n");
}

AVCodecParameters* VideoDec_FFMPEG::getCodecPar()
{
    return video_dec_par;
}

int VideoDec_FFMPEG::openDec(const char* filename, int extra_frame_buffer_num,
                             int sophon_idx, int pcie_no_copyback)
{
    int ret = 0;

    ret = avformat_open_input(&ifmt_ctx, filename, NULL, NULL);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot open input file\n");
        return ret;
    }

    ret = avformat_find_stream_info(ifmt_ctx, NULL);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot find stream information\n");
        return ret;
    }

#ifdef BM_PCIE_MODE
    ret = openCodecContext(&video_stream_idx, &video_dec_ctx, ifmt_ctx, AVMEDIA_TYPE_VIDEO ,
                           extra_frame_buffer_num,sophon_idx,pcie_no_copyback);
#else
    ret = openCodecContext(&video_stream_idx, &video_dec_ctx, ifmt_ctx, AVMEDIA_TYPE_VIDEO ,
                           extra_frame_buffer_num);
#endif
    if (ret >= 0) {
        width   = video_dec_ctx->width;
        height  = video_dec_ctx->height;
        pix_fmt = video_dec_ctx->pix_fmt;
    }
    av_log(video_dec_ctx, AV_LOG_INFO,
           "openDec video_stream_idx = %d, pix_fmt = %d\n",
           video_stream_idx, pix_fmt);
    return ret;
}

void VideoDec_FFMPEG::closeDec()
{
    if (video_dec_ctx) {
        avcodec_free_context(&video_dec_ctx);
        video_dec_ctx = NULL;
    }
    if (ifmt_ctx) {
        avformat_close_input(&ifmt_ctx);
        ifmt_ctx = NULL;
    }
    if (frame) {
        av_frame_free(&frame);
        frame = NULL;
    }
}

int VideoDec_FFMPEG::openCodecContext(int *stream_idx,AVCodecContext **dec_ctx, AVFormatContext *fmt_ctx,
                                      enum AVMediaType type,
                                      int extra_frame_buffer_num, int sophon_idx, int pcie_no_copyback)
{
    int ret, stream_index;
    AVStream *st;
    AVCodec *dec = NULL;
    AVDictionary *opts = NULL;

    ret = av_find_best_stream(fmt_ctx, type, -1, -1, NULL, 0);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Could not find %s stream \n",av_get_media_type_string(type));
        return ret;
    }

    stream_index = ret;
    st = fmt_ctx->streams[stream_index];

    /* find decoder for the stream */
    decoder = bm_find_hw_decoder(st->codecpar->codec_id);
    if (!decoder) {
        av_log(NULL, AV_LOG_FATAL,"Failed to find %s codec\n",
               av_get_media_type_string(type));
        return AVERROR(EINVAL);
    }

    /* Allocate a codec context for the decoder */
    *dec_ctx = avcodec_alloc_context3(decoder);
    if (!*dec_ctx) {
        av_log(NULL, AV_LOG_FATAL, "Failed to allocate the %s codec context\n",
               av_get_media_type_string(type));
        return AVERROR(ENOMEM);
    }

    /* Copy codec parameters from input stream to output codec context */
    ret = avcodec_parameters_to_context(*dec_ctx, st->codecpar);
    if (ret < 0) {
        av_log(NULL, AV_LOG_FATAL, "Failed to copy %s codec parameters to decoder context\n",
               av_get_media_type_string(type));
        return ret;
    }

    video_dec_par = st->codecpar;
    /* Init the decoders, with or without reference counting */
    av_dict_set(&opts, "refcounted_frames", refcount ? "1" : "0", 0);
#ifdef BM_PCIE_MODE
    av_dict_set_int(&opts, "zero_copy", pcie_no_copyback, 0);
    av_dict_set_int(&opts, "sophon_idx", sophon_idx, 0);
#endif
    if(extra_frame_buffer_num > 5)
       av_dict_set_int(&opts, "extra_frame_buffer_num", extra_frame_buffer_num, 0);  // if we use dma_buffer mode

    ret = avcodec_open2(*dec_ctx, dec, &opts);
    if (ret < 0) {
        av_log(NULL, AV_LOG_FATAL, "Failed to open %s codec\n",
               av_get_media_type_string(type));
        return ret;
    }
    *stream_idx = stream_index;

    av_dict_free(&opts);

    return 0;
}

AVFrame * VideoDec_FFMPEG::grabFrame()
{
    int ret = 0;
    int got_frame = 0;

    while (1) {
        av_packet_unref(&pkt);
        ret = av_read_frame(ifmt_ctx, &pkt);
        if (ret < 0) {
            return NULL; // TODO
        }

        if (pkt.stream_index != video_stream_idx) {
            continue;
        }

        if (!frame) {
            av_log(video_dec_ctx, AV_LOG_ERROR, "Could not allocate frame\n");
            return NULL;
        }

        if (refcount)
            av_frame_unref(frame);

        ret = avcodec_decode_video2(video_dec_ctx, frame, &got_frame, &pkt);
        if (ret < 0) {
            av_log(video_dec_ctx, AV_LOG_ERROR, "Error decoding video frame (%d)\n", ret);
            continue; // TODO
        }

        if (!got_frame) {
            continue;
        }

        width   = video_dec_ctx->width;
        height  = video_dec_ctx->height;
        pix_fmt = video_dec_ctx->pix_fmt;
        if (frame->width != width || frame->height != height || frame->format != pix_fmt) {
            av_log(video_dec_ctx, AV_LOG_ERROR,
                   "Error: Width, height and pixel format have to be "
                   "constant in a rawvideo file, but the width, height or "
                   "pixel format of the input video changed:\n"
                   "old: width = %d, height = %d, format = %s\n"
                   "new: width = %d, height = %d, format = %s\n",
                   width, height, av_get_pix_fmt_name((AVPixelFormat)pix_fmt),
                   frame->width, frame->height,
                   av_get_pix_fmt_name((AVPixelFormat)frame->format));
            continue;
        }

        break;
    }

    return frame;
}


