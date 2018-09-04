/*********************************************************************************
  *Copyright(
    HandlePtr ptr,C),2010-2016,fencer Company
  *FileName: global.h
  *Author:  �ߴ���
  *Version:  1.0
  *Date:  2016/1/14
  *Description: �����
  *Others:  ��
  *Function List:
     1.��������
     2.��������
  *History:
     1.Date:
       Author:
       Modification:
     2.��������
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

#define QUIET 0 /*�򿪾�Ĭģʽ*/

#if QUIET
#define DEBUG   0 /*������Ϣ*/
#define ERROR   0 /*������Ϣ*/
#define HELPER  0 /*һЩ����������Ϣ*/
#endif

#if !QUIET
#define DEBUG  1 /*������Ϣ*/
#define ERROR  1 /*������Ϣ*/
#define HELPER 1 /*һЩ����������Ϣ*/
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
    ������:
    ����:����ص�
    ����:
    mainCommand ��������255 ��С 0
    minorCommand ����� ��� 255 ��С 0
    reqOrRes ���������Ӧ��� 0 �������� 1 ��Ӧ����
    content ��������.������������� mainCommand minorCommand ת��
    len �����峤��
    ����ֵ:��
**/
typedef void  (*_CallbackProcPtr)(int mainCommand,int minorCommand,int reqOrRes,void *buffer,int len);

/**
 *  �ýṹ�嶨����ÿ�������û������õ�����������
 *  ���ջ������ͷ��ͻ����������ڲ�ͬ���߳���ʹ�ã��緢�ͻ�������A�̡߳����ջ�������B�̡߳���ͬһ��������ֻ����һ���߳���ʹ��
 *  �緢�ͻ�����ֻ����A�߳���ʹ��,�����������߳���ʹ�ã����ͬһ�������������ڶ���߳����ܱ�֤���ݵ�������
 *  ���Ϊ���̣߳���ÿ���߳���ӵ���Լ��ľ���ṹ
 *
**/
STRUCT
{
    _UInt8 station;/*0 ��վ(�����)��1 ��վ(�ͻ��ˡ��豸��)*/
    _UInt8 devType;/*0 ��Ƭ�� 1 �ǵ�Ƭ�� ����ֵ��Ч*/
    
    _UInt8 *rBuf; /*�����ڴ�ռ��׵�ַ*/
    _UInt32 rBufSize; /*���������ڴ��С*/
    _UInt32 rContentSize; /*�ռ������ݳ���*/
    _CallbackProcPtr rCallBack;
#ifdef __Win32__
    CRITICAL_SECTION rMutex;
#elif  __linux__
    pthread_mutex_t rMutex;
#endif

    _UInt8 *sBuf; /*���ͻ������׵�ַ*/
    _UInt32 sBufSize; /*���ջ������ڴ��С*/
    _UInt32 sContentSize; /*�ռ����ݳ���*/
#ifdef __Win32__
    CRITICAL_SECTION sMutex;
#elif  __linux__
    pthread_mutex_t sMutex;
#endif

}Handle,*HandlePtr;

/*�̶�֡ͷ*/
STRUCT
{
 /*��ʼ�ַ�*/
 _UInt8 start1;
 
 /*֡����(�����򡢵�ַ��Ӧ�÷������ݵ�Ԫ֮��)*/
 _UInt16 len;

 /*��ʼ�ַ�*/
 _UInt8 start2;  

 /*������*/
 _UInt8 res:1;     /*RES*/
 _UInt8 prm:1;     /*PRM*/
 _UInt8 fcbAcd:1;  /*FCB �� ACD*/
 _UInt8 fcvDfc:1;  /*FCV �� DFC*/
 _UInt8 funCode:4; /*������*/

 /*��ַ��*/
 _UInt8 addr;

 /*������ʾ*/
 _UInt8 type;

 /*�ɱ�ṹ�޶���*/
 _UInt8 sort:1;    /*Ԫ���Ƿ����� 0 ������ 1 ����*/
 _UInt8 eleNum:7;  /*Ԫ�ظ���*/

 /*����ԭ��*/
 _UInt8 t:1;       /*1 ʵ�� 0 δʵ��*/
 _UInt8 pn:1;      /*0 ����ȷ�� 1 �϶�ȷ��*/
 _UInt8 other:5;   /*����*/
 _UInt8 nUse:1;    /*δʹ�ã�Ĭ������*/

 /*������ַ*/
 _UInt8 publicAddr;

 /*��Ϣ���ַ*/
 _UInt16 informosome; 
}Frame;

