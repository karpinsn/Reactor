#include "DeplanarReaderFilter.h"

reactor::DeplanarReaderFilter::DeplanarReaderFilter(MediaFrameReader* reader) : ReaderFilter(reader)
{
  m_convertedFrame = avcodec_alloc_frame();
  int numberBytes = avpicture_get_size(reader->getPixelFormat(), reader->getWidth(), reader->getHeight());

  if(numberBytes > 0)
  {
	m_convertedFrame->width = reader->getWidth();
	m_convertedFrame->height = reader->getHeight();

	m_convertedBuffer = (uint8_t*)av_malloc(numberBytes * sizeof(uint8_t));
	if(m_convertedBuffer)
	{
	  avpicture_fill((AVPicture*)m_convertedFrame, m_convertedBuffer, reader->getPixelFormat(), reader->getWidth(), reader->getHeight());

	  m_initialized = true;
	}
  }
}

reactor::DeplanarReaderFilter::~DeplanarReaderFilter()
{
  //  Release the memory used by the frame
  if(m_initialized)
  {
	av_free(m_convertedBuffer);  
  }

  //  Release the frame
  free(m_convertedFrame);
}

reactor::MediaFrame reactor::DeplanarReaderFilter::readFrame(void)
{
  if(!m_initialized)
  {
	return ReaderFilter::readFrame();
  }

  MediaFrame frame = ReaderFilter::readFrame();
  AVFrame* srcFrame = frame.getFrame();

  deplanarMemcpy(m_convertedFrame->data[0], srcFrame->data, frame.getWidth(), frame.getHeight());

  return MediaFrame(m_convertedFrame, frame.getPixelFormat());
}

extern "C" void deplanarMemcpy(uint8_t* dest, uint8_t** src, int width, int height)
{
  //  Make a copy so we dont change the actual value
  uint8_t* srcPtr[3];
  srcPtr[0] = src[0];
  srcPtr[1] = src[1];
  srcPtr[2] = src[2];

  for(int y = 0; y < height; ++y)
  {
	for(int x = 0; x < width; ++x)
	{
	  *dest++ = *srcPtr[0]++;
	  *dest++ = *srcPtr[1]++;
	  *dest++ = *srcPtr[2]++;
	}
  }
}