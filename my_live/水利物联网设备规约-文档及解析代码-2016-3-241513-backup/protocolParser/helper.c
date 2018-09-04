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

	/*��ʼ�ַ�0x68 (1��)*/  /*֡����L (1��)*/  /*��ʼ�ַ�0x68 (1��)*/  /*������ (5��)*/  /*��·��ַ�� (1��)*/     
	/*���ͱ�ʾ (1��)*/  /*�ɱ�ṹ�޶��� (2��)*/  /*����ԭ�� (4��)*/  /*������ַ (1��)*/  /*��Ϣ���ַ (1��)*/

	if(ReqOrRes==eReq)
		packageingHeader(&f, (_UInt8)0x68, (_UInt16)(userDatalen+FrameFixLen), (_UInt8)0x68,
		(_UInt8)0/*������---RES������*/, 
		(_UInt8)0/*������---PRM: 0Ϊ��վ����վ���䱨�� 1Ϊ��վ����վ���䱨��*/,
		(_UInt8)0/*������---FCB/ACD*/, 
		(_UInt8)0/*������---FCV/DFC*/,
		(_UInt8)uFunCode/*������---������ 1Ϊ�������� 2Ϊ��������Ӧ����֡ 0Ϊ��λԶ����·(ƽ̨����)*/, 

		(_UInt8)1/*��·��ַ��*/, 
		(_UInt8)1/*���ͱ�ʾ 1Ϊ������Ϣ*/, 

		/*�ɱ�ṹ�޶��ʣ�������������Ԫ�ظ�����Ĭ��Ϊ1��*/
		(_UInt8)0, (_UInt8)uInfoNum,

		/*����ԭ��(ǰ��������Ϊ0��)*/
		(_UInt8)0, (_UInt8)0, (_UInt8)uCause,(_UInt8)0,

		(_UInt8)0/*������ַ 0δ��*/,
		(_UInt16)uInfoAddr/*��Ϣ���ַ*/ );

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
   /*ң��*/                                                                             
  switch(funCode){                                                                  
      //״̬��1                                          
	case eRemoteSignalingState1:
		  //״̬��2           
	case eRemoteSignalingState2:
		  //״̬��3           
	case eRemoteSignalingState3:
		  //״̬��4           
	case eRemoteSignalingState4:
		  //״̬��5           
	case eRemoteSignalingState5:
		  //״̬��6           
	case eRemoteSignalingState6:
		  //״̬��7           
	case eRemoteSignalingState7:
		  //״̬��8           
	case eRemoteSignalingState8:
		  //״̬��9           
	case eRemoteSignalingState9:
		  //״̬��10          
	case eRemoteSignalingState10:
		  //״̬��11          
	case eRemoteSignalingState11:
		  //״̬��12          
	case eRemoteSignalingState12:
		  //״̬��13          
	case eRemoteSignalingState13:
		  //״̬��14          
	case eRemoteSignalingState14:
		  //״̬��15          
	case eRemoteSignalingState15:
		  //״̬��16          
	case eRemoteSignalingState16:
		  //״̬��17          
	case eRemoteSignalingState17:
		  //״̬��18          
	case eRemoteSignalingState18:
		  //״̬��19          
	case eRemoteSignalingState19:
		  //״̬��20          
	case eRemoteSignalingState20:
		  //״̬��21          
	case eRemoteSignalingState21:
		  //״̬��22          
	case eRemoteSignalingState22:
		  //״̬��23          
	case eRemoteSignalingState23:
		  //״̬��24          
	case eRemoteSignalingState24:
		  //״̬��25          
	case eRemoteSignalingState25:
		  //״̬��26          
	case eRemoteSignalingState26:
		  //״̬��27          
	case eRemoteSignalingState27:
		  //״̬��28          
	case eRemoteSignalingState28:
		  //״̬��29          
	case eRemoteSignalingState29:
		  //״̬��30          
	case eRemoteSignalingState30:
		  //״̬��31          
	case eRemoteSignalingState31:
		  //״̬��32          
	case eRemoteSignalingState32:{
	        SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
				(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)funCode );
	        break;
	       }
		             
                                                                                 
                                                                                     
     /*ң��*/                                                                       
        //���ݿ�1                                         
	case eRemoteMeteringData1:
		    //���ݿ�2              
	case eRemoteMeteringData2:
		    //���ݿ�3              
	case eRemoteMeteringData3:
		    //���ݿ�4              
	case eRemoteMeteringData4:
		    //���ݿ�5              
	case eRemoteMeteringData5:
		    //���ݿ�6              
	case eRemoteMeteringData6:
		    //���ݿ�7              
	case eRemoteMeteringData7:
		    //���ݿ�8              
	case eRemoteMeteringData8:
		    //���ݿ�9              
	case eRemoteMeteringData9:
		    //���ݿ�10             
	case eRemoteMeteringData10:
		    //���ݿ�11             
	case eRemoteMeteringData11:
		    //���ݿ�12             
	case eRemoteMeteringData12:
		    //���ݿ�13             
	case eRemoteMeteringData13:
		    //���ݿ�14             
	case eRemoteMeteringData14:
		    //���ݿ�15             
	case eRemoteMeteringData15:
		    //���ݿ�16             
	case eRemoteMeteringData16:
		    //���ݿ�17             
	case eRemoteMeteringData17:
		    //���ݿ�18             
	case eRemoteMeteringData18:
		    //���ݿ�19             
	case eRemoteMeteringData19:
		    //���ݿ�20             
	case eRemoteMeteringData20:{
	    SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)funCode);
	       	break;
	       }
		                   
	                                                                                   
	       /*21-220����*/                                                              
                                                                              
                                                                                     
