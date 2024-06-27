#include "ff_video_filter.h"
#include "bmlib_runtime.h"

int initFilter(ffmpegFilterContext *filter, int src_width, int src_height, int dst_width, int dst_height, int src_pix_fmt, int fps, int sophon_idx){
    char args[512]                = {};
    char str_out_desc[128]        = {};
    //AVBufferSinkParams *params    = NULL;
    const AVFilter *filterSrc     = NULL;
    const AVFilter *filterSink    = NULL;
    AVFilterInOut *filterInOutIn  = NULL;
    AVFilterInOut *filterInOutOut = NULL;
    enum AVPixelFormat pix_fmts[] = {AV_PIX_FMT_YUV420P, AV_PIX_FMT_NONE };

    snprintf(str_out_desc,sizeof(str_out_desc),"scale_bm=%d:%d:sophon_idx=%d",dst_width,dst_height,sophon_idx);

    // Create video filter graph
    filter->filterGraph = avfilter_graph_alloc();
    if (!filter->filterGraph) {
        printf("Cannot alloc filter graph\n");
        goto end;
    }

    filterSrc  = avfilter_get_by_name("buffer");
    filterSink = avfilter_get_by_name("buffersink");
    if (!filterSrc || !filterSink) {
        printf("Cannot get filter\n");
        goto end;
    }

    filterInOutIn  = avfilter_inout_alloc();
    filterInOutOut = avfilter_inout_alloc();
    if (!filterInOutIn || !filterInOutOut) {
        printf("Cannot alloc filter inout\n");
        goto end;
    }

    snprintf(args, sizeof(args), \
             "video_size=%dx%d:pix_fmt=%d:time_base=%d/%d:pixel_aspect=%d/%d", \
             src_width, src_height, src_pix_fmt, 1, fps, 1, 1);

    printf("filter src fmt=%s,args=%s\n",av_get_pix_fmt_name((AVPixelFormat)src_pix_fmt) ,args);

    filter->filterGraph->thread_type=0;
    if ((avfilter_graph_create_filter(&filter->filterContextSrc,  filterSrc,  "in",  args, NULL, filter->filterGraph) < 0)
      ||(avfilter_graph_create_filter(&filter->filterContextSink, filterSink, "out", NULL, NULL, filter->filterGraph) < 0)) {
        printf("Cannot create filter\n");
        //av_free(params);
        goto end;
    }

    av_opt_set_int_list(filter->filterContextSink, "pix_fmts", pix_fmts,AV_PIX_FMT_NONE, AV_OPT_SEARCH_CHILDREN);

    /* endpoints for the filter graph. */
    filterInOutOut->name       = av_strdup("in");
    filterInOutOut->filter_ctx = filter->filterContextSrc;
    filterInOutOut->pad_idx    = 0;
    filterInOutOut->next       = NULL;

    filterInOutIn->name        = av_strdup("out");
    filterInOutIn->filter_ctx  = filter->filterContextSink;
    filterInOutIn->pad_idx     = 0;
    filterInOutIn->next        = NULL;

    if (avfilter_graph_parse(filter->filterGraph, str_out_desc, filterInOutIn, filterInOutOut, NULL) < 0) {
        printf("Cannot parse filter graph\n");
        goto end;
    }

    if (avfilter_graph_config(filter->filterGraph, NULL) < 0) {
        printf("Cannot config filter graph\n");
        goto end;
    }
    return 0;

end:
    if (filter->filterGraph) {
        avfilter_graph_free(&filter->filterGraph);
    }
    return -1;
}

int getFilterFrame(ffmpegFilterContext filter, AVFrame *in, AVFrame *out){
    int ret = av_buffersrc_write_frame(filter.filterContextSrc, in);
    if(ret < 0)
        return -1;
    ret = av_buffersink_get_frame(filter.filterContextSink, out);
    if(ret < 0)
        return -1;
    return 0;
}

int deInitFilter(ffmpegFilterContext filter){
    avfilter_graph_free(&(filter.filterGraph));
    return 0;
}
