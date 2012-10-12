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
//  errorCode = av_open_input_file(&m_videoState.m_FormatContext, 
	//							  filename.c_str(), 
		//						  nullptr, 0, nullptr);

  if(errorCode != 0)
  {
	cout << "Unable to open video: " << filename << endl;
	return m_fileOpen;
  }

  errorCode = av_find_stream_info(m_videoState.m_FormatContext);
  if(errorCode < 0)
  {
	cout << "Unable to decode stream info!" << endl;
	return m_fileOpen;
  }

  //  Find the video stream
  m_videoState.m_videoStreamIndex = -1;
  for(unsigned int streamNumber = 0; streamNumber < m_videoState.m_FormatContext->nb_streams; ++streamNumber)
  {
	if(m_videoState.m_FormatContext->streams[streamNumber]->codec->codec_type==AVMEDIA_TYPE_VIDEO)
	{
	  m_videoState.m_videoStreamIndex = streamNumber;
	  break;
	}
  }

  if(-1 == m_videoState.m_videoStreamIndex)
  {
	cout << "Unable to find a video stream in the file!" << endl;
	return m_fileOpen;
  }

  // Get a pointer to the video codec context for the video streams
  m_videoState.m_CodecContext = m_videoState.m_FormatContext->streams[m_videoState.m_videoStreamIndex]->codec;
  // Need to get a decoder for the video stream
  m_videoState.m_Codec = avcodec_find_decoder(m_videoState.m_CodecContext->codec_id);

  if(nullptr == m_videoState.m_Codec)
  {
	cout << "Unable to find a codec for the video file!" << endl;
	return m_fileOpen;
  }

  errorCode = avcodec_open(m_videoState.m_CodecContext, m_videoState.m_Codec);

  if(errorCode < 0)
  {
	cout << "Unable to open a codec for the video file!" << endl;
	return m_fileOpen;
  }

  //  Allocate a video frame
  m_videoState.m_CurrentFrame = avcodec_alloc_frame();

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
  av_free(m_videoState.m_CurrentFrame);
  //  Close the codec
  avcodec_close(m_videoState.m_CodecContext);
  //  Close the input file
  av_close_input_file(m_videoState.m_FormatContext);

  return !m_fileOpen;
}

enum PixelFormat reactor::VideoFileReader::getPixelFormat(void)
{
  if(nullptr != m_videoState.m_CodecContext)
  {
	return m_videoState.m_CodecContext->pix_fmt;
  }

  return PIX_FMT_NONE;
}

const int reactor::VideoFileReader::getWidth(void)
{
  if(nullptr != m_videoState.m_CodecContext)
  {
	return m_videoState.m_CodecContext->width;
  }
  
  return 0;
}
	
const int reactor::VideoFileReader::getHeight(void)
{
  if(nullptr != m_videoState.m_CodecContext)
  {
	return m_videoState.m_CodecContext->height;
  }
  
  return 0;
}

reactor::MediaFrame reactor::VideoFileReader::readFrame()
{
  if(!m_fileOpen)
  {
	cout << "There is no open file to read from!" << endl;
	//	Return an empty video frame
	return MediaFrame();
  }

  int		frameFinished = 0;
  AVPacket	packet;
  
  while(av_read_frame(m_videoState.m_FormatContext, &packet) >= 0)
  {
	//	Make sure that this packet is a video packet
	if(packet.stream_index == m_videoState.m_videoStreamIndex)
	{
	  avcodec_decode_video2(m_videoState.m_CodecContext, m_videoState.m_CurrentFrame, &frameFinished, &packet);

	  if(frameFinished)
	  {
		cout << "Got a frame!" << endl;
		//	Return a video frame that wraps the current frame
		return MediaFrame(m_videoState.m_CurrentFrame, m_videoState.m_CodecContext->pix_fmt);
	  }
	}

	av_free_packet(&packet);
  }

  return MediaFrame();
}