/*ң��*/                                                                                           
enum                                                                                               
{                                                                                                  
	       eRemoteSignalingState1        =       0x0001     ,//      ״̬��1              
	       eRemoteSignalingState2        =       0x0002     ,//      ״̬��2              
	       eRemoteSignalingState3        =       0x0003     ,//      ״̬��3              
	       eRemoteSignalingState4        =       0x0004     ,//      ״̬��4              
	       eRemoteSignalingState5        =       0x0005     ,//      ״̬��5              
	       eRemoteSignalingState6        =       0x0006     ,//      ״̬��6              
	       eRemoteSignalingState7        =       0x0007     ,//      ״̬��7              
	       eRemoteSignalingState8        =       0x0008     ,//      ״̬��8              
	       eRemoteSignalingState9        =       0x0009     ,//      ״̬��9              
	       eRemoteSignalingState10       =       0x000A     ,//      ״̬��10             
	       eRemoteSignalingState11       =       0x000B     ,//      ״̬��11             
	       eRemoteSignalingState12       =       0x000C     ,//      ״̬��12             
	       eRemoteSignalingState13       =       0x000D     ,//      ״̬��13             
	       eRemoteSignalingState14       =       0x000E     ,//      ״̬��14             
	       eRemoteSignalingState15       =       0x000F     ,//      ״̬��15             
	       eRemoteSignalingState16       =       0x0010     ,//      ״̬��16             
	       eRemoteSignalingState17       =       0x0011     ,//      ״̬��17             
	       eRemoteSignalingState18       =       0x0012     ,//      ״̬��18             
	       eRemoteSignalingState19       =       0x0013     ,//      ״̬��19             
	       eRemoteSignalingState20       =       0x0014     ,//      ״̬��20             
	       eRemoteSignalingState21       =       0x0015     ,//      ״̬��21             
	       eRemoteSignalingState22       =       0x0016     ,//      ״̬��22             
	       eRemoteSignalingState23       =       0x0017     ,//      ״̬��23             
	       eRemoteSignalingState24       =       0x0018     ,//      ״̬��24             
	       eRemoteSignalingState25       =       0x0019     ,//      ״̬��25             
	       eRemoteSignalingState26       =       0x001A     ,//      ״̬��26             
	       eRemoteSignalingState27       =       0x001B     ,//      ״̬��27             
	       eRemoteSignalingState28       =       0x001C     ,//      ״̬��28             
	       eRemoteSignalingState29       =       0x001D     ,//      ״̬��29             
	       eRemoteSignalingState30       =       0x001E     ,//      ״̬��30             
	       eRemoteSignalingState31       =       0x001F     ,//      ״̬��31             
	       eRemoteSignalingState32       =       0x0020      //      ״̬��32             
};                                                                                                 
                                                                                                   
/*ң��*/                                                                                           
enum                                                                                               
{                                                                                                  
	       eRemoteMeteringData1       =        0x4001    ,//     ���ݿ�1           
	       eRemoteMeteringData2       =        0x4002    ,//     ���ݿ�2           
	       eRemoteMeteringData3       =        0x4003    ,//     ���ݿ�3           
	       eRemoteMeteringData4       =        0x4004    ,//     ���ݿ�4           
	       eRemoteMeteringData5       =        0x4005    ,//     ���ݿ�5           
	       eRemoteMeteringData6       =        0x4006    ,//     ���ݿ�6           
	       eRemoteMeteringData7       =        0x4007    ,//     ���ݿ�7           
	       eRemoteMeteringData8       =        0x4008    ,//     ���ݿ�8           
	       eRemoteMeteringData9       =        0x4009    ,//     ���ݿ�9           
	       eRemoteMeteringData10      =        0x400A    ,//     ���ݿ�10          
	       eRemoteMeteringData11      =        0x400B    ,//     ���ݿ�11          
	       eRemoteMeteringData12      =        0x400C    ,//     ���ݿ�12          
	       eRemoteMeteringData13      =        0x400D    ,//     ���ݿ�13          
	       eRemoteMeteringData14      =        0x400E    ,//     ���ݿ�14          
	       eRemoteMeteringData15      =        0x400F    ,//     ���ݿ�15          
	       eRemoteMeteringData16      =        0x4020    ,//     ���ݿ�16          
	       eRemoteMeteringData17      =        0x4021    ,//     ���ݿ�17          
	       eRemoteMeteringData18      =        0x4022    ,//     ���ݿ�18          
	       eRemoteMeteringData19      =        0x4023    ,//     ���ݿ�19          
	       eRemoteMeteringData20      =        0x4024     //     ���ݿ�20          
	                                                                                                 
