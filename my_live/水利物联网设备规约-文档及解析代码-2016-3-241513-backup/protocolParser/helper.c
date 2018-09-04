#include "helper.h"
#include "global.h"
#include <stdio.h>
#include <stdlib.h>
void SetInfo( _UInt8 *buf,  void *userData, _UInt32 userDatalen, _UInt8 ReqOrRes, _UInt32 FrameFixLen, 
			  _UInt8 uFunCode, _UInt8 uDirection, _UInt8 uInfoNum, _UInt8 uCause, _UInt16 uInfoAddr)
{
	 Frame f;
	_UInt8 check=0;
	_UInt8 end=0;
	_UInt8 *pos=buf;
	if(buf==NULL || userData==NULL)
		return;

	/*起始字符0x68 (1个)*/  /*帧长度L (1个)*/  /*起始字符0x68 (1个)*/  /*控制域 (5个)*/  /*链路地址域 (1个)*/     
	/*类型标示 (1个)*/  /*可变结构限定词 (2个)*/  /*传输原因 (4个)*/  /*公共地址 (1个)*/  /*信息体地址 (1个)*/

	if(ReqOrRes==eReq)
		packageingHeader(&f, (_UInt8)0x68, (_UInt16)(userDatalen+FrameFixLen), (_UInt8)0x68,
		(_UInt8)0/*控制域---RES：备用*/, 
		(_UInt8)0/*控制域---PRM: 0为子站向主站传输报文 1为主站向子站传输报文*/,
		(_UInt8)0/*控制域---FCB/ACD*/, 
		(_UInt8)0/*控制域---FCV/DFC*/,
		(_UInt8)uFunCode/*控制域---功能码 1为发送数据 2为以数据响应请求帧 0为复位远方链路(平台方向)*/, 

		(_UInt8)1/*链路地址域*/, 
		(_UInt8)1/*类型标示 1为单点信息*/, 

		/*可变结构限定词（下面两个代表元素个数。默认为1）*/
		(_UInt8)0, (_UInt8)uInfoNum,

		/*传送原因(前两个参数为0，)*/
		(_UInt8)0, (_UInt8)0, (_UInt8)uCause,(_UInt8)0,

		(_UInt8)0/*公共地址 0未用*/,
		(_UInt16)uInfoAddr/*信息体地址*/ );

	if(ReqOrRes==eRes)
		packageingHeader(&f, (_UInt8)0x68, (_UInt16)(userDatalen+FrameFixLen), (_UInt8)0x68,
		(_UInt8)0, (_UInt8)1, (_UInt8)0, (_UInt8)0, (_UInt8)uFunCode, 
		(_UInt8)1, (_UInt8)1, 
		(_UInt8)0, (_UInt8)uInfoNum, 
		(_UInt8)0, (_UInt8)0, (_UInt8)uCause,(_UInt8)0,
		(_UInt8)0,(_UInt16)uInfoAddr);


	//memcpy();
	memcpy(pos,(_SInt8*)&f,sizeof(Frame));
	pos+=sizeof(Frame);
	memcpy(pos,userData,userDatalen);
	pos+=userDatalen;

	end=(_UInt8)0x16;
	memcpy(pos,(_SInt8*)&check,sizeof(_UInt8));
	pos+=sizeof(_UInt8);
	memcpy(pos,(_SInt8*)&end,sizeof(_UInt8));
}
void packagingData(_UInt8 *buf,void *userData,_UInt32 userDatalen,_UInt16 funCode,_UInt8 stationType,_UInt8 ReqOrRes,_UInt32 FrameFixLen)
{
	Frame f;
	_UInt8 check=0;
	_UInt8 end=0;
	_UInt8 *pos=buf;
	if(buf==NULL || userData==NULL)
		return;
   /*遥信*/                                                                             
  switch(funCode){                                                                  
      //状态口1                                          
	case eRemoteSignalingState1:
		  //状态口2           
	case eRemoteSignalingState2:
		  //状态口3           
	case eRemoteSignalingState3:
		  //状态口4           
	case eRemoteSignalingState4:
		  //状态口5           
	case eRemoteSignalingState5:
		  //状态口6           
	case eRemoteSignalingState6:
		  //状态口7           
	case eRemoteSignalingState7:
		  //状态口8           
	case eRemoteSignalingState8:
		  //状态口9           
	case eRemoteSignalingState9:
		  //状态口10          
	case eRemoteSignalingState10:
		  //状态口11          
	case eRemoteSignalingState11:
		  //状态口12          
	case eRemoteSignalingState12:
		  //状态口13          
	case eRemoteSignalingState13:
		  //状态口14          
	case eRemoteSignalingState14:
		  //状态口15          
	case eRemoteSignalingState15:
		  //状态口16          
	case eRemoteSignalingState16:
		  //状态口17          
	case eRemoteSignalingState17:
		  //状态口18          
	case eRemoteSignalingState18:
		  //状态口19          
	case eRemoteSignalingState19:
		  //状态口20          
	case eRemoteSignalingState20:
		  //状态口21          
	case eRemoteSignalingState21:
		  //状态口22          
	case eRemoteSignalingState22:
		  //状态口23          
	case eRemoteSignalingState23:
		  //状态口24          
	case eRemoteSignalingState24:
		  //状态口25          
	case eRemoteSignalingState25:
		  //状态口26          
	case eRemoteSignalingState26:
		  //状态口27          
	case eRemoteSignalingState27:
		  //状态口28          
	case eRemoteSignalingState28:
		  //状态口29          
	case eRemoteSignalingState29:
		  //状态口30          
	case eRemoteSignalingState30:
		  //状态口31          
	case eRemoteSignalingState31:
		  //状态口32          
	case eRemoteSignalingState32:{
	        SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
				(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)funCode );
	        break;
	       }
		             
                                                                                 
                                                                                     
     /*遥测*/                                                                       
        //数据口1                                         
	case eRemoteMeteringData1:
		    //数据口2              
	case eRemoteMeteringData2:
		    //数据口3              
	case eRemoteMeteringData3:
		    //数据口4              
	case eRemoteMeteringData4:
		    //数据口5              
	case eRemoteMeteringData5:
		    //数据口6              
	case eRemoteMeteringData6:
		    //数据口7              
	case eRemoteMeteringData7:
		    //数据口8              
	case eRemoteMeteringData8:
		    //数据口9              
	case eRemoteMeteringData9:
		    //数据口10             
	case eRemoteMeteringData10:
		    //数据口11             
	case eRemoteMeteringData11:
		    //数据口12             
	case eRemoteMeteringData12:
		    //数据口13             
	case eRemoteMeteringData13:
		    //数据口14             
	case eRemoteMeteringData14:
		    //数据口15             
	case eRemoteMeteringData15:
		    //数据口16             
	case eRemoteMeteringData16:
		    //数据口17             
	case eRemoteMeteringData17:
		    //数据口18             
	case eRemoteMeteringData18:
		    //数据口19             
	case eRemoteMeteringData19:
		    //数据口20             
	case eRemoteMeteringData20:{
	    SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)funCode);
	       	break;
	       }
		                   
	                                                                                   
	       /*21-220保留*/                                                              
                                                                              
                                                                                     
