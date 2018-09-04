#ifndef __ST_PUSHER_SERVER_SESSION_TIMEOUT_TASK_H__
#define __ST_PUSHER_SERVER_SESSION_TIMEOUT_TASK_H__
#include "STPusherObject.h"
#include "Task.h"
#include "TCPSocket.h"
#include "OSMutex.h"
#include <vector>
#define USER_LOGIN_ID    	0x00000001          		/* 用户登录 */
#define USER_LOGIN_OUT_ID	0x00000002          		/* 用户登出 */
#define USER_ADD_ID			0x00000003           		/* 添加用户 */
#define USER_DEL_ID			0x00000004                  /* 删除用户 */
#define USER_REGISTER_ID	0x00000005      			/* 注册用户 */
#define USER_GET_USER_LIST	0x00000006       			/* 获取用户列表 */


#define STREAM_PULL_ID  	0x00000010					/* 拉流 */
#define STREAM_PUSH_ID 		0x00000011               	/* 推流 */
	
#define CLIENT_LIVE_ID  	0x00000020              	/* 心跳 */

struct RequestFrame
{
	char buffer[2048];
	int dataLen;
	int delayTime; /* 等待时间 */
};


class STPusherServerSessionTimeoutTask:public STPusherObject,public Task
{
	public:
		STPusherServerSessionTimeoutTask(void *r,void *p);
		~STPusherServerSessionTimeoutTask();
		void setSocket(TCPSocket *tSocket){fSocket=tSocket;}
		virtual SInt64 Run();
		int structureTestFrame();
		int structureLiveFrame();
		int structureLoginFrame(char *userName,char *passwd);
		int structurePullStreamFrame(unsigned int userId);
		int structurePushStreamFrame();
		int structureRegisterUserFrame( char *userName,char *passwd);
		int structureGetUserListFrame();
	private:
		TCPSocket *fSocket;
		OSMutex fMutex;
		std::vector<RequestFrame *> fRequestFrameQueue;
};
#endif