	       /*21-220����*/                                                                            
};                                                                                                 
                                                                                                   
                                                                                                   
/*ң��*/                                                                                           
enum                                                                                               
{                                                                                             
        eRemoteControlState1        =       0x6001 ,//    ״̬��1            
        eRemoteControlState2        =       0x6002 ,//    ״̬��2            
        eRemoteControlState3        =       0x6003 ,//    ״̬��3            
        eRemoteControlState4        =       0x6004 ,//    ״̬��4            
        eRemoteControlState5        =       0x6005 ,//    ״̬��5            
        eRemoteControlState6        =       0x6006 ,//    ״̬��6            
        eRemoteControlState7        =       0x6007 ,//    ״̬��7            
        eRemoteControlState8        =       0x6008 ,//    ״̬��8            
        eRemoteControlState9        =       0x6009 ,//    ״̬��9            
        eRemoteControlState10       =       0x600A ,//    ״̬��10           
        eRemoteControlState11       =       0x600B ,//    ״̬��11           
        eRemoteControlState12       =       0x600C ,//    ״̬��12           
        eRemoteControlState13       =       0x600D ,//    ״̬��13           
        eRemoteControlState14       =       0x600E ,//    ״̬��14           
        eRemoteControlState15       =       0x600F ,//    ״̬��15           
        eRemoteControlState16       =       0x6010 ,//    ״̬��16           
        eRemoteControlState17       =       0x6011 ,//    ״̬��17           
        eRemoteControlState18       =       0x6012 ,//    ״̬��18           
        eRemoteControlState19       =       0x6013 ,//    ״̬��19           
        eRemoteControlState20       =       0x6014 ,//    ״̬��20           
        eRemoteControlState21       =       0x6015 ,//    ״̬��21           
        eRemoteControlState22       =       0x6016 ,//    ״̬��22           
        eRemoteControlState23       =       0x6017 ,//    ״̬��23           
        eRemoteControlState24       =       0x6018 ,//    ״̬��24           
        eRemoteControlState25       =       0x6019 ,//    ״̬��25           
        eRemoteControlState26       =       0x601A ,//    ״̬��26           
        eRemoteControlState27       =       0x601B ,//    ״̬��27           
        eRemoteControlState28       =       0x601C ,//    ״̬��28           
        eRemoteControlState29       =       0x601D ,//    ״̬��29           
        eRemoteControlState30       =       0x601E ,//    ״̬��30           
        eRemoteControlState31       =       0x601F ,//    ״̬��31           
        eRemoteControlState32       =       0x6020  //     ״̬��32          
                                                                                                   
};                                                                                                 

/*������*/
enum
{
	      eParmsDevUpgrade              =  0x5001,//        �豸����                       
	      eParmsFactoryDefaults         =  0x5002,//        �ָ���������          
	      eParmsGetDevInfomation        =  0x5003,//        �豸��Ϣ��ȡ           
	      eParmsGetVersion              =  0x5004,//        Э��汾��ѯ                 
	      eParmsRemoteRestart           =  0x5005,//        Զ������                
	      eParmsConnectDev              =  0x5006,//        �豸����                     
	      eParmsDisConnectDev           =  0x5007,//        �豸����                  
	      eParmsDev                     =  0x5008,//        �豸����                  
	      eParmsSet                     =  0x5009,//        ����Ӳ����         
	      eParmsFormat                  =  0x500A,//        ��ʽ��                         
	      eParmsSetstorageConfig        =  0x500B,//        �洢����             
	      eParmsSetTime                 =  0x500C,//        ����ʱ��                      
	      eParmsSetDevConnectState      =  0x500D,//        �����豸����״̬    
	      eParmsGetDevNetState          =  0x500E,//        ��ȡ�豸����״̬         
	      eParmsSetFTFConfig            =  0x500F,//        485 ����                 
	      eParmsSetTTTConfig            =  0x5010,//        232 ����                 
	      eParmsModifyWarnConfig        =  0x5011,//        �޸ı�������         
	      eParmsGetWarnConfig           =  0x5012,//        ��ȡ��������              
	      eParmsModifyWarnSubscribe     =  0x5013,//        �޸ı���ԤԼ      
	      eParmsGetWarnSubscribe        =  0x5014,//        ��ȡ����ԤԼ           
	      eParmsModifySensorConfig      =  0x5015,//        �޸Ĵ���������     
	      eParmsGetSensorConfig         =  0x5016,//        ��ȡ����������          
	      eParmsGetSensorRelation       =  0x5017,//        ��ȡ��������Ӧ��ϵ  
	      eParmsSensorAuotSend          =  0x5018,//        �����������Զ��ϱ�     
	      eParmsDevSendWarn             =  0x5019,//        �豸�ϱ�����                
	      eParmsWireless                =  0x501A,//        ������������                             
	      eParmsTimeoutSendOldData      =  0x501B,//        ��ʷ�����ϱ�ʱ����        
	      eParmsMakeUpOldData           =  0x501C,//        ���ݲ�¼             
	      eParmsGeneralWarn             =  0x501D,//        ��ͨ����                 
	      eParmsDataWarn                =  0x501E,//        ���ݱ���                   
	      eParmsModifyDevUser           =  0x501F,//        �޸��豸�û�           
	      eParmsSetValue      			 		=  0x5020,//        ״ֵ̬����              
	      eParmsSetData            		  =  0x5021 //        ����ֵ����      
                       
};

