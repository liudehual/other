#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deviceInterface.h"
#include "clientInterface.h"
#include "serverInterface.h"



#define BUFFER_DEFAULT_SIZE  10*1024  /*默认帧长度(服务器，设备，客户端)*/
#define BUFFER_MAX_SIZE  70*1024  	  /*最大帧长度,通常情况下不会有如此大的命令(服务器，设备，客户端)*/
#define BUFFER_DEFAULT_STM_SIZE 100   /*默认帧长度(单片机)*/
#define BUFFER_MAX_STM_SIZE 200       /*最大帧长度(单片机)*/ 

#define FRAME_FIXED_FIELD  14 		  /*帧固定字段*/
#define FRAME_HEAD_FIXED_FILED 12     /*帧头固定字段*/
#define FRAME_TAIL_FIXED_FILED 2 	  /*帧尾固定字段*/

/*协议头字段索引*/
#define FRAME_HEAD_INDEX_1 0            /*帧开始*/
#define FRAME_LENGTH_INDEX 1            /*帧长度*/
#define FRAME_HEAD_INDEX_2 3            /*帧开始*/
#define FRAME_CONTROL_INDEX 4           /*控制域*/
#define FRAME_ADDR_INDEX 5              /*链路地址域*/  
#define FRAME_TYPE_INDEX 6              /*类型标示*/
#define FRAME_COT_INDEX 7               /*可变结构限定词*/
#define FRAME_READSION_INDEX 8          /*传输原因*/
#define FRAME_PUBLIC_ADDR_INDEX 9       /*公共地址*/
#define FRAME_INFO_ADDR_INDEX 10        /*信息体地址*/

/*数据来源*/
enum
{
    enum_wan=        0x00, //LAN
    enum_lan=        0x01  //WAN
};

enum
{
    enum_server=     0x00, //服务器
    enum_device=     0x10, //设备
    enum_client=     0x20  //客户端
};

/*====================================================================内部函数声明=========================================================================*/
/*************************************************************** 以下命令为用户数据处理命令***************************************/
static _UInt32 setDevId(_UInt8 *buf,_UInt32 devIdH,_UInt32 devIdL);
/******************************************************************************************************************************/
////////////////////////////////////////////////
/*预处理 记录上一个命令的结尾即当前命令的开始，同时检查内存是否够用*/
static _UInt8 *  preProcess(HandlePtr ptr,_UInt32 len);

/**/
static _UBool checkBuffer(HandlePtr ptr,_UInt32 len);
/*加锁发送缓冲区 暂未使用*/
static void lockSendBuf(HandlePtr ptr);
/*解锁发送缓冲区 暂未使用*/
static void unlockSendBuf(HandlePtr ptr);
/*加锁接收缓冲区 暂未使用*/
static void lockRecvBuf(HandlePtr ptr);
/*解锁接收缓冲区 暂未使用*/
static void unlockRecvBuf(HandlePtr ptr);
/*右移*/
static _UInt8 shiftRight(_UInt8 sorce);
/*左移*/
static _UInt8 shiftLeft(_UInt8 sorce);
/*内存申请封装*/
static _UInt8 *myMalloc(_UInt32 size);
/*获取指定大小的内存*/
static _UBool getMemory(HandlePtr ptr,_UInt32 rOrSBuf,_UInt32 len);
/*内存释放*/
static void myFree(void *p);
/*设置长度*/
static _UBool setLength(_UInt8 *buf,_UInt32 len);
/*设置帧尾*/
static _UBool setEnd(_UInt8 *buf,_UInt32 len);
/*设置命令*/
static _UBool setCommand(HandlePtr ptr);
/*验证命令完整性*/
static _UBool checkCompleteCommand(HandlePtr ptr);
/*和校验*/
static _UBool verify(HandlePtr ptr);
static void clearBuffer(HandlePtr ptr);
static void addDataToBuf(_SInt8 *pos,_SInt8 *buf,_UInt32 len);
static _UInt8 SumValid(_UInt8* puchData, _UInt32 len);
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++内部函数定义++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//和校验
_UInt8 sumValid(_UInt8* puchData, _UInt32 len)
{
    _UInt8 sum = 0;
    while (len--) sum = sum + (*puchData++);
    return sum;
}
void addDataToBuf(_SInt8 *pos,_SInt8 *buf,_UInt32 len)
{
    memcpy(pos,buf,len);
}
_UInt8 * preProcess(HandlePtr ptr,_UInt32 len)
{
    /*记录一下当前位置*/
    _UInt8 *currentPos=ptr->sBuf;
    _UInt32 oldContentSize;
    currentPos+=ptr->sContentSize;
    oldContentSize=ptr->sContentSize;
    /*检查是否有足够的空间存储数据*/
    if(!checkBuffer(ptr,len )){
        if(getMemory(ptr,eResetSendBuffer,len)){
            _UInt8 *pos=ptr->sBuf;
            /**/
            if(DEBUG)fprintf(stderr,"new buffer is %d\n",ptr->sContentSize);
            return pos+oldContentSize;
        }else{
            if(ERROR) fprintf(stderr,"[PROTOCOL_PARSER Function %s | %s]\n","preProcess","Not have Enough Memory");
            return NULL;
        }
    }else{
        ptr->sContentSize+=len+FRAME_FIXED_FIELD; /*内存空间充足，直接调整位置*/
    }
    return currentPos;
}
_UInt32 setDevId(_UInt8 *buf,_UInt32 devIdH,_UInt32 devIdL)
{
    _UInt32 *dH=(_UInt32 *)(buf);
    _UInt32 *dL=(_UInt32 *)(buf+sizeof(_UInt32));
    *dH=devIdH;
    *dL=devIdL;
    return sizeof(_UInt32)*2;
}

void clearBuffer(HandlePtr ptr)
{
    memset(ptr->sBuf,0,ptr->sBufSize);
}
void lockSendBuf(HandlePtr ptr)
{
#ifdef __Win32__
    ::EnterCriticalSection(&(ptr->sMutex));
#elif  __linux__
    if(DEBUG)fprintf(stderr,"%s\n","lockSendBuf");
    (void)pthread_mutex_lock(&(ptr->sMutex));
#endif
}
void unlockSendBuf(HandlePtr ptr)
{
#ifdef __Win32__
    ::LeaveCriticalSection(&(ptr->sMutex));
#elif  __linux__
    if(DEBUG)fprintf(stderr,"%s\n","unlockSendBuf");
    pthread_mutex_unlock(&(ptr->sMutex));
#endif
}
void lockRecvBuf(HandlePtr ptr)
{
#ifdef __Win32__
    ::EnterCriticalSection(&(ptr->rMutex));
#elif  __linux__
    (void)pthread_mutex_lock(&(ptr->rMutex));
#endif
}
void unlockRecvBuf(HandlePtr ptr)
{
#ifdef __Win32__
    ::LeaveCriticalSection(&(ptr->rMutex));
#elif  __linux__
    pthread_mutex_unlock(&(ptr->rMutex));
#endif
}
_UBool registerHandle(HandlePtr ptr,_UInt8 station,_UInt8 devType,_SInt32 sBufSize,_SInt32 rBufSize,_CallbackProcPtr cb)
{
#ifdef __Win32__
    ::InitializeCriticalSection(&(ptr->sMutex));
    ::InitializeCriticalSection(&(ptr->rMutex));
#elif  __linux__
    (void)pthread_mutex_init(&(ptr->sMutex),NULL);
    (void)pthread_mutex_init(&(ptr->rMutex),NULL);
#endif
    /*检查*/
    if(ptr==NULL || cb==NULL){
        if(ERROR)fprintf(stderr,"%s\n","register Error HandlePtr or _CallbackProcPtr is NULL");
        return False;
    }
    if(devType !=eStm && devType!=eNoStm){
        if(ERROR)fprintf(stderr,"DevType is error %d\n",devType);
        return False;
    }
    if(station!=eMasterStation && station!= eSubStation){
        if(ERROR)fprintf(stderr,"Station is error %d\n",station);
        return False;
    }

    /*确定申请内存大小*/
    if(sBufSize<=0){
        if(devType==eStm){
           sBufSize=BUFFER_DEFAULT_STM_SIZE;
        }else if(devType==eNoStm){
        sBufSize=BUFFER_DEFAULT_SIZE;
        }
    }
    if(sBufSize> BUFFER_MAX_SIZE){
        if(devType==eStm){
           sBufSize=BUFFER_MAX_STM_SIZE;
        }else if(devType==eNoStm){
        sBufSize=BUFFER_MAX_SIZE;
        }
    }
    if(rBufSize<=0){
        if(devType==eStm){
           sBufSize=BUFFER_DEFAULT_STM_SIZE;
        }else if(devType==eNoStm){
        sBufSize=BUFFER_DEFAULT_SIZE;
        }
    }
    if(rBufSize>BUFFER_MAX_SIZE){
        if(devType==eStm){
           sBufSize=BUFFER_MAX_STM_SIZE;
        }else if(devType==eNoStm){
        sBufSize=BUFFER_MAX_SIZE;
        }
    }

    /*为用户句柄赋值*/
    ptr->devType=devType;
    ptr->station=station;
    ptr->rBuf=NULL;
    ptr->sBuf=NULL;
    ptr->sContentSize=0;
    ptr->rContentSize=0;
    lockSendBuf(ptr);
    ptr->rBuf=myMalloc(rBufSize);
    if(ptr->rBuf==NULL){
        if(ERROR)fprintf(stderr,"%s\n","malloc Recv Buffer is error");
        return False;
    }
    ptr->rBufSize=rBufSize;
    if(DEBUG)fprintf(stderr,"new ptr->rBufSize %d\n",(int)ptr->rBufSize);
    unlockSendBuf(ptr);
    ptr->sBuf=myMalloc(sBufSize);
    if(ptr->sBuf==NULL){
        if(ERROR)fprintf(stderr,"%s\n","malloc Send Buffer is error");
        return False;
    }
    ptr->sBufSize=sBufSize;
    if(DEBUG)fprintf(stderr,"ptr->sBufSize %d\n",(int)ptr->sBufSize);
    ptr->rCallBack=cb;
    /*初始化完成*/
    return True;
}
_UBool removeHandle(HandlePtr ptr)
{
    if(ptr==NULL) //为空 默认成功
        return True;
    ptr->devType=5;
    ptr->station=5;
    ptr->rBufSize=0;
    ptr->rContentSize=0;
    myFree((void *)ptr->rBuf);
    ptr->rBuf=NULL;
    ptr->sBufSize=0;
    ptr->sContentSize=0;
    myFree((void *)ptr->sBuf);
    ptr->sBuf=NULL;
    return True;
}
_UBool  resetBuffer(HandlePtr ptr,_UInt32 sOrRBuf,_UInt32 hLen)
{
    if(DEBUG)fprintf(stderr,"resetBuffer You Want clear data number %d but You have all data number is %d\n",hLen,ptr->sContentSize);
    if(ptr==NULL || hLen<=0){
        if(ERROR)fprintf(stderr,"Ptr Or hLen is illegal\n");
        return False;
    }
    if(sOrRBuf!=eResetSendBuffer && sOrRBuf!=eResetRecvBuffer){
        if(ERROR)fprintf(stderr,"sOrRBuf is error %d\n",sOrRBuf);
        return False;
    }
    if(hLen>ptr->sContentSize){ /**/
        if(ERROR)fprintf(stderr,"resetBuffer You want delete the number of data is langer than all data,the memory will be clear \n");
        memset(ptr->sBuf,0,ptr->sBufSize);
        return False;
    }
    switch(sOrRBuf){
    case 0:{
        _UInt8 *pos=ptr->sBuf;
        if(hLen==ptr->sContentSize){ /*数据处理完成，清空缓冲区*/
            ptr->sContentSize-=hLen;
            memset(ptr->sBuf,0,hLen);
            return True;
        }
        pos+=hLen;
        memmove(ptr->sBuf,pos,ptr->sContentSize-hLen);
        ptr->sContentSize-=hLen;
    }
        break;
    case 1:{
        _UInt8 *pos=ptr->rBuf;
        if(hLen==ptr->rContentSize){
            ptr->rContentSize-=hLen;/*数据已经处理完毕，rCotnentSize置零*/
            memset(ptr->rBuf,0,hLen);
            return True;
        }
        pos+=hLen;
        memmove(ptr->rBuf,pos,ptr->rContentSize-hLen);
        ptr->rContentSize-=hLen;
    }
        break;
    default:/*do nothing*/;
    }
    return True;
}
/////////////////////////////////////////////////////// 工具函数 ////////////////////////////
_UInt8 *myMalloc(_UInt32 size)
{
    return (_UInt8 *)malloc(sizeof(_UInt8)*size);
}
void myFree(void *p)
{
    if(p==NULL) return;
    free(p);
}
_UBool checkCompleteCommand(HandlePtr ptr)
{
    _UInt32 pos;
    _UInt32 len;
    char *p=ptr->rBuf;
    _UInt32 errLen=0;
#if 0
    if((unsigned char)p[0]!=0xBB){
        char *pos=p;
        while(True){
            if(errLen==ptr->rContentSize){
                break;
            }
            if((unsigned char)(*pos)==0xBB){
                break;
            }
            pos+=1;
            errLen+=1;
        }
    }
#endif
    if((unsigned char )p[0]==0xBB){
        /*提取长度字段*/
        _UInt16 *len=(_UInt16 *)&p[1];
        _UInt8 check;
        /*命令最小长度 及最大长度*/
        if((*len) < FRAME_FIXED_FIELD || (*len)> BUFFER_MAX_SIZE){
            if(ERROR)fprintf(stderr,"%s frame length %d\n","the data length is overflow",*len);
            return False;
        }
        /*提取校验位 暂未实现*/
        /*_UInt8 */check=p[(*len)-FRAME_TAIL_FIXED_FILED];
        /*判断结尾是否正确*/
        if(p[*len-1]==0xEE){
            return True;
        }
    }
    return False;
}

