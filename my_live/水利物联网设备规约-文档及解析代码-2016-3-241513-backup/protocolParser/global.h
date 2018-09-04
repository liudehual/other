/*********************************************************************************
  *Copyright(
    HandlePtr ptr,C),2010-2016,fencer Company
  *FileName: global.h
  *Author:  高春田
  *Version:  1.0
  *Date:  2016/1/14
  *Description: 命令定义
  *Others:  无
  *Function List:
     1.…………
     2.…………
  *History:
     1.Date:
       Author:
       Modification:
     2.…………
**********************************************************************************/
#ifndef _GLOBAL_
#define _GLOBAL_

#ifdef  __Win32__
#include <windows.h>
#include <winsock2.h>
#include <mswsock.h>
#include <process.h>
#include <ws2tcpip.h>
#include <io.h>
#include <direct.h>
#include <errno.h>
#elif __linux__
#include <sys/errno.h>
#include <pthread.h>
#include <unistd.h>
#endif

#define QUIET 0 /*打开静默模式*/

#if QUIET
#define DEBUG   0 /*调试信息*/
#define ERROR   0 /*出错信息*/
#define HELPER  0 /*一些其他辅助信息*/
#endif

#if !QUIET
#define DEBUG  1 /*调试信息*/
#define ERROR  1 /*出错信息*/
#define HELPER 1 /*一些其他辅助信息*/
#endif

#define True 1
#define False 0

#define STRUCT typedef struct

typedef unsigned char       _UInt8;
typedef signed char         _SInt8;
typedef unsigned short      _UInt16;
typedef signed short        _SInt16;
typedef unsigned long       _UInt32;
typedef signed long         _SInt32;
typedef signed long long    _SInt64;
typedef unsigned long long  _UInt64;
typedef float               _UFloat;

typedef _UInt16 _UBool;

/**
    函数名:
    描述:命令回调
    参数:
    mainCommand 主命令。最大255 最小 0
    minorCommand 副命令。 最大 255 最小 0
    reqOrRes 请求命令、响应命令。 0 请求命令 1 响应命令
    content 命令内容.具体命令请根据 mainCommand minorCommand 转化
    len 命令体长度
    返回值:无
**/
typedef void  (*_CallbackProcPtr)(int mainCommand,int minorCommand,int reqOrRes,void *buffer,int len);

/**
 *  该结构体定义了每个申请用户可能用到的所有数据
 *  接收缓冲区和发送缓冲区可以在不同的线程中使用，如发送缓冲区在A线程、接收缓冲区在B线程。但同一个缓冲区只能在一个线程中使用
 *  如发送缓冲区只可在A线程中使用,不可再其他线程中使用，如果同一个缓冲区被用于多个线程则不能保证数据的完整性
 *  如果为多线程，则每个线程需拥有自己的句柄结构
 *
**/
STRUCT
{
    _UInt8 station;/*0 主站(服务端)，1 子站(客户端、设备端)*/
    _UInt8 devType;/*0 单片机 1 非单片机 其他值无效*/
    
    _UInt8 *rBuf; /*接收内存空间首地址*/
    _UInt32 rBufSize; /*接收申请内存大小*/
    _UInt32 rContentSize; /*空间中内容长度*/
    _CallbackProcPtr rCallBack;
#ifdef __Win32__
    CRITICAL_SECTION rMutex;
#elif  __linux__
    pthread_mutex_t rMutex;
#endif

    _UInt8 *sBuf; /*发送缓冲区首地址*/
    _UInt32 sBufSize; /*接收缓冲区内存大小*/
    _UInt32 sContentSize; /*空间内容长度*/
#ifdef __Win32__
    CRITICAL_SECTION sMutex;
#elif  __linux__
    pthread_mutex_t sMutex;
#endif

}Handle,*HandlePtr;

/*固定帧头*/
STRUCT
{
 /*起始字符*/
 _UInt8 start1;
 
 /*帧长度(控制域、地址域、应用服务数据单元之和)*/
 _UInt16 len;

 /*起始字符*/
 _UInt8 start2;  

 /*控制域*/
 _UInt8 res:1;     /*RES*/
 _UInt8 prm:1;     /*PRM*/
 _UInt8 fcbAcd:1;  /*FCB 或 ACD*/
 _UInt8 fcvDfc:1;  /*FCV 或 DFC*/
 _UInt8 funCode:4; /*功能码*/

 /*地址域*/
 _UInt8 addr;

 /*类型提示*/
 _UInt8 type;

 /*可变结构限定词*/
 _UInt8 sort:1;    /*元素是否排序 0 不排序 1 排序*/
 _UInt8 eleNum:7;  /*元素个数*/

 /*传输原因*/
 _UInt8 t:1;       /*1 实验 0 未实验*/
 _UInt8 pn:1;      /*0 否认确认 1 肯定确认*/
 _UInt8 other:5;   /*其它*/
 _UInt8 nUse:1;    /*未使用，默认置零*/

 /*公共地址*/
 _UInt8 publicAddr;

 /*信息体地址*/
 _UInt16 informosome; 
}Frame;

