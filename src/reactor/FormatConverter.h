#ifndef _REACTOR_FORMAT_CONVERTER_H_
#define _REACTOR_FORMAT_CONVERTER_H_

#include <iostream>
#include <string>

#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif
extern "C"
{
  #include <libavformat/avformat.h>
  #include <libswscale/swscale.h>
}

#include "MediaFrame.h"

#include <cv.h>
#include <highgui.h>

using namespace std;

namespace reactor
{
  class FormatConverter
  {
  private:
	struct SwsContext* m_convertContext;

  public:
	bool init(enum PixelFormat sourceFormat, enum PixelFormat destinationFormat);
	bool convert(MediaFrame& source, MediaFrame& destination);

	bool iplImage2AVFrame(IplImage* image, AVFrame* frame);
	bool avFrame2IplImage(AVFrame* frame, IplImage* image);
  };
}

#endif