_UBool setLength(_UInt8 *buf,_UInt32 len)
{
    _UInt8 *p=buf;
    _UInt16 *myLen=(_UInt16 *)(p+1);
    *myLen=len+FRAME_FIXED_FIELD;
    if(DEBUG)fprintf(stderr,"---%d\n",*myLen);
    return True;
}
_UBool setEnd(_UInt8 *buf,_UInt32 len)
{
    buf[len-1]=(_UInt8)0xEE;
    return True;
}
_UBool setCommand(HandlePtr ptr)
{
}
_UBool verify(HandlePtr ptr)
{
}
_UBool addMessage(HandlePtr ptr,char *buf,int len)
{
    _SInt32 rightLen;
    _UInt8 *pos;
    _UInt8 *p;
    _UInt16 rLen; /*帧长度*/
    _UInt8 source; /*来源*/
    _UInt8 mainCommand; /*主命令*/
    _UInt8 minorCommand;/*副命令*/
    _UInt8 tDir;
    int dir; /*指定是请求命令还是响应命令*/
    if(buf==NULL || buf[0]=='\0' || len<=0){
        if(DEBUG)fprintf(stderr,"%s\n","buffer or len is error");
        return False;
    }
    /*计算缓冲区剩余大小*/
    /*_SInt32 */rightLen=ptr->rBufSize-ptr->rContentSize;
    /*缓冲区剩余大小小于len,此处有两种方案1.直接将buf截断 2.重新申请内存，默认采用第二种方案，但最大长度不超过60K*/
    if((rightLen <0 || rightLen<len)  && ptr->rBufSize < BUFFER_MAX_SIZE){
        if(!checkBuffer(ptr,len)){  /*数据过大，超出了最大限制*/
            if(getMemory(ptr,eResetSendBuffer,len))return False;
        }
    }
    /*_UInt8 **/pos=ptr->rBuf;
    pos+=ptr->rContentSize;
    /*拷贝数据，并调整数据大小*/
    memcpy((_SInt8 *)pos,(_SInt8 *)buf,len);
    ptr->rContentSize+=len; /*拷贝完成，调整数据大小*/
    /*检查帧完整性*/
    if(!checkCompleteCommand(ptr)){
        if(HELPER)fprintf(stderr,"%s\n","the data is can't use");
        return False;
    }
    /*_UInt8 **/p=ptr->rBuf;
    /*_UInt16 */rLen=*((_UInt16 *)(p+1)); /*帧长度*/
    /*_UInt8 */source=*((_UInt8 *)(p+3)); /*来源*/
    /*_UInt8 */mainCommand=*((_UInt8 *)(p+4)); /*主命令*/
    /*_UInt8 */minorCommand=*((_UInt8 *)(p+5));/*副命令*/
    /*_UInt8 */tDir=*((_UInt8 *)(p+6));
    /*int *///dir=(int)((tDir >> 6) & 0x01); /*指定是请求命令还是响应命令*/
    ptr->rCallBack(mainCommand,minorCommand,tDir,p+FRAME_HEAD_FIXED_FILED,rLen-9); /*数据处理回调函数*/
    resetBuffer(ptr, eResetRecvBuffer,rLen); /*数据解析完毕，清除必要缓存*/
    return True;
}
_UBool getMemory(HandlePtr ptr,_UInt32 rOrSBuf,_UInt32 len)
{
    if(rOrSBuf==eResetSendBuffer){
        _UInt8 *newBuf;
        /*重新申请内存*/
        _UInt32 newSize=ptr->sContentSize+len+FRAME_FIXED_FIELD;
#if 1
        if(newSize>BUFFER_MAX_SIZE){ /*数据量大于最大限制，继续申请已没有意义，直接将整个buffer清空*/
            if(DEBUG) fprintf(stderr,"%d\n","command content is too long,we can't parser it ",newSize);
            memset(ptr->sBuf,0,ptr->sBufSize);
            ptr->sContentSize=0;
            return True;
        }
#endif
        if(DEBUG)fprintf(stderr,"new Size====%d\n",newSize);
        /*_UInt8 **/newBuf=myMalloc(newSize);
        if(newBuf==NULL){
            return False;
        }
        /*拷贝数据*/
        memcpy((_SInt8 *)newBuf,(_SInt8 *)(ptr->sBuf),ptr->sContentSize);
        /*清除原有内存*/
        myFree((void *)ptr->sBuf);
        ptr->sBuf=NULL;
        ptr->sBufSize=0;
        ptr->sContentSize=0;
        /*重新赋值*/
        ptr->sBufSize=newSize;
        ptr->sContentSize=newSize;
        ptr->sBuf=newBuf;
        if(DEBUG)fprintf(stderr,"getMemory ptr->sContentSize %d",ptr->sContentSize);
        return True;
    }
    if(rOrSBuf==eResetRecvBuffer){
        _UInt8 *newBuf;
        /*重新申请内存*/
        _UInt32 newSize=ptr->rContentSize+len+FRAME_TAIL_FIXED_FILED+FRAME_HEAD_FIXED_FILED;
#if 1
        if(newSize>BUFFER_MAX_SIZE){
            if(DEBUG)fprintf(stderr,"%d\n","command content is too long,we can't parser it ");
            memset(ptr->rBuf,0,ptr->rBufSize); /*数据量大于最大限制，继续申请已没有意义，直接将整个buffer清空*/
            ptr->rContentSize=0;
            return True;
        }
#endif
        /*_UInt8 **/newBuf=myMalloc(newSize);
        /*拷贝数据*/
        memcpy((_SInt8 *)newBuf,(_SInt8 *)(ptr->rBuf),ptr->rContentSize);
        /*清除原有内存*/
        myFree((void *)(ptr->rBuf));
        ptr->rBufSize=0;
        ptr->rContentSize=0;
        /*重新赋值*/
        ptr->rBufSize=newSize;
        ptr->rContentSize=newSize;
        ptr->rBuf=newBuf;
        return True;
    }
    return True; /*默认实现*/
}
_UBool checkBuffer(HandlePtr ptr,_UInt32 len)
{
    if(ptr->sContentSize+len+FRAME_TAIL_FIXED_FILED+FRAME_HEAD_FIXED_FILED >ptr->sBufSize){ /*数据量大于内存空间，扩展*/
        if(ERROR)fprintf(stderr,"%s %d\n","There is too much Data,it make memory overflow",len+FRAME_TAIL_FIXED_FILED+FRAME_HEAD_FIXED_FILED);
        return False;
    }
    return True;
}
_UInt8 shiftRight(_UInt8 sorce){}
_UInt8 shiftLeft(_UInt8 sorce){}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                         以下为具体的命令接口函数定义                                                                                                  ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/*协议版本查询*/
_UBool setReqVersion(
        HandlePtr ptr,
        _UInt32 devIdH, /*设备编号 分高位4字节 低位4字节*/
        _UInt32 devIdL,
        _UInt32 proVer /*协议版本号*/
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqVersion version;
    if(ptr==NULL) return False;
    if(devIdH <0 || devIdL <0) return False;
    /*_UInt32 */len=sizeof(ReqVersion);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,check_version,0x00,0x00);
    if(DEBUG) fprintf(stderr,"%d %d %d\n",devIdH,devIdL,proVer);
    /*处理用户数据*/
    pos+=FRAME_HEAD_FIXED_FILED;
    version.devIdH=devIdH;  version.devIdL=devIdL;
    version.proVer=proVer;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&version,len);       
    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
    //setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