/*遥信*/                                                                                           
enum                                                                                               
{                                                                                                  
	       eRemoteSignalingState1        =       0x0001     ,//      状态口1              
	       eRemoteSignalingState2        =       0x0002     ,//      状态口2              
	       eRemoteSignalingState3        =       0x0003     ,//      状态口3              
	       eRemoteSignalingState4        =       0x0004     ,//      状态口4              
	       eRemoteSignalingState5        =       0x0005     ,//      状态口5              
	       eRemoteSignalingState6        =       0x0006     ,//      状态口6              
	       eRemoteSignalingState7        =       0x0007     ,//      状态口7              
	       eRemoteSignalingState8        =       0x0008     ,//      状态口8              
	       eRemoteSignalingState9        =       0x0009     ,//      状态口9              
	       eRemoteSignalingState10       =       0x000A     ,//      状态口10             
	       eRemoteSignalingState11       =       0x000B     ,//      状态口11             
	       eRemoteSignalingState12       =       0x000C     ,//      状态口12             
	       eRemoteSignalingState13       =       0x000D     ,//      状态口13             
	       eRemoteSignalingState14       =       0x000E     ,//      状态口14             
	       eRemoteSignalingState15       =       0x000F     ,//      状态口15             
	       eRemoteSignalingState16       =       0x0010     ,//      状态口16             
	       eRemoteSignalingState17       =       0x0011     ,//      状态口17             
	       eRemoteSignalingState18       =       0x0012     ,//      状态口18             
	       eRemoteSignalingState19       =       0x0013     ,//      状态口19             
	       eRemoteSignalingState20       =       0x0014     ,//      状态口20             
	       eRemoteSignalingState21       =       0x0015     ,//      状态口21             
	       eRemoteSignalingState22       =       0x0016     ,//      状态口22             
	       eRemoteSignalingState23       =       0x0017     ,//      状态口23             
	       eRemoteSignalingState24       =       0x0018     ,//      状态口24             
	       eRemoteSignalingState25       =       0x0019     ,//      状态口25             
	       eRemoteSignalingState26       =       0x001A     ,//      状态口26             
	       eRemoteSignalingState27       =       0x001B     ,//      状态口27             
	       eRemoteSignalingState28       =       0x001C     ,//      状态口28             
	       eRemoteSignalingState29       =       0x001D     ,//      状态口29             
	       eRemoteSignalingState30       =       0x001E     ,//      状态口30             
	       eRemoteSignalingState31       =       0x001F     ,//      状态口31             
	       eRemoteSignalingState32       =       0x0020      //      状态口32             
};                                                                                                 
                                                                                                   
/*遥测*/                                                                                           
enum                                                                                               
{                                                                                                  
	       eRemoteMeteringData1       =        0x4001    ,//     数据口1           
	       eRemoteMeteringData2       =        0x4002    ,//     数据口2           
	       eRemoteMeteringData3       =        0x4003    ,//     数据口3           
	       eRemoteMeteringData4       =        0x4004    ,//     数据口4           
	       eRemoteMeteringData5       =        0x4005    ,//     数据口5           
	       eRemoteMeteringData6       =        0x4006    ,//     数据口6           
	       eRemoteMeteringData7       =        0x4007    ,//     数据口7           
	       eRemoteMeteringData8       =        0x4008    ,//     数据口8           
	       eRemoteMeteringData9       =        0x4009    ,//     数据口9           
	       eRemoteMeteringData10      =        0x400A    ,//     数据口10          
	       eRemoteMeteringData11      =        0x400B    ,//     数据口11          
	       eRemoteMeteringData12      =        0x400C    ,//     数据口12          
	       eRemoteMeteringData13      =        0x400D    ,//     数据口13          
	       eRemoteMeteringData14      =        0x400E    ,//     数据口14          
	       eRemoteMeteringData15      =        0x400F    ,//     数据口15          
	       eRemoteMeteringData16      =        0x4020    ,//     数据口16          
	       eRemoteMeteringData17      =        0x4021    ,//     数据口17          
	       eRemoteMeteringData18      =        0x4022    ,//     数据口18          
	       eRemoteMeteringData19      =        0x4023    ,//     数据口19          
	       eRemoteMeteringData20      =        0x4024     //     数据口20          
	                                                                                                 
