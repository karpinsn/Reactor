#ifndef _REACTOR_READER_FILTER_H_
#define _REACTOR_READER_FILTER_H_

#include "MediaFrame.h"
#include "MediaFrameReader.h"

namespace reactor
{
  class ReaderFilter : public MediaFrameReader
  {
  protected:
	MediaFrameReader* m_reader;

  public:
	ReaderFilter(MediaFrameReader* reader);
	virtual MediaFrame readFrame(void);
	virtual enum PixelFormat getPixelFormat(void);
  };
}

#endif // _REACTOR_READER_FILTER_H_