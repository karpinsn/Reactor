#ifndef _REACTOR_COLOR_SPACE_READER_FILTER_H_
#define _REACTOR_COLOR_SPACE_READER_FILTER_H_

#include "MediaFrameReader.h"
#include "MediaFrame.h"
#include "ReaderFilter.h"

namespace reactor
{
  class ColorSpaceReaderFilter : public ReaderFilter
  {
  private:
	enum PixelFormat m_format;

  public:
	ColorSpaceReaderFilter(MediaFrameReader* reader, enum PixelFormat destinationFormat);
	MediaFrame readFrame(void);
	enum PixelFormat getPixelFormat(void);
  };
}

#endif // _REACTOR_COLOR_SPACE_READER_FILTER_H_