	       /*21-220保留*/                                                                            
};                                                                                                 
                                                                                                   
                                                                                                   
/*遥控*/                                                                                           
enum                                                                                               
{                                                                                             
        eRemoteControlState1        =       0x6001 ,//    状态口1            
        eRemoteControlState2        =       0x6002 ,//    状态口2            
        eRemoteControlState3        =       0x6003 ,//    状态口3            
        eRemoteControlState4        =       0x6004 ,//    状态口4            
        eRemoteControlState5        =       0x6005 ,//    状态口5            
        eRemoteControlState6        =       0x6006 ,//    状态口6            
        eRemoteControlState7        =       0x6007 ,//    状态口7            
        eRemoteControlState8        =       0x6008 ,//    状态口8            
        eRemoteControlState9        =       0x6009 ,//    状态口9            
        eRemoteControlState10       =       0x600A ,//    状态口10           
        eRemoteControlState11       =       0x600B ,//    状态口11           
        eRemoteControlState12       =       0x600C ,//    状态口12           
        eRemoteControlState13       =       0x600D ,//    状态口13           
        eRemoteControlState14       =       0x600E ,//    状态口14           
        eRemoteControlState15       =       0x600F ,//    状态口15           
        eRemoteControlState16       =       0x6010 ,//    状态口16           
        eRemoteControlState17       =       0x6011 ,//    状态口17           
        eRemoteControlState18       =       0x6012 ,//    状态口18           
        eRemoteControlState19       =       0x6013 ,//    状态口19           
        eRemoteControlState20       =       0x6014 ,//    状态口20           
        eRemoteControlState21       =       0x6015 ,//    状态口21           
        eRemoteControlState22       =       0x6016 ,//    状态口22           
        eRemoteControlState23       =       0x6017 ,//    状态口23           
        eRemoteControlState24       =       0x6018 ,//    状态口24           
        eRemoteControlState25       =       0x6019 ,//    状态口25           
        eRemoteControlState26       =       0x601A ,//    状态口26           
        eRemoteControlState27       =       0x601B ,//    状态口27           
        eRemoteControlState28       =       0x601C ,//    状态口28           
        eRemoteControlState29       =       0x601D ,//    状态口29           
        eRemoteControlState30       =       0x601E ,//    状态口30           
        eRemoteControlState31       =       0x601F ,//    状态口31           
        eRemoteControlState32       =       0x6020  //     状态口32          
                                                                                                   
};                                                                                                 

/*参数量*/
enum
{
	      eParmsDevUpgrade              =  0x5001,//        设备升级                       
	      eParmsFactoryDefaults         =  0x5002,//        恢复出厂设置          
	      eParmsGetDevInfomation        =  0x5003,//        设备信息获取           
	      eParmsGetVersion              =  0x5004,//        协议版本查询                 
	      eParmsRemoteRestart           =  0x5005,//        远程重启                
	      eParmsConnectDev              =  0x5006,//        设备上线                     
	      eParmsDisConnectDev           =  0x5007,//        设备下线                  
	      eParmsDev                     =  0x5008,//        设备心跳                  
	      eParmsSet                     =  0x5009,//        设置硬盘数         
	      eParmsFormat                  =  0x500A,//        格式化                         
	      eParmsSetstorageConfig        =  0x500B,//        存储设置             
	      eParmsSetTime                 =  0x500C,//        设置时间                      
	      eParmsSetDevConnectState      =  0x500D,//        设置设备网络状态    
	      eParmsGetDevNetState          =  0x500E,//        获取设备网络状态         
	      eParmsSetFTFConfig            =  0x500F,//        485 配置                 
	      eParmsSetTTTConfig            =  0x5010,//        232 配置                 
	      eParmsModifyWarnConfig        =  0x5011,//        修改报警配置         
	      eParmsGetWarnConfig           =  0x5012,//        获取报警设置              
	      eParmsModifyWarnSubscribe     =  0x5013,//        修改报警预约      
	      eParmsGetWarnSubscribe        =  0x5014,//        获取报警预约           
	      eParmsModifySensorConfig      =  0x5015,//        修改传感器配置     
	      eParmsGetSensorConfig         =  0x5016,//        获取传感器设置          
	      eParmsGetSensorRelation       =  0x5017,//        获取传感器对应关系  
	      eParmsSensorAuotSend          =  0x5018,//        传感器配置自动上报     
	      eParmsDevSendWarn             =  0x5019,//        设备上报报警                
	      eParmsWireless                =  0x501A,//        开关无线网卡                             
	      eParmsTimeoutSendOldData      =  0x501B,//        历史数据上报时间间隔        
	      eParmsMakeUpOldData           =  0x501C,//        数据补录             
	      eParmsGeneralWarn             =  0x501D,//        普通报警                 
	      eParmsDataWarn                =  0x501E,//        数据报警                   
	      eParmsModifyDevUser           =  0x501F,//        修改设备用户           
	      eParmsSetValue      			 		=  0x5020,//        状态值配置              
	      eParmsSetData            		  =  0x5021 //        测量值配置      
                       
};

