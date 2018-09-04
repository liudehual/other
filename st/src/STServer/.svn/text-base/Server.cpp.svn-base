#include "Server.h"
#include "ConfigFileParser.h"
#include "LogSession.h"
#include "UserAuthentication.h"
#include "Log.h"
#include "CommonListener.h"
#include "Util.h"
#include "ClientSession.h"
#include "OSQueue.h"
#include "CommonListener.h"
#include "RTPSession.h"
Server::Server():Object(this,this),Task(),fNetInfoArray(NULL)
{

	/* 初始化log */
	initLog(this);

	fConfParser=new ConfigFileParser(this,this);
	fLogSession=new LogSession(this,this);
	fUserAuthentication=new UserAuthentication(this,this);
}

Server::~Server()
{

}

SInt64 Server::Run()
{
	EventFlags events = this->GetEvents();
	if ((events & Task::kKillEvent)){
		return -1;
	}
	{
		OSMutexLocker theLocker(&fClientSessionQueueMutex);
   		for (OSQueueIter theIter(&fClientSessionQueue); !theIter.IsDone(); theIter.Next()) {
        	OSQueueElem *theElem = theIter.GetCurrent();;

			ClientSession* theDeadClientSession=(ClientSession *)theElem->GetEnclosingObject();
			if(!theDeadClientSession->getLiveState()){
				theElem->Remove();
				theDeadClientSession->Signal(Task::kKillEvent);
				break;
			}else{
			/* we can do something */
			}
    	}
	}
	for (OSQueueIter theIter(&fCommonListenerQueue); !theIter.IsDone(); theIter.Next()) {
        OSQueueElem *theElem = theIter.GetCurrent();;

		CommonListener* theDeadClientSession=(CommonListener *)theElem->GetEnclosingObject();
		/* we can do something */
     }

	return 1000;
}

ConfigFileParser *Server::getConfigFileParser()
{
	return fConfParser;
}

int Server::startServer()
{
	this->Signal(Task::kTimeoutEvent);
	fLogSession->Signal(Task::kTimeoutEvent);
}

#define DEFAULT_SERVER_PORT 13339

int Server::initialize(UInt16 inPortOverride)
{
  	fNetInfoArray=GetNetInterfaceInfo();
  	if(!fNetInfoArray){
		return -1;
  	}
	for(int i=0;i<arrayNums;i++){
		if(fNetInfoArray[i]==NULL){
			continue;
  		}
  		if(!strcmp(fNetInfoArray[i]->name,"lo")){
			continue;
  		}
  		log_fprintf(stderr, "name: %s "
  							"ip: %s "
  							"mac: %s "
  							"mask: %s\n",
							fNetInfoArray[i]->name,
							fNetInfoArray[i]->ip,
							fNetInfoArray[i]->mac,
							fNetInfoArray[i]->netmask);
		if(inPortOverride==0){
			inPortOverride=DEFAULT_SERVER_PORT;
		}
		CommonListener *listener=new CommonListener(this,this);
		int err =listener->Initialize(ConvertStringToAddr(fNetInfoArray[i]->ip),inPortOverride);
		listener->RequestEvent(EV_RE);
		log_fprintf(stderr,"listener init state %d\n",err);
		fCommonListenerQueue.EnQueue(listener->getElem());
	}
	return 1;
}
int Server::addRTPSessionToQueue(void *session,unsigned dstUserId)
{
	ClientSession *theDstClientSession=(ClientSession *)session;

	OSMutexLocker theLocker(&fClientSessionQueueMutex);
	for (OSQueueIter theIter(&fClientSessionQueue); !theIter.IsDone(); theIter.Next()) {
		OSQueueElem *theElem = theIter.GetCurrent();;
	
		ClientSession* theClientSession=(ClientSession *)theElem->GetEnclosingObject();
		if(theClientSession->getUserID()==dstUserId){
			/* 检查RTPSession任务队列长度，不为 0 则说明有客户端在对讲 */
			theClientSession->getAudioRTPSession()->addRtpSessionToQueue(theDstClientSession->getAudioRTPSession());
			return 1;
		}
	}
	return 1;
}
int Server::delRTPSessionFromQueue(void *session)
{
	OSMutexLocker theLocker(&fClientSessionQueueMutex);
	for (OSQueueIter theIter(&fClientSessionQueue); !theIter.IsDone(); theIter.Next()) {
		OSQueueElem *theElem = theIter.GetCurrent();;
	
		ClientSession* theClientSession=(ClientSession *)theElem->GetEnclosingObject();
		
		ClientSession *theDstClientSession=(ClientSession *)session;
		theClientSession->getAudioRTPSession()->delRTPSessionFromQueue(theDstClientSession->getAudioRTPSession());
	}
	return 1;
}
int Server::setDstRTPSession(void *session,unsigned dstUserId)
{

	log_fprintf(stderr,"Server::setDstRTPSession \n");
	ClientSession *theDstClientSession=(ClientSession *)session;

	OSMutexLocker theLocker(&fClientSessionQueueMutex);
	for (OSQueueIter theIter(&fClientSessionQueue); !theIter.IsDone(); theIter.Next()) {
		OSQueueElem *theElem = theIter.GetCurrent();;
	
		ClientSession* theClientSession=(ClientSession *)theElem->GetEnclosingObject();
		/* 
			此处可能会有非常复杂的任务添加规则。
			可能的规则如下:
			1.是否是管理员，如果是则无条件置换
			2.检查是否在组对话中，如果是直接返回，如果不是检查3步骤
			3.是否是普通用户，
		*/
		if(theClientSession->getUserID()==dstUserId){
			/* 检查RTPSession任务队列长度，不为 0 则说明有客户端在对讲 */
			theClientSession->getAudioRTPSession()->setDstRTPSession(theDstClientSession->getAudioRTPSession());
			theDstClientSession->getAudioRTPSession()->setDstRTPSession(theClientSession->getAudioRTPSession());
			return 1;
		}
	}
	return 1;
}

