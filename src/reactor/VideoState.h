#ifndef _VIDEO_STATE_H_
#define _VIDEO_STATE_H_

//	FFmpeg Includes
#define __STDC_CONSTANT_MACROS
extern "C"
{
  #include <libavcodec/avcodec.h>
  #include <libavformat/avformat.h>
  #include <libswscale/swscale.h>
}

typedef struct VideoState
{
  AVFormatContext *pFormatContext;
  AVCodecContext  *pCodecContext;
  AVCodec		  *pCodec;
  AVFrame		  *pVideoFrame;
  int			  videoStream;
} VideoState;

#endif