#if 0  //debug
    _UInt8 *point=currentPos;
    _UInt8 *myHead=(_UInt8 *)point;
    _UInt16 *myLen=(_UInt16 *)(point+1);
    if(DEBUG)fprintf(stderr,"%d %d \n",*myHead,*myLen);
    if(DEBUG)fprintf(stderr,"%d\n",ptr->sContentSize);
#endif
    return True;
}
_UBool setResVersion(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 proVer
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResVersion version;
    if(ptr==NULL)  return False;
    if(devIdH<0 || devIdL<0) return False;
    /*_UInt32 */len=sizeof(ResVersion);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,check_version,0x00,0x01);
    /*处理用户数据*/

    //pos+=FRAME_HEAD_FIXED_FILED;
    version.devIdH=devIdH;  version.devIdL=devIdL;
    version.proVer=proVer;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&version,len);
    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*心跳*/ /*设备心跳无响应*/
_UBool setReqDLive(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 cumulative
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqDLive live;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqDLive);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,dev_heartbeat,0x00,0x00);
    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    live.devIdH=devIdH;  live.devIdL=devIdL;
    live.cumulative=cumulative;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&live,len);
    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*设备检索*/
_UBool setReqFindDev(
        HandlePtr ptr,
        _UInt32 proType,
        _UInt32 devType
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqFindDev findDev;

    if(ptr==NULL) return False;
    if(proType <0 || devType < 0) return False;

    /*_UInt32 */len=sizeof(ReqFindDev);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;

    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,find_dev,0x00,0x00);
    /*处理用户数据*/

    //pos+=FRAME_HEAD_FIXED_FILED;

    findDev.devType=devType;  findDev.proType=proType;

    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&findDev,len);
    packagingData(pos,len,NULL,ptr->station,eReq,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResFindDev(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 devType,
        _UInt32 chNum,
        _UInt32 netIp,
        _UInt32 netDns,
        _UInt32 netGateWay,
        _UInt32 netMask,
        _UInt8  *netMac,
        _UInt32 macLen,
        _UInt8  *buf,
        _UInt32 bufLen
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResFindDev findDev;
    if(ptr==NULL || netMac==NULL || buf==NULL) return False;
    if(macLen>sizeof(findDev.netMac) || macLen<=0) return False;
    if(bufLen>sizeof(findDev.buf) || bufLen<=0) return False;
    /*_UInt32 */len=sizeof(ResFindDev);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL)  return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,find_dev,0x00,0x01);
    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    findDev.devIdH=devIdH;      findDev.devIdL=devIdL;
    findDev.devType=devType;  findDev.chNum=chNum;
    findDev.netDns=netDns;      findDev.netGateWay=netGateWay;
    findDev.netIp=netIp;            findDev.netMask=netMask;
    memcpy((_SInt8 *)findDev.netMac,(_SInt8 *)netMac,macLen);
    memcpy((_SInt8 *)findDev.buf,(_SInt8 *)buf,bufLen);
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&findDev,len);
    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*设备上下线*/
/*设备管理*/
/*设备维护*/
/*获取地域信息*/
/*客户端上下线*/
/*用户*/
/*设备信息*/
/*客户端心跳*/
/*获取传感器对应信息*/
/*报警*/
/*数据发送*/
_UBool setResData(
        HandlePtr ptr,
        _UInt8 *data,
        _UInt32 dataLen
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    if(ptr==NULL || dataLen>1*1024 || dataLen<=0 || data==NULL) return False;
    /*_UInt32 */len=dataLen;
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,data_send,0x00,0x01);
    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    memcpy((_UInt8 *)pos,(_UInt8 *)data,dataLen);
    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*视频发送*/
_UBool setResVideoData(
        HandlePtr ptr,
        _UInt8 *vData,
        _UInt32 dataLen
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    if(ptr==NULL || vData==NULL || dataLen<=0 || dataLen>1*1024) return False;
    if(dataLen>(BUFFER_MAX_SIZE-FRAME_FIXED_FIELD) || dataLen<=0 ) return False;

    /*_UInt32 */len=dataLen;
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,video_send,0x00,0x01);
    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;

    memcpy((_UInt8 *)pos,(_UInt8 *)vData,dataLen);
    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*获取历史数据*/
_UBool setReqGetHistordata(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt32 date,
        _UInt32 sTime,
        _UInt32 eTime
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqGetHistordata hData;
    if(ptr==NULL)return False;
    /*_UInt32 */len=sizeof(ReqGetHistordata);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL)return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,get_history_data,0x00,0x00);
    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    hData.devIdH=devIdH;        hData.devIdL=devIdL;
    hData.chId=chId;                  hData.date=date;
    hData.eTime=eTime;            hData.sTime=sTime;
    //addDataToBuf(pos,(_SInt8 *)&hData,len);
    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResGetHistordata(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResGetHistordata hData;
    if(ptr==NULL)return False;
    /*_UInt32 */len=sizeof(ResGetHistordata);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL)return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,get_history_data,0x00,0x01);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    hData.devIdH=devIdH;  hData.devIdL=devIdL;
    hData.result=result;
    //addDataToBuf(pos,(_SInt8 *)&hData,len);
    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*用户登录*/
_UBool setReqUserLogin(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  *name,
        _UInt32 nameLen,
        _UInt8  *passwd,
        _UInt32 passwdLen
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqUserLogin login;
    if(ptr==NULL || name==NULL || passwd ==NULL)return False;
    if(nameLen>sizeof(login.name)) return False;
    if(passwdLen>sizeof(login.passwd))return False;
    /*_UInt32 */len=sizeof(ReqUserLogin);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,user_login,0x00,0x00);
    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    login.devIdH=devIdH;  login.devIdL=devIdL;
    memcpy(login.name,name,nameLen);
    memcpy(login.passwd,passwd,passwdLen);
    //addDataToBuf(pos,(_SInt8 *)&login,len);
    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResUserLogin(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResUserLogin login;
    if(ptr==NULL)return False;
    /*_UInt32 */len=sizeof(ResUserLogin);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL)return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,user_login,0x00,0x01);
    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    login.devIdH=devIdH;  login.devIdL=devIdL;
    login.result=result;
    //addDataToBuf(pos,(_SInt8 *)&login,len);
    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*云台*/
/////////////////
/*设备上线*/
_UBool setReqDevConn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  devType,
        _UInt8  chType,
        _UInt8  connType,
        _UInt8  sigStrength
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqDevConn devConn;
    if(ptr==NULL)return False;
    /*_UInt32 */len=sizeof(ReqDevConn);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL)return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,connect_disc_dev,conn_dev,0x00);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;

    devConn.devIdH=devIdH;            devConn.devIdL=devIdL;
    devConn.devType=devType;        devConn.chType=chType;
    devConn.connType=connType;   devConn.sigStrength=sigStrength;
    //addDataToBuf(pos,(_SInt8 *)&devConn,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResDevConn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8 result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResDevConn devConn;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResDevConn);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL)  return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,connect_disc_dev,conn_dev,0x01);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    devConn.devIdH=devIdH;  devConn.devIdL=devIdL;
    devConn.result=result;
    //addDataToBuf(pos,(_SInt8 *)&devConn,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*设备下线*/
_UBool setReqDevDisConn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqDevDisConn disConn;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqDevDisConn);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,connect_disc_dev,disconn_dev,0x00);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    disConn.devIdH=devIdH;  disConn.devIdL=devIdL;
    //addDataToBuf(pos,(_SInt8 *)&disConn,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResDevDisConn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResDevDisConn disConn;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(_UInt32);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,connect_disc_dev,disconn_dev,0x01);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    disConn.devIdH=devIdH;  disConn.devIdL=devIdL;
    disConn.result=result;
    //addDataToBuf(pos,(_SInt8 *)&disConn,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*获取传感器配置*/
_UBool setReqGetSensorConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 terId,
        _UInt8  chId
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqGetSensorConf gsConf;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqGetSensorConf);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;

    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_sensor_conf,0x00);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gsConf.devIdH=devIdH;  gsConf.devIdL=devIdL;
    gsConf.chId=chId;            gsConf.terId=terId;
    //addDataToBuf(pos,(_SInt8 *)&gsConf,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResGetSensorConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 terId,
        _UInt8  chId,
        _UInt32 minThreshlod,
        _UInt32 maxThreshlod,
        _UInt32 maxRefer,
        _UInt32 minRefer,
        _UInt32 range
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResGetSensorConf gsConf;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResGetSensorConf);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_sensor_conf,0x01);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gsConf.devIdH=devIdH;                          gsConf.devIdL=devIdL;
    gsConf.chId=chId;                                    gsConf.minThreshlod=minThreshlod;
    gsConf.maxThreshlod=maxThreshlod;  gsConf.minRefer=minRefer;
    gsConf.maxRefer=maxRefer;                  gsConf.range=range;
    gsConf.terId=terId;
    //addDataToBuf(pos,(_SInt8 *)&gsConf,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*修改传感器配置*/
_UBool setReqModSensorConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 terId,
        _UInt8  chId,
        _UInt32 minThreshlod,
        _UInt32 maxThreshlod,
        _UInt32 maxRefer,
        _UInt32 minRefer
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqModSensorConf msConf;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqModSensorConf);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,modify_sensor_conf,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    msConf.chId=chId;                                    msConf.devIdH=devIdH;
    msConf.devIdL=devIdL;                            msConf.maxRefer=maxRefer;
    msConf.maxThreshlod=maxThreshlod;  msConf.minRefer=minRefer;
    msConf.minThreshlod=minThreshlod;   msConf.terId=terId;
    //addDataToBuf(pos,(_SInt8 *)&msConf,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);

    return True;
}
_UBool setResModSensorConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 terId,
        _UInt8  chId,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResModSensorConf msConf;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResModSensorConf);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,modify_sensor_conf,0x01);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    msConf.chId=chId;          msConf.devIdH=devIdH;
    msConf.devIdL=devIdL;  msConf.result=result;
    msConf.terId=terId;
    //addDataToBuf(pos,(_SInt8 *)&msConf,len);
    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*历史数据上报时间间隔*/
_UBool setReqHisDataReportTime(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt16 time
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqHisDataReportTime drTime;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqHisDataReportTime);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,history_data_report_time,0x00);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    drTime.devIdH=devIdH;  drTime.devIdL=devIdL;
    drTime.time=time;
    //addDataToBuf(pos,(_SInt8 *)&drTime,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResHisDataReportTime(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResHisDataReportTime drTime;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResHisDataReportTime);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,history_data_report_time,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    drTime.devIdH=devIdH;  drTime.devIdL=devIdL;
    drTime.result=result;
    //addDataToBuf(pos,(_SInt8 *)&drTime,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*485配置*/
