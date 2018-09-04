#include "STPusherServerSession.h"
#include "STPusherRTPSession.h"
#include "SocketUtils.h"
#include "STPusherServerSessionTimeoutTask.h"
#include "STPusherLog.h"
#include "STPusherServerSessionTimeoutTask.h"
#include "STPusherUtil.h"
STPusherServerSession::STPusherServerSession(void *r,void *p):STPusherObject(r,p),Task(),
																	fRemoteAddr(0),
																	fRemoteAudioPort(0),
																	fRemoteVideoPort(0)
												
{
	fSocket=new TCPSocket(this,Socket::kNonBlockingSocketType);
	fSocket->Open();
	fSocket->Bind(0,0);
	fAudioRTPSession=new STPusherRTPSession(this->getRoot(),this,AUDIO_TYPE);
	fVideoRTPSession=new STPusherRTPSession(this->getRoot(),this,VIDEO_TYPE);
	fTimeoutTask=new STPusherServerSessionTimeoutTask(this->getRoot(),this);

	fAudioRTPSession->Signal(Task::kStartEvent);
	fVideoRTPSession->Signal(Task::kStartEvent);
}
STPusherServerSession::~STPusherServerSession()
{
	fAudioRTPSession->Signal(Task::kKillEvent);
	fVideoRTPSession->Signal(Task::kKillEvent);
	fTimeoutTask->Signal(Task::kKillEvent);
}
SInt64 STPusherServerSession::Run()
{
	EventFlags events = this->GetEvents();
	if ((events & Task::kKillEvent)){
		return -1;
	}

	unsigned char buffer[80*1024]={'\0'};
	UInt32 outLen=0;
	fSocket->Read(buffer, 80*1024, &outLen);
	if(!fSocket->IsConnected()){
		return 0;
	}
	for(int i=0;i<outLen;i++){
		log_fprintf(stderr,"%02X ",buffer[i]);
	}

	this->parser((char *)buffer,(int)outLen);
	
	fSocket->RequestEvent(EV_RE);
	return 0;
}
int STPusherServerSession::connectToServer(char *ip,unsigned short port)
{
	//log_fprintf(stderr,"ip %s port %d \n",ip,port);
	int theErr=fSocket->Connect(SocketUtils::ConvertStringToAddr(ip),port);
	//log_fprintf(stderr,"theErr %d OS_NoErr %d \n",theErr,OS_NoErr);
	if(!fSocket->IsConnected()){
		return 0;
	}
	
	fTimeoutTask->setSocket(fSocket);
	fSocket->RequestEvent(EV_RE);
	fTimeoutTask->Signal(Task::kStartEvent);
	return 1;
}
int STPusherServerSession::sendData(Frame tFrame)
{
	if(tFrame.type==AUDIO_TYPE){
		fAudioRTPSession->sendData(tFrame);
	}
	if(tFrame.type==VIDEO_TYPE){
		fVideoRTPSession->sendData(tFrame);
	}
	return 0;
}

int STPusherServerSession::checkRight(char *buffer,int bufferLen)
{
	if(buffer[0]!=0x68 || buffer[3]!=0x68){
		#if 0
		log_fprintf(stderr,"buffer header flags != 0x68 \n");
		#endif
		return -1;
	}
	unsigned short userDataLen=*((unsigned short *)&buffer[1]);
	userDataLen=ntohs(userDataLen);

	char sum=checkSum((unsigned char *)&buffer[4],userDataLen);
	if(sum!=buffer[userDataLen+4]){
		#if 0
		log_fprintf(stderr,"sum error sum %d "
							"buffer[userDataLen+5] %d \n",
							sum,
							buffer[userDataLen+5]);
		#endif
		return -1;
	}
	if(buffer[userDataLen+5]!=0x16){
		#if 0
		log_fprintf(stderr,"buffer tail flag != 0x16 \n");
		#endif
		return -1;
	}
	#if 0
	log_fprintf(stderr,"This is a good frame \n");
	#endif
	return 1;
	
}
int STPusherServerSession::parser(char *buffer,int bufferLen)
{
	char *pos=buffer;
	char *end=buffer+bufferLen;
	char *start=buffer;
	//log_fprintf(stderr,"end-pos %d\n",end-pos);
	pos--; /* 后移一个字节，确保我们能从头读取数据 */
	while(pos!=end){
		pos++;
		int theErr=checkRight(pos, end-pos);
		if(theErr==-1){
			continue;
		}
		unsigned frameId=*(unsigned *)&pos[4];
		frameId=ntohl(frameId);
	
		unsigned short userDataLen=*(unsigned short *)&pos[1];
		userDataLen=ntohs(userDataLen);

		switch(frameId){
 			case USER_LOGIN_ID:{/* 用户登录 */
				parserLoginFrame((char *)&pos[4],userDataLen);
				break;
			}	          		
			case USER_LOGIN_OUT_ID:{/* 用户登出 */
				parserLoginOutFrame((char *)&pos[4],userDataLen);
				break;
			}      		
			case USER_ADD_ID:{ /* 添加用户 */
				parserAddUserFrame((char *)&pos[4],userDataLen);
				break;
			}         		
			case USER_DEL_ID:{ /* 删除用户 */
				parserDelUserFrame((char *)&pos[4],userDataLen);
				break;
			}               
			case USER_REGISTER_ID:{ /* 注册用户 */
				parserRegisterFrame((char *)&pos[4],userDataLen);
				break;
			}		
			case USER_GET_USER_LIST:{ /* 获取用户列表 */
				parserGetUserListFrame((char *)&pos[4],userDataLen);
				break;
			}		
			case STREAM_PULL_ID:{ /* 拉流 */
				parserPullStreamFrame((char *)&pos[4],userDataLen);
				break;
			}			
			case STREAM_PUSH_ID:{ /* 推流 */
				parserPushStreamFrame((char *)&pos[4],userDataLen);
				break;
			}     	
		}
  	}
}
int STPusherServerSession::parserLoginFrame(char *buffer,int bufferLen)
{
	unsigned frameId=*(unsigned *)&buffer[0];
	unsigned frame_id=ntohl(frameId);
	//log_fprintf(stderr,"%08X \n",frame_id);

	char loginResult=buffer[4];
	unsigned userID=*(unsigned *)&buffer[5];
	fUserID=userID=ntohl(userID);
	//log_fprintf(stderr,"usrId %08X \n",userID);
	
	return 1;
}

