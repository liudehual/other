#ifndef __ST_PUSHER_RTP_SESSION_TIMEOUT_TASK_H__
#define __ST_PUSHER_RTP_SESSION_TIMEOUT_TASK_H__
#include "STPusherObject.h"
#include "Task.h"
#include "UDPSocket.h"
#include "STPusherAPI.h"
class CacheManager;
class RtpBuffer;
class STPusherRTPSessionTimeoutTask:public STPusherObject,public Task
{
	public:
		STPusherRTPSessionTimeoutTask(void *r,void *p,int type);
		~STPusherRTPSessionTimeoutTask();
		void setSocket(UDPSocket *tSocket){fSocket=tSocket;}
		virtual SInt64 Run();
		CacheManager *getCacheManager(){return fManager; }
		int sendData(Frame tFrame);
	private:
		UDPSocket *fSocket;
		int fLiveState;

		CacheManager *fManager;
		RtpBuffer * fRtpPackager;

		int mediaType;
};


#endif
