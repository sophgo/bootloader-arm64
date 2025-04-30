#ifndef __FF_VIDEO_DECODE_H
#define __FF_VIDEO_DECODE_H
#define INBUF_SIZE 4096
#include <iostream>

extern "C"
{
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <time.h>
}
enum DATATYPE
{
    PACKETDATA = 1,
    FRAMEDATA = 2,
};

class VideoDec_FFMPEG
{
public:
    VideoDec_FFMPEG();
    ~VideoDec_FFMPEG();

    int openDec(const char *filename, int codec_name_flag,
                const char *coder_name, int output_format_mode = 100,
                int extra_frame_buffer_num = 5,
                int sophon_idx = 0, int pcie_no_copyback = 0, int api_version = 0);

    void closeDec();

    AVCodecParameters *getCodecPar();
    AVFrame *grabFrame();         // using readframe to get frame,and using the avcodec_decode_video2
    AVFrame *grabFrameByParser(); // using av_parser_parse2 to get frame
    AVFrame *grabFrame2();        // using new api send_pkt and receive_frame

private:
    AVFormatContext *ifmt_ctx;
    AVCodec *decoder;
    AVCodecContext *video_dec_ctx;
    AVCodecParameters *video_dec_par;
    uint8_t *data_ptr;
    uint8_t *buf_data;
    int width;
    int height;
    int pix_fmt;
    int data_size;
    AVCodecParserContext *parser;

    int video_stream_idx;
    AVFrame *frame;
    AVPacket pkt;
    AVPacket tempPacket;
    char file_name[256];

    FILE *file;
    FILE *RecordFile;
    int refcount;
    int loop_enable;
    int dump_enable;
    int fflush_flag;

    int WriteDataToFile(int datatype, const char *filename, void *data, int width, int hight);
    int readDataFromFile(const char *filename);
    AVCodec *findBmDecoder(AVCodecID dec_id, const char *name = "h264_bm",
                           int codec_name_flag = 0,
                           enum AVMediaType type = AVMEDIA_TYPE_VIDEO);
    int openCodecContext(int *stream_idx, AVCodecContext **dec_ctx,
                         AVFormatContext *fmt_ctx, enum AVMediaType type,
                         int codec_name_flag, const char *coder_name,
                         int output_format_mode = 100,
                         int extra_frame_buffer_num = 5,
                         int sophon_idx = 0, int pcie_no_copyback = 0);
    int InitForParser(AVCodecContext **dec_ctx, enum AVMediaType type,
                      int codec_name_flag,
                      const char *coder_name,
                      int output_format_mode = 100,
                      int extra_frame_buffer_num = 5,
                      int sophon_idx = 0,
                      int pcie_no_copyback = 0);
    AVFrame *flushDecoder(AVCodecContext *dec_ctx, int API_VERSION);
};

#endif /*__FF_VIDEO_DECODE_H*/
