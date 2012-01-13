#ifndef _MEDIA_STATE_H_
#define _MEDIA_STATE_H_

//	FFmpeg Includes
#define __STDC_CONSTANT_MACROS
extern "C"
{
  #include <libavcodec/avcodec.h>
  #include <libavformat/avformat.h>
  #include <libswscale/swscale.h>
}

typedef struct MediaState
{
  AVFormatContext *m_FormatContext;
  AVCodecContext  *m_CodecContext;
  AVCodec		  *m_Codec;
  AVFrame		  *m_CurrentFrame;

  int			  m_videoStreamIndex;
  int			  m_audioStreamIndex;
} VideoState;

#endif	// _MEDIA_STATE_H_