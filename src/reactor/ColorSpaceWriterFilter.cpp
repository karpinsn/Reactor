#include "ColorSpaceWriterFilter.h"

reactor::ColorSpaceWriterFilter::ColorSpaceWriterFilter(MediaFrameWriter* writer, enum PixelFormat sourceFormat) : WriterFilter(writer)
{
  m_format = sourceFormat;

  m_convertedFrame = avcodec_alloc_frame();
  int numberBytes = avpicture_get_size(m_format, writer->getWidth(), writer->getHeight());
  
  if(numberBytes > 0)
  {
	m_convertedFrame->width	  = writer->getWidth();
	m_convertedFrame->height  = writer->getHeight();

	m_convertedBuffer = (uint8_t*)av_malloc(numberBytes * sizeof(uint8_t));
	if(m_convertedBuffer)
	{
	  avpicture_fill((AVPicture*)m_convertedFrame, m_convertedBuffer, m_format, writer->getWidth(), writer->getHeight());
	  m_conversionContext = sws_getContext(writer->getWidth(), writer->getHeight(), sourceFormat, 
										 writer->getWidth(), writer->getHeight(), writer->getPixelFormat(), 
										 SWS_BICUBIC, nullptr, nullptr, nullptr);
	  m_initialized = true;
	}
  }
}

reactor::ColorSpaceWriterFilter::~ColorSpaceWriterFilter()
{
  //  Release the memory used by the frame
  if(m_initialized)
  {
	av_free(m_convertedBuffer);  
  }

  //  Release the frame
  free(m_convertedFrame);
}

void reactor::ColorSpaceWriterFilter::writeFrame(MediaFrame& frame)
{
  if(m_initialized)
  {
	// Perform the conversion
	sws_scale(m_conversionContext, 
			  frame.getBuffer(), frame.getLineSize(), 0, frame.getHeight(), 
			  m_convertedFrame->data, m_convertedFrame->linesize);

      MediaFrame frame(m_convertedFrame, m_format);
      
	WriterFilter::writeFrame(frame);
  }
}

enum PixelFormat reactor::ColorSpaceWriterFilter::getPixelFormat(void)
{
  return m_format;
}