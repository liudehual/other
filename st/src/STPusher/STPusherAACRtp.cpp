#include "STPusherAACRtp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AACRtpBuffer::AACRtpBuffer():RtpBuffer((unsigned char)96)
{

}
AACRtpBuffer::~AACRtpBuffer()
{

}


//@@@@@@@@@@@@@@@@@@@@@@@@@ add by gct 1605100919 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void AACRtpBuffer::addFrameToBuffer(unsigned char *frame,unsigned fLen)
{
	/* 
		fLen指ADTS payload 长度(不包含ADTS头) 
	*/
	if(frame==NULL || fLen==0){
		return;
	}
	 getTimeStamp();
	 /* 大于则截断 */
	 if(fLen>PACKET_MAX_SIZE-12){
		fLen=PACKET_MAX_SIZE-12;
	 }
	 
	 /* 第一版 不支持分包 */
	 if(fLen<=PACKET_MAX_SIZE-12){
	   RtpPacket * packet=getFreePacket();
       if(packet==NULL)return;
       setRtpHeader(packet);
	   unsigned char *buf=packet->getPacketBuffer();
       packet->setPacketLen(fLen+12);
       buf=packet->getPacketBuffer();
       memcpy(buf,frame,fLen);
	}
}
unsigned AACRtpBuffer::getTimeStamp()
{
	return fTimeStamp+=(1024/*samples-per-frame*/*1000000) / 44100/*samples-per-second*/;
}