_UBool setReqFEFConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 terId,
        _UInt16 rTime,
        _UInt32 baud,
        _UInt32 dLen,
        _UInt8  sFlags,
        _UInt32 eoCheck
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqFEFConf FEFConf;
    if(ptr==NULL)  return False;
    /*_UInt32 */len=sizeof(ReqFEFConf);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL)  return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,set_foureightfive_conf,0x00);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    FEFConf.baud=baud;               FEFConf.devIdH=devIdH;
    FEFConf.devIdL=devIdL;         FEFConf.dLen=dLen;
    FEFConf.eoCheck=eoCheck;   FEFConf.rTime=rTime;
    FEFConf.sFlags=sFlags;            FEFConf.terId=terId;
    //addDataToBuf(pos,(_SInt8 *)&FEFConf,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResFEFConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResFEFConf  FEFConf;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResFEFConf);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,set_foureightfive_conf,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    FEFConf.devIdH=devIdH;  FEFConf.devIdL=devIdL;
    FEFConf.result=result;
    //addDataToBuf(pos,(_SInt8 *)&FEFConf,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*232配置*/
_UBool setReqTTTConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 baud,
        _UInt32 dLen,
        _UInt8  sFlags,
        _UInt32 eoCheck
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqTTTConf TTTConf;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqTTTConf);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,set_twothreetwo_conf,0x00);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    TTTConf.baud=baud;              TTTConf.devIdH=devIdH;
    TTTConf.devIdL=devIdL;        TTTConf.dLen=dLen;
    TTTConf.eoCheck=eoCheck;  TTTConf.sFlags=sFlags;
    //addDataToBuf(pos,(_SInt8 *)&TTTConf,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResTTTConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8   result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResTTTConf TTTConf;
    if(ptr==NULL) return False;

    /*_UInt32 */len=sizeof(ResTTTConf);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;

    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,set_twothreetwo_conf,0x01);

    /*处理用户数据*/
    pos+=FRAME_HEAD_FIXED_FILED;
    TTTConf.devIdH=devIdH;   TTTConf.devIdL=devIdL;
    TTTConf.result=result;
    //addDataToBuf(pos,(_SInt8 *)&TTTConf,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*数据补录 无请求*/
_UBool setResDataMakeUp(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  dType,
        _UInt32 pTime,
        _UInt32 buf1Len,
        _UInt32 *buf1,
        _UInt32 buf2Len,
        _UFloat *buf2,
        _UInt32 buf3Len,
        _UFloat *buf3
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    _UInt32 *dH;
    _UInt32 *dL;
    _UInt8 *dT;
    _UInt32 *pT;
    _UInt32 *b1Len;
    _UInt32 *b2Len;
    _UInt32 *b3Len;
    if(ptr==NULL || buf1==NULL || buf2==NULL || buf3==NULL)  return False;

    /*此处是否检查buffer长度待确认*/
    // if(buf1Len > 1*1024 || buf1Len<=0 || buf2Len > 1*1024 || buf2Len<=0 || buf2Len > 1*1024 || buf2Len<=0 || buf3Len > 1*1024 || buf3Len<=0)return False;

    /*_UInt32 */len=sizeof(_UInt32)*6+sizeof(_UInt8)+buf1Len*4+buf2Len*4+buf3Len*4;
    /*_UInt8 **/currentPos=preProcess(ptr,len);

    if(currentPos==NULL) return False;

    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,data_makeup,0x01);

    /*处理用户数据*/
    pos+=FRAME_HEAD_FIXED_FILED;
    /*_UInt32 **/dH=(_UInt32 *)(pos);
    *dH=devIdH;
    pos+=sizeof(_UInt32);

    /*_UInt32 **/dL=(_UInt32 *)(pos);
    *dL=devIdL;
    pos+=sizeof(_UInt32);

    /*_UInt8 **/dT=(_UInt8 *)(pos);
    *dT=dType;
    pos+=sizeof(_UInt8);

    /*_UInt32 **/pT=(_UInt32 *)(pos);
    *pT=pTime;
    pos+=sizeof(_UInt32);

    /*_UInt32 **/b1Len=(_UInt32)(pos);
    *b1Len=buf1Len;
    pos+=sizeof(_UInt32);
    memcpy(pos,buf1,buf1Len*4);
    pos+=buf1Len*4;

    /*_UInt32 **/b2Len=(_UInt32)(pos);
    *b2Len=buf2Len;
    pos+=sizeof(_UInt32);
    memcpy(pos,buf2,buf2Len*4);
    pos+=buf2Len*4;

    /*_UInt32 **/b3Len=(_UInt32)(pos);
    *b3Len=buf3Len;
    pos+=sizeof(_UInt32);
    memcpy(pos,buf3,buf3Len*4);
    pos+=buf3Len*4;

    pos=currentPos;
    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len);
    return True;
}
/*传感器配置自动上报*/
_UBool setReqSensorAutoReport(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt8  *sName,
        _UInt32 nameLen,
        _UInt8  sType,
        _UInt32 minThreshlod,
        _UInt32 maxThreshlod,
        _UInt32 maxRefer,
        _UInt32 minRefer,
        _UInt32 range
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqSensorAutoReport saReport;
    if(ptr==NULL || sName==NULL) return False;
    if(nameLen > sizeof(saReport.sName))  return False;

    /*_UInt32 */len=sizeof(ReqSensorAutoReport);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;

    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,sensor_conf_auto_report,0x00);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    saReport.chId=chId;          saReport.devIdH=devIdH;
    saReport.devIdL=devIdL;  saReport.maxRefer=maxRefer;
    saReport.maxThreshlod=maxThreshlod ; saReport.minRefer=minRefer;
    saReport.minThreshlod=minThreshlod;   saReport.range=range;

    memcpy(saReport.sName,sName,nameLen);
    saReport.sType=sType;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&saReport,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResSensorAutoReport(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResSensorAutoReport saReport;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResSensorAutoReport);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,sensor_conf_auto_report,0x01);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    saReport.chId=chId;  saReport.devIdH=devIdH;
    saReport.devIdL=devIdL; saReport.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&saReport,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*获取报警设置*/
_UBool setReqGetWarnPlace(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wType,
        _UInt8  chId
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqGetWarnPlace gwPlace;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqGetWarnPlace);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_warn_conf,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gwPlace.chId=chId;  gwPlace.devIdH=devIdH;
    gwPlace.devIdL=devIdL; gwPlace.wType=wType;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&gwPlace,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResGetWarnPlace(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wType,
        _UInt8  chId,
        _UInt8  alarm,
        _UInt8  email,
        _UInt8  screenshot,
        _UInt8  capturePic,
        _UInt8  callPreset,
        _UInt8  PreChId,
        _UInt8  PreId,
        _UInt8  sendToClient,
        _UInt8  startVideo,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResGetWarnPlace gwPlace;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResGetWarnPlace);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_warn_conf,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gwPlace.devIdH=        devIdH;
    gwPlace.devIdL=       devIdL;
    gwPlace.wType=        wType;
    gwPlace.chId=         chId;
    gwPlace.alarm=        alarm;
    gwPlace.email=        email;
    gwPlace.screenshot=   screenshot;
    gwPlace.capturePic=   capturePic;
    gwPlace.callPreset=   callPreset;
    gwPlace.PreChId=      PreChId;
    gwPlace.PreId=        PreId;
    gwPlace.sendToClient=  sendToClient;
    gwPlace.startVideo=   startVideo;
    gwPlace.result=        result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&gwPlace,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);


    /*nihao*/
    return True;
}
/*修改报警设置*/
_UBool setReqModWarnPlace(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wType,
        _UInt8  warnOther,
        _UInt8  chId,
        _UInt8  alarm,
        _UInt8  email,
        _UInt8  screenshot,
        _UInt8  capturePic,
        _UInt8  callPreset,
        _UInt8  PreChId,
        _UInt8  PreId,
        _UInt8  sendToClient,
        _UInt8  startVideo
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqModWarnPlace mwPlace;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqModWarnPlace);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,modify_warn_conf,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    mwPlace.devIdH=            devIdH;
    mwPlace.devIdL=            devIdL;
    mwPlace.wType=             wType;
    mwPlace.warnOther=         warnOther;
    mwPlace.chId=              chId;
    mwPlace.alarm=             alarm;
    mwPlace.email=             email;
    mwPlace.screenshot=        screenshot;
    mwPlace.capturePic=        capturePic;
    mwPlace.callPreset=        callPreset;
    mwPlace.PreChId=           PreChId;
    mwPlace.PreId=             PreId;
    mwPlace.sendToClient=      sendToClient;
    mwPlace.startVideo=        startVideo;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&mwPlace,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);


    return True;
}
_UBool setResModWarnPlace(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResModWarnPlace mwPlace;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResModWarnPlace);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,modify_warn_conf,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    mwPlace.devIdH=devIdH;
    mwPlace.devIdL=devIdL;
    mwPlace.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&mwPlace,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*报警清除*/
_UBool setReqWarnClear(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wType,
        _UInt8  chId
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqWarnClear wc;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqWarnClear);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,clean_warn,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    wc.chId=chId;
    wc.devIdH=devIdH;
    wc.devIdL=devIdL;
    wc.wType=wType;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&wc,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResWarnClear(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResWarnClear wc;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResWarnClear);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,clean_warn,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    wc.devIdH=devIdH; wc.devIdL=devIdL;
    wc.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&wc,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*获取报警预约*/
