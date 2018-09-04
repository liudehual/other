#ifndef __AUDIO_READ_H__
#define __AUDIO_READ_H__

/*
	从aac文件中读取一帧数据( ADTS数据 )
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "STPusherAPI.h"
#include "OSMutex.h"

unsigned char adtsFrameBuf[1024*1024];
unsigned int adtsFrameLen=0;
OSMutex adtsMutex;

/* audio(aac) */
int getADTSframe(unsigned char* buffer, int buf_size, unsigned char* data ,int* data_size){
    int size = 0;

    if(!buffer || !data || !data_size ){
        return -1;
    }

    while(1){
        if(buf_size < 7 ){
            return -1;
        }
        //Sync words
        if((buffer[0] == 0xff) && ((buffer[1] & 0xf0) == 0xf0) ){
            size |= ((buffer[3] & 0x03) <<11);     //high 2 bit
            size |= buffer[4]<<3;                //middle 8 bit
            size |= ((buffer[5] & 0xe0)>>5);        //low 3bit
            break;
        }
        --buf_size;
        ++buffer;
    }

    if(buf_size < size){
        return 1;
    }

    memcpy(data, buffer, size);
    *data_size = size;

    return 0;
}

int simplest_aac_parser(char *url)
{
    int data_size = 0;
    int size = 0;
    int cnt=0;
    int offset=0;

    //FILE *myout=fopen("output_log.txt","wb+");
    FILE *myout=stdout;

    unsigned char *aacframe=(unsigned char *)malloc(1024*5);
    unsigned char *aacbuffer=(unsigned char *)malloc(20*1024*1024);

    FILE *ifile = fopen(url, "rb");
    if(!ifile){
        fprintf(stderr,"Open file error \n");
        return -1;
    }

    fprintf(stderr,"-----+- ADTS Frame Table -+------+\n");
    fprintf(stderr," NUM | Profile | Frequency| Size |\n");
    fprintf(stderr,"-----+---------+----------+------+\n");

	int sendFrameNums=0;
    while(!feof(ifile)){
        data_size = fread(aacbuffer+offset, 1, 20*1024*1024-offset, ifile);
        unsigned char* input_data = aacbuffer;

        while(1){
            int ret=getADTSframe(input_data, data_size, aacframe, &size);
            if(ret==-1){
                break;
            }else if(ret==1){
                memcpy(aacbuffer,input_data,data_size);
                offset=data_size;
                break;
            }
			usleep(23219);

	/* 测试audio_decode.h文件的从内存中读取的功能 */
#if 0
		adtsMutex.Lock();
		memcpy(adtsFrameBuf,aacframe,size);
		adtsFrameLen=size;
		adtsMutex.Unlock();
#endif
#if 1
			/* 压入到推流器中 */
			/* 传入音频帧结构 */
			Frame tFrame;
			tFrame.buffer=aacframe;
			tFrame.bufferLen=size;
			tFrame.type=AUDIO_TYPE;
	        STPusher_pushFrame(tFrame);
#endif
            data_size -= size;
            input_data += size;
        }
    }
    
    fclose(ifile);
    free(aacbuffer);
    free(aacframe);

    return 0;
}

void *read_aac(void *args)
{
	char *aac_file_name=(char *)args;
	char aacFileName[256]={'\0'};
	memcpy(aacFileName,aac_file_name,strlen(aac_file_name));
	while(1){
		simplest_aac_parser(aacFileName);
		usleep(1000*1000);
	}
}

#endif