/*遥控*/                                                                             
       //状态口1                                            
   case eRemoteControlState1:
   		   //状态口2                  
   case eRemoteControlState2:
		   //状态口3                  
   case eRemoteControlState3:
   		   //状态口4                  
   case eRemoteControlState4:
   		   //状态口5                  
   case eRemoteControlState5:
   		   //状态口6                  
   case eRemoteControlState6:
   		   //状态口7                  
   case eRemoteControlState7:
   		   //状态口8                  
   case eRemoteControlState8:
   		   //状态口9                  
   case eRemoteControlState9:
   		   //状态口10                 
   case eRemoteControlState10:
   		   //状态口11                 
   case eRemoteControlState11:
   		   //状态口12                 
   case eRemoteControlState12:
   		   //状态口13                 
   case eRemoteControlState13:
   		   //状态口14                 
   case eRemoteControlState14:
   		   //状态口15                 
   case eRemoteControlState15:
   		   //状态口16                 
   case eRemoteControlState16:
   		   //状态口17                 
   case eRemoteControlState17:
   		   //状态口18                 
   case eRemoteControlState18:
   		   //状态口19                 
   case eRemoteControlState19:
   		   //状态口20                 
   case eRemoteControlState20:
   		   //状态口21                 
   case eRemoteControlState21:
   		   //状态口22                 
   case eRemoteControlState22:
   		   //状态口23                 
   case eRemoteControlState23:
   		   //状态口24                 
   case eRemoteControlState24:
   		   //状态口25                 
   case eRemoteControlState25:
   		   //状态口26                 
   case eRemoteControlState26:
   		   //状态口27                 
   case eRemoteControlState27:
   		   //状态口28                 
   case eRemoteControlState28:
   		   //状态口29                 
   case eRemoteControlState29:
   		   //状态口30                 
   case eRemoteControlState30:
   		   //状态口31                 
   case eRemoteControlState31:
   		   //状态口32                
   case eRemoteControlState32:  {
          SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)funCode);
        		break;
        }
                                                                                     
