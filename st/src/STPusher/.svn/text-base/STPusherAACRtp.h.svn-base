#ifndef __STPUSHER_AAC_RTP_H__
#define __STPUSHER_AAC_RTP_H__
#include "STPusherRtp.h"

class AACRtpBuffer:public RtpBuffer
{
	public:
		AACRtpBuffer();
		~AACRtpBuffer();
		//@@@@@@@@@@@@@@@@@@@@@@@@@ add by gct 1605100919 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    	virtual void addFrameToBuffer(unsigned char *frame,unsigned fLen);
    	virtual unsigned getTimeStamp();
};

#endif
