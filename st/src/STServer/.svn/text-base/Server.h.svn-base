#ifndef __SERVER_HH__
#define __SERVER_HH__
#include "Task.h"
#include "Object.h"
#include "OSQueue.h"
#include "GetNetInterfaceInfo.h"
class LogSession;
class ConfigFileParser;
class ClientSession;
class UserAuthentication;
class Server:public Object,public Task
{
	public:
		Server();
		~Server();
		int initialize(UInt16 inPortOverride);
		int startServer();
		virtual SInt64 Run();
		ConfigFileParser *getConfigFileParser();
		OSQueue *getClientSessionQueue(){return &fClientSessionQueue;}
		LogSession *getLogSession(){return fLogSession;}
		UserAuthentication *getUserAuthentication(){return fUserAuthentication;}

		int addRTPSessionToQueue(void *session,unsigned dstUserId);
		
		int delRTPSessionFromQueue(void *session);


		int setDstRTPSession(void *session,unsigned dstUserId);
	private:
		ConfigFileParser *fConfParser;
		LogSession *fLogSession;
		UserAuthentication *fUserAuthentication;

		
		OSQueue fClientSessionQueue;
		OSMutex fClientSessionQueueMutex;
		
		OSQueue fCommonListenerQueue;

		Info **fNetInfoArray;  /* Íø¿ÚÁÐ±í */

		
		

};
#endif

