#include "ColorSpaceWriterFilter.h"

reactor::ColorSpaceWriterFilter::ColorSpaceWriterFilter(MediaFrameWriter* writer, enum PixelFormat destinationFormat) : WriterFilter(writer)
{
  m_format = destinationFormat;

  //  TODO - Comeback and initalize a AVFrame for conversion
  //  along with a SWScaling context
}

void reactor::ColorSpaceWriterFilter::writeFrame(MediaFrame& frame)
{
  //  TODO - Convert the frame and pass it up
  WriterFilter::writeFrame(frame);
}

enum PixelFormat reactor::ColorSpaceWriterFilter::getPixelFormat(void)
{
  return m_format;
}