#ifndef _REACTOR_VIDEO_FILE_WRITER_H_
#define _REACTOR_VIDEO_FILE_WRITER_H_

#include <iostream>
#include <string>

//	FFmpeg Includes
#define __STDC_CONSTANT_MACROS
extern "C"
{
  #include <libavcodec/avcodec.h>
  #include <libavformat/avformat.h>
  #include <libswscale/swscale.h>
}

#include "VideoState.h"
#include "VideoFrame.h"

using namespace std;

namespace reactor
{
  class VideoFileWriter
  {
  private:
	VideoState m_videoState;
	bool m_fileOpen;
	FILE* m_fileHandle;

	static const int m_outputBufferSize = 1000000;
	uint8_t*  m_outputBuffer;

  public:
	VideoFileWriter(void);
	~VideoFileWriter();
	bool openFile(string& filename);
	bool closeFile(void);

	bool writeFrame(VideoFrame& frame);

  private:
	void _setContextParameters(void);
  };
}

#endif // _REACTOR_VIDEO_FILE_WRITER_H_