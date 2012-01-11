#ifndef _REACTOR_VIDEO_FRAME_H
#define _REACTOR_VIDEO_FRAME_H

//	FFmpeg Includes
#define __STDC_CONSTANT_MACROS
extern "C"
{
  #include <libavformat/avformat.h>
}

namespace reactor
{
  class VideoFrame
  {
  private:
	AVFrame*		  m_frame;
	enum PixelFormat  m_format;

  public:
	VideoFrame();
	VideoFrame(AVFrame* frame, enum PixelFormat format);

	bool isEmpty(void);
	AVFrame* getFrame(void);
	enum PixelFormat getPixelFormat(void);
	uint8_t** getBuffer(void);
	const int* getLineSize(void);
  };
}

#endif