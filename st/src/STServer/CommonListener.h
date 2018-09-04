#ifndef __COMMON_LISTENER_H__
#define __COMMON_LISTENER_H__
#include "Task.h"
#include "Object.h"
#include "TCPListenerSocket.h"
#include "OSQueue.h"

class CommonListener:public Object,public TCPListenerSocket
{
	public:
        CommonListener(void *r,void *p);
        virtual ~CommonListener();
        virtual Task*   GetSessionTask(TCPSocket** outSocket);
		OSQueueElem *getElem(){return &fElem;}
	private:
		OSQueueElem fElem;
 };

#endif
