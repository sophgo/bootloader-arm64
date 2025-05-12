/*
 * Copyright (c) 2019 BitMain
 *
 *
 * @file
 *  example for video encode from BGR data,
 *   ps: i implement a C++ encoder it will be more easy to understand ffmpeg
 */
#ifdef __cplusplus
extern "C" {
#endif
#include "libavcodec/avcodec.h"
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavformat/avformat.h>
#include <libavfilter/buffersink.h>
#include <libavfilter/buffersrc.h>
#include <libavutil/opt.h>
#include <libavutil/pixdesc.h>
#ifdef __cplusplus
}
#endif

#include <iostream>

#define SIMD_SIZE 32

class VideoEnc_FFMPEG
{
public:
    VideoEnc_FFMPEG();
    ~VideoEnc_FFMPEG();
    int openEnc(const char* filename, int codecId, int framerate,
                int width, int height, int inputformat, int bitrate,
                bool isdmabufer = false, int sophon_idx = 0);

    int flush_encoder();
    void closeEnc();
    int writeFrame( const uint8_t* data, int step, int width, int height);
    int writeAvFrame(AVFrame * inputPicture);
    AVCodecContext  * enc_ctx;
private:
    AVFormatContext * ofmt_ctx;
    AVFrame         * picture;
    AVFrame         * input_picture;
    AVStream        * out_stream;
    AVPixelFormat     input_pix_fmt;
    uint8_t         * aligned_input;
    int               frame_width;
    int               frame_height;
    int               frame_idx;
    struct SwsContext *img_convert_ctx; // TODO

    AVCodec* find_hw_video_encoder(int codecId)
    {
        AVCodec *encoder = NULL;
        switch (codecId)
        {
        case AV_CODEC_ID_H264:
            encoder = avcodec_find_encoder_by_name("h264_bm");
            break;
        case AV_CODEC_ID_H265:
            encoder = avcodec_find_encoder_by_name("h265_bm");
            break;
        default:
            break;
        }
        return encoder;
    }
};

VideoEnc_FFMPEG::VideoEnc_FFMPEG()
{
    ofmt_ctx = NULL;
    picture= NULL;
    input_picture = NULL;
    out_stream = NULL;
    input_pix_fmt = AV_PIX_FMT_NONE;
    aligned_input  = NULL;
    frame_width = 0;
    frame_height = 0;
    frame_idx = 0;
    img_convert_ctx = NULL;
}
VideoEnc_FFMPEG::~VideoEnc_FFMPEG()
{
    printf("#######VideoEnc_FFMPEG exit \n");
}

int VideoEnc_FFMPEG::openEnc(const char* filename, int codecId, int framerate,
                             int width, int height, int inputformat, int bitrate,
                             bool isdmabufer, int sophon_idx)
{
    AVCodec *encoder;
    AVDictionary *opts = NULL;
    frame_idx = 0;
    input_pix_fmt = (AVPixelFormat)inputformat;
    frame_width = width;
    frame_height = height;
    int ret = 0;

    avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, filename);
    if (!ofmt_ctx) {
        av_log(NULL, AV_LOG_ERROR, "Could not create output context\n");
        return AVERROR_UNKNOWN;
    }

    /* Find the hardware video encoder */
    encoder = find_hw_video_encoder((AVCodecID)codecId);
    if (!encoder) {
        av_log(NULL, AV_LOG_FATAL, "Necessary Hardware encoder not found\n");
        return AVERROR_INVALIDDATA;
    }

    enc_ctx = avcodec_alloc_context3(encoder);
    if (!enc_ctx) {
        av_log(NULL, AV_LOG_FATAL, "Failed to allocate the encoder context\n");
        return AVERROR(ENOMEM);
    }
    enc_ctx->codec_id = (AVCodecID)codecId;
    enc_ctx->height   = height;
    enc_ctx->width    = width;
    enc_ctx->pix_fmt  = AV_PIX_FMT_YUV420P;
    if (encoder->pix_fmts) {
        for (int i=0; encoder->pix_fmts[i] != AV_PIX_FMT_NONE; i++) {
            av_log(enc_ctx, AV_LOG_DEBUG, "format %d: %s\n", i, av_get_pix_fmt_name(encoder->pix_fmts[i]));
            if (encoder->pix_fmts[i] == inputformat) {
                enc_ctx->pix_fmt = (AVPixelFormat)inputformat;
                break;
            }
        }
    }
    av_log(enc_ctx, AV_LOG_INFO, "input format %s\n", av_get_pix_fmt_name((AVPixelFormat)inputformat));
    av_log(enc_ctx, AV_LOG_INFO, "selected format %s\n", av_get_pix_fmt_name(enc_ctx->pix_fmt));

    enc_ctx->bit_rate_tolerance = bitrate;
    enc_ctx->bit_rate = (int)bitrate;
    enc_ctx->gop_size = 32;

    /* video time_base can be set to whatever is handy and supported by encoder */
    //enc_ctx->time_base = (AVRational){1, framerate};   // only for network stream frame rate
    //enc_ctx->framerate = (AVRational){framerate,1};
    enc_ctx->time_base.num = 1;
    enc_ctx->time_base.den = framerate;
    enc_ctx->framerate.num = framerate;
    enc_ctx->framerate.den = 1;

    out_stream = avformat_new_stream(ofmt_ctx, encoder);
    out_stream->time_base = enc_ctx->time_base;
    out_stream->avg_frame_rate = enc_ctx->framerate;
    out_stream->r_frame_rate = out_stream->avg_frame_rate;

    av_dict_set_int(&opts, "gop_preset", 8, 0);
    if (isdmabufer)
        av_dict_set_int(&opts, "is_dma_buffer", 1, 0);
    else
        av_dict_set_int(&opts, "is_dma_buffer", 0, 0);
