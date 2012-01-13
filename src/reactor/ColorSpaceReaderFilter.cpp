#include "ColorSpaceReaderFilter.h"

reactor::ColorSpaceReaderFilter::ColorSpaceReaderFilter(MediaFrameReader* reader, enum PixelFormat destinationFormat) : ReaderFilter(reader)
{
}

reactor::MediaFrame reactor::ColorSpaceReaderFilter::readFrame(void)
{
  // TODO Convert the frame that has been read in
  return ReaderFilter::readFrame();
}

enum PixelFormat reactor::ColorSpaceReaderFilter::getPixelFormat(void)
{
  return m_format;
}