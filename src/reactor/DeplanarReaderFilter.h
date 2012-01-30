#ifndef _REACTOR_DEPLANAR_READER_FILTER_H_
#define _REACTOR_DEPLANAR_READER_FILTER_H_

#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif
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
  class DeplanarReaderFilter : public ReaderFilter
  {
  private:
	AVFrame*		  m_convertedFrame;
	uint8_t*		  m_convertedBuffer;
	
	bool			  m_initialized;

  public:
	DeplanarReaderFilter(MediaFrameReader* reader);
	~DeplanarReaderFilter();
    
	MediaFrame readFrame(void);
  };
}

extern "C" void deplanarMemcpy(uint8_t* dest, uint8_t** src, int width, int height);

#endif // _REACTOR_DEPLANAR_READER_FILTER_H_