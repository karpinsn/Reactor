#ifndef _REACTOR_MEDIA_FRAME_READER_H_
#define _REACTOR_MEDIA_FRAME_READER_H_

#include "MediaFrame.h"

//	FFmpeg includes
#define __STDC_CONSTANT_MACROS
extern "C"
{
  #include <libavformat/avformat.h>
}

namespace reactor
{
  class MediaFrameReader
  {
  public:
	virtual MediaFrame		  readFrame(void)		= 0;
	virtual enum PixelFormat  getPixelFormat(void)	= 0;
	virtual const int		  getWidth(void)		= 0;
	virtual const int		  getHeight(void)		= 0;
  };
}

#endif // _REACTOR_MEDIA_FRAME_READER_H_