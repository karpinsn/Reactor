#include "VideoFrame.h"

reactor::VideoFrame::VideoFrame()
{
  m_frame = NULL;
  m_format = PIX_FMT_NONE;
}

reactor::VideoFrame::VideoFrame(AVFrame* frame, enum PixelFormat format)
{
  m_frame = frame;
  m_format = format;
}

bool reactor::VideoFrame::isEmpty(void)
{
  return NULL == m_frame;
}

enum PixelFormat reactor::VideoFrame::getPixelFormat(void)
{
  return m_format;
}