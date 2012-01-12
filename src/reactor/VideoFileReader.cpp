/*
 *  VideoFileReader.cpp
 *  Holoencoder
 *
 *  Created by Nikolaus Karpinsky on 01/09/12.
 *  Copyright 2012 ISU. All rights reserved.
 *
 */

#include "VideoFileReader.h"

reactor::VideoFileReader::VideoFileReader(void)
{
  m_fileOpen = false;

  //  Initialize FFmpeg
  av_register_all();
}

bool reactor::VideoFileReader::openFile(string& filename)
{
  if(m_fileOpen)
  {
	cout << "A file is already open! Can't open another till its closed..." << endl;
	return false;
  }

  //  Open the video file
  int errorCode;
  errorCode = av_open_input_file(&m_videoState.pFormatContext, 
								  filename.c_str(), 
								  NULL, 0, NULL);

  if(errorCode != 0)
  {
	cout << "Unable to open video: " << filename << endl;
	return m_fileOpen;
  }

  //  Find the video stream
  m_videoState.videoStream = -1;
  for(unsigned int streamNumber = 0; streamNumber < m_videoState.pFormatContext->nb_streams; ++streamNumber)
  {
	if(m_videoState.pFormatContext->streams[streamNumber]->codec->codec_type==AVMEDIA_TYPE_VIDEO)
	{
	  m_videoState.videoStream = streamNumber;
	  break;
	}
  }

  if(-1 == m_videoState.videoStream)
  {
	cout << "Unable to find a video stream in the file!" << endl;
	return m_fileOpen;
  }

  // Get a pointer to the video codec context for the video streams
  m_videoState.pCodecContext = m_videoState.pFormatContext->streams[m_videoState.videoStream]->codec;
  // Need to get a decoder for the video stream
  m_videoState.pCodec = avcodec_find_decoder(m_videoState.pCodecContext->codec_id);

  if(NULL == m_videoState.pCodec)
  {
	cout << "Unable to find a codec for the video file!" << endl;
	return m_fileOpen;
  }

  errorCode = avcodec_open(m_videoState.pCodecContext, m_videoState.pCodec);

  if(errorCode < 0)
  {
	cout << "Unable to open a codec for the video file!" << endl;
	return m_fileOpen;
  }

  //  Allocate a video frame
  m_videoState.pCurrentFrame = avcodec_alloc_frame();

  m_fileOpen = true;
  return m_fileOpen;
}

bool reactor::VideoFileReader::closeFile()
{
  if(!m_fileOpen)
  {
	cout << "There is no open file to close!" << endl;
	return m_fileOpen;
  }

  //  Free the frame handle
  av_free(m_videoState.pCurrentFrame);
  //  Close the codec
  avcodec_close(m_videoState.pCodecContext);
  //  Close the input file
  av_close_input_file(m_videoState.pFormatContext);

  return !m_fileOpen;
}

reactor::VideoFrame reactor::VideoFileReader::readFrame()
{
  if(!m_fileOpen)
  {
	cout << "There is no open file to read from!" << endl;
	//	Return an empty video frame
	return VideoFrame();
  }

  int		frameFinished = 0;
  AVPacket	packet;
  
  while(av_read_frame(m_videoState.pFormatContext, &packet) >= 0)
  {
	//	Make sure that this packet is a video packet
	if(packet.stream_index == m_videoState.videoStream)
	{
	  avcodec_decode_video2(m_videoState.pCodecContext, m_videoState.pCurrentFrame, &frameFinished, &packet);

	  if(frameFinished)
	  {
		cout << "Got a frame!" << endl;
		//	Return a video frame that wraps the current frame
		return VideoFrame(m_videoState.pCurrentFrame, m_videoState.pCodecContext->pix_fmt);
	  }
	}

	av_free_packet(&packet);
  }

  return VideoFrame();
}