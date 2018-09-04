#include "STPusherServerSessionTimeoutTask.h"
#include "STPusherLog.h"
#include "STPusherUtil.h"
#include "STPusherRTPSession.h"
#include "STPusherServerSession.h"
#include "SocketUtils.h"

STPusherServerSessionTimeoutTask::STPusherServerSessionTimeoutTask(void *r,void *p):
		STPusherObject(r,p),
		Task(),
		fSocket(NULL)
{
	
}
STPusherServerSessionTimeoutTask::~STPusherServerSessionTimeoutTask()
{

}
SInt64 STPusherServerSessionTimeoutTask::Run()
{
	EventFlags events = this->GetEvents();
	if ((events & Task::kKillEvent)){
		return -1;
	}
	
	#if 1
	/* 维持心跳 */
	if(!structureLiveFrame()){
		return 0;
	}
	#endif
	
	return 1000;
}
int STPusherServerSessionTimeoutTask::structureLiveFrame()
{
	OSMutexLocker theLocker(&fMutex);

	unsigned short userDataLen=htons(4);
	unsigned int frameId=htonl(CLIENT_LIVE_ID);
		
	char buffer[2048]={'\0'};

	/* 构建帧头 */
	buffer[0]=0x68;
	memcpy(&buffer[1],(char *)&userDataLen,sizeof(userDataLen));
	buffer[3]=0x68;
	
	/* 构建用户数据区 */
	memcpy(&buffer[4],(char *)&frameId,sizeof(frameId));
	
	/* 构建帧尾 */
	buffer[8]=checkSum((unsigned char *)&buffer[4],4);
	buffer[9]=0x16;
		
	UInt32 outLen=0;
	fSocket->Send(buffer, 10, &outLen);
	if(!fSocket->IsConnected()){
		return 0;
	}
	return 1;
}

int STPusherServerSessionTimeoutTask::structureLoginFrame(char *userName,char *passwd)
{
	OSMutexLocker theLocker(&fMutex);
	
	unsigned short userDataLen=htons(100);
	unsigned int frameId=htonl(USER_LOGIN_ID);
		
	char buffer[2048]={'\0'};
	
	/* 构建帧头 */
	buffer[0]=0x68;
	memcpy(&buffer[1],(char *)&userDataLen,sizeof(userDataLen));
	buffer[3]=0x68;
	
	/* 构建用户数据区 */
	memcpy(&buffer[4],(char *)&frameId,sizeof(frameId));
	memcpy(&buffer[8],userName,strlen(userName));
	memcpy(&buffer[72],passwd,strlen(passwd));
	
	/* 构建帧尾 */
	buffer[104]=checkSum((unsigned char *)&buffer[4],100);
	buffer[105]=0x16;
		
	UInt32 outLen=0;
	fSocket->Send(buffer, 106, &outLen);
	if(!fSocket->IsConnected()){
		return 0;
	}
	return 1;
}
int STPusherServerSessionTimeoutTask::structureTestFrame()
{
	OSMutexLocker theLocker(&fMutex);
	char buffer[2048]={'\0'};
	buffer[0]=0x68;
	buffer[1]=4;
	buffer[2]=0x68;
	int a=123456;
	memcpy(&buffer[3],(char *)&a,sizeof(a));
	buffer[7]=0x02;
	buffer[8]=0x16;
	
	UInt32 outLen=0;
	fSocket->Send(buffer, 9, &outLen);
	if(!fSocket->IsConnected()){
		return 0;
	}
	
	return 1;
}
int STPusherServerSessionTimeoutTask::structurePullStreamFrame(unsigned int userId)
{
	OSMutexLocker theLocker(&fMutex);

	if(userId==0){
		log_fprintf(stderr,"pull frame error userId is %d \n",userId);
		return 0;
	}

	char *localIp="0.0.0.0";
	unsigned short localPort=0;
	unsigned short userDataLen=htons(14);
	unsigned int frameId=htonl(STREAM_PULL_ID);
	
	char buffer[2048]={'\0'};

	unsigned lIp=htonl(ConvertStringToAddr(localIp));
	unsigned short lPort=htons(localPort);

	userId=htonl(userId);
	/* 构建帧头 */
	buffer[0]=0x68;
	memcpy(&buffer[1],(char *)&userDataLen,sizeof(userDataLen));
	buffer[3]=0x68;
	
	/* 构建用户数据区 */
	memcpy(&buffer[4],(char *)&frameId,sizeof(frameId));
	memcpy(&buffer[8],(char *)&userId,sizeof(userId));
	memcpy(&buffer[12],(char *)&lIp,sizeof(lIp));
	memcpy(&buffer[16],(char *)&lPort,sizeof(lPort));

	/* 构建帧尾 */
	buffer[18]=checkSum((unsigned char *)&buffer[4],14);
	buffer[19]=0x16;
	
	UInt32 outLen=0;
	fSocket->Send(buffer, 20, &outLen);
	if(!fSocket->IsConnected()){
		return 0;
	}
	return 1;
}
int STPusherServerSessionTimeoutTask::structurePushStreamFrame()
{
	OSMutexLocker theLocker(&fMutex);
	
	unsigned short userDataLen=htons(10);
	unsigned int frameId=htonl(STREAM_PUSH_ID);
	
	char buffer[2048]={'\0'};

	STPusherServerSession *theSession=(STPusherServerSession *)this->getParent();
	STPusherRTPSession *theRTPSession=theSession->getAudioRTPSession();

	unsigned lIp=htonl(theRTPSession->getSocket()->GetLocalAddr());
	unsigned short lPort=htons(theRTPSession->getSocket()->GetLocalPort());

	char ipBuf[32]={'\0'};
	UInt32ToStringIp(theRTPSession->getSocket()->GetLocalAddr(),ipBuf);
	log_fprintf(stderr,"GetLocalAddr() % u push Ip %s push Port %d \n",theRTPSession->getSocket()->GetLocalAddr(),ipBuf,lPort);
	/* 构建帧头 */
	buffer[0]=0x68;
	memcpy(&buffer[1],(char *)&userDataLen,sizeof(userDataLen));
	buffer[3]=0x68;

	/* 构建用户数据区 */
	memcpy(&buffer[4],(char *)&frameId,sizeof(frameId));
	memcpy(&buffer[8],(char *)&lIp,sizeof(lIp));
	memcpy(&buffer[12],(char *)&lPort,sizeof(lPort));
	
	/* 构建帧尾 */
	buffer[14]=checkSum((unsigned char *)&buffer[4],10);
	buffer[15]=0x16;
	
	UInt32 outLen=0;
	fSocket->Send(buffer, 16, &outLen);
	if(!fSocket->IsConnected()){
		return 0;
	}

	return 1;
}

