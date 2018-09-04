#include "STPusher.h"
#include "STPusherLogSession.h"
#include "STPusherServerSession.h"
#include "STPusherLogSession.h"
#include "STPusherServerSession.h"
#include "STPusherLog.h"
#include "STPusherServerSessionTimeoutTask.h"
STPusher::STPusher(callBackFunc func):STPusherObject(this,this),
											Task(),
											fDataCallBack(func),
											fIsConnected(false)
{
	Info **fNetInfoArray=GetNetInterfaceInfo();
	memset(fLocalIp,'\0',sizeof(fLocalIp));
	for(int i=0;i<arrayNums;i++){
		if(fNetInfoArray[i]==NULL){
			continue;
  		}
  		if(!strcmp(fNetInfoArray[i]->name,"lo")){
			continue;
  		}
		memcpy(fLocalIp,fNetInfoArray[i]->ip,strlen(fNetInfoArray[i]->ip));
		break;
	}
	
	initLog(this);
	fLogSession=new STPusherLogSession(this->getRoot(),this);
	fServerSession=new STPusherServerSession(this->getRoot(),this);
}
											
STPusher::~STPusher()
{
	fLogSession->Signal(Task::kKillEvent);
	fServerSession->Signal(Task::kKillEvent);
}

SInt64 STPusher::Run()
{
	EventFlags events = this->GetEvents();
	if ((events & Task::kKillEvent)){
		return -1;
	}

	return 0;
}

int STPusher::connectToServer(char *serverIp,unsigned short serverPort)
{
	if(fServerSession->connectToServer(serverIp, serverPort)){
		fIsConnected=true;
		return 1;
	}
	return 0;
}
int STPusher::sendData(Frame tFrame)
{
	if(!fIsConnected){
		return 0;
	}
	fServerSession->sendData(tFrame);
	return 1;
}
int STPusher::loginToServer(char *name,char *passwd)
{
	if(!fIsConnected){
		return 0;
	}
	return fServerSession->getTimeoutTask()->structureLoginFrame(name,passwd);
}
int STPusher::registerToServer(char *name,char *passwd)
{
	if(!fIsConnected){
		return 0;
	}
	return fServerSession->getTimeoutTask()->structureRegisterUserFrame(name,passwd);
}
int STPusher::getUserList()
{
	if(!fIsConnected){
		return 0;
	}
	return fServerSession->getTimeoutTask()->structureGetUserListFrame();
}
int STPusher::startPushFrame()
{
	if(!fIsConnected){
		return 0;
	}
	
	return fServerSession->getTimeoutTask()->structurePushStreamFrame();
}
int STPusher::startPullFrame(unsigned id)
{
		if(!fIsConnected){
		return 0;
	}
	
	return fServerSession->getTimeoutTask()->structurePullStreamFrame(id);
}

unsigned STPusher::getUserID(char *userName)
{
	return fServerSession->getUserID(userName);
}

