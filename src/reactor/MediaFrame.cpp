#include "MediaFrame.h"

reactor::MediaFrame::MediaFrame()
{
  m_frame = NULL;
  m_format = PIX_FMT_NONE;
}

reactor::MediaFrame::MediaFrame(AVFrame* frame, enum PixelFormat format)
{
  m_frame = frame;
  m_format = format;
}

bool reactor::MediaFrame::isEmpty(void)
{
  return NULL == m_frame;
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

const int* reactor::MediaFrame::getLineSize(void)
{
  return m_frame->linesize;
}