_UBool setReqGetWarnOrder(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wType,
        _UInt8  chId
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqGetWarnOrder gwOrder;
    if(ptr==NULL)  return False;
    /*_UInt32 */len=sizeof(ReqGetWarnOrder);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_warn_order,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gwOrder.chId=chId;gwOrder.devIdH=devIdH;
    gwOrder.devIdL=devIdL; gwOrder.wType=wType;

    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&gwOrder,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResGetWarnOrder(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wType,
        _UInt8  chId,
        _UInt32 sTime,
        _UInt32 eTime
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResGetWarnOrder gwOrder;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResGetWarnOrder);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_warn_order,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gwOrder.chId=chId; gwOrder.devIdH=devIdH;
    gwOrder.devIdL=devIdL; gwOrder.eTime=eTime;
    gwOrder.sTime=sTime;  gwOrder.wType=wType;

    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&gwOrder,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*修改报警预约*/
_UBool setReqModWarnOrder(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wType,
        _UInt8  chId,
        _UInt32 sTime,
        _UInt32 eTime
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqModWarnOrder mwOrder;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqModWarnOrder);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,modify_warn_order,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    mwOrder.chId=chId;  mwOrder.devIdH=devIdH;
    mwOrder.devIdL=devIdL;  mwOrder.eTime=eTime;
    mwOrder.sTime=sTime;  mwOrder.wType=wType;

    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&mwOrder,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResModWarnOrder(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8 chId
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResModWarnOrder mwOrder;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResModWarnOrder);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,modify_warn_order,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    mwOrder.chId=chId;  mwOrder.devIdH=devIdH;
    mwOrder.devIdL=devIdL;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&mwOrder,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*普通报警*/
_UBool setReqGeneralWarn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wType,
        _UInt8  chId,
        _UInt8  *wContent,
        _UInt32 contentLen
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqGeneralWarn gw;
    if(ptr==NULL || wContent==NULL) return False;
    if(contentLen>sizeof(gw.wContent)) return False;

    /*_UInt32 */len=sizeof(ReqGeneralWarn);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,general_warn,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gw.chId=chId;  gw.devIdH=devIdH;
    gw.devIdL=devIdL;  gw.wType=wType;

    memcpy((_SInt8 *)gw.wContent,(_SInt8*)wContent,contentLen);
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&gw,len);
    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResGeneralWarn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResGeneralWarn gw;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResGeneralWarn);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,general_warn,0x01);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gw.devIdH=devIdH;  gw.devIdL=devIdL;
    gw.result=result;

    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&gw,len);
    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*数据报警*/
_UBool setReqDataWarn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  *devName,
        _UInt32 nameLen,
        _UInt8  wType,
        _UInt8  chId,
        _UInt32 sVal,
        _UInt32 minVal,
        _UInt32 maxVal,
        _UInt8  dType,
        _UInt8  tName,
        _UInt32 unit,
        _UInt32 time
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqDataWarn dw;
    if(ptr==NULL || devName==NULL) return False;
    if(nameLen>sizeof(dw.devName)) return False;
    /*_UInt32 */len=sizeof(ReqDataWarn);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,data_warn,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;

    dw.devIdH=     devIdH;
    dw.devIdL=     devIdL;


    memcpy(dw.devName,devName,nameLen);
    dw.wType=      wType;  dw.chId=       chId;
    dw.sVal=       sVal;  dw.minVal=     minVal;
    dw.maxVal=     maxVal;  dw.dType=      dType;
    dw.tName=      tName;  dw.unit=       unit;
    dw.time=        time;

    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&dw,len);
    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResDataWarn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResDataWarn dw;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResDataWarn);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,data_warn,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    dw.devIdH=devIdH;
    dw.devIdL=devIdL;
    dw.result=result;

    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&dw,len);
    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*获取设备网络状态*/
_UBool setReqGetNetState(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqGetNetState gnState;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqGetNetState);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_dev_net_state,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gnState.devIdH=devIdH;  gnState.devIdL=devIdL;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&gnState,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResGetNetState(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  netType,
        _UInt32 ip,
        _UInt32 dns,
        _UInt32 mask,
        _UInt32 gateway,
        _UInt8  *mac,
        _UInt32 macLen,
        _UInt8  dhcp
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResGetNetState gnState;
    if(ptr==NULL || mac==NULL) return False;
    if(macLen>sizeof(gnState.mac)) return False;

    /*_UInt32 */len=sizeof(ResGetNetState);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_dev_net_state,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gnState.devIdH=devIdH;  gnState.devIdL=devIdL;
    gnState.dhcp=dhcp;  gnState.dns=dns;
    gnState.gateway=gateway;  gnState.ip=ip;
    memcpy(gnState.mac,mac,macLen);
    gnState.mask=mask;
    gnState.netType=netType;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&gnState,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*设置设备网络状态*/
_UBool setReqSetNetState(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  netType,
        _UInt32 ip,
        _UInt32 dns,
        _UInt32 mask,
        _UInt32 gateway,
        _UInt8  *mac,
        _UInt32 macLen,
        _UInt8  dhcp
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqSetNetState snState;
    if(ptr==NULL || mac==NULL) return False;
    /*_UInt32 */len=sizeof(ReqSetNetState);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,set_dev_net_state,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    snState.devIdH=devIdH;  snState.devIdL=devIdL;
    snState.dhcp=dhcp;  snState.dns=dns;
    snState.gateway=gateway;  snState.ip=ip;
    if(strlen(mac)>sizeof(snState.mac))return False;
    memcpy(snState.mac,mac,strlen(mac));
    snState.mask=mask;
    snState.netType=netType;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&snState,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResSetNetState(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResSetNetState snState;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResSetNetState);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,set_dev_net_state,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    snState.devIdH=devIdH;  snState.devIdL=devIdL;
    snState.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&snState,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*3G 获取网络状态*/
_UBool setReqGetNetState3G(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  nType,
        _UInt8  cType
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqGetNetState3G gnState;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqGetNetState3G);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_dev_net_state_threeg,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gnState.cType=cType;  gnState.devIdH=devIdH;
    gnState.devIdL=devIdL;  gnState.nType=nType;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&gnState,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResGetNetState3G(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  *name,
        _UInt32 nameLen,
        _UInt8  *passwd,
        _UInt32 passwdLen,
        _UInt8  apn
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResGetNetState3G gnState;
    if(ptr==NULL || name==NULL || passwd==NULL) return False;
    if(nameLen>sizeof(gnState.name)) return False;
    if(passwdLen>sizeof(gnState.passwd)) return False;

    /*_UInt32 */len=sizeof(ResGetNetState3G);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_dev_net_state_threeg,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gnState.apn=apn;
    gnState.devIdH=devIdH;  gnState.devIdL=devIdL;
    memcpy(gnState.name,name,strlen(name));
    memcpy(gnState.passwd,passwd,strlen(passwd));
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&gnState,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*远程桌面通信*/
_UBool setReqRemoteDisktop(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqRemoteDisktop rd;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqRemoteDisktop);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,remote_desktop,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    rd.devIdH=devIdH;  rd.devIdL=devIdL;

    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&rd,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);

    return True;
}
_UBool setResRemoteDistop(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResRemoteDistop rd;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResRemoteDistop);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,remote_desktop,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    rd.devIdH=devIdH;  rd.devIdL=devIdL;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&rd,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*获取设备用户 此处设置不完全*/
_UBool setReqGetDevUser(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqGetDevUser gdUser;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqGetDevUser);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_dev_user,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gdUser.devIdH=devIdH;  gdUser.devIdL=devIdL;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&gdUser,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResGetDevUser(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  *uName,
        _UInt32 nameLen,
        _UInt16 power
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResGetDevUser gdUser;
    if(ptr==NULL || uName==NULL) return False;
    if(nameLen>sizeof(gdUser.uName))return False;

    /*_UInt32 */len=sizeof(_UInt32);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_dev_user,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gdUser.devIdH=devIdH;  gdUser.devIdL=devIdL;
    gdUser.power=power;
    memcpy(gdUser.uName,uName,strlen(uName));
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&gdUser,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*修改设备用户*/
_UBool setReqModDevUser(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  *uName,
        _UInt32 nameLen,
        _UInt8  *uPasswd,
        _UInt32 passwdLen,
        _UInt8  pVideo,
        _UInt8  pConnection,
        _UInt8  pYTControl,
        _UInt8  pShutDown,
        _UInt8  pCapturePic,
        _UInt8  pSystemSet,
        _UInt8  pVideoChange,
        _UInt8  pUserManager,
        _UInt8  pPicChange,
        _UInt8  pRemoteManager,
        _UInt8  pAudioListen
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqModDevUser mdUser;
    if(ptr==NULL || uName==NULL || uPasswd==NULL) return False;
    if(nameLen>sizeof(mdUser.uName)) return False;
    if(passwdLen>sizeof(mdUser.uPasswd)) return False;

    /*_UInt32 */len=sizeof(ReqModDevUser);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,modify_dev_user,0x00);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    mdUser.devIdH=devIdH;  mdUser.devIdL=devIdL;
    mdUser.pAudioListen=pAudioListen;  mdUser.pCapturePic=pCapturePic;
    mdUser.pConnection=pConnection;  mdUser.pPicChange=pPicChange;
    mdUser.pRemoteManager=pRemoteManager;  mdUser.pShutDown=pShutDown;
    mdUser.pSystemSet=pSystemSet;  mdUser.pUserManager=pUserManager;
    mdUser.pVideo=pVideo;  mdUser.pVideoChange=pVideoChange;
    mdUser.pYTControl=pYTControl;
    memcpy(mdUser.uName,uName,nameLen);
    memcpy(mdUser.uPasswd,uPasswd,passwdLen);
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&mdUser,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResModDevUser(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResModDevUser mdUser;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResModDevUser);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,modify_dev_user,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    mdUser.devIdH=devIdH;  mdUser.devIdL=devIdL;
    mdUser.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&mdUser,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*设置时间*/
_UBool setReqSetTime(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqSetTime st;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqSetTime);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,set_time,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    st.devIdH=devIdH;  st.devIdL=devIdL;

    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&st,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResSetTime(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 time
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResSetTime st;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResSetTime);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,set_time,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    st.devIdH=devIdH;  st.devIdL=devIdL;
    st.time=time;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&st,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*云台设置*/
_UBool setReqYunTaiSet(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt8  command,
        _UInt8  rate
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqYunTaiSet yt;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqYunTaiSet);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,set_yuntai,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    yt.chId=chId;  yt.command=command;
    yt.devIdH=devIdH;  yt.devIdL=devIdL;
    yt.rate=rate;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&yt,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResYunTaiSet(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResYunTaiSet yt;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResYunTaiSet);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,set_yuntai,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    yt.devIdH=devIdH;  yt.devIdL=devIdL;
    yt.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&yt,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*获取云台*/
_UBool setReqGetYunTaiInfo(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqGetYunTaiInfo ytInfo;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqGetYunTaiInfo);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_yuntai,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    ytInfo.chId=chId;  ytInfo.devIdH=devIdH;
    ytInfo.devIdL=devIdL;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&ytInfo,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResGetYunTaiInfo(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt32 baud,
        _UInt32 addr,
        _UInt8  pType
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResGetYunTaiInfo ytInfo;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResGetYunTaiInfo);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;

    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_yuntai,0x01);


    /*处理用户数据*/
    ////pos+=FRAME_HEAD_FIXED_FILED;
    ytInfo.addr=addr;  ytInfo.baud=baud;
    ytInfo.chId=chId;  ytInfo.devIdH=devIdH;
    ytInfo.devIdL=devIdL;  ytInfo.pType=pType;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&ytInfo,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*控制云台*/
_UBool setReqControlYunTai(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt8  command,
        _UInt8  rate
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqControlYunTai cYt;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(_UInt32);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,control_yuntai,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    cYt.chId=chId;  cYt.command=command;
    cYt.devIdH=devIdH;  cYt.devIdL=devIdL;
    cYt.rate=rate;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&cYt,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResControlYunTai(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResControlYunTai cYt;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResControlYunTai);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,control_yuntai,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    cYt.chId=chId;  cYt.devIdH=devIdH;
    cYt.devIdL=devIdL;  cYt.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&cYt,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*获取预置点*/
_UBool setReqGetPreset(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqGetPreset gp;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqGetPreset);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_preset,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gp.chId=chId;  gp.devIdH=devIdH;
    gp.devIdL=devIdL;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&gp,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResGetPreset(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt32 pLen,
        _UInt16 *proset
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResGetPreset gp;
    if(ptr==NULL || proset==NULL ) return False;
    if(pLen>sizeof(gp.proset)) return False;

    /*_UInt32 */len=sizeof(ResGetPreset);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_preset,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gp.chId=chId;  gp.devIdH=devIdH;
    gp.devIdL=devIdL;
    memcpy(gp.proset,proset,pLen);
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&gp,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*修改预置点*/
_UBool setReqModPreset(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt8  cType,
        _UInt16 point
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqModPreset mp;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqModPreset);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,modify_preset,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    mp.chId=chId;  mp.cType=cType;
    mp.devIdH=devIdH;  mp.devIdL=devIdL;
    mp.point=point;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&mp,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResModPreset(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResModPreset mp;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResModPreset);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,modify_preset,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    mp.chId=chId;  mp.devIdH=devIdH;
    mp.devIdL=devIdL;
    mp.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&mp,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*获取巡航配置*/
_UBool setReqGetCruiseConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqGetCruiseConf gcConf;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqGetCruiseConf);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_curise_conf,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gcConf.chId=chId;  gcConf.devIdH=devIdH;
    gcConf.devIdL=devIdL;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&gcConf,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResGetCruiseConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt32 listLen,
        _UInt16 *list
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResGetCruiseConf gcConf;
    if(ptr==NULL || list==NULL) return False;
    if(listLen>sizeof(gcConf.list)) return False;

    /*_UInt32 */len=sizeof(ResGetCruiseConf);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_curise_conf,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gcConf.chId=chId;  gcConf.devIdH=devIdH;
    gcConf.devIdL=devIdL;
    memcpy(gcConf.list,list,listLen);
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&gcConf,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*修改巡航配置*/
_UBool setReqModCruiseConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt32 listLen,
        _UInt16 *list
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqModCruiseConf mcConf;
    if(ptr==NULL) return False;
    if(listLen>sizeof(mcConf.list)) return False;

    /*_UInt32 */len=sizeof(ReqModCruiseConf);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,modify_curise_conf,0x00);

    
    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    mcConf.chId=chId;  mcConf.devIdH=devIdH;
    mcConf.devIdL=devIdL;
    memcpy(mcConf.list,list,listLen);
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&mcConf,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResModCruiseConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResModCruiseConf mcConf;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResModCruiseConf);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,modify_curise_conf,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    mcConf.chId=chId;  mcConf.devIdH=devIdH;
    mcConf.devIdL=devIdL;
    mcConf.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&mcConf,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*获取邮箱配置*/
