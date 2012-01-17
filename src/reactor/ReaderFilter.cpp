#include "ReaderFilter.h"

reactor::ReaderFilter::ReaderFilter(MediaFrameReader* reader)
{
  m_reader = reader;
}

reactor::MediaFrame reactor::ReaderFilter::readFrame(void)
{
  return m_reader->readFrame();
}

enum PixelFormat reactor::ReaderFilter::getPixelFormat(void)
{
  return m_reader->getPixelFormat();
}

const int reactor::ReaderFilter::getWidth(void)
{
  return m_reader->getWidth();
}

const int reactor::ReaderFilter::getHeight(void)
{
  return m_reader->getHeight();
}