#include "MediaFrame.h"

reactor::MediaFrame::MediaFrame()
{
  m_frame = nullptr;
  m_format = PIX_FMT_NONE;
}

reactor::MediaFrame::MediaFrame(AVFrame* frame, enum PixelFormat format)
{
  m_frame = frame;
  m_format = format;
}

bool reactor::MediaFrame::isEmpty(void)
{
  return nullptr == m_frame;
}

AVFrame* reactor::MediaFrame::getFrame(void)
{
  return m_frame;
}

enum PixelFormat reactor::MediaFrame::getPixelFormat(void)
{
  return m_format;
}

uint8_t** reactor::MediaFrame::getBuffer(void)
{
  return m_frame->data;
}

const int* reactor::MediaFrame::getLineSize(void) const
{
  return m_frame->linesize;
}

const int reactor::MediaFrame::getWidth(void) const
{
  return m_frame->width;
}

const int reactor::MediaFrame::getHeight(void) const
{
  return m_frame->height;
}