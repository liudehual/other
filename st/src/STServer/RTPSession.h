#ifndef __RTP_SESSION_H__
#define __RTP_SESSION_H__

#include "Task.h"
#include "UDPSocket.h"
#include "Object.h"
#include "OSQueue.h"
class RTPSession:public Object,public Task
{
	public:
		RTPSession(void *r,void *p,int mediaType);
		~RTPSession();
		virtual SInt64 Run();
		UDPSocket *getSocket(){return fSocket;}
		int getLiveState(){return fLiveState;}
		int setLiveState(int state){fLiveState=state;}
		int sendData(unsigned remoteAddr,unsigned short remotePort,char *buffer,int len);
		int getMediaType(){return fMediaType;}
		UInt16 getPort(){return fPort;}

		void setClientNetInfo(unsigned cIp,unsigned short cPort){fClientIp=cIp;fClientPort=cPort;}
		void getClientNetInfo(unsigned &cIp,unsigned short &cPort){cIp=fClientIp;cPort=fClientPort;}

		int addRtpSessionToQueue(RTPSession *rSession);
		int delRTPSessionFromQueue(RTPSession *rSession);
		int getRTPSessionQueueLen();

		int setDstRTPSession(RTPSession *rSession);
		OSQueueElem *getElem(){return &fElem;}

		unsigned getClientAddr(){return fClientIp;}
		unsigned short getClientPort(){return fClientPort;}
	private:
		UDPSocket *fSocket;
		
		/* 单人对讲 */
		RTPSession *fDstRtpSession;
		OSMutex fDstRTPSessionMutex;

		/* 组对讲暂未实现 组对讲的优先级高于单人对讲 */
		OSQueue fRTPSessionQueue; /* 用于多人对讲 */
		OSMutex fRTPSessionQueueMutex;

		int fLiveState;

		int fMediaType;

		UInt16 fPort;

		unsigned fClientIp;
		unsigned short fClientPort;

		OSQueueElem fElem;

		
};

#endif
