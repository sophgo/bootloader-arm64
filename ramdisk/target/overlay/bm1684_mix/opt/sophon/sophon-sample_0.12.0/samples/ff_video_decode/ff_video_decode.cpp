#include "ff_video_decode.h"
#include <iostream>

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

VideoDec_FFMPEG::VideoDec_FFMPEG()
{
    ifmt_ctx = NULL;
    video_dec_ctx = NULL;
    video_dec_par = NULL;
    decoder = NULL;
    width = 0;
    height = 0;
    pix_fmt = 0;
    data_size = 0;
    video_stream_idx = -1;
    refcount = 1;

    loop_enable = 0;
    dump_enable = 0;

    buf_data = (uint8_t *)malloc(sizeof(uint8_t) * (INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE));
    memset(buf_data + INBUF_SIZE, 0, AV_INPUT_BUFFER_PADDING_SIZE);
    data_ptr = buf_data;

    av_init_packet(&pkt);
    av_init_packet(&tempPacket);
    pkt.data = NULL;
    pkt.size = 0;
    file = NULL;
    RecordFile = NULL;
    tempPacket.data = NULL;
    tempPacket.size = 0;
    frame = av_frame_alloc();
    fflush_flag = 0;
    parser = NULL;
}
VideoDec_FFMPEG::~VideoDec_FFMPEG()
{
    av_packet_unref(&pkt);
    closeDec();

    printf("#VideoDec_FFMPEG exit \n");
}

AVCodecParameters *VideoDec_FFMPEG::getCodecPar()
{
    return video_dec_par;
}

int VideoDec_FFMPEG::openDec(const char *filename, int codec_name_flag,
                             const char *coder_name, int output_format_mode,
                             int extra_frame_buffer_num, int sophon_idx, int pcie_no_copyback,
                             int api_version)
{
    int ret = 0;
    AVDictionary *dict = NULL;

    av_dict_set(&dict, "rtsp_flags", "prefer_tcp", 0);
    av_dict_set(&dict, "stimeout", "5*1000*1000", 0); //Returns (Connection timed out) every  5 seconds ,when disconnect
    ret = avformat_open_input(&ifmt_ctx, filename, NULL, &dict);

    if (ret < 0)
    {
        av_log(NULL, AV_LOG_ERROR, "Cannot open input file\n");
        return ret;
    }

    ret = avformat_find_stream_info(ifmt_ctx, NULL);
    if (ret < 0)
    {
        av_log(NULL, AV_LOG_ERROR, "Cannot find stream information\n");
        return ret;
    }

    if (api_version < 2)
        ret = openCodecContext(&video_stream_idx, &video_dec_ctx, ifmt_ctx, AVMEDIA_TYPE_VIDEO,
                               codec_name_flag, coder_name, output_format_mode, extra_frame_buffer_num,
                               sophon_idx, pcie_no_copyback);
    else
        ret = InitForParser(&video_dec_ctx, AVMEDIA_TYPE_VIDEO,
                            codec_name_flag, coder_name,
                            output_format_mode, extra_frame_buffer_num,
                            sophon_idx, pcie_no_copyback);
    if (ret >= 0)
    {
        width = video_dec_ctx->width;
        height = video_dec_ctx->height;
        pix_fmt = video_dec_ctx->pix_fmt;
    }
    av_log(video_dec_ctx, AV_LOG_INFO,
           "openDec video_stream_idx = %d, pix_fmt = %d\n",
           video_stream_idx, pix_fmt);
    av_dict_free(&dict);
    if (strlen(filename) < sizeof(file_name))
        strncpy(file_name, filename, strlen(filename) + 1);
    else
    {
        av_log(video_dec_ctx, AV_LOG_INFO,
               "the filename is too long");
    }
    return ret;
}

