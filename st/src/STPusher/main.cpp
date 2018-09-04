#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h> 

#include "STPusherAPI.h"
#include "audio_decode.h"
#include "audio_read.h"


extern "C"{  
#include "libavformat/avformat.h"  
#include "libavcodec/avcodec.h"  
#include "libavutil/avutil.h"  
#include "libswscale/swscale.h"  
#include "libavformat/avio.h"  
#include "libavutil/frame.h"
#include "SDL/SDL.h"  
}  


#define BUF_SIZE 4096 * 500  

unsigned char audioDataBuffer[4*1024]={'\0'};
unsigned char videoDataBuffer[2*1024*1024]={'\0'};

int getData(Frame tFrame)
{
	//fprintf(stderr,"type %d frameLen %d \n",tFrame.type,tFrame.bufferLen);

	/* 收到数据后请立即拷贝到自己的缓冲区中 */
	adtsMutex.Lock();
	if(tFrame.type==AUDIO_TYPE){
		memcpy(adtsFrameBuf,tFrame.buffer,tFrame.bufferLen);
		adtsFrameLen=tFrame.bufferLen;
	}
	adtsMutex.Unlock();
	if(tFrame.type==VIDEO_TYPE){
		memcpy(videoDataBuffer,tFrame.buffer,tFrame.bufferLen);
	}
	return 1;
}
void usage()
{	
	fprintf(stderr,"./STPusher user_name user_passwd dst_user_name aac_file_name \n");
	return;
}
int main(int argc,char *argv[])
{	
	if(argc<5){
		usage();
		exit(0);
	}
	STPusher_Init(getData);
	STPusher_connect("192.168.8.105",12345,"", "");

	usleep(1000*1000);
	STPusher_RegisterToServer(argv[1],argv[2]);

	STPusher_loginToServer(argv[1],argv[2]);

	/* 程序必须要先推流 */
	STPusher_StartPushFrame();

	fprintf(stderr,"Hello AudioPusher \n");

	pthread_t thread_read;
	pthread_create(&thread_read,NULL,read_aac,(void *)argv[4]);


	
	usleep(1000*1000*10);
	STPusher_GetUserList();
	usleep(1000*1000*3);
	unsigned uId=STPusher_GetUerID(argv[3]);

	fprintf(stderr,"--------->%08X \n",uId);
	STPusher_StartPullFrame(uId);
	

	usleep(5*1000*1000);
	pthread_t thread_decode;
	pthread_create(&thread_decode,NULL,decode_audio,NULL);
	while(1){
		usleep(1000*1000);
	}
	return 1;
}