int STPusherServerSessionTimeoutTask::structureRegisterUserFrame(char *userName,char *passwd)
{

	OSMutexLocker theLocker(&fMutex);

	unsigned short userDataLen=htons(100);
	unsigned int frameId=htonl(USER_REGISTER_ID);
	
	char buffer[2048]={'\0'};

	/* 构建帧头 */
	buffer[0]=0x68;
	memcpy(&buffer[1],(char *)&userDataLen,sizeof(userDataLen));
	buffer[3]=0x68;

	/* 构建用户数据区 */
	memcpy(&buffer[4],(char *)&frameId,sizeof(frameId));
	memcpy(&buffer[8],userName,strlen(userName));
	memcpy(&buffer[72],passwd,strlen(passwd));

	/* 构建帧尾 */
	buffer[104]=checkSum((unsigned char *)&buffer[4],100);
	buffer[105]=0x16;
	
	UInt32 outLen=0;
	fSocket->Send(buffer, 106, &outLen);
	if(!fSocket->IsConnected()){
		return 0;
	}

	return 1;
}
int STPusherServerSessionTimeoutTask::structureGetUserListFrame()
{
	
	OSMutexLocker theLocker(&fMutex);
	unsigned short userDataLen=htons(4);
	unsigned int frameId=htonl(USER_GET_USER_LIST);
			
	char buffer[2048]={'\0'};
	
	/* 构建帧头 */
	buffer[0]=0x68;
	memcpy(&buffer[1],(char *)&userDataLen,sizeof(userDataLen));
	buffer[3]=0x68;
		
	/* 构建用户数据区 */
	memcpy(&buffer[4],(char *)&frameId,sizeof(frameId));
		
	/* 构建帧尾 */
	buffer[8]=checkSum((unsigned char *)&buffer[4],4);
	buffer[9]=0x16;
			
	UInt32 outLen=0;
	fSocket->Send(buffer, 10, &outLen);
	if(!fSocket->IsConnected()){
		return 0;
	}

	return 1;
}