void VideoDec_FFMPEG::closeDec()
{

    if (frame)
    {
        av_frame_free(&frame);
        frame = NULL;
    }
    if (buf_data != NULL)
    {
        free(buf_data);
        buf_data = NULL;
    }
    if (file != NULL)
    {
        //fseek(file, 0, SEEK_SET);
        fclose(file);
        file = NULL;
    }
    if (RecordFile != NULL)
    {
        fclose(RecordFile);
        RecordFile = NULL;
    }

    if(parser)
    {
        av_parser_close(parser);
        parser = NULL;
    }

    if (video_dec_ctx)
    {
        avcodec_free_context(&video_dec_ctx);
        video_dec_ctx = NULL;
    }
    if (ifmt_ctx)
    {
        avformat_close_input(&ifmt_ctx);
        ifmt_ctx = NULL;
    }
}
AVCodec *VideoDec_FFMPEG::findBmDecoder(AVCodecID dec_id, const char *name, int codec_name_flag, enum AVMediaType type)
{
    /* find video decoder for the stream */
    AVCodec *codec = NULL;
    if (codec_name_flag && type == AVMEDIA_TYPE_VIDEO)
    {
        const AVCodecDescriptor *desc;
        const char *codec_string = "decoder";

        codec = avcodec_find_decoder_by_name(name);
        if (!codec && (desc = avcodec_descriptor_get_by_name(name)))
        {
            codec = avcodec_find_decoder(desc->id);
        }

        if (!codec)
        {
            av_log(NULL, AV_LOG_FATAL, "Unknown %s '%s'\n", codec_string, name);
            exit(1);
        }
        if (codec->type != type)
        {
            av_log(NULL, AV_LOG_FATAL, "Invalid %s type '%s'\n", codec_string, name);
            exit(1);
        }
    }
    else
    {
        codec = avcodec_find_decoder(dec_id);
    }

    if (!codec)
    {
        fprintf(stderr, "Failed to find %s codec\n", av_get_media_type_string(type));
        exit(1);
    }
    return codec;
}

int VideoDec_FFMPEG::openCodecContext(int *stream_idx, AVCodecContext **dec_ctx, AVFormatContext *fmt_ctx,
                                      enum AVMediaType type, int codec_name_flag, const char *coder_name,
                                      int output_format_mode, int extra_frame_buffer_num, int sophon_idx, int pcie_no_copyback)
{
    int ret, stream_index;
    AVStream *st;
    AVCodec *dec = NULL;
    AVDictionary *opts = NULL;
    ret = av_find_best_stream(fmt_ctx, type, -1, -1, NULL, 0);
    if (ret < 0)
    {
        av_log(NULL, AV_LOG_ERROR, "Could not find %s stream \n", av_get_media_type_string(type));
        return ret;
    }

    stream_index = ret;
    st = fmt_ctx->streams[stream_index];

    /* find decoder for the stream */
    if (codec_name_flag && coder_name)
        decoder = findBmDecoder((AVCodecID)0, coder_name, codec_name_flag, AVMEDIA_TYPE_VIDEO);
    else
        decoder = findBmDecoder(st->codecpar->codec_id);
    if (!decoder)
    {
        av_log(NULL, AV_LOG_FATAL, "Failed to find %s codec\n",
               av_get_media_type_string(type));
        return AVERROR(EINVAL);
    }

    /* Allocate a codec context for the decoder */
    *dec_ctx = avcodec_alloc_context3(decoder);
    if (!*dec_ctx)
    {
        av_log(NULL, AV_LOG_FATAL, "Failed to allocate the %s codec context\n",
               av_get_media_type_string(type));
        return AVERROR(ENOMEM);
    }

    /* Copy codec parameters from input stream to output codec context */
    ret = avcodec_parameters_to_context(*dec_ctx, st->codecpar);
    if (ret < 0)
    {
        av_log(NULL, AV_LOG_FATAL, "Failed to copy %s codec parameters to decoder context\n",
               av_get_media_type_string(type));
        return ret;
    }
    video_dec_par = st->codecpar;
    /* Init the decoders, with or without reference counting */
    av_dict_set(&opts, "refcounted_frames", refcount ? "1" : "0", 0);

    av_dict_set_int(&opts, "zero_copy", pcie_no_copyback, 0);
    av_dict_set_int(&opts, "sophon_idx", sophon_idx, 0);

    if (output_format_mode == 101)
        av_dict_set_int(&opts, "output_format", output_format_mode, 18);

    // if(extra_frame_buffer_num > 5)
    av_dict_set_int(&opts, "extra_frame_buffer_num", extra_frame_buffer_num, 0); // if we use dma_buffer mode
    // av_dict_set_int(&opts, "extra_frame_buffer_num", 1, 0);  // if we use dma_buffer mode

    ret = avcodec_open2(*dec_ctx, dec, &opts);
    if (ret < 0)
    {
        av_log(NULL, AV_LOG_FATAL, "Failed to open %s codec\n",
               av_get_media_type_string(type));
        return ret;
    }
    *stream_idx = stream_index;

    av_dict_free(&opts);

    return 0;
}