#ifdef BM_PCIE_MODE
    av_dict_set_int(&opts, "sophon_idx", sophon_idx, 0);
#endif
    /* Third parameter can be used to pass settings to encoder */
    ret = avcodec_open2(enc_ctx, encoder, &opts);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot open video encoder ");
        return ret;
    }
    av_dict_free(&opts);

    ret = avcodec_parameters_from_context(out_stream->codecpar, enc_ctx);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Failed to copy encoder parameters to output stream ");
        return ret;
    }
    if (!(ofmt_ctx->oformat->flags & AVFMT_NOFILE)) {
        ret = avio_open(&ofmt_ctx->pb, filename, AVIO_FLAG_WRITE);
        if (ret < 0) {
            av_log(NULL, AV_LOG_ERROR, "Could not open output file '%s'", filename);
            return ret;
        }
    }

    /* init muxer, write output file header */
    ret = avformat_write_header(ofmt_ctx, NULL);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Error occurred when opening output file\n");
        return ret;
    }
    //av_dump_format(ofmt_ctx, 0, filename, 1);   // only for debug

    picture = av_frame_alloc();
    picture->format = enc_ctx->pix_fmt;
    picture->width  = width;
    picture->height = height;

    if (enc_ctx->pix_fmt != input_pix_fmt) {
        input_picture = av_frame_alloc();
        input_picture->format = input_pix_fmt;
        input_picture->width  = width;
        input_picture->height = height;

        int buffsize = av_image_get_buffer_size(enc_ctx->pix_fmt, width, height, 1);
        uint8_t* picture_buf = (uint8_t *)av_malloc(buffsize);
        if (!picture_buf) {
            av_free(picture);
            av_free(input_picture);
            return -1;
        }

        av_image_fill_arrays(picture->data, picture->linesize,
                             picture_buf,
                             enc_ctx->pix_fmt, width, height, 1);

        img_convert_ctx = sws_getContext(width, height, input_pix_fmt,
                                         enc_ctx->width, enc_ctx->height, enc_ctx->pix_fmt,
                                         SWS_BICUBIC,
                                         NULL, NULL, NULL);
        if (!img_convert_ctx)
            return -1;
    }
    return 0;
}

//data is allign with 32
int VideoEnc_FFMPEG::writeFrame(const uint8_t* data, int step, int width, int height)
{
    int ret = 0 ;
    int got_output = 0;

    if( step % SIMD_SIZE != 0) {
        av_log(enc_ctx, AV_LOG_ERROR, "input step must align with SIMD_SIZE\n");
        return -1;
    }

    if ( enc_ctx->pix_fmt != input_pix_fmt ) {
        // let input_picture point to the raw data buffer of 'image'
        //input_picture->linesize[0] = step;

        av_image_fill_arrays(input_picture->data, input_picture->linesize,
                             (uint8_t*)data,
                             (AVPixelFormat)input_pix_fmt, width, height, 1);
        input_picture->linesize[0] = step;

        ret = sws_scale(img_convert_ctx,
                        input_picture->data, input_picture->linesize, 0, height,
                        picture->data, picture->linesize);
        if ( ret < 0 )
            return -1;
    } else {
        av_image_fill_arrays(picture->data, picture->linesize, (uint8_t *) data, enc_ctx->pix_fmt, width, height, 1);
        picture->linesize[0] = step;
    }

    picture->pts = frame_idx;
    frame_idx++;
    AVPacket enc_pkt;
    av_log(enc_ctx, AV_LOG_INFO, "Encoding frame\n");

    /* encode filtered frame */
    enc_pkt.data = NULL;
    enc_pkt.size = 0;
    av_init_packet(&enc_pkt);

    ret = avcodec_encode_video2(enc_ctx, &enc_pkt, picture, &got_output);
    if (ret < 0)
        return ret;
    if (got_output == 0) {
       av_log(enc_ctx, AV_LOG_ERROR, "can't get output from encoder\n");
       return -1;
    }

    /* prepare packet for muxing */
    av_log(enc_ctx, AV_LOG_DEBUG, "[%s,%d] enc_pkt.pts=%ld,enc_pkt.dts=%ld\n",
           __func__, __LINE__, enc_pkt.pts, enc_pkt.dts);

    av_packet_rescale_ts(&enc_pkt, enc_ctx->time_base,out_stream->time_base);

    av_log(enc_ctx, AV_LOG_DEBUG, "[%s,%d] real enc_pkt.pts=%ld,enc_pkt.dts=%ld\n",
           __func__, __LINE__, enc_pkt.pts, enc_pkt.dts);

    /* mux encoded frame */
    av_log(enc_ctx, AV_LOG_DEBUG, "Muxing frame\n");
    ret = av_interleaved_write_frame(ofmt_ctx, &enc_pkt);
    return ret;

}