_UBool setReqGetEmailConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqGetEmailConf geConf;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqGetEmailConf);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_email_conf,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    geConf.devIdH=devIdH;  geConf.devIdL=devIdL;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&geConf,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResGetEmailConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  *eServer,
        _UInt32 serverLen,
        _UInt16 port,
        _UInt8  sType,
        _UInt8  *sName,
        _UInt32 nameLen,
        _UInt8  *sPasswd,
        _UInt32 passwdLen,
        _UInt32 timeOut,
        _UInt8  *recver1,
        _UInt32 len1,
        _UInt8  *recver2,
        _UInt32 len2,
        _UInt8  *recver3,
        _UInt32 len3,
        _UInt8  *recver4,
        _UInt32 len4
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResGetEmailConf ge;
    if(ptr==NULL || eServer==NULL || sName==NULL || sPasswd==NULL
            || recver1==NULL || recver2==NULL || recver3==NULL ||
            recver4==NULL) return False;
    if(serverLen>sizeof(ge.eServer)) return False;
    if(nameLen>sizeof(ge.sName))return False;
    if(passwdLen>sizeof(ge.sPasswd))return False;
    if(len1>sizeof(ge.recver1))return False;
    if(len2>sizeof(ge.recver2))return False;
    if(len3>sizeof(ge.recver3))return False;
    if(len4>sizeof(ge.recver4))return False;

    /*_UInt32 */len=sizeof(ResGetEmailConf);

    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_email_conf,0x01);
    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    ge.devIdH=devIdH;
    ge.devIdL=devIdL;
    memcpy(ge.eServer,eServer,strlen(eServer));
    ge.port=port;
    ge.sType=sType;
    memcpy(ge.sName,sName,nameLen);
    memcpy(ge.sPasswd,sPasswd,passwdLen);
    ge.timeOut=timeOut;
    memcpy(ge.recver1,recver1,len1);
    memcpy(ge.recver2,recver2,len2);
    memcpy(ge.recver3,recver3,len3);
    memcpy(ge.recver4,recver4,len4);

    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&ge,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*修改邮箱配置*/
_UBool setReqModEmailConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8 *eServer,
        _UInt32 serverLen,
        _UInt16 port,
        _UInt8 sType,
        _UInt8 *sName,
        _UInt32 nameLen,
        _UInt8 *sPasswd,
        _UInt32 passwdLen,
        _UInt32 timeOut,
        _UInt8 *recver1,
        _UInt32 len1,
        _UInt8 *recver2,
        _UInt32 len2,
        _UInt8 *recver3,
        _UInt32 len3,
        _UInt8 *recver4,
        _UInt32 len4
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqModEmailConf ge;

    if(ptr==NULL || eServer==NULL || sName==NULL || sPasswd==NULL
            || recver1==NULL || recver2==NULL || recver3==NULL ||
            recver4==NULL) return False;
    if(serverLen>sizeof(ge.eServer)) return False;
    if(nameLen>sizeof(ge.sName))return False;
    if(passwdLen>sizeof(ge.sPasswd))return False;
    if(len1>sizeof(ge.recver1))return False;
    if(len2>sizeof(ge.recver2))return False;
    if(len3>sizeof(ge.recver3))return False;
    if(len4>sizeof(ge.recver4))return False;

    /*_UInt32 */len=sizeof(ReqModEmailConf);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,modify_email_conf,0x00);
    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    ge.devIdH=devIdH;
    ge.devIdL=devIdL;
    if(serverLen>sizeof(ge.eServer)) return False;
    memcpy(ge.eServer,eServer,serverLen);
    ge.port=port;
    ge.sType=sType;
    memcpy(ge.sName,sName,nameLen);
    memcpy(ge.sPasswd,sPasswd,passwdLen);
    ge.timeOut=timeOut;
    memcpy(ge.recver1,recver1,len1);
    memcpy(ge.recver2,recver2,len2);
    memcpy(ge.recver3,recver3,len3);
    memcpy(ge.recver4,recver4,len4);
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&ge,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResModEmailConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8 chId,
        _UInt8 result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResModEmailConf meConf;
    if(ptr==NULL)return False;
    /*_UInt32 */len=sizeof(ResModEmailConf);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,modify_email_conf,0x01);
    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    meConf.chId=chId;
    meConf.devIdH=devIdH;  meConf.devIdL=devIdL;
    meConf.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&meConf,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*测试邮箱配置*/
_UBool setReqTestEmailConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqTestEmailConf teConf;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqTestEmailConf);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,test_email_conf,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    teConf.devIdH=devIdH;  teConf.devIdL=devIdL;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&teConf,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResTestEmailConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8 result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResTestEmailConf teConf;
    if(ptr==NULL)  return False;
    /*_UInt32 */len=sizeof(ResTestEmailConf);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,test_email_conf,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    teConf.devIdH=devIdH;  teConf.devIdL=devIdL;
    teConf.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&teConf,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*遥控开关设置*/
_UBool setReqRemoteControlSet(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8 wSwitch
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqRemoteControlSet rcSet;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqRemoteControlSet);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,set_remote_switch,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    rcSet.devIdH=devIdH;  rcSet.devIdL=devIdL;
    rcSet.wSwitch=wSwitch;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&rcSet,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResRemoteControlSet(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResRemoteControlSet rc;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResRemoteControlSet);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,set_remote_switch,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    rc.devIdH=devIdH;  rc.devIdL=devIdL;
    rc.result =result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&rc,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*遥控开关状态获取*/
_UBool setReqRemoteControlGet(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wSwitch
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqRemoteControlGet rcGet;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqRemoteControlGet);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_remote_switch_state,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    rcGet.devIdH=devIdH;  rcGet.devIdL=devIdL;
    rcGet.wSwitch=wSwitch;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&rcGet,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResRemoteControlGet(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  sState
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResRemoteControlGet rcGet;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResRemoteControlGet);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_remote_switch_state,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    rcGet.devIdH=devIdH;  rcGet.devIdL=devIdL;
    rcGet.sState=sState;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&rcGet,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*设置硬盘参数*/
_UBool setReqSetHardDiskParm(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8   hdSize
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqSetHardDiskParm hd;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqSetHardDiskParm);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,set_hard_disk_parms,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    hd.devIdH=devIdH;  hd.devIdL=devIdL;
    hd.hdSize=hdSize;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&hd,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResSetHardDiskParm(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResSetHardDiskParm hd;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResSetHardDiskParm);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,set_hard_disk_parms,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    hd.devIdH=devIdH;  hd.devIdL=devIdL;
    hd.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&hd,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*格式化*/
_UBool setReqFormat(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  operation
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqFormat rFormat;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqFormat);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,format,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    rFormat.devIdH=devIdH;  rFormat.devIdL=devIdL;
    rFormat.operation=operation;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&rFormat,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResFormat(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResFormat rFormat;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResFormat);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,format,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    rFormat.devIdH=devIdH;  rFormat.devIdL=devIdL;
    rFormat.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&rFormat,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*录像满*/
_UBool setReqVideoFull(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  vFull
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqVideoFull vf;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqVideoFull);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,full_video,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    vf.devIdH=devIdH;  vf.devIdL=devIdL;
    vf.vFull=vFull;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&vf,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResVideoFull(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResVideoFull vf;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResVideoFull);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,full_video,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    vf.devIdH=devIdH;  vf.devIdL=devIdL;
    vf.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&vf,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*对讲*/