/*��ý�����*/
enum
{
	 eVideoPlay                   =  0x5201,//        ��Ƶ���Ų���     
	 eVideoParmsSet               =  0x5202,//        ������Ƶ����     
	 eVideoParmsGet               =  0x5203,//        ��ȡ��Ƶ����     
	 ePicGet                      =  0x5204,//        ͼ��             
	 eVideoDownload               =  0x5205,//        ��Ƶ����         
	 eFullVideo                   =  0x5206,//        ¼����           
	 eVideoOpen                   =  0x5207,//        ��Ƶ��         
	 eAudioOper                   =  0x5208,//        ��Ƶ����         
	 eYunTaiGet                   =  0x5209,//        ��̨��ȡ         
	 eYunTaiSet                   =  0x520A,//        ��̨����         
	 eYunTaiControl               =  0x520B,//        ��̨����         
	 eModifyPreset                =  0x520C,//        �޸�Ԥ�õ�       
	 eModifyXunHang               =  0x520D,//        �޸�Ѳ������     
	 ePresetGet                   =  0x520E,//        ��ȡԤ�õ�       
	 eXunHangGet                  =  0x520F //        ��ȡѲ������     
};

enum
{
  eReq=0x00,  /*����*/
  eRes=0x01   /*��Ӧ*/
};

enum
{
  eSubStation,   /*��վ(�豸�ˡ��ͻ���)*/
  eMasterStation /*��վ(�����)*/
};
enum
{
    eStm=0,
    eNoStm=1
};
/**
 *   ������: register,//andle
 *   ����:ע���Ҫ��Ϣ
 *   ����:
 *       ptr �����Ϣ�ṹ�� ����Ϊ��
 *       station 0 ��վ(�����) 1 ��վ(�豸�ˣ��ͻ���)
 *       devType 0 ��Ƭ�� 1 �ǵ�Ƭ�� 
 *       sBufSize ���ͻ�������С�� <=0 Ĭ�ϴ�С10K(��Ƭ�� 100�ֽ�)�� >0 && <= 60000 �Զ����С�� >60000 ��󲻴���60K(��Ƭ��������200�ֽ�)
 *       rBufSize ���ջ�������С   <=0 Ĭ�ϴ�С10K(��Ƭ�� 100�ֽ�)�� >0 && <60000 �Զ����С�� >60000 ��󲻴���60K(��Ƭ��������200�ֽ�)
 *       _CallbackProcPtr cb �û���������ص����� ����Ϊ��
 *   ����ֵ:
 *       True �ɹ�
 *       False ʧ��
 **/
_UBool registerHandle(HandlePtr ptr,_UInt8 station,_UInt8 devType,_SInt32 sBufSize,_SInt32 rBufSize,_CallbackProcPtr cb);

/**
   ������:  removeHandle
   ����:��������Ϣ���˺������û����ٴ���ʹ��ʱע����
   ����:
     HandlePtr ptr �û���Ϣ�ṹ��
   ����ֵ: �ú������غ�Ϊ�ɹ�
**/
_UBool removeHandle(HandlePtr ptr);

enum
{
    eResetSendBuffer=0, /*���÷��ͻ�����*/
    eResetRecvBuffer=1  /*���ý��ջ�����*/
};
/**
    ������:resetBuffer
    ����:�������÷��ͻ���������ջ�����
    ����:
        HandlePtr ptr �����Ϣ�ṹ�� ����Ϊ��
        sOrRBuf 0 ���ͻ�����
                1 ���ջ�����
        hLen �Ѵ������ݳ���
    ����ֵ: �ú������غ�Ϊ�ɹ�
**/
_UBool  resetBuffer(HandlePtr ptr,_UInt32 sOrRBuf,_UInt32 hLen);

/*
    ������:addMessage
    ����:��ӽ��յ�����Ϣ��ָ��λ��(��socket������λ��)
    ����:
        ptr �����Ϣ�ṹ�� ����Ϊ��
        buf ����
        ���ݳ���
    ����ֵ:
        ���ݹ����������� ʧ��
    
*/
_UBool addMessage(HandlePtr ptr,char *buf,int len);
#endif
