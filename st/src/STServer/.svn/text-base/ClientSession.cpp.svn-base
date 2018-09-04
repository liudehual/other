#include "ClientSession.h"
#include "RTPSession.h"
#include "Log.h"
#include <stdio.h>
#include <stdlib.h>
#include "Util.h"
#include <arpa/inet.h>
#include "Server.h"
#include "UserAuthentication.h"
ClientSession::ClientSession(void *r,void *p):Object(r,p),
											Task(),
											fLiveState(1),
											fUserId(0),
											fGetNumbers(0),
											fUserListNumbers(0),
											fDataLen(0),
											fHandleDataLen(0)
{
	fElem.SetEnclosingObject(this);
	fSocket=new TCPSocket(this,Socket::kNonBlockingSocketType);
	fAudioSession=new RTPSession(this->getRoot(),this,AUDIO_TYPE);
	//fVideoSession=new RTPSession(this->getRoot(),this,VIDEO_TYPE);
}
ClientSession::~ClientSession()
{

}
SInt64 ClientSession::Run()
{
	EventFlags events = this->GetEvents();
	if ((events & Task::kKillEvent)){
		return -1;
	}
	
	char buffer[80*1024]={'\0'};
	UInt32 outLen=0;
	fSocket->Read(&buffer[0],80*1024,&outLen);
	if(!fSocket->IsConnected()){
		fLiveState=0;
		return 0;
	}
	
	log_fprintf(stderr,"outLen %d\n",outLen);
	for(int i=0;i<outLen;i++){
		log_fprintf(stderr,"%02X ",buffer[i]);
	}
	log_fprintf(stderr,"\n");

	this->parser(buffer, outLen);
	
	fSocket->RequestEvent(EV_RE);
	return 0;
}
int ClientSession::parser(char *buffer,int bufferLen)
{
	char *pos=buffer;
	char *end=buffer+bufferLen;
	char *start=buffer;
	log_fprintf(stderr,"end-pos %d\n",end-pos);
	pos--;
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
			case CLIENT_LIVE_ID:{ /* 心跳 */
				parserLiveFrame((char *)&pos[4],userDataLen);
				break;
			}           			
		}
  	}
}

int ClientSession::checkRight(char *buffer,int bufferLen)
{
	if(buffer[0]!=0x68 || buffer[3]!=0x68){
		#if 0
		log_fprintf(stderr,"buffer header flags != 0x68 \n");
		#endif
		return -1;
	}
	unsigned short userDataLen=*((unsigned short *)&buffer[1]);
	userDataLen=ntohs(userDataLen);
	log_fprintf(stderr,"userDataLen %d\n",userDataLen);
	char sum=checkSum((unsigned char *)&buffer[4],userDataLen);
	if(sum!=buffer[userDataLen+4]){
		#if 1
		log_fprintf(stderr,"sum error sum %d "
							"buffer[userDataLen+5] %d \n",
							sum,
							buffer[userDataLen+5]);
		#endif
		return -1;
	}
	if(buffer[userDataLen+5]!=0x16){
		#if 1
		log_fprintf(stderr,"buffer tail flag != 0x16 \n");
		#endif
		return -1;
	}
	#if 0
	log_fprintf(stderr,"This is a good frame \n");
	#endif
	return 1;
	
}
int ClientSession::parserLiveFrame(char *buffer,int bufferLen)
{
	unsigned frameId=*(unsigned *)&buffer[0];
	unsigned frame_id=ntohl(frameId);
	log_fprintf(stderr,"%08X \n",frame_id);
	return 1;
}
int ClientSession::parserLoginFrame(char *buffer,int bufferLen)
{
	unsigned frameId=*(unsigned *)&buffer[0];
	unsigned frame_id=ntohl(frameId);
	log_fprintf(stderr,"%08X \n",frame_id);

	char userName[64]={'\0'};
	char userPasswd[32]={'\0'};

	memcpy(userName,(char *)&buffer[4],64);
	memcpy(userPasswd,(char *)&buffer[68],32);

	log_fprintf(stderr,"register frame userName %s userPasswd %s \n",
						userName,
						userPasswd);


	Server *theServer=(Server *)this->getRoot();

	UserAuthentication *theAuth=theServer->getUserAuthentication();

	char result=theAuth->userLogin(userName,userPasswd);
	if(result==1){
		fUserId=theAuth->getUserId(userName);
	}else{
		fUserId=0;
	}
	 
	unsigned short userDataLen=htons(9);
		
	char resFrameBuffer[2048]={'\0'};

	/* 构建帧头 */
	resFrameBuffer[0]=0x68;
	memcpy(&resFrameBuffer[1],(char *)&userDataLen,sizeof(userDataLen));
	resFrameBuffer[3]=0x68;
	
	/* 构建用户数据区 */
	memcpy(&resFrameBuffer[4],(char *)&frameId,sizeof(frameId));

	resFrameBuffer[8]=result;
	
	unsigned userId=htonl(fUserId);
	memcpy(&resFrameBuffer[9],(char *)&userId,sizeof(userId));
	
	/* 构建帧尾 */
	resFrameBuffer[13]=checkSum((unsigned char *)&resFrameBuffer[4],9);
	resFrameBuffer[14]=0x16;
		
	UInt32 outLen=0;
	fSocket->Send(resFrameBuffer, 15, &outLen);
	if(!fSocket->IsConnected()){
		return 0;
	}
	
	return 1;

}

