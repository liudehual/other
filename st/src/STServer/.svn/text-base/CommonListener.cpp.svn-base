#include "CommonListener.h"
#include "TCPSocket.h"
#include "ClientSession.h"
#include "Server.h"
#include "Log.h"
CommonListener::CommonListener(void *r,void *p):Object(r,p),TCPListenerSocket()
{

}
CommonListener::~CommonListener() 
{

}
        
Task *CommonListener::GetSessionTask(TCPSocket** outSocket)
{
	ClientSession* theTask = new ClientSession(this->getRoot(),this->getRoot());
	Server *theServer=(Server *)this->getRoot();
	theServer->getClientSessionQueue()->EnQueue(theTask->getElem());
    *outSocket = theTask->GetSocket();
	log_fprintf(stderr,"Create ClientSession Succeed \n");
	return theTask;
}
