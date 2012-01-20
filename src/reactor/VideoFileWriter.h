#ifndef _REACTOR_VIDEO_FILE_WRITER_H_
#define _REACTOR_VIDEO_FILE_WRITER_H_

#include <iostream>
#include <string>

//	FFmpeg Includes
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif
extern "C"
{
  #include <libavcodec/avcodec.h>
  #include <libavformat/avformat.h>
  #include <libswscale/swscale.h>
}

#include "MediaState.h"
#include "MediaFrame.h"
#include "MediaFrameWriter.h"

using namespace std;

namespace reactor
{
  class VideoFileWriter : public MediaFrameWriter
  {
  private:
	MediaState m_videoState;
	bool m_fileOpen;
	FILE* m_fileHandle;

	static const int m_outputBufferSize = 100000000;
	uint8_t*  m_outputBuffer;

  public:
	VideoFileWriter(void);
	~VideoFileWriter();
	bool openFile(string& filename);
	bool closeFile(void);
	void writeFrame(MediaFrame& frame);

	enum PixelFormat  getPixelFormat(void);
  	const int		  getWidth(void);
	const int		  getHeight(void);

  private:
	void _setContextParameters(void);
  };
}

#endif // _REACTOR_VIDEO_FILE_WRITER_H_