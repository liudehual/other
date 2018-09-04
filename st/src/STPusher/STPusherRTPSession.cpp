
#include "STPusherRTPSession.h"
#include "STPusherRTPSessionTimeoutTask.h"
#include "STPusher.h"
#include "STPusherLog.h"
#include "STPusherServerSession.h"
STPusherRTPSession::STPusherRTPSession(void *r,void *p,int mediaType):
				STPusherObject(r,p),
				Task(),
				fLiveState(1),
				fMediaType(mediaType),
				fStartPump(0)
{
	fSocket=new UDPSocket(this,Socket::kNonBlockingSocketType);
	fSocket->Open();
	fSocket->Bind(0,0);
	fPump=new STPusherRTPSessionTimeoutTask(this->getRoot(),this,fMediaType);
	fPump->setSocket(fSocket);
	fPump->Signal(Task::kStartEvent);
}
STPusherRTPSession::~STPusherRTPSession()
{
	fPump->Signal(Task::kKillEvent);
}
bool STPusherRTPSession::unpackRTPAAC(void * bufIn, int recvLen, void** pBufOut,  int* pOutLen)
{
    unsigned char*  bufRecv = (unsigned char*)bufIn;
   
    unsigned char ADTS[] = {0xFF, 0xF1, 0x00, 0x00, 0x00, 0x00, 0xFC};
    int audioSamprate = 44100;//音频采样率
    int audioChannel = 2;//音频声道 1或2
    int audioBit = 16;//16位 固定
    switch(audioSamprate){
    case  16000:{
        ADTS[2] = 0x60;
        break;
	}
    case  32000:{
        ADTS[2] = 0x54;
        break;
	}
    case  44100:{
        ADTS[2] = 0x50;
        break;
	}
    case  48000:{
        ADTS[2] = 0x4C;
        break;
	}
    case  96000:{
        ADTS[2] = 0x40;
        break;
	}
    default:
        break;
    }
    ADTS[3] = (audioChannel==2)?0x80:0x40;
 
    int len = recvLen - 16 + 7;
    len <<= 5;//8bit * 2 - 11 = 5(headerSize 11bit)
    len |= 0x1F;//5 bit    

    ADTS[4] = len>>8;
    ADTS[5] = len & 0xFF;
    *pBufOut = (char*)bufIn+16-7;
    memcpy(*pBufOut, ADTS, sizeof(ADTS));
    *pOutLen = recvLen - 16 + 7;
	
    return true;
}

SInt64 STPusherRTPSession::Run()
{
	EventFlags events = this->GetEvents();
	if((events & Task::kKillEvent)){
		return -1;
	}

	char buff[2048]={'\0'};
	UInt32 outLen=0;

	UInt32 remoteAddr;
	UInt16 remotePort;
	fSocket->RecvFrom(&remoteAddr,&remotePort,buff,sizeof(buff),&outLen);

	if(outLen<=12/* RTP header + AU header = 12+4 = 16 */){
		fSocket->RequestEvent(EV_RE);
		return 0;
	}
	
	char *adtsBuffer=NULL;
	int adtsOutLen=0;
	
	Frame theFrame;
	theFrame.type=fMediaType;
	theFrame.buffer=(unsigned char *)&buff[12];
	theFrame.bufferLen=outLen-12;
	
	STPusher *pusher=(STPusher *)this->getRoot();
	/* 此处不缓存数据 */
	pusher->getCallBack()(theFrame);
	
	fSocket->RequestEvent(EV_RE);
	return 0;
}
int STPusherRTPSession::sendData(Frame tFrame)
{	
	return fPump->sendData(tFrame);
}