AVFrame *VideoDec_FFMPEG::grabFrame()
{
    int ret = 0;
    int got_frame = 0;
#ifdef WIN32
    clock_t tv1, tv2;
    tv1 = clock();
#else
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
#endif
    if (fflush_flag == 0)
    {
        while (1)
        {
            av_packet_unref(&pkt);
            ret = av_read_frame(ifmt_ctx, &pkt);
            if (ret < 0)
            {
                if (ret == AVERROR(EAGAIN))
                {
#ifdef WIN32
                    tv2 = clock();
                    if ((tv2 - tv1) > 1000 * 60)
#else
                    gettimeofday(&tv2, NULL);
                    if (((tv2.tv_sec - tv1.tv_sec) * 1000 + (tv2.tv_usec - tv1.tv_usec) / 1000) > 1000 * 60)
#endif
                    {
                        av_log(video_dec_ctx, AV_LOG_WARNING, "av_read_frame failed ret(%d) retry time >60s.\n", ret);
                        break;
                    }
#ifdef WIN32
                    Sleep(10);
#else
                    usleep(10 * 1000);
#endif
                    continue;
                }
                if (ret == AVERROR_EOF)
                {
                    fflush_flag = 1;
                    av_log(video_dec_ctx, AV_LOG_ERROR, "av_read_frame ret(%d) maybe eof...\n", ret);
                    break;
                }
            }

            if (pkt.stream_index != video_stream_idx)
            {
                continue;
            }

            if (!frame)
            {
                av_log(video_dec_ctx, AV_LOG_ERROR, "Could not allocate frame\n");
                return NULL;
            }

            if (refcount)
                av_frame_unref(frame);

#ifdef WIN32
            tv1 = clock();
#else
            gettimeofday(&tv1, NULL);
#endif
            ret = avcodec_decode_video2(video_dec_ctx, frame, &got_frame, &pkt);
            if (ret < 0)
            {
                av_log(video_dec_ctx, AV_LOG_ERROR, "Error decoding video frame (%d)\n", ret);
                if(ret == AVERROR_EXTERNAL)
                    return NULL;
                continue; // TODO
            }

            if (!got_frame)
            {
                continue;
            }

            width = video_dec_ctx->width;
            height = video_dec_ctx->height;
            pix_fmt = video_dec_ctx->pix_fmt;
            if (frame->width != width || frame->height != height || frame->format != pix_fmt)
            {
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
        if (dump_enable)
            WriteDataToFile(FRAMEDATA, "grabframe.yuv", frame, frame->width, frame->height);
        return frame;
    }
    if (fflush_flag)
    {
        return flushDecoder(video_dec_ctx, 0); // Clean up residual frames in the decoder
    }
}

AVFrame *VideoDec_FFMPEG::grabFrame2()
{
    int ret = 0;
#ifdef WIN32
    clock_t tv1, tv2;
    tv1 = clock();
#else
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
#endif
    if (fflush_flag == 0)
        while (1)
        {
            av_packet_unref(&pkt);
            ret = av_read_frame(ifmt_ctx, &pkt);
            if (ret < 0)
            {
                if (ret == AVERROR(EAGAIN))
                {
#ifdef WIN32
                    tv2 = clock();
                    if ((tv2 - tv1) > 1000 * 60)
#else
                    gettimeofday(&tv2, NULL);
                    if (((tv2.tv_sec - tv1.tv_sec) * 1000 + (tv2.tv_usec - tv1.tv_usec) / 1000) > 1000 * 60)
#endif

                    {
                        av_log(video_dec_ctx, AV_LOG_WARNING, "av_read_frame failed ret(%d) retry time >60s.\n", ret);
                        break;
                    }
#ifdef WIN32
                    Sleep(10);
#else
                    usleep(10 * 1000);
#endif
                    continue;
                }
                if (ret == AVERROR_EOF)
                {
                    fflush_flag = 1;
                    av_log(video_dec_ctx, AV_LOG_ERROR, "av_read_frame ret(%d) maybe eof...\n", ret);
                    break;
                }
            }

            if (pkt.stream_index != video_stream_idx)
            {
                continue;
            }

            if (!frame)
            {
                av_log(video_dec_ctx, AV_LOG_ERROR, "Could not allocate frame\n");
                break;
            }

            if (refcount)
                av_frame_unref(frame);

#ifdef WIN32
            tv1 = clock();
#else
            gettimeofday(&tv1, NULL);
#endif
            ret = avcodec_send_packet(video_dec_ctx, &pkt);
            if (ret < 0)
            {
                fprintf(stderr, "Error sending a packet for decoding\n");
                return NULL;
            }
            while (ret >= 0)
            {
                ret = avcodec_receive_frame(video_dec_ctx, frame);
                if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                    break;
                else if (ret < 0)
                {
                    fprintf(stderr, "Error during decoding\n");
                }

                if (dump_enable)
                    WriteDataToFile(FRAMEDATA, "grabframe.yuv", frame, frame->width, frame->height);

                return frame;
            }
        }
    if (fflush_flag)
    {
        return flushDecoder(video_dec_ctx, 1); // Clean up residual frames in the decoder
    }
}

int VideoDec_FFMPEG::WriteDataToFile(int datatype, const char *filename, void *data, int width, int height)
{
    AVFrame *write_frame = NULL;
    write_frame = (AVFrame *)data;
    int y_size = 0;
    if (RecordFile == NULL)
    {
        RecordFile = fopen(filename, "wb");
        if (RecordFile == NULL)
        {
            av_log(NULL, AV_LOG_ERROR, "Could not open the file  \n");
            exit(0);
        }
    }
    if (datatype == FRAMEDATA) // frame_data
    {
        int scale;
        if (write_frame->data[2] == NULL)
            scale = 2;
        else
            scale = 4;
        y_size = height * width;
        fwrite(write_frame->data[0], 1, y_size, RecordFile);             // Y
        fwrite(write_frame->data[1], 1, y_size / scale, RecordFile);     // U
        if (write_frame->data[2] != NULL)                                // When the video format is nv12, there are only two channels,
            fwrite(write_frame->data[2], 1, y_size / scale, RecordFile); // and there are 3 channels when I420
                                                                         // V
    }
    else if (datatype == PACKETDATA)
    {
        AVPacket *packte = (AVPacket *)data;
        fwrite(packte->data, 1, packte->size, RecordFile);
    }
    return 0;
}
AVFrame *VideoDec_FFMPEG::flushDecoder(AVCodecContext *dec_ctx, int API_VERSION)
{
    static int ret;
    av_frame_unref(frame);

    ret = avcodec_send_packet(dec_ctx, NULL);
    ret = avcodec_receive_frame(dec_ctx, frame);
    if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF || ret < 0)
    {
        fflush_flag = 0;
        ret = 1;
        dump_enable = 0; // stop dumpping after first round
        return NULL;
    }
    if (dump_enable)
    {
        if (API_VERSION == 2)
            WriteDataToFile(FRAMEDATA, "parse2.yuv", frame, frame->width, frame->height);
        else if (API_VERSION == 1)
        {
            WriteDataToFile(FRAMEDATA, "grabframe2.yuv", frame, frame->width, frame->height);
        }
        else if (API_VERSION == 0)
        {
            WriteDataToFile(FRAMEDATA, "grabframe.yuv", frame, frame->width, frame->height);
        }
    }
    fprintf(stderr, "flushing frames\n");
    return frame;
}

int VideoDec_FFMPEG::readDataFromFile(const char *filename)
{
    int size;
    if (file == NULL)
    {
        file = fopen(filename, "rb");
        if (file == NULL)
        {
            av_log(NULL, AV_LOG_ERROR, "Open input file faild\n");
            exit(1);
        }
    }
    if (feof(file))
    {
        if (!loop_enable) // yes or no to flush the decoder
        {
            size = 0;
            return size;
        }
        else
            fseek(file, 0, SEEK_SET);
    }
    size = fread(buf_data, sizeof(uint8_t), INBUF_SIZE, file);
    data_ptr = buf_data;
    return size;
}
int VideoDec_FFMPEG::InitForParser(AVCodecContext **dec_ctx, enum AVMediaType type,
                                   int codec_name_flag, const char *coder_name, int output_format_mode,
                                   int extra_frame_buffer_num, int sophon_idx, int pcie_no_copyback)
{
    AVDictionary *opts = NULL;
    video_stream_idx = 0;

    if (codec_name_flag && coder_name)
        decoder = findBmDecoder((AVCodecID)0, coder_name, codec_name_flag, type);
    else
    {
        av_log(NULL, AV_LOG_ERROR, "Please enter an decoder name!\n");
        exit(1);
    }
    if (!decoder)
    {
        av_log(NULL, AV_LOG_ERROR, "Failed to find %s codec\n",
               av_get_media_type_string(AVMEDIA_TYPE_VIDEO));
        return AVERROR(EINVAL);
    }

    parser = av_parser_init(decoder->id);
    if (!parser)
    {
        av_log(NULL, AV_LOG_ERROR, "parser not found \n");
        return -1;
    }

    *dec_ctx = avcodec_alloc_context3(decoder);
    if (!*dec_ctx)
    {
        av_log(NULL, AV_LOG_ERROR, " Could not allocate video codec context\n");
        return -1;
    }

    av_dict_set(&opts, "refcounted_frames", refcount ? "1" : "0", 0);

    av_dict_set_int(&opts, "zero_copy", pcie_no_copyback, 0);
    av_dict_set_int(&opts, "sophon_idx", sophon_idx, 0);
    if (output_format_mode == 101)
        av_dict_set_int(&opts, "output_format", output_format_mode, 18);

    av_dict_set_int(&opts, "extra_frame_buffer_num", extra_frame_buffer_num, 0);

    if (avcodec_open2(*dec_ctx, decoder, &opts) < 0)
    {
        av_log(NULL, AV_LOG_ERROR, " Could not allocate video codec context\n");
        exit(1);
    }

    av_dict_free(&opts);
    av_log(NULL, AV_LOG_INFO, "parser initialized successfully\n");
    return 0;
}

AVFrame *VideoDec_FFMPEG::grabFrameByParser()
{
    int ret = 0;
    int len;

#ifdef WIN32
    clock_t tv1, tv2;
    tv1 = clock();
#else
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
#endif
    while (!fflush_flag)
    {
        if (data_size <= 0)
        {
            data_size = readDataFromFile(file_name);
            if (data_size == 0){
                fflush_flag = 1; // in the last,there have data in the tempPacket
            }
        }
        av_packet_unref(&tempPacket);
        len = av_parser_parse2(parser, video_dec_ctx,
                               &tempPacket.data, &tempPacket.size, data_ptr, data_size,
                               AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);
        data_size -= len;
        data_ptr += len;
        if (tempPacket.size == 0)
            continue;
        if (parser->key_frame == 1 ||
            (parser->key_frame == -1 &&
             parser->pict_type == AV_PICTURE_TYPE_I))
        {
            tempPacket.flags |= AV_PKT_FLAG_KEY;
        }
        if (tempPacket.stream_index != video_stream_idx)
        {
            continue;
        }

        if (!frame)
        {
            av_log(video_dec_ctx, AV_LOG_ERROR, "Could not allocate frame\n");
            return NULL;
        }

        if (refcount)
            av_frame_unref(frame);

#ifdef WIN32
        tv1 = clock();
#else
        gettimeofday(&tv1, NULL);
#endif
        ret = avcodec_send_packet(video_dec_ctx, &tempPacket);
        if (ret < 0)
        {
            fprintf(stderr, "Error sending a packet for decoding\n");
            return NULL;
        }
        while (ret >= 0)
        {
            ret = avcodec_receive_frame(video_dec_ctx, frame);
            if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                break;
            else if (ret < 0)
            {
                fprintf(stderr, "Error during decoding\n");
            }

            if (dump_enable)
                WriteDataToFile(FRAMEDATA, "parse2.yuv", frame, frame->width, frame->height);
            return frame;
        }
    }
    if (fflush_flag)
    {
        return flushDecoder(video_dec_ctx, 2); // Clean up residual frames in the decoder
    }
    return NULL;
}
