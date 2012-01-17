#ifndef _REACTOR_COLOR_SPACE_WRITER_FILTER_H_
#define _REACTOR_COLOR_SPACE_WRITER_FILTER_H_

#define __STDC_CONSTANT_MACROS
extern "C"
{
  #include <libavformat/avformat.h>
  #include <libswscale/swscale.h>
}

#include "MediaFrame.h"
#include "MediaFrameWriter.h"
#include "WriterFilter.h"

namespace reactor
{
  class ColorSpaceWriterFilter : public WriterFilter
  {
  private:
	enum PixelFormat  m_format;
	AVFrame*		  m_convertedFrame;
	uint8_t*		  m_convertedBuffer;
	SwsContext*       m_conversionContext;

	bool			  m_initialized;

  public:
	ColorSpaceWriterFilter(MediaFrameWriter* writer, enum PixelFormat sourceFormat);
	~ColorSpaceWriterFilter();
	void writeFrame(MediaFrame& frame);
	enum PixelFormat getPixelFormat(void);
  };
}

#endif	// _REACTOR_COLOR_SPACE_WRITER_FILTER_H_