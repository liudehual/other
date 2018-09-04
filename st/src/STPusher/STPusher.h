#ifndef __AUDIO_PUSHER_H__
#define __AUDIO_PUSHER_H__
#include "STPusherObject.h"
#include "Task.h"
#include "STPusherAPI.h"
#include "STPusherGetNetInterfaceInfo.h"
class STPusherLogSession ;
class STPusherServerSession;


class STPusher:public STPusherObject,public Task
{
	public:
		STPusher(callBackFunc func);
		~STPusher();
		virtual SInt64 Run();
		STPusherLogSession *getLogSession(){return fLogSession;}
		int connectToServer(char *serverIp,unsigned short serverPort);
		int sendData(Frame tFrame);

		int loginToServer(char *name,char *passwd);
		int registerToServer(char *name,char *passwd);
		int getUserList();
		int startPushFrame();
		int startPullFrame(unsigned id);
		callBackFunc getCallBack(){return fDataCallBack;}
		bool isConnected(){return fIsConnected;}

		char *getLocalIp(){return fLocalIp;}

		unsigned getUserID(char *userName);
	private:
		STPusherLogSession *fLogSession;
		STPusherServerSession *fServerSession;

		callBackFunc fDataCallBack;

		int fIsConnected;

		char fLocalIp[32];
};

#endif