/*ң��*/                                                                             
       //״̬��1                                            
   case eRemoteControlState1:
   		   //״̬��2                  
   case eRemoteControlState2:
		   //״̬��3                  
   case eRemoteControlState3:
   		   //״̬��4                  
   case eRemoteControlState4:
   		   //״̬��5                  
   case eRemoteControlState5:
   		   //״̬��6                  
   case eRemoteControlState6:
   		   //״̬��7                  
   case eRemoteControlState7:
   		   //״̬��8                  
   case eRemoteControlState8:
   		   //״̬��9                  
   case eRemoteControlState9:
   		   //״̬��10                 
   case eRemoteControlState10:
   		   //״̬��11                 
   case eRemoteControlState11:
   		   //״̬��12                 
   case eRemoteControlState12:
   		   //״̬��13                 
   case eRemoteControlState13:
   		   //״̬��14                 
   case eRemoteControlState14:
   		   //״̬��15                 
   case eRemoteControlState15:
   		   //״̬��16                 
   case eRemoteControlState16:
   		   //״̬��17                 
   case eRemoteControlState17:
   		   //״̬��18                 
   case eRemoteControlState18:
   		   //״̬��19                 
   case eRemoteControlState19:
   		   //״̬��20                 
   case eRemoteControlState20:
   		   //״̬��21                 
   case eRemoteControlState21:
   		   //״̬��22                 
   case eRemoteControlState22:
   		   //״̬��23                 
   case eRemoteControlState23:
   		   //״̬��24                 
   case eRemoteControlState24:
   		   //״̬��25                 
   case eRemoteControlState25:
   		   //״̬��26                 
   case eRemoteControlState26:
   		   //״̬��27                 
   case eRemoteControlState27:
   		   //״̬��28                 
   case eRemoteControlState28:
   		   //״̬��29                 
   case eRemoteControlState29:
   		   //״̬��30                 
   case eRemoteControlState30:
   		   //״̬��31                 
   case eRemoteControlState31:
   		   //״̬��32                
   case eRemoteControlState32:  {
          SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)funCode);
        		break;
        }
                                                                                     
