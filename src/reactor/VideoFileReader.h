/*
 Filename:		VideoFileReader.h
 Author:		Nikolaus Karpinsky
 Date Created:	01/09/12
 Last Edited:	01/09/12
 
 Revision Log:
 01/09/12 - Nik Karpinsky - Original creation.
 */

#ifndef _VIDEO_FILE_READER_H_
#define _VIDEO_FILE_READER_H_

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
	class VideoFileReader
	{
	private:
	  VideoState  m_videoState;
	  bool		  m_fileOpen;

	public:
	  VideoFileReader(void);
	  bool openFile(string& filename);
	  bool closeFile();

	  VideoFrame readFrame();
	};
}

#endif	// _VIDEO_FILE_READER_H_
