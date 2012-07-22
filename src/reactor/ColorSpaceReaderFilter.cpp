#include "ColorSpaceReaderFilter.h"

reactor::ColorSpaceReaderFilter::ColorSpaceReaderFilter(MediaFrameReader* reader, enum PixelFormat destinationFormat) : ReaderFilter(reader)
{
  m_format = destinationFormat;

  m_convertedFrame = avcodec_alloc_frame();
  int numberBytes = avpicture_get_size(m_format, reader->getWidth(), reader->getHeight());

  if(numberBytes > 0)
  {
	m_convertedFrame->width = reader->getWidth();
	m_convertedFrame->height = reader->getHeight();

	m_convertedBuffer = (uint8_t*)av_malloc(numberBytes * sizeof(uint8_t));
	if(m_convertedBuffer)
	{
	  avpicture_fill((AVPicture*)m_convertedFrame, m_convertedBuffer, m_format, reader->getWidth(), reader->getHeight());
	  m_conversionContext = sws_getContext(reader->getWidth(), reader->getHeight(), reader->getPixelFormat(),
										   reader->getWidth(), reader->getHeight(), destinationFormat,
										   SWS_BICUBIC, nullptr, nullptr, nullptr);

	  m_initialized = true;
	}
  }
}

reactor::ColorSpaceReaderFilter::~ColorSpaceReaderFilter()
{
  //  Release the memory used by the frame
  if(m_initialized)
  {
	av_free(m_convertedBuffer);  
  }

  //  Release the frame
  free(m_convertedFrame);
}

reactor::MediaFrame reactor::ColorSpaceReaderFilter::readFrame(void)
{
  if(!m_initialized)
  {
	return ReaderFilter::readFrame();
  }

  MediaFrame frame = ReaderFilter::readFrame();

  sws_scale(m_conversionContext, frame.getBuffer(), frame.getLineSize(), 0, frame.getHeight(),
			m_convertedFrame->data, m_convertedFrame->linesize);

  return MediaFrame(m_convertedFrame, m_format);
}

enum PixelFormat reactor::ColorSpaceReaderFilter::getPixelFormat(void)
{
  return m_format;
}