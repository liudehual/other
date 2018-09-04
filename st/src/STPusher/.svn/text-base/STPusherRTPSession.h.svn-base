#ifndef __ST_PUSHER_RTP_SESSION_H__
#define __ST_PUSHER_RTP_SESSION_H__
#include "STPusherObject.h"
#include "Task.h"
#include "UDPSocket.h"
#include "STPusherAPI.h"
class STPusherRTPSessionTimeoutTask;
class STPusherRTPSession:public STPusherObject,public Task
{
	public:
		STPusherRTPSession(void *r,void *p,int mediaType);
		~STPusherRTPSession();
		virtual SInt64 Run();
		int sendData(Frame tFrame);
		UDPSocket *getSocket(){return fSocket;}
		bool unpackRTPAAC(void * bufIn, int recvLen, void** pBufOut,  int* pOutLen);
		void startPump(){fStartPump=1;}
		void stopPump(){fStartPump=0;}
		int getPumpState(){return fStartPump;}
		int getMediaType(){return fMediaType;}
	private:
		UDPSocket *fSocket;
		STPusherRTPSessionTimeoutTask *fPump;

		int fLiveState;

		int fMediaType;

		int fStartPump;
};
#endif
