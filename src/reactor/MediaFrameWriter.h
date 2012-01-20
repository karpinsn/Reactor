#ifndef _REACTOR_MEDIA_FRAME_WRITER_H_
#define _REACTOR_MEDIA_FRAME_WRITER_H_

#include "MediaFrame.h"

//	FFmpeg includes
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif
extern "C"
{
  #include <libavformat/avformat.h>
}

namespace reactor
{
  class MediaFrameWriter
  {
  public:
	virtual void			  writeFrame(MediaFrame& frame) = 0;
	virtual enum PixelFormat  getPixelFormat(void)			= 0;
	virtual const int		  getWidth(void)				= 0;
	virtual const int		  getHeight(void)				= 0;
  };
}

#endif // _REACTOR_MEDIA_FRAME_WRITER_H_