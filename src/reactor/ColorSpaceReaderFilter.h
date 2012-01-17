#ifndef _REACTOR_COLOR_SPACE_READER_FILTER_H_
#define _REACTOR_COLOR_SPACE_READER_FILTER_H_

#define __STDC_CONSTANT_MACROS
extern "C"
{
  #include <libavformat/avformat.h>
  #include <libswscale/swscale.h>
}

#include "MediaFrameReader.h"
#include "MediaFrame.h"
#include "ReaderFilter.h"

namespace reactor
{
  class ColorSpaceReaderFilter : public ReaderFilter
  {
  private:
	enum PixelFormat  m_format;
	AVFrame*		  m_convertedFrame;
	uint8_t*		  m_convertedBuffer;
	SwsContext*       m_conversionContext;

	bool			  m_initialized;

  public:
	ColorSpaceReaderFilter(MediaFrameReader* reader, enum PixelFormat destinationFormat);
	~ColorSpaceReaderFilter();
	MediaFrame readFrame(void);
	enum PixelFormat getPixelFormat(void);
  };
}

#endif // _REACTOR_COLOR_SPACE_READER_FILTER_H_