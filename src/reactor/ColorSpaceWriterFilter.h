#ifndef _REACTOR_COLOR_SPACE_WRITER_FILTER_H_
#define _REACTOR_COLOR_SPACE_WRITER_FILTER_H_

#include "MediaFrame.h"
#include "MediaFrameWriter.h"
#include "WriterFilter.h"

namespace reactor
{
  class ColorSpaceWriterFilter : public WriterFilter
  {
  private:
	enum PixelFormat m_format;

  public:
	ColorSpaceWriterFilter(MediaFrameWriter* writer, enum PixelFormat destinationFormat);
	void writeFrame(MediaFrame& frame);
	enum PixelFormat getPixelFormat(void);
  };
}

#endif	// _REACTOR_COLOR_SPACE_WRITER_FILTER_H_