int ClientSession::parserLoginOutFrame(char *buffer,int bufferLen)
{
	/* do nothing */
	unsigned frameId=*(unsigned *)&buffer[0];
		unsigned frame_id=ntohl(frameId);
	log_fprintf(stderr,"%08X \n",frame_id);
	
	unsigned short userDataLen=htons(5);
		
	char resFrameBuffer[2048]={'\0'};

	/* 构建帧头 */
	resFrameBuffer[0]=0x68;
	memcpy(&resFrameBuffer[1],(char *)&userDataLen,sizeof(userDataLen));
	resFrameBuffer[3]=0x68;
	
	/* 构建用户数据区 */
	memcpy(&resFrameBuffer[4],(char *)&frameId,sizeof(frameId));
	resFrameBuffer[8]=1;

	
	/* 构建帧尾 */
	resFrameBuffer[9]=checkSum((unsigned char *)&resFrameBuffer[4],5);
	resFrameBuffer[10]=0x16;
		
	UInt32 outLen=0;
	fSocket->Send(resFrameBuffer, 11, &outLen);
	if(!fSocket->IsConnected()){
		return 0;
	}
	return 1;

}

int ClientSession::parserAddUserFrame(char *buffer,int bufferLen)
{
	unsigned frameId=*(unsigned *)&buffer[0];
	unsigned frame_id=ntohl(frameId);
	log_fprintf(stderr,"%08X \n",frame_id);

	return 1;

}

int ClientSession::parserDelUserFrame(char *buffer,int bufferLen)
{
	unsigned frameId=*(unsigned *)&buffer[0];
	unsigned frame_id=ntohl(frameId);
	log_fprintf(stderr,"%08X \n",frame_id);

	return 1;

}

int ClientSession::parserRegisterFrame(char *buffer,int bufferLen)
{
	unsigned frameId=*(unsigned *)&buffer[0];
	unsigned frame_id=ntohl(frameId);
	log_fprintf(stderr,"%08X \n",frame_id);


	
	char userName[64]={'\0'};
	char userPasswd[32]={'\0'};
	
	memcpy(userName,(char *)&buffer[4],64);
	memcpy(userPasswd,(char *)&buffer[68],32);
	log_fprintf(stderr,"register frame userName %s userPasswd %s \n",
						userName,
						userPasswd);
	Server *theServer=(Server *)this->getRoot();
	
	UserAuthentication *theAuth=theServer->getUserAuthentication();

	char theResult=theAuth->addUser(userName, userPasswd,Genernal_GROUP);

	unsigned short userDataLen=htons(5);
		
	char resFrameBuffer[2048]={'\0'};

	/* 构建帧头 */
	resFrameBuffer[0]=0x68;
	memcpy(&resFrameBuffer[1],(char *)&userDataLen,sizeof(userDataLen));
	resFrameBuffer[3]=0x68;
	
	/* 构建用户数据区 */
	memcpy(&resFrameBuffer[4],(char *)&frameId,sizeof(frameId));
	resFrameBuffer[8]=theResult;
	
	/* 构建帧尾 */
	resFrameBuffer[9]=checkSum((unsigned char *)&resFrameBuffer[4],5);
	resFrameBuffer[10]=0x16;
		
	UInt32 outLen=0;
	fSocket->Send(resFrameBuffer, 11, &outLen);
	if(!fSocket->IsConnected()){
		return 0;
	}
	return 1;

}

int ClientSession::parserGetUserListFrame(char *buffer,int bufferLen)
{
	unsigned frameId=*(unsigned *)&buffer[0];
	unsigned frame_id=ntohl(frameId);
	log_fprintf(stderr,"%08X \n",frame_id);

	Server *theServer=(Server *)this->getRoot();
	UserAuthentication *theAuth=theServer->getUserAuthentication();

	if(fUserListNumbers==0){
		theAuth->getAllUser(fUserListBuffer,68*10000, fUserListNumbers);
	}
	
	char resFrameBuffer[2048]={'\0'};
	unsigned short userDataLen=0;

	/* 构建帧体 */
	memcpy(&resFrameBuffer[4],(char *)&frameId,sizeof(frameId));
	if(fUserListNumbers<=20){
		memcpy(&resFrameBuffer[9],&fUserListBuffer[fGetNumbers*68],fUserListNumbers*68);	
		userDataLen=fUserListNumbers*68+5;
		resFrameBuffer[8]=1;
		fGetNumbers=0;
		fUserListNumbers=0;
	}else{
		memcpy(&resFrameBuffer[9],&fUserListBuffer[fGetNumbers*68],20*68);
		fGetNumbers+=20;
		fUserListNumbers-=20;
		userDataLen=20*68+5;
		resFrameBuffer[8]=0;
	}

	/* 构建帧尾 */
	resFrameBuffer[userDataLen+4]=checkSum((unsigned char *)&resFrameBuffer[4],userDataLen);
	resFrameBuffer[userDataLen+5]=0x16;

	/* 数据区长度不确定，最后构建帧头 */
	resFrameBuffer[0]=0x68;
	unsigned short dataLen=htons(userDataLen);
	memcpy(&resFrameBuffer[1],(char *)&dataLen,sizeof(dataLen));
	resFrameBuffer[3]=0x68;

	UInt32 outLen=0;
	fSocket->Send(resFrameBuffer, userDataLen+6, &outLen);
	if(!fSocket->IsConnected()){
		return 0;
	}
	return 1;

}

