#ifndef __SERVER_SESSION_H__
#define __SERVER_SESSION_H__
#include "STPusherObject.h"
#include "Task.h"
#include "TCPSocket.h"
#include "STPusherAPI.h"
#include "OSQueue.h"

class UserInfoElem
{
	public:
		UserInfoElem()
		{
			memset(fUserName,'\0',64);
			fUserId=0;
		}
		~UserInfoElem(){}
		OSQueueElem *getElem(){return &fElem;}
		char *getUserName(){return fUserName;}
		unsigned getUserId(){return fUserId;}
		int setUserInfo(char *userName,unsigned uId)
		{
			if(userName==NULL 
				|| strlen(userName)==0 
				|| uId==0
				|| strlen(userName)>64){
				return -1;
			}
			memcpy(fUserName,userName,strlen(userName));
			fUserId=uId;

			return 1;
			
		}
		
	private:
		OSQueueElem fElem;

		char fUserName[64];
		unsigned fUserId;
};

class STPusherRTPSession;
class STPusherServerSessionTimeoutTask;

struct UserListElem
{
	public:
	UserListElem(){fElem.SetEnclosingObject(this);}
	char fUserName[64];
	unsigned fUserId;
	OSQueueElem fElem;
};
class STPusherServerSession:public STPusherObject,public Task
{
	public:
		STPusherServerSession(void *r,void *p);
		~STPusherServerSession();
		int connectToServer(char *ip,unsigned short port);
		virtual SInt64 Run();
		int sendData(Frame tFrame);
		STPusherRTPSession *getAudioRTPSession(){return fAudioRTPSession;}
		STPusherRTPSession *getVideoRTPSession(){return fVideoRTPSession;}
		STPusherServerSessionTimeoutTask *getTimeoutTask(){return fTimeoutTask;}
		int checkRight(char *buffer,int bufferLen);
		int parser(char *buffer,int bufferLen);

		int parserLoginFrame(char *buffer,int bufferLen);
		
		int parserLoginOutFrame(char *buffer,int bufferLen);
		
		int parserAddUserFrame(char *buffer,int bufferLen);
		
		int parserDelUserFrame(char *buffer,int bufferLen);
		
		int parserRegisterFrame(char *buffer,int bufferLen);
		
		int parserGetUserListFrame(char *buffer,int bufferLen);
		
		int parserPullStreamFrame(char *buffer,int bufferLen);
		
		int parserPushStreamFrame(char *buffer,int bufferLen);
		unsigned getRemoteAddr(){return fRemoteAddr;}
		unsigned short getRemoteAudioPort(){return fRemoteAudioPort;}
		unsigned short getRemoteVideoPort(){return fRemoteVideoPort;}

		unsigned getUserID(char *userName);
	private:
		STPusherRTPSession *fAudioRTPSession;
		STPusherRTPSession *fVideoRTPSession;
		TCPSocket *fSocket;
		STPusherServerSessionTimeoutTask *fTimeoutTask;

		OSQueue fUserInfoList;
		OSMutex fUserListMutex;
		unsigned fUserID;

		unsigned fRemoteAddr;
		unsigned fRemoteAudioPort;
		unsigned fRemoteVideoPort;
};

#endif
