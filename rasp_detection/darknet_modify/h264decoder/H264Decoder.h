//
// Created by curi on 17-6-28.
//

#ifndef OPENCVIDEO_MASTER_H264DECODER_H
#define OPENCVIDEO_MASTER_H264DECODER_H

//#define __STDC_CONSTANT_MACROS
#include <stdio.h>
#include <unistd.h>
// Opencv
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect.hpp>

extern "C" {
//#include "libavutil/avutil.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
};

#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(55,28,1)
#define av_frame_alloc  avcodec_alloc_frame
#endif


class H264Decoder {

public :

    H264Decoder();
    ~H264Decoder();
    void init();
    void decode(unsigned char *inputbuf, size_t insize);
    void play();
    cv::Mat getMat();
    void getIpl(IplImage ** ipl);

private:

    unsigned char *buf = nullptr;
    int size = 0;

    const AVCodec *codec;
    AVCodecContext *c = nullptr;
    AVCodecParserContext *cp = nullptr;
    AVFrame *frame;
    AVPacket avpkt;
    AVFrame *pFrameBGR;

    int BGRsize;
    uint8_t *out_buffer = nullptr;

    struct SwsContext *img_convert_ctx;
    cv::Mat pCvMat;
    IplImage pIpl;
    bool matReady;

};

#endif //OPENCVIDEO_MASTER_H264DECODER_H