/*参数量*/                                                                           
      //设备升级                                                     
	case eParmsDevUpgrade:{
		SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsDevUpgrade);

		if(DEBUG)fprintf(stderr,"################设备升级: ###############\n");

			break;
		}//恢复出厂设置              
	case eParmsFactoryDefaults:{
     SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsFactoryDefaults );

		if(DEBUG)fprintf(stderr,"################恢复出厂设置: ###############\n");
			break;
		}//设备信息获取              
	case eParmsGetDevInfomation:{
     SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsGetDevInfomation );

		if(DEBUG)fprintf(stderr,"################设备信息获取: ###############\n");
			break;
		}//协议版本查询              
	case eParmsGetVersion:{
    SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsGetVersion );

		if(DEBUG)fprintf(stderr,"################协议版本查询: ###############\n");
			break;
		}//远程重启                  
	case eParmsRemoteRestart:{
     SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsRemoteRestart );

		if(DEBUG)fprintf(stderr,"################协议版本查询: ###############\n");
			break;
		}//设备上线                  
	case eParmsConnectDev:{
		SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsConnectDev );

		if(DEBUG)fprintf(stderr,"################协议版本查询: ###############\n");
			break;
		}//设备下线                  
	case eParmsDisConnectDev:{
		SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsDisConnectDev );

		if(DEBUG)fprintf(stderr,"################协议版本查询: ###############\n");
			break;
		}//设备心跳                  
	case eParmsDev:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsDev );

		if(DEBUG)fprintf(stderr,"################协议版本查询: ###############\n");
			break;
		}//设置硬盘数                
	case eParmsSet:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsSet );

		if(DEBUG)fprintf(stderr,"################协议版本查询: ###############\n");
			break;
		}//格式化                    
	case eParmsFormat:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsFormat );

		if(DEBUG)fprintf(stderr,"################协议版本查询: ###############\n");
			break;
		}//存储设置                  
	case eParmsSetstorageConfig:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsSetstorageConfig );

		if(DEBUG)fprintf(stderr,"################协议版本查询: ###############\n");
			break;
		}//设置时间                  
	case eParmsSetTime:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsSetTime );

		if(DEBUG)fprintf(stderr,"################协议版本查询: ###############\n");
			break;
		}//设置设备网络状态          
	case eParmsSetDevConnectState:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsSetDevConnectState );

		if(DEBUG)fprintf(stderr,"################协议版本查询: ###############\n");
			break;
		}//获取设备网络状态          
	case eParmsGetDevNetState:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsGetDevNetState );

		if(DEBUG)fprintf(stderr,"################协议版本查询: ###############\n");
			break;
		}//485 配置                  
	case eParmsSetFTFConfig:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsSetFTFConfig );

		if(DEBUG)fprintf(stderr,"################协议版本查询: ###############\n");
			break;
		}//232 配置                  
	case eParmsSetTTTConfig:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsSetTTTConfig );

		if(DEBUG)fprintf(stderr,"################协议版本查询: ###############\n");
			break;
		}//修改报警配置              
	case eParmsModifyWarnConfig:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsModifyWarnConfig );

		if(DEBUG)fprintf(stderr,"################协议版本查询: ###############\n");
			break;
		}//获取报警设置              
	case eParmsGetWarnConfig:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsGetWarnConfig );

		if(DEBUG)fprintf(stderr,"################协议版本查询: ###############\n");
			break;
		}//修改报警预约              
	case eParmsModifyWarnSubscribe:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsModifyWarnSubscribe );

		if(DEBUG)fprintf(stderr,"################协议版本查询: ###############\n");
			break;	
		}//获取报警预约              
	case eParmsGetWarnSubscribe:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsGetWarnSubscribe );

		if(DEBUG)fprintf(stderr,"################协议版本查询: ###############\n");
			break;
		}//修改传感器配置            
	case eParmsModifySensorConfig:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsModifySensorConfig );

		if(DEBUG)fprintf(stderr,"################修改传感器配置: ###############\n");
			break;
		}//获取传感器设置            
	case eParmsGetSensorConfig:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsGetSensorConfig );

		if(DEBUG)fprintf(stderr,"################获取传感器设置: ###############\n");
			break;
		}//获取传感器对应关系        
	case eParmsGetSensorRelation:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsGetSensorRelation );

		if(DEBUG)fprintf(stderr,"################获取传感器对应关系: ###############\n");
			break;
		}//传感器配置自动上报        
	case eParmsSensorAuotSend:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsSensorAuotSend );

		if(DEBUG)fprintf(stderr,"################传感器配置自动上报: ###############\n");
			break;
		}//设备上报报警              
	case eParmsDevSendWarn:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsDevSendWarn );

		if(DEBUG)fprintf(stderr,"################设备上报报警: ###############\n");
			break;
		}//开关无线网卡              
	case eParmsWireless:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsWireless );

		if(DEBUG)fprintf(stderr,"################开关无线网卡: ###############\n");
			break;
		}//历史数据上报时间间隔      
	case eParmsTimeoutSendOldData:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsTimeoutSendOldData );

		if(DEBUG)fprintf(stderr,"################历史数据上报时间间隔: ###############\n");
			break;
		}//数据补录                  
	case eParmsMakeUpOldData:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsMakeUpOldData );

		if(DEBUG)fprintf(stderr,"################数据补录: ###############\n");
			break;
		}//普通报警                  
	case eParmsGeneralWarn:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsGeneralWarn );

		if(DEBUG)fprintf(stderr,"################普通报警: ###############\n");
			break;
		}//数据报警                  
	case eParmsDataWarn:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsDataWarn );

		if(DEBUG)fprintf(stderr,"################数据报警: ###############\n");
			break;
		}//修改设备用户              
	case eParmsModifyDevUser:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsModifyDevUser );

		if(DEBUG)fprintf(stderr,"################修改设备用户: ###############\n");
			break;
		}//状态值配置                
	case eParmsSetValue:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsSetValue );

		if(DEBUG)fprintf(stderr,"################状态值配置: ###############\n");
			break;
		}//测量值配置                
	case eParmsSetData:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsSetData );

		if(DEBUG)fprintf(stderr,"################测量值配置: ###############\n");
			break;
		}        
 /*多媒体操作*/                                                                       
       //视频播放操作                                                
	case eVideoPlay:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eVideoPlay );

		if(DEBUG)fprintf(stderr,"################视频播放操作: ###############\n");
			break;
		} //设置视频参数                  
	case eVideoParmsSet:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eVideoParmsSet );

		if(DEBUG)fprintf(stderr,"################设置视频参数: ###############\n");
			break;
		} //获取视频参数                  
	case eVideoParmsGet:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eVideoParmsGet );

		if(DEBUG)fprintf(stderr,"################获取视频参数: ###############\n");
			break;
		} //图像                          
	case ePicGet:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)ePicGet );

		if(DEBUG)fprintf(stderr,"################图像: ###############\n");
			break;
		} //视频下载                      
	case eVideoDownload:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eVideoDownload );

		if(DEBUG)fprintf(stderr,"################视频下载: ###############\n");
			break;
		} //录像满                        
	case eFullVideo:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eFullVideo );

		if(DEBUG)fprintf(stderr,"################录像满: ###############\n");
			break;
		} //视频打开                      
	case eVideoOpen:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eVideoOpen );

		if(DEBUG)fprintf(stderr,"################视频打开: ###############\n");
			break;
		} //音频操作                      
	case eAudioOper:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eAudioOper );

		if(DEBUG)fprintf(stderr,"################音频操作: ###############\n");
			break;
		} //云台获取                      
	case eYunTaiGet:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eYunTaiGet );

		if(DEBUG)fprintf(stderr,"################云台获取: ###############\n");
			break;
		} //云台设置                      
	case eYunTaiSet:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eYunTaiSet );

		if(DEBUG)fprintf(stderr,"################云台设置: ###############\n");
			break;
		} //云台控制                      
	case eYunTaiControl:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eYunTaiControl );

		if(DEBUG)fprintf(stderr,"################云台控制: ###############\n");
			break;
		} //修改预置点                    
	case eModifyPreset:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eModifyPreset );

		if(DEBUG)fprintf(stderr,"################修改预置点: ###############\n");
			break;
		} //修改巡航配置                  
	case eModifyXunHang:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eModifyXunHang );

		if(DEBUG)fprintf(stderr,"################修改巡航配置: ###############\n");
			break;
		} //获取预置点                    
	case ePresetGet:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)ePresetGet );

		if(DEBUG)fprintf(stderr,"################获取预置点: ###############\n");
			break;
		} //获取巡航配置                  
	case eXunHangGet:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eXunHangGet );

		if(DEBUG)fprintf(stderr,"################获取巡航配置: ###############\n");
			break;
		} 
		default:{/*do nothing*/}                  
                                                                                 
}
    


}
void unpackagingData()
{


}
void packageingHeader(Frame *f, _UInt8  start1,       
                                _UInt16   len,        
                                _UInt8  start2,       
                                _UInt8  res,          
                                _UInt8  prm,          
                                _UInt8  fcbAcd,       
                                _UInt8  fcvDfc,       
                                _UInt8  funCode,      
                                _UInt8  addr,         
                                _UInt8  type,         
                                _UInt8  sort,         
                                _UInt8  eleNum,       
                                _UInt8  t,            
                                _UInt8  pn,           
                                _UInt8  other,        
                                _UInt8  nUse,         
                                _UInt8  publicAddr,   
                                _UInt16  informosome )
                                {
                           f->start1=start1;f->len=len;
                           f->start2=start2;
                           f->res=res;    f->prm=prm;               
                           f->fcbAcd=fcbAcd; f->fcvDfc=fcvDfc;            
                           f->funCode=funCode;                       
                           f->addr=addr;                  
                           f->type=type;                  
                           f->sort=sort;  f->eleNum=eleNum;             
                           f->t=t;     f->pn=pn;                 
                           f->other=other; f->nUse=nUse;               
                           f->publicAddr=publicAddr;          
                           f->informosome=informosome;     
}