_UBool setReqTalk(
        HandlePtr ptr,
        _UInt16 rPort,
        _UInt8  code
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqTalk rTalk;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqTalk);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,talk,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    rTalk.code=code;  rTalk.rPort=rPort;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&rTalk,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResTalk(
        HandlePtr ptr,
        _UInt8 result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResTalk rTalk;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResTalk);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,talk,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    rTalk.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&rTalk,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*音频下载*/
_UBool setReqAudioDownload(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt32 sTime,
        _UInt32 eTime,
        _UInt8  *fName,
        _UInt32 nameLen
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqAudioDownload ad;
    if(ptr==NULL || fName==NULL) return False;
    if(nameLen>sizeof(ad.fName)) return False;

    /*_UInt32 */len=sizeof(ReqAudioDownload);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,audio_download,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    ad.chId=chId;  ad.devIdH=devIdH;
    ad.devIdL=devIdL;  ad.eTime=eTime;
    ad.sTime=sTime;
    memcpy(ad.fName,fName,nameLen);
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&ad,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResAudioDownload(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt32 sTime,
        _UInt32 eTime,
        _UInt8  *path,
        _UInt32  pathLen,
        _UInt8  *fName,
        _UInt32 nameLen
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResAudioDownload ad;
    if(ptr==NULL || path==NULL || fName==NULL) return False;
    if(nameLen>sizeof(ad.fName)) return False;
    if(pathLen>sizeof(ad.path)) return False;

    /*_UInt32 */len=sizeof(ResAudioDownload);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;

    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,audio_download,0x01);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    ad.chId=chId;  ad.devIdH=devIdH;
    ad.devIdL=devIdL;  ad.eTime=eTime;
    ad.sTime=sTime;
    memcpy(ad.fName,fName,nameLen);
    memcpy(ad.path,path,pathLen);

    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&ad,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*视频下载*/
_UBool setReqVideoDownload(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt32 sTime,
        _UInt32 eTime,
        _UInt8  *fName,
        _UInt32 nameLen
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqVideoDownload vd;
    if(ptr==NULL || fName==NULL) return False;
    if(nameLen>sizeof(vd.fName)) return False;

    /*_UInt32 */len=sizeof(ReqVideoDownload);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,video_download,0x00);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    vd.chId=chId;  vd.devIdH=devIdH;
    vd.devIdL=devIdL;  vd.eTime=eTime;
    vd.sTime=sTime;
    memcpy(vd.fName,fName,strlen(fName));

    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&vd,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResVideoDownload(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt32 sTime,
        _UInt32 eTime,
        _UInt8  *path,
        _UInt32 pathLen,
        _UInt8  *fName,
        _UInt32 nameLen
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResVideoDownload vd;

    if(ptr==NULL || path==NULL || fName==NULL) return False;
    if(pathLen>sizeof(vd.path)) return False;
    if(nameLen>sizeof(vd.fName)) return False;

    /*_UInt32 */len=sizeof(ResVideoDownload);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,video_download,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    vd.chId=chId;  vd.devIdH=devIdH;
    vd.devIdL=devIdL;  vd.eTime=eTime;
    vd.sTime=sTime;
    memcpy(vd.path,path,pathLen);
    memcpy(vd.fName,fName,nameLen);
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&vd,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*刷图*/
_UBool setReqRefresh(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqRefresh fresh;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqRefresh);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,refresh_pic,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    fresh.chId=chId;  fresh.devIdH=devIdH;
    fresh.devIdL=devIdL;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&fresh,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResRefresh(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResRefresh fresh;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResRefresh);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;

    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,refresh_pic,0x01);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    fresh.devIdH=devIdH;  fresh.devIdL=devIdL;
    fresh.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&fresh,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*视频播放操作*/
_UBool setReqVideoPlay(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt32 stream,
        _UInt32 time,
        _UInt16 port,
        _UInt8  oType,
        _UInt8  extend
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqVideoPlay vp;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqVideoPlay);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,play_video,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    vp.chId=chId;  vp.devIdH=devIdH;
    vp.devIdL=devIdL;  vp.extend=extend;
    vp.oType=oType;  vp.port=port;
    vp.stream=stream;  vp.time=time;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&vp,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResVideoPlay(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResVideoPlay vp;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResVideoPlay);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,play_video,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    vp.devIdH=devIdH;  vp.devIdL=devIdL;
    vp.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&vp,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*获取视频参数*/
_UBool setReqGetVideoParms(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt16 stream
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqGetVideoParms getVp;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqGetVideoParms);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_video_parms,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    getVp.chId=chId;  getVp.devIdH=devIdH;
    getVp.devIdL=devIdL;  getVp.stream=stream;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&getVp,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResGetVideoParms(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt16 stream,
        _UInt16 width,
        _UInt16 height,
        _UInt16 sRate,
        _UInt16 fRate
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResGetVideoParms getVP;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResGetVideoParms);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,get_video_parms,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    getVP.chId=chId;                getVP.devIdH=devIdH;
    getVP.devIdL=devIdL;        getVP.fRate=fRate;
    getVP.height=height;          getVP.sRate=sRate;
    getVP.stream=stream;       getVP.width=width;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&getVP,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*设置视频参数*/
_UBool setReqSetVideoParms(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt16 stream,
        _UInt16 width,
        _UInt16 height,
        _UInt16 sRate,
        _UInt16 fRate
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqSetVideoParms sVp;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqSetVideoParms);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,set_video_parms,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    sVp.chId=chId;            sVp.devIdH=devIdH;
    sVp.devIdL=devIdL;    sVp.fRate=fRate;
    sVp.height=height;     sVp.sRate=sRate;
    sVp.stream=stream;   sVp.width=width;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&sVp,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResSetVideoParms(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt16 stream,
        _UInt8  type
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResSetVideoParms sVp;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResSetVideoParms);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,set_video_parms,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    sVp.chId=chId;  sVp.devIdH=devIdH;
    sVp.devIdL=devIdL;  sVp.stream=stream;
    sVp.type=type;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&sVp,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*视频打开操作*/
_UBool setReqVideoOpen(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  operation,
        _UInt8  chId,
        _UInt16 port
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqVideoOpen vo;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqVideoOpen);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,video_open,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    vo.chId=chId;  vo.devIdH=devIdH;
    vo.devIdL=devIdL;  vo.operation=operation;
    vo.port=port;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&vo,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResVideoOpen(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt16 stream
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResVideoOpen vo;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResVideoOpen);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,manager_dev,video_open,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    vo.chId=chId;  vo.devIdH=devIdH;
    vo.devIdL=devIdL;  vo.stream=stream;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&vo,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*设备远程重启*/
_UBool setReqDevRemoteRestart(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  rRestart
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqDevRemoteRestart drr;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqDevRemoteRestart);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,weihu_dev,restart_remote_dev,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    drr.devIdH=devIdH;  drr.devIdL=devIdL;
    drr.rRestart=rRestart;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&drr,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResDevRemoteRestart(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResDevRemoteRestart drr;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResDevRemoteRestart);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,weihu_dev,restart_remote_dev,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    drr.devIdH=devIdH;  drr.devIdL=devIdL;
    drr.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&drr,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*设备升级*/
_UBool setReqDevUpgrade(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  *fContent,/*此处为文件内容，每次1KB数据，如不能数据量不足1KB仍按1KB发送，在最后一字节数据后加'\0'*/
        _UInt32 contentLen
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqDevUpgrade du;
    if(ptr==NULL || fContent==NULL) return False;
    if(contentLen>sizeof(du.fContent)) return False;

    /*_UInt32 */len=sizeof(ReqDevUpgrade);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,weihu_dev,upgrade_de,0x00);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    du.devIdH=devIdH;  du.devIdL=devIdL;
    memcpy(du.fContent,fContent,strlen(fContent));
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&du,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResDevUpgrade(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  *fName,
        _UInt32 nameLen
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResDevUpgrade du;
    if(ptr==NULL || fName==NULL) return False;
    if(nameLen>sizeof(du.fName)) return False;

    /*_UInt32 */len=sizeof(ResDevUpgrade);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,weihu_dev,upgrade_de,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    du.devIdH=devIdH;  du.devIdL=devIdL;
    memcpy(du.fName,fName,strlen(fName));
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&du,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*客户端上线*/
_UBool setReqClientConn(
        HandlePtr ptr,
        _UInt8 *name,
        _UInt32 nameLen,
        _UInt8 *passwd,
        _UInt32 passwdLen

        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqClientConn cc;
    if(ptr==NULL || name==NULL || passwd==NULL) return False;
    if(nameLen>sizeof(cc.name)) return False;
    if(passwdLen>sizeof(cc.passwd)) return False;

    /*_UInt32 */len=sizeof(ReqClientConn);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,conn_disconn_client,conn_client,0x00);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    memcpy(cc.name,name,strlen(name));
    memcpy(cc.passwd,passwd,strlen(passwd));
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&cc,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResClientConn(
        HandlePtr ptr,
        _UInt8 result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResClientConn cc;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResClientConn);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,conn_disconn_client,conn_client,0x01);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    cc.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&cc,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*客户端下线*/
_UBool setReqClientDisConn(
        HandlePtr ptr,
        _UInt8  *name,
        _UInt32 nameLen,
        _UInt8  *passwd,
        _UInt32 passwdLen,
        _UInt16 code,
        _UInt32 ip,
        _UInt16 port,
        _UInt8  natType
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqClientDisConn cdc;
    if(ptr==NULL || name==NULL || passwd==NULL) return False;
    if(nameLen>sizeof(cdc.name)) return False;
    if(passwdLen>sizeof(cdc.passwd)) return False;

    /*_UInt32 */len=sizeof(ReqClientDisConn);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;

    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,conn_disconn_client,disconn_client,0x00);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    cdc.code=code;  cdc.ip=ip;
    cdc.natType=natType;  cdc.port=port;
    memcpy(cdc.name,name,strlen(name));
    memcpy(cdc.passwd,passwd,strlen(passwd));
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&cdc,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResClientDisConn(
        HandlePtr ptr,
        _UInt8  *name,
        _UInt32 nameLen,
        _UInt8  power,
        _UInt32 province,
        _UInt32 city,
        _UInt32 country,
        _UInt32 town,
        _UInt32 village
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResClientDisConn dc;
    if(ptr==NULL || name==NULL) return False;
    if(nameLen>sizeof(dc.name)) return False;

    /*_UInt32 */len=sizeof(ResClientDisConn);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;

    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,conn_disconn_client,disconn_client,0x01);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    memcpy(dc.name,name,strlen(name));
    dc.city=city;  dc.country=country;
    dc.power=power;  dc.province=province;
    dc.town=town;  dc.village=village;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&dc,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*用户注册*/
_UBool setReqUserRegister(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  *loginName,
        _UInt32 nameLen,
        _UInt8  *loginPasswd,
        _UInt32 passwdLen,
        _UInt8  *email,
        _UInt32 emailLen,
        _UInt8  *phone,
        _UInt32 phoneLen
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqUserRegister ur;
    if(ptr==NULL || loginName==NULL || loginPasswd==NULL
            || email==NULL || phone==NULL) return False;
    if(nameLen>sizeof(ur.loginName)) return False;
    if(passwdLen>sizeof(ur.loginPasswd)) return False;
    if(emailLen>sizeof(ur.email)) return False;
    if(phoneLen>sizeof(ur.phone)) return False;

    /*_UInt32 */len=sizeof(ReqUserRegister);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,user,user_register,0x00);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    ur.devIdH=devIdH;
    ur.devIdL=devIdL;
    memcpy(ur.loginName,loginName,nameLen);
    memcpy(ur.loginPasswd,loginPasswd,passwdLen);
    memcpy(ur.email,email,emailLen);
    memcpy(ur.phone,phone,phoneLen);
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&ur,len);
    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResUserRegister(
        HandlePtr ptr,
        _UInt8 result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResUserRegister ur;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResUserRegister);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,user,user_register,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    ur.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&ur,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*用户信息获取*/
