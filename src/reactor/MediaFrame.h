#ifndef _REACTOR_MEDIA_FRAME_H
#define _REACTOR_MEDIA_FRAME_H

//	FFmpeg Includes
#define __STDC_CONSTANT_MACROS
extern "C"
{
  #include <libavformat/avformat.h>
}

namespace reactor
{
  class MediaFrame
  {
  private:
	AVFrame*		  m_frame;
	enum PixelFormat  m_format;

  public:
	MediaFrame();
	MediaFrame(AVFrame* frame, enum PixelFormat format);

	bool isEmpty(void);
	AVFrame* getFrame(void);
	enum PixelFormat getPixelFormat(void);
	uint8_t** getBuffer(void);
	const int* getLineSize(void);
  };
}

#endif	// _REACTOR_MEDIA_FRAME_H