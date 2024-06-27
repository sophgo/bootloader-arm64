#ifndef __AVFRAME_FILTER_H_
#define __AVFRAME_FILTER_H_

extern "C" {
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
#include "libavformat/avformat.h"
#include "libavfilter/buffersink.h"
#include "libavfilter/buffersrc.h"
#include "libavutil/opt.h"
#include "libavutil/pixdesc.h"
#include <stdio.h>
#include <unistd.h>
#include "bmcv_api.h"
#include "bmcv_api_ext.h"
}

//In SoC mode, heap distribution is the same as that of PCIe
/*
 * heap0   tpu
 * heap1   vpp
 * heap2   vpu
*/
#if 0
#define USEING_MEM_HEAP2 4
#define USEING_MEM_HEAP0 2

typedef struct{
        bm_image *bmImg;
        uint8_t* buf0;
        uint8_t* buf1;
        uint8_t* buf2;
}transcode_t;
#endif

typedef struct ffmpegFilterContext{
    AVFilterGraph *filterGraph{nullptr};
    AVFilterContext *filterContextSrc{nullptr};
    AVFilterContext *filterContextSink{nullptr};
}ffmpegFilterContext;

int initFilter(ffmpegFilterContext *filter, int f_src_width, int f_src_height, int f_dst_width, int f_dst_height, int src_pix_fmt, int fps, int sophon_idx);
int getFilterFrame(ffmpegFilterContext filter, AVFrame *in, AVFrame *out);
int deInitFilter(ffmpegFilterContext filter);

#endif
