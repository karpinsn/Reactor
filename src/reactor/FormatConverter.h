#ifndef _REACTOR_FORMAT_CONVERTER_H_
#define _REACTOR_FORMAT_CONVERTER_H_

#define __STDC_CONSTANT_MACROS
extern "C"
{
  #include <libavformat/avformat.h>
  #include <libswscale/swscale.h>
}

#include "VideoFrame.h"

namespace reactor
{
  class FormatCovnerter
  {
  private:
	struct SwsContext* m_convertContext;

  public:
	bool init(enum PixelFormat sourceFormat, enum PixelFormat destinationFormat);
	bool convert(VideoFrame& source, VideoFrame& destination);
  };
}

#endif