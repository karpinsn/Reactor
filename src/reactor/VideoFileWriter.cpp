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
  m_videoState.m_Codec = avcodec_find_encoder(CODEC_ID_H264);
  if(NULL == m_videoState.m_Codec)
  {
	cout << "Unable to load the H.264 codec!" << endl;
	return false;
  }

  m_videoState.m_CodecContext = avcodec_alloc_context3(m_videoState.m_Codec);
  if(NULL == m_videoState.m_CodecContext)
  {
	cout << "Unable to allocate a codec context!" << endl;
	return false;
  }

  //  Set parameters ... TODO comeback and fix this!
  _setContextParameters();

  int videoOpen = avcodec_open(m_videoState.m_CodecContext, m_videoState.m_Codec);
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
	outputSize = avcodec_encode_video(m_videoState.m_CodecContext, m_outputBuffer, m_outputBufferSize, NULL);
	fwrite(m_outputBuffer, 1, outputSize, m_fileHandle);
  }while(outputSize > 0);

  fclose(m_fileHandle);

  m_fileOpen = false;
  return !m_fileOpen;
}

void reactor::VideoFileWriter::writeFrame(MediaFrame& frame)
{
  int outputSize = avcodec_encode_video(m_videoState.m_CodecContext, m_outputBuffer, m_outputBufferSize, frame.getFrame());
  fwrite(m_outputBuffer, 1, outputSize, m_fileHandle);
}

enum PixelFormat reactor::VideoFileWriter::getPixelFormat(void)
{
  return m_videoState.m_CodecContext->pix_fmt;
}

const int reactor::VideoFileWriter::getWidth(void)
{
  if(NULL != m_videoState.m_CodecContext)
  {
	return m_videoState.m_CodecContext->width;
  }
  
  return 0;
}
	
const int reactor::VideoFileWriter::getHeight(void)
{
  if(NULL != m_videoState.m_CodecContext)
  {
	return m_videoState.m_CodecContext->height;
  }
  
  return 0;
}

