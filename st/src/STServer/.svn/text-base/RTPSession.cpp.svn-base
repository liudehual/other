#include "RTPSession.h"
#include "Util.h"
#include "Log.h"
RTPSession::RTPSession(void *r,void *p,int mediaType):Object(r,p),
														Task(),
														fLiveState(1),
														fMediaType(mediaType),
														fPort(0),
														fClientIp(0),
														fClientPort(0),
														fDstRtpSession(NULL)

{
	fSocket=new UDPSocket(this,Socket::kNonBlockingSocketType);
	fSocket->Open();
	fSocket->Bind(0,0);
	
	fSocket->RequestEvent(EV_RE);
}
RTPSession::~RTPSession()
{

}
SInt64 RTPSession::Run()
{
	EventFlags events = this->GetEvents();
	if ((events & Task::kKillEvent)){
		return -1;
	}

	char buffer[2000]={'\0'};
	UInt32 readLen=0;
	
	fSocket->RecvFrom(&fClientIp,&fClientPort,buffer,sizeof(buffer), &readLen);
	char ipBuf[32]={'\0'};
	UInt32ToStringIp(fClientIp,ipBuf);
	//log_fprintf(stderr,"remoteIp %s remotePort %d readLen %d \n",ipBuf,fClientPort,readLen);

	/* 组对讲 */
	if(fRTPSessionQueue.GetLength()!=0){

				   /* 组对讲，暂未实现 */
				   /* 发送数据时，需要加锁 */
				   OSMutexLocker theLocker(&fRTPSessionQueueMutex);

				   /* 遍历所有注册时RTPSession,可以群发或按照优先级发送 */
				   for (OSQueueIter theIter(&fRTPSessionQueue); !theIter.IsDone(); theIter.Next()) {
					   OSQueueElem *theElem = theIter.GetCurrent();;
		
					   RTPSession * theRTPSession=(RTPSession *)theElem->GetEnclosingObject();
					   /* */
					   int theErr=theRTPSession->sendData(theRTPSession->getClientAddr(),theRTPSession->getClientPort(),buffer,readLen);
					   if(!theErr){}
				   }

	}else{ /* 单人对讲 */
			OSMutexLocker theLocket(&fDstRTPSessionMutex);
			if(fDstRtpSession){ /*单人对讲 */
				//	log_fprintf(stderr,"send remoteIp %s remotePort %d readLen %d \n",ipBuf,fClientPort,readLen);
				fDstRtpSession->sendData(fDstRtpSession->getClientAddr(),fDstRtpSession->getClientPort(),buffer,readLen);
			}
	}

	fSocket->RequestEvent(EV_RE);
	return 0;
}

int RTPSession::sendData(unsigned remoteAddr,unsigned short remotePort,char *buffer,int len)
{
	UInt32 outLen=0;
    fSocket->SendTo(remoteAddr,remotePort,buffer,len);
	return outLen;
}

int RTPSession::addRtpSessionToQueue(RTPSession *rSession)
{
	if(!rSession){
		return 0;
	}
	OSMutexLocker theLocker(&fRTPSessionQueueMutex);
	fRTPSessionQueue.EnQueue(rSession->getElem());
	return 1;
}

int RTPSession::delRTPSessionFromQueue(RTPSession *rSession)
{
	if(!rSession){
			return 0;
	}
	OSMutexLocker theLocker(&fRTPSessionQueueMutex);
	for (OSQueueIter theIter(&fRTPSessionQueue); !theIter.IsDone(); theIter.Next()) {
		OSQueueElem *theElem = theIter.GetCurrent();;
		RTPSession * theRTPSession=(RTPSession *)theElem->GetEnclosingObject();
		if(rSession==theRTPSession){
			fRTPSessionQueue.Remove(theElem);
			break;
		}
	}
	return 1;
}
int RTPSession::getRTPSessionQueueLen()
{
	OSMutexLocker theLocker(&fRTPSessionQueueMutex);
	return fRTPSessionQueue.GetLength();

}
int RTPSession::setDstRTPSession(RTPSession *rSession)
{
	OSMutexLocker theLocket(&fDstRTPSessionMutex);
	fDstRtpSession=rSession;
	return 1;
}