int STPusherServerSession::parserLoginOutFrame(char *buffer,int bufferLen)
{
	unsigned frameId=*(unsigned *)&buffer[0];
	unsigned frame_id=ntohl(frameId);
	//log_fprintf(stderr,"%08X \n",frame_id);

	return 1;
}

int STPusherServerSession::parserAddUserFrame(char *buffer,int bufferLen)
{
	unsigned frameId=*(unsigned *)&buffer[0];
	unsigned frame_id=ntohl(frameId);
	//log_fprintf(stderr,"%08X \n",frame_id);

	return 1;
}

int STPusherServerSession::parserDelUserFrame(char *buffer,int bufferLen)
{
	unsigned frameId=*(unsigned *)&buffer[0];
	unsigned frame_id=ntohl(frameId);
	//log_fprintf(stderr,"%08X \n",frame_id);

	return 1;
}

int STPusherServerSession::parserRegisterFrame(char *buffer,int bufferLen)
{
	unsigned frameId=*(unsigned *)&buffer[0];
	unsigned frame_id=ntohl(frameId);
	log_fprintf(stderr,"%08X \n",frame_id);
	
	char result=buffer[4];
	if(result==0){
		//log_fprintf(stderr,"register error.name or password is error \n");
	}
	if(result==1){
		//log_fprintf(stderr,"register succeed \n");
	}
	if(result==2){
		//log_fprintf(stderr,"the user have registed \n");
	}
	return 1;
}

int STPusherServerSession::parserGetUserListFrame(char *buffer,int bufferLen)
{
	unsigned frameId=*(unsigned *)&buffer[0];
	unsigned frame_id=ntohl(frameId);
	//log_fprintf(stderr,"%08X \n",frame_id);

	char getState=buffer[4];
	//log_fprintf(stderr,"getState %d \n",getState);

	unsigned short userDataLen=bufferLen;
	//log_fprintf(stderr,"getUserListFrame userDataLen %d \n",userDataLen);

	int fListElemNums=(bufferLen-5)/68;
	char *pos=&buffer[5];

	OSMutexLocker theLocker(&fUserListMutex);
	for(int i=0;i<fListElemNums;i++){
		UserListElem *theElem=new UserListElem;
		memcpy(theElem->fUserName,pos,64);
		unsigned tUserId=*(unsigned *)&pos[64];
		theElem->fUserId=ntohl(tUserId);
		if(fUserID==tUserId){ /* 只获取别人的ID号 */
			delete theElem;
			continue;
		}
		fUserInfoList.EnQueue(&theElem->fElem);
		log_fprintf(stderr,"-----> UserName %s UserId %08X \n",theElem->fUserName,theElem->fUserId);
		pos+=68;
	}

	/* 接收未完成 */
	if(!getState){
		this->getTimeoutTask()->structureGetUserListFrame();
	}
	return 1;

}

int STPusherServerSession::parserPullStreamFrame(char *buffer,int bufferLen)
{
	unsigned frameId=*(unsigned *)&buffer[0];
	unsigned frame_id=ntohl(frameId);
	//log_fprintf(stderr,"%08X \n",frame_id);

	return 1;
}

int STPusherServerSession::parserPushStreamFrame(char *buffer,int bufferLen)
{
	unsigned frameId=*(unsigned *)&buffer[0];
	unsigned frame_id=ntohl(frameId);
	//log_fprintf(stderr,"%08X \n",frame_id);

	unsigned serverIp=*(unsigned *)&buffer[4];
	serverIp=ntohl(serverIp);

	unsigned short serverPort=*(unsigned short *)&buffer[8];
	serverPort=ntohs(serverPort);
	//char ipBuf[32]={'\0'};
	//UInt32ToStringIp(serverIp,ipBuf);
	//log_fprintf(stderr,"-----> serverIp %s serverPort %u\n",ipBuf,serverPort);

	fRemoteAudioPort=serverPort;
	fRemoteAddr=serverIp;
	
	fAudioRTPSession->startPump();
	return 1;
}
unsigned STPusherServerSession::getUserID(char *userName)
{
	OSMutexLocker theLocker(&fUserListMutex);
	for (OSQueueIter theIter(&fUserInfoList); !theIter.IsDone(); theIter.Next()) {
		OSQueueElem *theElem = theIter.GetCurrent();;
		UserListElem * theListElem=(UserListElem *)theElem->GetEnclosingObject();
		if(!strcmp(userName,theListElem->fUserName)){
			log_fprintf(stderr,"UserName %s %02X \n",theListElem->fUserName,theListElem->fUserId);
			return theListElem->fUserId;
		}
	}
	return 0;
}