void reactor::VideoFileWriter::_setContextParameters(void)
{
  m_videoState.m_CodecContext->width = 512;
  m_videoState.m_CodecContext->height = 512;
  m_videoState.m_CodecContext->time_base.num = 1;
  m_videoState.m_CodecContext->time_base.num = 30;
  m_videoState.m_CodecContext->pix_fmt = PIX_FMT_YUV422P;

  //  Lossless max
  
  m_videoState.m_CodecContext->codec_type = AVMEDIA_TYPE_VIDEO;
  m_videoState.m_CodecContext->me_method = ME_FULL;
  m_videoState.m_CodecContext->me_subpel_quality = 8;
  m_videoState.m_CodecContext->me_range = 16;
  m_videoState.m_CodecContext->gop_size = 250;
  m_videoState.m_CodecContext->keyint_min = 25;
  m_videoState.m_CodecContext->scenechange_threshold = 40;
  m_videoState.m_CodecContext->i_quant_factor = .71;
  m_videoState.m_CodecContext->b_frame_strategy = 1;
  m_videoState.m_CodecContext->qcompress = .6;
  m_videoState.m_CodecContext->qmin = 0;
  m_videoState.m_CodecContext->qmax = 69;
  m_videoState.m_CodecContext->max_qdiff = 4;
  m_videoState.m_CodecContext->refs = 16;
  m_videoState.m_CodecContext->directpred = 1;
  m_videoState.m_CodecContext->cqp = 0;
  m_videoState.m_CodecContext->weighted_p_pred = 2;
  m_videoState.m_CodecContext->flags2 |= CODEC_FLAG2_MIXED_REFS | CODEC_FLAG2_8X8DCT | CODEC_FLAG2_FASTPSKIP;
  m_videoState.m_CodecContext->me_cmp |= 1;
  m_videoState.m_CodecContext->flags |= CODEC_FLAG_LOOP_FILTER;
  m_videoState.m_CodecContext->partitions |= X264_PART_I8X8 | X264_PART_I4X4 | X264_PART_P8X8 | X264_PART_P4X4;
  

  //  Lossless Slower
  /*
  m_videoState.m_CodecContext->codec_type = AVMEDIA_TYPE_VIDEO;
  m_videoState.m_CodecContext->flags |= CODEC_FLAG_LOOP_FILTER | CODEC_FLAG_CLOSED_GOP;
  m_videoState.m_CodecContext->me_cmp |= 1;
  m_videoState.m_CodecContext->partitions |= X264_PART_I8X8 | X264_PART_I4X4 | X264_PART_P8X8 | X264_PART_P4X4;
  m_videoState.m_CodecContext->partitions &= ~(X264_PART_B8X8);
  m_videoState.m_CodecContext->me_method = ME_UMH;
  m_videoState.m_CodecContext->me_subpel_quality = 8;
  m_videoState.m_CodecContext->me_range = 16;
  m_videoState.m_CodecContext->gop_size = 250;
  m_videoState.m_CodecContext->keyint_min = 25;
  m_videoState.m_CodecContext->scenechange_threshold = 40;
  m_videoState.m_CodecContext->i_quant_factor = .71;
  m_videoState.m_CodecContext->b_frame_strategy = 1;
  m_videoState.m_CodecContext->qcompress = .6;
  m_videoState.m_CodecContext->qmin = 0;
  m_videoState.m_CodecContext->qmax = 69;
  m_videoState.m_CodecContext->max_qdiff = 4;
  m_videoState.m_CodecContext->refs = 4;
  m_videoState.m_CodecContext->directpred = 1;
  m_videoState.m_CodecContext->flags2 |= CODEC_FLAG2_MIXED_REFS | CODEC_FLAG2_8X8DCT | CODEC_FLAG2_FASTPSKIP;
  m_videoState.m_CodecContext->cqp = 0;
  m_videoState.m_CodecContext->weighted_p_pred = 2;
  */

  //  Ultrafast
  /*
  m_videoState.m_CodecContext->codec_type = AVMEDIA_TYPE_VIDEO;
  m_videoState.m_CodecContext->flags |= CODEC_FLAG_LOOP_FILTER | CODEC_FLAG_CLOSED_GOP;
  m_videoState.m_CodecContext->me_cmp |= 1;
  m_videoState.m_CodecContext->partitions &= (X264_PART_I8X8 | X264_PART_I4X4 | X264_PART_P8X8 | X264_PART_P4X4 | X264_PART_B8X8);
  m_videoState.m_CodecContext->me_method = ME_EPZS;
  m_videoState.m_CodecContext->me_subpel_quality = 0;
  m_videoState.m_CodecContext->me_range = 16;
  m_videoState.m_CodecContext->gop_size = 250;
  m_videoState.m_CodecContext->keyint_min = 25;
  m_videoState.m_CodecContext->scenechange_threshold = 40;
  m_videoState.m_CodecContext->i_quant_factor = .71;
  m_videoState.m_CodecContext->b_frame_strategy = 1;
  m_videoState.m_CodecContext->qcompress = .6;
  m_videoState.m_CodecContext->qmin = 0;
  m_videoState.m_CodecContext->qmax = 69;
  m_videoState.m_CodecContext->max_qdiff = 4;
  m_videoState.m_CodecContext->directpred = 1;
  m_videoState.m_CodecContext->flags2 |= CODEC_FLAG2_FASTPSKIP;
  m_videoState.m_CodecContext->cqp = 0;
  */

  //  Medium
  /*
  m_videoState.m_CodecContext->codec_type = AVMEDIA_TYPE_VIDEO;
  m_videoState.m_CodecContext->me_method = ME_FULL;
  m_videoState.m_CodecContext->me_subpel_quality = 8;
  m_videoState.m_CodecContext->me_range = 16;
  m_videoState.m_CodecContext->gop_size = 250;
  m_videoState.m_CodecContext->keyint_min = 25;
  m_videoState.m_CodecContext->scenechange_threshold = 40;
  m_videoState.m_CodecContext->i_quant_factor = .71;
  m_videoState.m_CodecContext->b_frame_strategy = 1;
  m_videoState.m_CodecContext->qcompress = .6;
  m_videoState.m_CodecContext->qmin = 0;
  m_videoState.m_CodecContext->qmax = 69;
  m_videoState.m_CodecContext->max_qdiff = 4;
  m_videoState.m_CodecContext->refs = 16;
  m_videoState.m_CodecContext->directpred = 1;
  m_videoState.m_CodecContext->cqp = 0;
  m_videoState.m_CodecContext->weighted_p_pred = 2;
  m_videoState.m_CodecContext->flags2 = CODEC_FLAG2_MIXED_REFS | CODEC_FLAG2_8X8DCT | CODEC_FLAG2_FASTPSKIP;
  m_videoState.m_CodecContext->me_cmp |= 1;
  m_videoState.m_CodecContext->flags |= CODEC_FLAG_LOOP_FILTER;
  m_videoState.m_CodecContext->partitions |= X264_PART_I8X8 | X264_PART_I4X4 | X264_PART_P8X8 | X264_PART_P4X4;
  */

  //  Baseline
  /*
  m_videoState.m_CodecContext->coder_type = 0;
  //m_videoState.m_CodecContext->max_b_frames = 0;
  m_videoState.m_CodecContext->flags2 &= ~(CODEC_FLAG2_WPRED | CODEC_FLAG2_8X8DCT);
  m_videoState.m_CodecContext->weighted_p_pred = 0;
  
  //  + Nik Settings
  m_videoState.m_CodecContext->flags2 |= CODEC_FLAG2_8X8DCT;
  m_videoState.m_CodecContext->flags |= CODEC_FLAG_LOOP_FILTER;
  m_videoState.m_CodecContext->partitions |= X264_PART_I8X8 | X264_PART_I4X4 | X264_PART_P8X8 | X264_PART_P4X4;
  m_videoState.m_CodecContext->me_method = ME_FULL;
  m_videoState.m_CodecContext->me_subpel_quality = 8;
  m_videoState.m_CodecContext->me_range = 16;
  m_videoState.m_CodecContext->gop_size = 250;
  m_videoState.m_CodecContext->keyint_min = 25;
  m_videoState.m_CodecContext->scenechange_threshold = 40;
  m_videoState.m_CodecContext->i_quant_factor = .71;
  m_videoState.m_CodecContext->b_frame_strategy = 1;
  m_videoState.m_CodecContext->qcompress = .6;
  m_videoState.m_CodecContext->qmin = 0;
  m_videoState.m_CodecContext->qmax = 69;
  m_videoState.m_CodecContext->max_qdiff = 4;
  m_videoState.m_CodecContext->refs = 16;
*/  

  //  HQ - Paper MQ
/*
  m_videoState.m_CodecContext->codec_type = AVMEDIA_TYPE_VIDEO;
  m_videoState.m_CodecContext->flags |= CODEC_FLAG_LOOP_FILTER;
  m_videoState.m_CodecContext->me_cmp = 1;
  m_videoState.m_CodecContext->partitions |= X264_PART_I8X8 | X264_PART_I4X4 | X264_PART_P8X8 | X264_PART_B8X8;
  m_videoState.m_CodecContext->me_method = ME_UMH;
  m_videoState.m_CodecContext->me_subpel_quality = 8;
  m_videoState.m_CodecContext->me_range = 16;
  m_videoState.m_CodecContext->gop_size = 250;
  m_videoState.m_CodecContext->keyint_min = 25;
  m_videoState.m_CodecContext->scenechange_threshold = 40;
  m_videoState.m_CodecContext->i_quant_factor = .71;
  m_videoState.m_CodecContext->b_frame_strategy = 2;
  m_videoState.m_CodecContext->qcompress = .6;
  m_videoState.m_CodecContext->max_qdiff = 4;
  m_videoState.m_CodecContext->max_b_frames = 4;
  m_videoState.m_CodecContext->refs = 4;
  m_videoState.m_CodecContext->directpred = 3;
  m_videoState.m_CodecContext->trellis = 1;
  m_videoState.m_CodecContext->flags2 = CODEC_FLAG2_BPYRAMID | CODEC_FLAG2_WPRED | CODEC_FLAG2_MIXED_REFS | CODEC_FLAG2_8X8DCT | CODEC_FLAG2_FASTPSKIP;
  */
}