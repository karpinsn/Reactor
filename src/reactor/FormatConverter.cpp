#include "FormatConverter.h"

bool reactor::FormatConverter::init(enum PixelFormat sourceFormat, enum PixelFormat destinationFormat)
{
  //  Initalize the context
  m_convertContext = sws_getContext(512, 512, sourceFormat, 512, 512, destinationFormat, SWS_BICUBIC, NULL, NULL, NULL);

  //  Return whether or not the context was initialized correctly
  return NULL != m_convertContext;
}

bool reactor::FormatConverter::convert(VideoFrame& source, VideoFrame& destination)
{
  if(NULL == m_convertContext)
  {
	// No conversion context present
	cout << "FormatConverter not initalized. Cannot convert!"
	return false;
  }

  // Perform the conversion
  sws_scale(m_convertContext, 
			source.getBuffer(), source.getLineSize(), 0, height, 
			destination.getBuffer(), destination.getLineSize());

  
  return true;
}