/*������*/                                                                           
      //�豸����                                                     
	case eParmsDevUpgrade:{
		SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsDevUpgrade);

		if(DEBUG)fprintf(stderr,"################�豸����: ###############\n");

			break;
		}//�ָ���������              
	case eParmsFactoryDefaults:{
     SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsFactoryDefaults );

		if(DEBUG)fprintf(stderr,"################�ָ���������: ###############\n");
			break;
		}//�豸��Ϣ��ȡ              
	case eParmsGetDevInfomation:{
     SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsGetDevInfomation );

		if(DEBUG)fprintf(stderr,"################�豸��Ϣ��ȡ: ###############\n");
			break;
		}//Э��汾��ѯ              
	case eParmsGetVersion:{
    SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsGetVersion );

		if(DEBUG)fprintf(stderr,"################Э��汾��ѯ: ###############\n");
			break;
		}//Զ������                  
	case eParmsRemoteRestart:{
     SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsRemoteRestart );

		if(DEBUG)fprintf(stderr,"################Э��汾��ѯ: ###############\n");
			break;
		}//�豸����                  
	case eParmsConnectDev:{
		SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsConnectDev );

		if(DEBUG)fprintf(stderr,"################Э��汾��ѯ: ###############\n");
			break;
		}//�豸����                  
	case eParmsDisConnectDev:{
		SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsDisConnectDev );

		if(DEBUG)fprintf(stderr,"################Э��汾��ѯ: ###############\n");
			break;
		}//�豸����                  
	case eParmsDev:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsDev );

		if(DEBUG)fprintf(stderr,"################Э��汾��ѯ: ###############\n");
			break;
		}//����Ӳ����                
	case eParmsSet:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsSet );

		if(DEBUG)fprintf(stderr,"################Э��汾��ѯ: ###############\n");
			break;
		}//��ʽ��                    
	case eParmsFormat:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsFormat );

		if(DEBUG)fprintf(stderr,"################Э��汾��ѯ: ###############\n");
			break;
		}//�洢����                  
	case eParmsSetstorageConfig:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsSetstorageConfig );

		if(DEBUG)fprintf(stderr,"################Э��汾��ѯ: ###############\n");
			break;
		}//����ʱ��                  
	case eParmsSetTime:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsSetTime );

		if(DEBUG)fprintf(stderr,"################Э��汾��ѯ: ###############\n");
			break;
		}//�����豸����״̬          
	case eParmsSetDevConnectState:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsSetDevConnectState );

		if(DEBUG)fprintf(stderr,"################Э��汾��ѯ: ###############\n");
			break;
		}//��ȡ�豸����״̬          
	case eParmsGetDevNetState:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsGetDevNetState );

		if(DEBUG)fprintf(stderr,"################Э��汾��ѯ: ###############\n");
			break;
		}//485 ����                  
	case eParmsSetFTFConfig:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsSetFTFConfig );

		if(DEBUG)fprintf(stderr,"################Э��汾��ѯ: ###############\n");
			break;
		}//232 ����                  
	case eParmsSetTTTConfig:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsSetTTTConfig );

		if(DEBUG)fprintf(stderr,"################Э��汾��ѯ: ###############\n");
			break;
		}//�޸ı�������              
	case eParmsModifyWarnConfig:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsModifyWarnConfig );

		if(DEBUG)fprintf(stderr,"################Э��汾��ѯ: ###############\n");
			break;
		}//��ȡ��������              
	case eParmsGetWarnConfig:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsGetWarnConfig );

		if(DEBUG)fprintf(stderr,"################Э��汾��ѯ: ###############\n");
			break;
		}//�޸ı���ԤԼ              
	case eParmsModifyWarnSubscribe:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsModifyWarnSubscribe );

		if(DEBUG)fprintf(stderr,"################Э��汾��ѯ: ###############\n");
			break;	
		}//��ȡ����ԤԼ              
	case eParmsGetWarnSubscribe:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsGetWarnSubscribe );

		if(DEBUG)fprintf(stderr,"################Э��汾��ѯ: ###############\n");
			break;
		}//�޸Ĵ���������            
	case eParmsModifySensorConfig:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsModifySensorConfig );

		if(DEBUG)fprintf(stderr,"################�޸Ĵ���������: ###############\n");
			break;
		}//��ȡ����������            
	case eParmsGetSensorConfig:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsGetSensorConfig );

		if(DEBUG)fprintf(stderr,"################��ȡ����������: ###############\n");
			break;
		}//��ȡ��������Ӧ��ϵ        
	case eParmsGetSensorRelation:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsGetSensorRelation );

		if(DEBUG)fprintf(stderr,"################��ȡ��������Ӧ��ϵ: ###############\n");
			break;
		}//�����������Զ��ϱ�        
	case eParmsSensorAuotSend:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsSensorAuotSend );

		if(DEBUG)fprintf(stderr,"################�����������Զ��ϱ�: ###############\n");
			break;
		}//�豸�ϱ�����              
	case eParmsDevSendWarn:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsDevSendWarn );

		if(DEBUG)fprintf(stderr,"################�豸�ϱ�����: ###############\n");
			break;
		}//������������              
	case eParmsWireless:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsWireless );

		if(DEBUG)fprintf(stderr,"################������������: ###############\n");
			break;
		}//��ʷ�����ϱ�ʱ����      
	case eParmsTimeoutSendOldData:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsTimeoutSendOldData );

		if(DEBUG)fprintf(stderr,"################��ʷ�����ϱ�ʱ����: ###############\n");
			break;
		}//���ݲ�¼                  
	case eParmsMakeUpOldData:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsMakeUpOldData );

		if(DEBUG)fprintf(stderr,"################���ݲ�¼: ###############\n");
			break;
		}//��ͨ����                  
	case eParmsGeneralWarn:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsGeneralWarn );

		if(DEBUG)fprintf(stderr,"################��ͨ����: ###############\n");
			break;
		}//���ݱ���                  
	case eParmsDataWarn:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsDataWarn );

		if(DEBUG)fprintf(stderr,"################���ݱ���: ###############\n");
			break;
		}//�޸��豸�û�              
	case eParmsModifyDevUser:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsModifyDevUser );

		if(DEBUG)fprintf(stderr,"################�޸��豸�û�: ###############\n");
			break;
		}//״ֵ̬����                
	case eParmsSetValue:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsSetValue );

		if(DEBUG)fprintf(stderr,"################״ֵ̬����: ###############\n");
			break;
		}//����ֵ����                
	case eParmsSetData:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eParmsSetData );

		if(DEBUG)fprintf(stderr,"################����ֵ����: ###############\n");
			break;
		}        
 /*��ý�����*/                                                                       
       //��Ƶ���Ų���                                                
	case eVideoPlay:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eVideoPlay );

		if(DEBUG)fprintf(stderr,"################��Ƶ���Ų���: ###############\n");
			break;
		} //������Ƶ����                  
	case eVideoParmsSet:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eVideoParmsSet );

		if(DEBUG)fprintf(stderr,"################������Ƶ����: ###############\n");
			break;
		} //��ȡ��Ƶ����                  
	case eVideoParmsGet:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eVideoParmsGet );

		if(DEBUG)fprintf(stderr,"################��ȡ��Ƶ����: ###############\n");
			break;
		} //ͼ��                          
	case ePicGet:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)ePicGet );

		if(DEBUG)fprintf(stderr,"################ͼ��: ###############\n");
			break;
		} //��Ƶ����                      
	case eVideoDownload:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eVideoDownload );

		if(DEBUG)fprintf(stderr,"################��Ƶ����: ###############\n");
			break;
		} //¼����                        
	case eFullVideo:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eFullVideo );

		if(DEBUG)fprintf(stderr,"################¼����: ###############\n");
			break;
		} //��Ƶ��                      
	case eVideoOpen:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eVideoOpen );

		if(DEBUG)fprintf(stderr,"################��Ƶ��: ###############\n");
			break;
		} //��Ƶ����                      
	case eAudioOper:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eAudioOper );

		if(DEBUG)fprintf(stderr,"################��Ƶ����: ###############\n");
			break;
		} //��̨��ȡ                      
	case eYunTaiGet:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eYunTaiGet );

		if(DEBUG)fprintf(stderr,"################��̨��ȡ: ###############\n");
			break;
		} //��̨����                      
	case eYunTaiSet:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eYunTaiSet );

		if(DEBUG)fprintf(stderr,"################��̨����: ###############\n");
			break;
		} //��̨����                      
	case eYunTaiControl:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eYunTaiControl );

		if(DEBUG)fprintf(stderr,"################��̨����: ###############\n");
			break;
		} //�޸�Ԥ�õ�                    
	case eModifyPreset:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eModifyPreset );

		if(DEBUG)fprintf(stderr,"################�޸�Ԥ�õ�: ###############\n");
			break;
		} //�޸�Ѳ������                  
	case eModifyXunHang:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eModifyXunHang );

		if(DEBUG)fprintf(stderr,"################�޸�Ѳ������: ###############\n");
			break;
		} //��ȡԤ�õ�                    
	case ePresetGet:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)ePresetGet );

		if(DEBUG)fprintf(stderr,"################��ȡԤ�õ�: ###############\n");
			break;
		} //��ȡѲ������                  
	case eXunHangGet:{
			SetInfo( buf, userData, userDatalen, ReqOrRes, FrameFixLen, 
			(_UInt8)1, (_UInt8)0, (_UInt8)1, (_UInt8)1, (_UInt16)eXunHangGet );

		if(DEBUG)fprintf(stderr,"################��ȡѲ������: ###############\n");
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