/*多媒体操作*/
enum
{
	 eVideoPlay                   =  0x5201,//        视频播放操作     
	 eVideoParmsSet               =  0x5202,//        设置视频参数     
	 eVideoParmsGet               =  0x5203,//        获取视频参数     
	 ePicGet                      =  0x5204,//        图像             
	 eVideoDownload               =  0x5205,//        视频下载         
	 eFullVideo                   =  0x5206,//        录像满           
	 eVideoOpen                   =  0x5207,//        视频打开         
	 eAudioOper                   =  0x5208,//        音频操作         
	 eYunTaiGet                   =  0x5209,//        云台获取         
	 eYunTaiSet                   =  0x520A,//        云台设置         
	 eYunTaiControl               =  0x520B,//        云台控制         
	 eModifyPreset                =  0x520C,//        修改预置点       
	 eModifyXunHang               =  0x520D,//        修改巡航配置     
	 ePresetGet                   =  0x520E,//        获取预置点       
	 eXunHangGet                  =  0x520F //        获取巡航配置     
};

enum
{
  eReq=0x00,  /*请求*/
  eRes=0x01   /*响应*/
};

enum
{
  eSubStation,   /*子站(设备端、客户端)*/
  eMasterStation /*主站(服务端)*/
};
enum
{
    eStm=0,
    eNoStm=1
};
/**
 *   函数名: register,//andle
 *   描述:注册必要信息
 *   参数:
 *       ptr 句柄信息结构体 不可为空
 *       station 0 主站(服务端) 1 子站(设备端，客户端)
 *       devType 0 单片机 1 非单片机 
 *       sBufSize 发送缓冲区大小。 <=0 默认大小10K(单片机 100字节)， >0 && <= 60000 自定义大小， >60000 最大不大于60K(单片机不大于200字节)
 *       rBufSize 接收缓冲区大小   <=0 默认大小10K(单片机 100字节)， >0 && <60000 自定义大小， >60000 最大不大于60K(单片机不大于200字节)
 *       _CallbackProcPtr cb 用户接收命令回调函数 不可为空
 *   返回值:
 *       True 成功
 *       False 失败
 **/
_UBool registerHandle(HandlePtr ptr,_UInt8 station,_UInt8 devType,_SInt32 sBufSize,_SInt32 rBufSize,_CallbackProcPtr cb);

/**
   函数名:  removeHandle
   描述:清除句柄信息，此函数在用户不再打算使用时注销用
   参数:
     HandlePtr ptr 用户信息结构体
   返回值: 该函数返回恒为成功
**/
_UBool removeHandle(HandlePtr ptr);

enum
{
    eResetSendBuffer=0, /*重置发送缓冲区*/
    eResetRecvBuffer=1  /*重置接收缓冲区*/
};
/**
    函数名:resetBuffer
    描述:重新设置发送缓冲区或接收缓冲区
    参数:
        HandlePtr ptr 句柄信息结构体 不可为空
        sOrRBuf 0 发送缓冲区
                1 接收缓冲区
        hLen 已处理数据长度
    返回值: 该函数返回恒为成功
**/
_UBool  resetBuffer(HandlePtr ptr,_UInt32 sOrRBuf,_UInt32 hLen);

/*
    函数名:addMessage
    描述:添加接收到的信息到指定位置(从socket或其他位置)
    参数:
        ptr 句柄信息结构体 不可为空
        buf 数据
        数据长度
    返回值:
        数据过大或命令不完整 失败
    
*/
_UBool addMessage(HandlePtr ptr,char *buf,int len);
#endif