_UBool setReqGetUserInfo(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  get
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqGetUserInfo gUi;
    if(ptr==NULL) return False;

    /*_UInt32 */len=sizeof(ReqGetUserInfo);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;

    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,user,get_user_info,0x00);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gUi.devIdH=devIdH;
    gUi.devIdL=devIdL;
    gUi.get=get;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&gUi,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResGetUserInfo(
        HandlePtr ptr,
        _UInt8  *name,
        _UInt32 nameLen,
        _UInt8  *passwd,
        _UInt32 passwdLen,
        _UInt8  type,
        _UInt16 power,
        _UInt16 area,
        _UInt16 operation
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResGetUserInfo gUi;
    if(ptr==NULL || name==NULL || passwd==NULL) return False;
    if(nameLen>sizeof(gUi.name)) return False;
    if(passwdLen>sizeof(gUi.passwd)) return False;

    /*_UInt32 */len=sizeof(ResGetUserInfo);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,user,get_user_info,0x01);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gUi.area=area;
    gUi.operation=operation;
    gUi.power=power;
    gUi.type=type;
    memcpy(gUi.name,name,nameLen);
    memcpy(gUi.passwd,passwd,passwdLen);
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&gUi,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*用户信息增加*/
_UBool setReqAddUserInfo(
        HandlePtr ptr,
        _UInt8 *name,
        _UInt32 nameLen,
        _UInt8 *passwd,
        _UInt32 passwdLen,
        _UInt8 type,
        _UInt8 power,
        _UInt16 area,
        _UInt16 operaion
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqAddUserInfo aUi;
    if(ptr==NULL || name==NULL || passwd==NULL) return False;
    if(nameLen>sizeof(aUi.name)) return False;
    if(passwdLen>sizeof(aUi.passwd)) return False;

    /*_UInt32 */len=sizeof(ReqAddUserInfo);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,user,add_user_info,0x00);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    aUi.area=area;
    aUi.operaion=operaion;
    aUi.power=power;
    aUi.type=type;
    memcpy(aUi.name,name,strlen(name));
    memcpy(aUi.passwd,passwd,strlen(passwd));
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&aUi,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResAddUserInfo(
        HandlePtr ptr,
        _UInt8 result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResAddUserInfo aUi;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResAddUserInfo);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,user,add_user_info,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    aUi.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&aUi,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*用户信息删除*/
_UBool setReqDelUserInfo(
        HandlePtr ptr,
        _UInt8 *name,
        _UInt32 nameLen
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqDelUserInfo dUi;
    if(ptr==NULL || name==NULL) return False;
    if(nameLen>sizeof(dUi.name)) return False;

    /*_UInt32 */len=sizeof(ReqDelUserInfo);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;

    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,user,del_user_info,0x00);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    memcpy(dUi.name,name,nameLen);
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&dUi,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResDelUserInfo(
        HandlePtr ptr,
        _UInt8 result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResDelUserInfo dUi;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResDelUserInfo);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,user,del_user_info,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    dUi.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&dUi,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*用户信息修改*/
_UBool setReqModUserInfo(
        HandlePtr ptr,
        _UInt8 *name,
        _UInt32 nameLen,
        _UInt8 *passwd,
        _UInt32 passwdLen,
        _UInt8 type,
        _UInt8 power,
        _UInt16 area,
        _UInt16 operation
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqModUserInfo mUi;
    if(ptr==NULL || name==NULL || passwd==NULL) return False;
    if(nameLen>sizeof(mUi.name)) return False;
    if(passwdLen>sizeof(mUi.passwd)) return False;

    /*_UInt32 */len=sizeof(ReqModUserInfo);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,user,modify_user_info,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    mUi.area=area;
    mUi.operaion=operation;
    mUi.power=power;
    mUi.type=type;
    memcpy(mUi.name,name,strlen(name));
    memcpy(mUi.passwd,passwd,strlen(passwd));
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&mUi,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResModUserInfo(
        HandlePtr ptr,
        _UInt8 result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResModUserInfo mUi;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResModUserInfo);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,user,modify_user_info,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    mUi.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&mUi,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*设备信息获取*/
_UBool setReqGetDevInfo(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  get
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqGetDevInfo gDi;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqGetDevInfo);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,info_dev,get_dev_info,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gDi.devIdH=devIdH;  gDi.devIdL=devIdL;
    gDi.get=get;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&gDi,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResGetDevInfo(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 chId,
        _UInt8  devType,
        _UInt8  *ip,
        _UInt32 ipLen
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResGetDevInfo gDi;
    if(ptr==NULL || ip==NULL) return False;
    if(ipLen>sizeof(gDi.ip)) return False;

    /*_UInt32 */len=sizeof(ResGetDevInfo);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,info_dev,get_dev_info,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    gDi.chId=chId;  gDi.devIdH=devIdH;
    gDi.devIdL=devIdL;  gDi.devType=devType;
    memcpy(gDi.ip,ip,strlen(ip));
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&gDi,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*设备信息删除*/
_UBool setReqDelDevInfo(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqDelDevInfo dDi;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqDelDevInfo);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,info_dev,del_dev_info,0x00);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    dDi.devIdH=devIdH;  dDi.devIdL=devIdL;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&dDi,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResDelDevInfo(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResDelDevInfo dDi;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResDelDevInfo);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,info_dev,del_dev_info,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    dDi.devIdH=devIdH;  dDi.devIdL=devIdL;
    dDi.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&dDi,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*设备信息修改*/
_UBool setReqModDevInfo(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  conf
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqModDevInfo mDi;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ReqModDevInfo);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,info_dev,modify_dev_info,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    mDi.conf=conf;  mDi.devIdH=devIdH;
    mDi.devIdL=devIdL;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&mDi,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResModDevInfo(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResModDevInfo mDi;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResModDevInfo);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,info_dev,modify_dev_info,0x01);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    mDi.devIdH=devIdH;  mDi.devIdL=devIdL;
    mDi.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&mDi,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*设备添加*/
_UBool setReqAddDev(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 chNum,
        _UInt8  dType,
        _UInt8  *name,
        _UInt32 nameLen,
        _UInt8  *passwd,
        _UInt32 passwdLen,
        _UInt8  *ip,
        _UInt32 ipLen
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqAddDev ad;
    if(ptr==NULL || name==NULL ||
            passwd==NULL || ip==NULL) return False;
    if(nameLen>sizeof(ad.name)) return False;
    if(passwdLen>sizeof(ad.passwd)) return False;
    if(ipLen>sizeof(ad.ip)) return False;

    /*_UInt32 */len=sizeof(ReqAddDev);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,info_dev,add_dev,0x00);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    ad.chNum=chNum;  ad.devIdH=devIdH;
    ad.devIdL=devIdL;  ad.dType=dType;
    memcpy(ad.name,name,nameLen);
    memcpy(ad.passwd,passwd,passwdLen);
    memcpy(ad.ip,ip,ipLen);

    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&ad,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResAddDev(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResAddDev ad;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResAddDev);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    //  //addDataToBuf((_SInt8 *)pos,(_SInt8 *)NULL,len);

    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,info_dev,add_dev,0x01);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    ad.devIdH=devIdH;  ad.devIdL=devIdL;
    ad.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&ad,len);
    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*服务器分发报警*/
_UBool setReqServerHandOutWarn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wType,
        _UInt8  chId,
        _UInt8  *wMessage,
        _UInt32 messageLen
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqServerHandOutWarn oWarn;
    if(ptr==NULL || wMessage==NULL) return False;
    if(messageLen>sizeof(oWarn.wMessage)) return False;

    /*_UInt32 */len=sizeof(ReqServerHandOutWarn);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,warn,server_send_warn,0x00);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    oWarn.chId=chId;            oWarn.devIdH=devIdH;
    oWarn.devIdL=devIdL;
    memcpy(oWarn.wMessage,wMessage,strlen(wMessage));
    oWarn.wType=wType;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&oWarn,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResServerHandOutWarn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResServerHandOutWarn ow;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResServerHandOutWarn);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,warn,server_send_warn,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    ow.devIdH=devIdH;  ow.devIdL=devIdL;
    ow.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&ow,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*服务器抛出存储报警*/
_UBool setReqServerThrowWarn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wType,
        _UInt8  chId,
        _UInt8  *wMessage,
        _UInt32 messageLen
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqServerThrowWarn tw;
    if(ptr==NULL || wMessage==NULL) return False;
    if(messageLen>sizeof(tw.wMessage)) return False;

    /*_UInt32 */len=sizeof(ReqServerThrowWarn);
    /*_UInt8 **/currentPos=preProcess(ptr,len);

    if(currentPos==NULL) return False;

    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,warn,server_throw_mem_warn,0x00);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    tw.chId=chId;  tw.devIdH=devIdH;
    tw.devIdL=devIdL;
    memcpy(tw.wMessage,wMessage,messageLen);
    tw.wType=wType;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&tw,len);

    //setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResServerThrowWarn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResServerThrowWarn tw;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResServerThrowWarn);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
//setHeader(pos,len,0x00,warn,server_throw_mem_warn,0x01);

    /*处理用户数据*/
    pos+=FRAME_HEAD_FIXED_FILED;
    tw.devIdH=devIdH;  tw.devIdL=devIdL;
    tw.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&tw,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
