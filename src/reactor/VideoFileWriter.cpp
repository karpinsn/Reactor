#include "VideoFileWriter.h"

reactor::VideoFileWriter::VideoFileWriter(void)
{
  m_fileOpen = false;
  m_outputBuffer = (uint8_t*)malloc(m_outputBufferSize);

  //  Init FFmpeg
  av_register_all();
}

reactor::VideoFileWriter::~VideoFileWriter()
{
  //  If there is an open file make sure that we close it
  if(m_fileOpen)
  {
	closeFile();
  }

  //  Make sure we release the output buffer
  free(m_outputBuffer);
}

bool reactor::VideoFileWriter::openFile(string& filename)
{
  m_videoState.pCodec = avcodec_find_encoder(CODEC_ID_H264);
  if(NULL == m_videoState.pCodec)
  {
	cout << "Unable to load the H.264 codec!" << endl;
	return false;
  }

  m_videoState.pCodecContext = avcodec_alloc_context3(m_videoState.pCodec);
  if(NULL == m_videoState.pCodecContext)
  {
	cout << "Unable to allocate a codec context!" << endl;
	return false;
  }

  //  Set parameters ... TODO comeback and fix this!
  _setContextParameters();

  int videoOpen = avcodec_open(m_videoState.pCodecContext, m_videoState.pCodec);
  if(videoOpen < 0)
  {
	cout << "Unable to open the codec!" << endl;
	return false;
  }

  m_fileHandle = fopen(filename.c_str(), "wb");
  if(!m_fileHandle)
  {
	cout << "Unable to open the file: " << filename << endl;
	return false;
  }

  m_fileOpen = true;
  return m_fileOpen;
}

bool reactor::VideoFileWriter::closeFile(void)
{
  if(!m_fileOpen)
  {
	cout << "There is no open file to close!" << endl;
	return false;
  }

  //  Make sure to push any lagging frames
  int outputSize;
  do
  {
	outputSize = avcodec_encode_video(m_videoState.pCodecContext, m_outputBuffer, m_outputBufferSize, NULL);
	fwrite(m_outputBuffer, 1, outputSize, m_fileHandle);
  }while(outputSize > 0);

  fclose(m_fileHandle);

  m_fileOpen = false;
  return !m_fileOpen;
}

bool reactor::VideoFileWriter::writeFrame(VideoFrame& frame)
{
  int outputSize = avcodec_encode_video(m_videoState.pCodecContext, m_outputBuffer, m_outputBufferSize, frame.getFrame());
  fwrite(m_outputBuffer, 1, outputSize, m_fileHandle);

  return false;
}

void reactor::VideoFileWriter::_setContextParameters(void)
{
  m_videoState.pCodecContext->width = 512;
  m_videoState.pCodecContext->height = 512;
  m_videoState.pCodecContext->time_base.num = 1;
  m_videoState.pCodecContext->time_base.num = 30;
  m_videoState.pCodecContext->pix_fmt = PIX_FMT_YUV422P;

  //  Lossless max
  m_videoState.pCodecContext->codec_type = AVMEDIA_TYPE_VIDEO;
  m_videoState.pCodecContext->me_method = ME_FULL;
  m_videoState.pCodecContext->me_subpel_quality = 8;
  m_videoState.pCodecContext->me_range = 16;
  m_videoState.pCodecContext->gop_size = 250;
  m_videoState.pCodecContext->keyint_min = 25;
  m_videoState.pCodecContext->scenechange_threshold = 40;
  m_videoState.pCodecContext->i_quant_factor = .71;
  m_videoState.pCodecContext->b_frame_strategy = 1;
  m_videoState.pCodecContext->qcompress = .6;
  m_videoState.pCodecContext->qmin = 0;
  m_videoState.pCodecContext->qmax = 69;
  m_videoState.pCodecContext->max_qdiff = 4;
  m_videoState.pCodecContext->refs = 16;
  m_videoState.pCodecContext->directpred = 1;
  m_videoState.pCodecContext->cqp = 0;
  m_videoState.pCodecContext->weighted_p_pred = 2;
  m_videoState.pCodecContext->flags2 |= CODEC_FLAG2_MIXED_REFS | CODEC_FLAG2_8X8DCT | CODEC_FLAG2_FASTPSKIP;
  m_videoState.pCodecContext->me_cmp |= 1;
  m_videoState.pCodecContext->flags |= CODEC_FLAG_LOOP_FILTER;
  m_videoState.pCodecContext->partitions |= X264_PART_I8X8 | X264_PART_I4X4 | X264_PART_P8X8 | X264_PART_P4X4;
}