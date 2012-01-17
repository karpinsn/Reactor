#include "WriterFilter.h"

reactor::WriterFilter::WriterFilter(MediaFrameWriter* writer)
{
  m_writer = writer;
}

void reactor::WriterFilter::writeFrame(MediaFrame& frame)
{
  m_writer->writeFrame(frame);
}

enum PixelFormat reactor::WriterFilter::getPixelFormat(void)
{
  return m_writer->getPixelFormat();
}

const int reactor::WriterFilter::getWidth(void)
{
  return m_writer->getWidth();
}

const int reactor::WriterFilter::getHeight(void)
{
  return m_writer->getHeight();
}