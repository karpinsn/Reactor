#ifndef _REACTOR_MEDIA_FRAME_H
#define _REACTOR_MEDIA_FRAME_H

//	FFmpeg Includes
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif
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

	bool              isEmpty(void);
	AVFrame*          getFrame(void);
	enum PixelFormat  getPixelFormat(void);
	uint8_t**         getBuffer(void);

	const int*        getLineSize(void) const;
	const int         getWidth(void)    const;
	const int         getHeight(void)   const;
  };
}

#endif	// _REACTOR_MEDIA_FRAME_H
