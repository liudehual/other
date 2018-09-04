#include "STPusherAPI.h"
#include "OS.h"
#include "STPusher.h"
#include "OSMutex.h"
STPusher *gPusher=NULL;
int STPusher_Init(callBackFunc func)
{
	if(!func){
		return -1;
	}
	if(gPusher){
		delete gPusher;
		gPusher=NULL;
	}
	static int init=0;
	if(!init){
		init=1;
		OS::Initialize();
	}
	
	gPusher=new STPusher(func);
	return 1;
}

int STPusher_connect(char *serverAddr,
					unsigned short serverPort,
					char *userName,
					char *userPassword)
{
	if(!gPusher){
		return 0;
	}
	return gPusher->connectToServer(serverAddr,serverPort);
}

int STPusher_pushFrame(Frame tFrame)
{
	
	static OSMutex sMutex;
	if(!gPusher){
		return -1;
	}
	if(!gPusher->isConnected()){
		return -2;
	}
	{
		OSMutexLocker locker(&sMutex);
		gPusher->sendData(tFrame);
	}
	return 1;
}

int STPusher_loginToServer(char *userName,		char *userPassword)
{
	if(userName==NULL 
		|| strlen(userName)==0
		|| userPassword==NULL
		|| strlen(userPassword)==0){
		return 0;
	}
	return gPusher->loginToServer(userName,userPassword);
}

int STPusher_RegisterToServer(char *userName,		char *userPassword)
{
	if(userName==NULL 
		|| strlen(userName)==0
		|| userPassword==NULL
		|| strlen(userPassword)==0){
		return 0;
	}
	return gPusher->registerToServer(userName,userPassword);
}

int STPusher_GetUserList()
{
	return gPusher->getUserList();
}

int STPusher_StartPushFrame()
{
	return gPusher->startPushFrame();
}
unsigned STPusher_GetUerID(char *userName)
{
	if(userName==NULL || strlen(userName)==0){
		return 0;
	}
	return gPusher->getUserID(userName);
}
int STPusher_StartPullFrame(unsigned id)
{
	if(id==0){
		return 0;
	}
	
	return gPusher->startPullFrame(id);
}

