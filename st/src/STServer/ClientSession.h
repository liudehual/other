#ifndef __CLIENT_SESSION_H__
#define __CLIENT_SESSION_H__
#include "Object.h"
#include "Task.h"
#include "TCPSocket.h"

#include "OSQueue.h"

#define USER_LOGIN_ID    	0x00000001          		/* 用户登录 */
#define USER_LOGIN_OUT_ID	0x00000002          		/* 用户登出 */
#define USER_ADD_ID			0x00000003           		/* 添加用户 */
#define USER_DEL_ID			0x00000004                  /* 删除用户 */
#define USER_REGISTER_ID	0x00000005      			/* 注册用户 */
#define USER_GET_USER_LIST	0x00000006       			/* 获取用户列表 */


#define STREAM_PULL_ID  	0x00000010					/* 拉流 */
#define STREAM_PUSH_ID 		0x00000011               	/* 推流 */
	
#define CLIENT_LIVE_ID  	0x00000020              	/* 心跳 */


class RTPSession;
class ProtocolParser;
class ClientSession:public Object,public Task
{
	public:
		ClientSession(void *r,void *p);
		~ClientSession();
		virtual SInt64 Run();
		TCPSocket*GetSocket(){ return fSocket; }
		OSQueueElem *getElem(){return &fElem;}
		int getLiveState(){return fLiveState;}
		int getUserID(){return fUserId;}
		int parser(char *buffer,int bufferLen);
		int checkRight(char *buffer,int bufferLen);

		int parserLiveFrame(char *buffer,int bufferLen);
		
		int parserLoginFrame(char *buffer,int bufferLen);
		
		int parserLoginOutFrame(char *buffer,int bufferLen);
		
		int parserAddUserFrame(char *buffer,int bufferLen);
		
		int parserDelUserFrame(char *buffer,int bufferLen);
		
		int parserRegisterFrame(char *buffer,int bufferLen);
		
		int parserGetUserListFrame(char *buffer,int bufferLen);
		
		int parserPullStreamFrame(char *buffer,int bufferLen);
		
		int parserPushStreamFrame(char *buffer,int bufferLen);

		RTPSession *getAudioRTPSession(){return fAudioSession;}
		RTPSession *getVideoRTPSession(){return fVideoSession;}
	private:
		TCPSocket *fSocket;
		
		OSQueueElem fElem;

		RTPSession *fAudioSession;
		RTPSession *fVideoSession;

		int fLiveState;

		unsigned fUserId;

		/* 获取用户列表的一些辅助参数 */
		int fGetNumbers; /*已发送个数 */
		char fUserListBuffer[68*10000]; /*最大一万个用户 */
		int fUserListNumbers;/* 用户列表缓冲区中的用户个数 */


		/* 协议解析需要用到的一些参数 */
		unsigned fDataLen;            /* 缓冲区内有效数据的总长度 */
		unsigned fHandleDataLen;	   /* 已处理的数据长度 */

		
};


#endif