int VideoEnc_FFMPEG::writeAvFrame(AVFrame * inputPicture)
{
    int ret = 0 ;
    int got_output = 0;
    inputPicture->pts = frame_idx;
    frame_idx++;
    AVPacket enc_pkt;

    av_log(enc_ctx, AV_LOG_DEBUG, "Encoding frame\n");

    /* encode filtered frame */
    enc_pkt.data = NULL;
    enc_pkt.size = 0;
    av_init_packet(&enc_pkt);
    //inputPicture->pict_type = AV_PICTURE_TYPE_NONE;
    ret = avcodec_encode_video2(enc_ctx, &enc_pkt, inputPicture, &got_output);
    if (ret < 0)
        return ret;
    if (got_output == 0)
    {
       av_log(enc_ctx, AV_LOG_WARNING, "No output from encoder\n");
       return -1;
    }
    /* prepare packet for muxing */
    av_log(enc_ctx, AV_LOG_DEBUG, "[%s,%d] enc_pkt.pts=%ld,enc_pkt.dts=%ld\n",
           __func__, __LINE__, enc_pkt.pts,enc_pkt.dts);

    av_packet_rescale_ts(&enc_pkt, enc_ctx->time_base,out_stream->time_base);

    av_log(enc_ctx, AV_LOG_DEBUG, "[%s,%d] real enc_pkt.pts=%ld,enc_pkt.dts=%ld\n",
           __func__, __LINE__, enc_pkt.pts,enc_pkt.dts);

    /* mux encoded frame */
    av_log(enc_ctx, AV_LOG_DEBUG, "Muxing frame\n");
    ret = av_interleaved_write_frame(ofmt_ctx, &enc_pkt);
    return ret;
}

int  VideoEnc_FFMPEG::flush_encoder()
{
    int ret = 0;
    int got_frame = 0;

    if (!(enc_ctx->codec->capabilities & AV_CODEC_CAP_DELAY))
        return 0;

    while (1) {
        AVPacket enc_pkt;
        enc_pkt.data = NULL;
        enc_pkt.size = 0;
        av_init_packet(&enc_pkt);

        av_log(enc_ctx, AV_LOG_INFO, "Flushing video encoder\n");
        ret = avcodec_encode_video2(enc_ctx, &enc_pkt, NULL, &got_frame);
        if (ret < 0)
            return ret;

        if (!got_frame)
            break;

        /* prepare packet for muxing */
        av_log(enc_ctx, AV_LOG_DEBUG, "[%s,%d] enc_pkt.pts=%ld,enc_pkt.dts=%ld\n",
              __func__, __LINE__, enc_pkt.pts, enc_pkt.dts);

        av_packet_rescale_ts(&enc_pkt, enc_ctx->time_base,out_stream->time_base);

        av_log(enc_ctx, AV_LOG_DEBUG, "[%s,%d] real enc_pkt.pts=%ld,enc_pkt.dts=%ld\n",
               __func__, __LINE__, enc_pkt.pts, enc_pkt.dts);

        /* mux encoded frame */
        av_log(enc_ctx, AV_LOG_DEBUG, "Muxing frame\n");
        ret = av_interleaved_write_frame(ofmt_ctx, &enc_pkt);
        if (ret < 0)
            break;
    }

    return ret;
}

void VideoEnc_FFMPEG::closeEnc()
{
    flush_encoder();
    av_write_trailer(ofmt_ctx);

    if (img_convert_ctx ) {
        sws_freeContext(img_convert_ctx);
        img_convert_ctx = 0;
    }

    if( enc_ctx->pix_fmt != input_pix_fmt) {
        if(picture->data[0])
            free(picture->data[0]);
        picture->data[0] = 0;
    }

    av_free(picture);

    if (input_picture)
        av_free(input_picture);

    avcodec_free_context(&enc_ctx);

    if (ofmt_ctx && !(ofmt_ctx->oformat->flags & AVFMT_NOFILE))
        avio_closep(&ofmt_ctx->pb);
    avformat_free_context(ofmt_ctx);
}

