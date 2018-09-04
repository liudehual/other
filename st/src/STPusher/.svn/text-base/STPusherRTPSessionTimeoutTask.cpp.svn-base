#include "STPusherRTPSessionTimeoutTask.h"
#include "STPusherFramesManager.h"
#include "STPusherH264Rtp.h"
#include "STPusherAACRtp.h"
#include "STPusherRTPSession.h"
#include "STPusherServerSession.h"
#include "STPusherLog.h"
STPusherRTPSessionTimeoutTask::STPusherRTPSessionTimeoutTask(void *r,void *p,int type):
		STPusherObject(r,p),
		Task(),
		fSocket(NULL),
		fLiveState(1),
		fManager(NULL),
		mediaType(type)
	
{
	if(mediaType==AUDIO_TYPE){
		fManager=new CacheManager(4*1024,3);
		fRtpPackager=new AACRtpBuffer();
	}
	if(mediaType==VIDEO_TYPE){
		fManager=new CacheManager(2*1024*1024,3);
		fRtpPackager=new H264RtpBuffer();
	}
}
STPusherRTPSessionTimeoutTask::~STPusherRTPSessionTimeoutTask()
{
	delete fManager;
}
SInt64 STPusherRTPSessionTimeoutTask::Run()
{
	EventFlags events = this->GetEvents();
	if ((events & Task::kKillEvent)){
		return -1;
	}
	STPusherRTPSession *theRTPSession=(STPusherRTPSession *)this->getParent();
	if(!theRTPSession->getPumpState()){
		return 20;
	}
	Frame theFrame;
	theFrame.buffer=NULL;
	theFrame.bufferLen=0;
	theFrame.type=0;
	
	fManager->readData(&theFrame);
	if(theFrame.bufferLen<=0){
		return 20;
	}
	
	fRtpPackager->addFrameToBuffer((unsigned char *)theFrame.buffer,theFrame.bufferLen);


	STPusherServerSession *theServerSession=(STPusherServerSession *)theRTPSession->getParent();
	unsigned remoteAddr=theServerSession->getRemoteAddr();
	unsigned short remotePort=0;
	if(mediaType==AUDIO_TYPE){
	 remotePort=theServerSession->getRemoteAudioPort();
	}
	
	if(mediaType==VIDEO_TYPE){
		remotePort=theServerSession->getRemoteVideoPort();
	}

	
	RtpPacket *packet=NULL;
	while((packet=fRtpPackager->getRtpPacket())!=NULL){
    	fSocket->SendTo(remoteAddr,remotePort,(char *)packet->getPacketBufStart(),(UInt32)packet->getPacketLen());
	}
	fRtpPackager->reset();
	return 20;
}
int STPusherRTPSessionTimeoutTask::sendData(Frame tFrame)
{
	return fManager->writeData(&tFrame);
}

