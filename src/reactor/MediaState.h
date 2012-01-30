#ifndef _MEDIA_STATE_H_
#define _MEDIA_STATE_H_

//	FFmpeg Includes
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif
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

  MediaState()
  {
	m_FormatContext		= NULL;
	m_CodecContext		= NULL;
	m_Codec				= NULL;
	m_CurrentFrame		= NULL;
	m_videoStreamIndex	= -1;
	m_audioStreamIndex	= -1;
  }
} VideoState;

#endif	// _MEDIA_STATE_H_