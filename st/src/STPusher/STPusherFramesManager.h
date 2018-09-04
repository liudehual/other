/*
	frame manager 2.0
	
*/

#ifndef _ST_PUSHER_FramesManager_H_
#define _ST_PUSHER_FramesManager_H_
#include <stdio.h>
#include <stdlib.h>
#include "STPusherAPI.h"

class OSMutex;

/*
	�ô������������H264FrameManager�� �Ѳ⣬����
	ԭ��
		CacheManager ����readQueue
	new Code
	add by gct 1608091706
*/
class FrameContainer
{
	public:
		FrameContainer(int frameSize);
		~FrameContainer();
		void cleanContainer();
		void setFreeStat(bool tFree){mFree=tFree;}
		bool getFreeStat(){return mFree;}
		int writeData(Frame *tFrame);
		int readData(Frame *tFrame);
		int getMediaType(){return f->type;}
	private:
		Frame *f;
		int memoryLen; /* �ڴ��ܳ��� */
		bool mFree;
		
};

class CacheManager
{
	public:
		CacheManager(int frameSize,int queueLen);
		~CacheManager();
		int writeData(Frame *tFrame);
		int readData(Frame *tFrame);
		int findMediaType();
		void swapQueue();
		void cleanCache();
	private:
		FrameContainer **readQueue;
		int readQueueLen;
		FrameContainer **writeQueue;
		int writeQueueLen;
		OSMutex *mutex;                 //ͬ����
		bool firstRead;
};
#endif