int ClientSession::parserPullStreamFrame(char *buffer,int bufferLen)
{
	unsigned frameId=*(unsigned *)&buffer[0];
	unsigned frame_id=ntohl(frameId);
	log_fprintf(stderr,"%08X \n",frame_id);


	/* 解析请求帧 */
	unsigned userId=*(unsigned *)&buffer[4];
	userId=ntohl(userId);

	unsigned clientIp=*(unsigned *)&buffer[8];
	clientIp=ntohl(clientIp);

	unsigned short clientPort=*(unsigned short*)&buffer[12];
	clientPort=ntohs(clientPort);

	int theErr=-1;
	
	log_fprintf(stderr,"%02X %02X add RTPSession \n",userId,fUserId);
	if(userId!=fUserId){
		Server *theServer=(Server *)this->getRoot();
		theErr=theServer->setDstRTPSession(this,userId);
	}
	/* 构建响应帧 */
	unsigned short userDataLen=htons(10);
		
	char resFrameBuffer[2048]={'\0'};

	/* 构建帧头 */
	resFrameBuffer[0]=0x68;
	memcpy(&resFrameBuffer[1],(char *)&userDataLen,sizeof(userDataLen));
	resFrameBuffer[3]=0x68;
	
	/* 构建用户数据区 */
	memcpy(&resFrameBuffer[4],(char *)&frameId,sizeof(frameId));
	unsigned serverIp=fSocket->GetLocalAddr();
	serverIp=htonl(serverIp);
	memcpy(&resFrameBuffer[8],(char *)&serverIp,sizeof(serverIp));

	unsigned short serverPort=fAudioSession->getSocket()->GetLocalPort();
	serverPort=htons(serverPort);
	memcpy(&resFrameBuffer[12],(char *)&serverPort,sizeof(serverPort));
	
	/* 构建帧尾 */
	resFrameBuffer[14]=checkSum((unsigned char *)&resFrameBuffer[4],10);
	resFrameBuffer[15]=0x16;
		
	UInt32 outLen=0;
	fSocket->Send(resFrameBuffer, 16, &outLen);
	if(!fSocket->IsConnected()){
		return 0;
	}
	return 1;
}

int ClientSession::parserPushStreamFrame(char *buffer,int bufferLen)
{
	unsigned frameId=*(unsigned *)&buffer[0];
	unsigned frame_id=ntohl(frameId);
	log_fprintf(stderr,"%08X \n",frame_id);


	/* 解析请求帧 */

	unsigned clientIp=*(unsigned *)&buffer[4];
	clientIp=ntohl(clientIp);

	unsigned short clientPort=*(unsigned short*)&buffer[8];
	clientPort=ntohs(clientPort);


		/* 构建响应帧 */
	unsigned short userDataLen=htons(10);
		
	char resFrameBuffer[2048]={'\0'};
	/* 构建帧头 */
	resFrameBuffer[0]=0x68;
	memcpy(&resFrameBuffer[1],(char *)&userDataLen,sizeof(userDataLen));
	resFrameBuffer[3]=0x68;
	
	/* 构建用户数据区 */
	memcpy(&resFrameBuffer[4],(char *)&frameId,sizeof(frameId));
	unsigned serverIp=fSocket->GetLocalAddr();
	serverIp=htonl(serverIp);
	memcpy(&resFrameBuffer[8],(char *)&serverIp,sizeof(serverIp));

	unsigned short serverPort=fAudioSession->getSocket()->GetLocalPort();
	serverPort=htons(serverPort);
	memcpy(&resFrameBuffer[12],(char *)&serverPort,sizeof(serverPort));
	
	/* 构建帧尾 */
	resFrameBuffer[14]=checkSum((unsigned char *)&resFrameBuffer[4],10);
	resFrameBuffer[15]=0x16;
		
	UInt32 outLen=0;
	fSocket->Send(resFrameBuffer, 16, &outLen);
	if(!fSocket->IsConnected()){
		return 0;
	}
	return 1;
}

