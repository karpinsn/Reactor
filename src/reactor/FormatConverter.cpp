#include "FormatConverter.h"

bool reactor::FormatConverter::init(enum PixelFormat sourceFormat, enum PixelFormat destinationFormat)
{
  //  Initalize the context
  m_convertContext = sws_getContext(512, 512, sourceFormat, 512, 512, destinationFormat, SWS_BICUBIC, NULL, NULL, NULL);

  //  Return whether or not the context was initialized correctly
  return NULL != m_convertContext;
}

bool reactor::FormatConverter::convert(VideoFrame& source, VideoFrame& destination)
{
  if(NULL == m_convertContext)
  {
	// No conversion context present
	cout << "FormatConverter not initalized. Cannot convert!" << endl;
	return false;
  }

  //  TODO - Comeback and fix this
  int height = 512;

  // Perform the conversion
  sws_scale(m_convertContext, 
			source.getBuffer(), source.getLineSize(), 0, height, 
			destination.getBuffer(), destination.getLineSize());

  
  return true;
}

bool reactor::FormatConverter::iplImage2AVFrame(IplImage* image, AVFrame* frame)
{
  IplImage* plane0 = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
  IplImage* plane1 = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
  IplImage* plane2 = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);

  cvSplit(image, plane0, plane1, plane2, NULL);
  for(int y = 0; y < frame->height; ++y)
  {
	memcpy(frame->data[0] + (y * frame->linesize[0]), plane2->imageData + (y * plane2->widthStep), frame->width);
	memcpy(frame->data[1] + (y * frame->linesize[1]), plane1->imageData + (y * plane1->widthStep), frame->width);
	memcpy(frame->data[2] + (y * frame->linesize[2]), plane0->imageData + (y * plane0->widthStep), frame->width);
  }

  cvReleaseImage(&plane0);
  cvReleaseImage(&plane1);
  cvReleaseImage(&plane2);

  return true;
}