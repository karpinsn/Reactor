#ifndef _REACTOR_WRITER_FILTER_H_
#define _REACTOR_WRITER_FILTER_H_

#include "MediaFrame.h"
#include "MediaFrameWriter.h"

namespace reactor
{
  class WriterFilter : public MediaFrameWriter
  {
  protected:
	MediaFrameWriter* m_writer;

  public:
	WriterFilter(MediaFrameWriter* writer);
	virtual void writeFrame(MediaFrame& frame);
	virtual enum PixelFormat getPixelFormat(void);
  };
}

#endif	// _REACTOR_WRITER_FILTER_H_