#ifndef _DEVICEINTERFACE_
#define _DEVICEINTERFACE_
#include "global.h"
/////////////////////////////////////////////////////////////////////////////////
/*
 *   �������,�������ȡ����
 *   �ú������ڴ������ȡ����
 *   �÷�:read(
    HandlePtr ptr,)->GetMessageFromNet
 */
/*
 ��������GetMessageFromNet
 �������������,�������ȡ����
       �ú������ڴ������ȡ����
       �÷�:read(
    HandlePtr ptr,)->GetMessageFromNet
 ������
    HandlePtr ptr,char *buf,int len
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool GetMessageFromNet(
        HandlePtr ptr,
        char *buf,
        int len
        );

/*��Ч����*/
/*Э��汾��ѯ*/

/*
 ��������setReqVersion
 ������Э��汾��ѯ����
 ������
    _UInt32 devIdH �豸��� �ָ�λ4�ֽ� ��λ4�ֽ�
    _UInt32 devIdL �豸��� ��λ4�ֽ�
    _UInt32 proVer Э��汾��
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqVersion(
        HandlePtr ptr,
        _UInt32 devIdH, /*�豸��� �ָ�λ4�ֽ�*/
        _UInt32 devIdL, //
        _UInt32 proVer /*Э��汾��*/
        );

/*
 ��������setResVersion
 ������Э��汾��ѯӦ��
 ������
    _UInt32 devIdH,   �豸��� ��λ4�ֽ�
    _UInt32 devIdL,   �豸��� ��λ4�ֽ�
    _UInt32 proVer    Э��汾��
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResVersion(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 proVer
        );
/*����*/ /*�豸��������Ӧ*/

/*
 ��������setReqDLive
 ���������� ���豸��������Ӧ��
 ������
   _UInt32 devIdH, �豸��� ��λ4�ֽ�
   _UInt32 devIdL, �豸��� ��λ4�ֽ�
   _UInt32 leiJi
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqDLive(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 Cumulative
        );
/*�豸����*/

/*
 ��������setReqFindDev
 �������豸�������� (
    HandlePtr ptr,����UDP)
 ������
    _UInt32 proType,
    _UInt32 devType
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqFindDev(
        HandlePtr ptr,
        _UInt32 proType,
        _UInt32 devType
        );

/*
 ��������setResFindDev
 �������豸����Ӧ�� (
    HandlePtr ptr,����UDP)
 ������
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
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
        );
/*�豸������*/
/*�豸����*/
/*�豸ά��*/
/*��ȡ������Ϣ*/
/*�ͻ���������*/
/*�û�*/
/*�豸��Ϣ*/
/*�ͻ�������*/
/*��ȡ��������Ӧ��Ϣ*/
/*����*/
/*���ݷ���*/

/*
 ��������setResData
 ���������ݷ���
 ������
    _UInt8 *data
    _UInt32 dataLen
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResData(
        HandlePtr ptr,
        _UInt8 *data,
        _UInt32 dataLen
        );

/*
 ��������setResVideoData
 ��������Ƶ���ݷ���
 ������
    _UInt8 *vData
    _UInt32 vLen
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResVideoData(
        HandlePtr ptr,
        _UInt8 *vData,
        _UInt32 vLen
        );
/*��ȡ��ʷ����*/

/*
 ��������setReqGetHistordata
 ��������ȡ��ʷ����
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt32 date,
    _UInt32 sTime,
    _UInt32 eTime
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqGetHistordata(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt32 date,
        _UInt32 sTime,
        _UInt32 eTime
        );

/*
 ��������setResGetHistordata
 ������
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResGetHistordata(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*�û���¼*/

/*
 ��������setReqUserLogin
 �������û���¼����
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt8  *name,
    _UInt8  *passwd
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqUserLogin(
    HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt8  *name,
    _UInt32 nameLen,
    _UInt8  *passwd,
    _UInt32 passwdLen        );

/*
 ��������setResUserLogin
 �������û���¼��Ӧ
 ������
   _UInt32 devIdH, �豸��� ��λ4�ֽ�
   _UInt32 devIdL, �豸��� ��λ4�ֽ�
   _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResUserLogin(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*��̨*/
/////////////////
/**/

/*
 ��������setReqDevConn
 ����: �豸����
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt8  devType,
    _UInt8  chType,
    _UInt8  connType,
    _UInt8  sigStrength
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqDevConn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  devType,
        _UInt8  chType,
        _UInt8  connType,
        _UInt8  sigStrength
        );

/*
 ��������setResDevConn
 �������豸����
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt8 result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResDevConn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8 result
        );
/*�豸����*/

/*
 ��������setReqDevDisConn
 ������ �豸����
 ������
    _UInt32 devIdH,
    _UInt32 devIdL
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqDevDisConn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        );

/*
 ��������setResDevDisConn
 ������ �豸����
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResDevDisConn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*��ȡ����������*/

/*
 ��������setReqGetSensorConf
 ��������ȡ��������������
 ������
   _UInt32 devIdH, �豸��� ��λ4�ֽ�
   _UInt32 devIdL, �豸��� ��λ4�ֽ�
   _UInt32 terId,
   _UInt8  chId
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqGetSensorConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 terId,
        _UInt8  chId
        );

/*
 ��������setResGetSensorConf
 ��������ȡ����������Ӧ��
 ������
   _UInt32 devIdH, �豸��� ��λ4�ֽ�
   _UInt32 devIdL, �豸��� ��λ4�ֽ�
   _UInt32 terId,
   _UInt8  chId,
   _UInt32 minThreshlod,
   _UInt32 maxThreshlod,
   _UInt32 maxRefer,
   _UInt32 minRefer,
   _UInt32 range
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
        );
/*�޸Ĵ���������*/

/*
 ��������setReqModSensorConf
 �������޸Ĵ�������������
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
   _UInt32 devIdL,  �豸��� ��λ4�ֽ�
   _UInt32 terId,
   _UInt8  chId,
   _UInt32 minThreshlod,
   _UInt32 maxThreshlod,
   _UInt32 maxRefer,
   _UInt32 minRefer
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
        );

/*
 ��������setResModSensorConf
 �������޸Ĵ���������Ӧ��
 ������
   _UInt32 devIdH, �豸��� ��λ4�ֽ�
   _UInt32 devIdL, �豸��� ��λ4�ֽ�
   _UInt32 terId,
   _UInt8  chId,
   _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResModSensorConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 terId,
        _UInt8  chId,
        _UInt8  result
        );

/*
 ��������setReqHisDataReportTime
 ��������ʷ�����ϱ�ʱ��������
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt16 time
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqHisDataReportTime(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt16 time
        );

/*
 ��������setResHisDataReportTime
 ��������ʷ�����ϱ�ʱ����Ӧ��
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
   _UInt32 devIdL,  �豸��� ��λ4�ֽ�
   _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResHisDataReportTime(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );

/*
 ��������setReqFEFConf
 ������485��������
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt32 terId,
    _UInt16 rTime,
    _UInt32 baud,
    _UInt32 dLen,
    _UInt8  sFlags,
    _UInt32 eoCheck
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
        );

/*
 ��������setResFEFConf
 ������485����Ӧ��
 ������
     _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResFEFConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*232����*/

/*
 ��������setReqTTTConf
 ������232��������
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt32 baud,
    _UInt32 dLen,
    _UInt8  sFlags,
    _UInt32 eoCheck
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqTTTConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 baud,
        _UInt32 dLen,
        _UInt8  sFlags,
        _UInt32 eoCheck
        );

/*
 ��������setResTTTConf
 ������232����Ӧ��
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResTTTConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*���ݲ�¼ ������*/

/*
 ��������setResDataMakeUp
 ���������ݲ�¼ ������(�˴����������ķ�ʽ����)
 ������
    _HandlePtr ptr,
        _UInt32 devIdH,       �豸��� ��λ4�ֽ�
        _UInt32 devIdL,        �豸��� ��λ4�ֽ�
        _UInt8  dType,
        _UInt32 pTime,
        _UInt32 *buf1,
        _UInt32 buf1Len,      ָbuf1�������ĸ���
        _UFloat *buf2,
        _UInt32 buf2Len,      ָbuf2�������ĸ���
        _UFloat *buf3 ,
        _UInt32 buf3Len       ָbuf3�������ĸ���
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
        );
/*�����������Զ��ϱ�*/

/*
 ��������setReqSensorAutoReport
 �����������������Զ��ϱ�����
 ������
    HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt8  chId,
    _UInt8  *sName,
    _UInt32 *nameLen,
    _UInt8  sType,
    _UInt32 minThreshlod,
    _UInt32 maxThreshlod,
    _UInt32 maxRefer,
    _UInt32 minRefer,
    _UInt32 range
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
        );

/*
 ��������setResSensorAutoReport
 �����������������Զ��ϱ�Ӧ��
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResSensorAutoReport(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt8  result
        );
/*��ȡ��������*/

/*
 ��������setReqGetWarnPlace
 ��������ȡ������������
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt8  wType,
    _UInt8  chId
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqGetWarnPlace(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wType,
        _UInt8  chId
        );

/*
 ��������setResGetWarnPlace
 ��������ȡ��������Ӧ��
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
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
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
        );
/*�޸ı�������*/

/*
 ��������setReqModWarnPlace
 �������޸ı�����������
 ������
    _UInt32 devIdH,   �豸��� ��λ4�ֽ�
    _UInt32 devIdL,   �豸��� ��λ4�ֽ�
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
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
        );

/*
 ��������setResModWarnPlace
 �������޸ı�������Ӧ��
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResModWarnPlace(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*�������*/

/*
 ��������setReqWarnClear
 �����������������
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  wType,
    _UInt8  chId
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqWarnClear(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wType,
        _UInt8  chId
        );

/*
 ��������setResWarnClear
 �������������Ӧ��
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResWarnClear(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*��ȡ����ԤԼ*/

/*
 ��������setReqGetWarnOrder
 ��������ȡ����ԤԼ����
 ������
    _UInt32 devIdH,       �豸��� ��λ4�ֽ�
    _UInt32 devIdL,       �豸��� ��λ4�ֽ�
    _UInt8  wType,
    _UInt8  chId
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqGetWarnOrder(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wType,
        _UInt8  chId
        );

/*
 ��������setResGetWarnOrder
 ��������ȡ����ԤԼӦ��
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt8  wType,
    _UInt8  chId,
    _UInt32 sTime,
    _UInt32 eTime
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResGetWarnOrder(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wType,
        _UInt8  chId,
        _UInt32 sTime,
        _UInt32 eTime
        );
/*�޸ı���ԤԼ*/

/*
 ��������setReqModWarnOrder
 �������޸ı���ԤԼ����
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  wType,
    _UInt8  chId,
    _UInt32 sTime,
    _UInt32 eTime
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqModWarnOrder(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wType,
        _UInt8  chId,
        _UInt32 sTime,
        _UInt32 eTime
        );

/*
 ��������setResModWarnOrder
 �������޸ı���ԤԼӦ��
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt8 chId
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResModWarnOrder(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8 chId
        );
/*��ͨ����*/

/*
 ��������setReqGeneralWarn
 ��������ͨ��������
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt8  wType,
    _UInt8  chId,
    _UInt8  *wContent
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqGeneralWarn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wType,
        _UInt8  chId,
        _UInt8  *wContent,
        _UInt32 contentLen
        );

/*
 ��������setResGeneralWarn
 ��������ͨ����Ӧ��
 ������
     _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResGeneralWarn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*���ݱ���*/

/*
 ��������setReqDataWarn
 ���������ݱ�������
 ������
    _UInt32 devIdH,   �豸��� ��λ4�ֽ�
    _UInt32 devIdL,   �豸��� ��λ4�ֽ�
    _UInt8  *devName,
    _UInt8  wType,
    _UInt8  chId,
    _UInt32 sVal,
    _UInt32 minVal,
    _UInt32 maxVal,
    _UInt8  dType,
    _UInt8  tName,
    _UInt32 unit,
    _UInt32 time
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
        );

/*
 ��������setResDataWarn
 ���������ݱ���Ӧ��
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResDataWarn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*��ȡ�豸����״̬*/

/*
 ��������setReqGetNetState
 ��������ȡ�豸����״̬����
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL   �豸��� ��λ4�ֽ�
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqGetNetState(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        );

/*
 ��������setResGetNetState
 ��������ȡ�豸����״̬Ӧ��
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  netType,
    _UInt32 ip,      �˴���ip��dns��mask����_UInt32 ��ʾ�ķ����д�����
    _UInt32 dns,
    _UInt32 mask,
    _UInt32 gateway,
    _UInt8  *mac,
    _UInt32 macLen,
    _UInt8  dhcp
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
        );
/*�����豸����״̬*/

/*
 ��������setReqSetNetState
 �����������豸����״̬����
 ������
    _UInt32 devIdH,   �豸��� ��λ4�ֽ�
    _UInt32 devIdL,   �豸��� ��λ4�ֽ�
    _UInt8  netType,
    _UInt32 ip,
    _UInt32 dns,
    _UInt32 mask,
    _UInt32 gateway,
    _UInt8  *mac,
    _UInt8  dhcp
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
        );

/*
 ��������setResSetNetState
 �����������豸����״̬Ӧ��
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResSetNetState(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*3G ��ȡ����״̬*/

/*
 ��������setReqGetNetState3G
 ������3G ��ȡ����״̬����
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  nType,
    _UInt8  cType
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqGetNetState3G(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  nType,
        _UInt8  cType
        );

/*
 ��������setResGetNetState3G
 ������3G ��ȡ����״̬Ӧ��
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  *name,
    _UInt8  *passwd,
    _UInt8  apn
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResGetNetState3G(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  *name,
        _UInt32 nameLen,
        _UInt8  *passwd,
        _UInt32 passwdLen,
        _UInt8  apn
        );
/*Զ������ͨ��*/

/*
 ��������setReqRemoteDisktop
 ������Զ������ͨ������
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL   �豸��� ��λ4�ֽ�
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqRemoteDisktop(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        );

/*
 ��������setResRemoteDistop
 ������Զ������ͨ��Ӧ��
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL  �豸��� ��λ4�ֽ�
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResRemoteDistop(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        );
/*��ȡ�豸�û� �˴����ò���ȫ*/

/*
 ��������setReqGetDevUser
 ��������ȡ�豸�û����� (
    HandlePtr ptr,�˴����ò���ȫ)
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL   �豸��� ��λ4�ֽ�
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqGetDevUser(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        );

/*
 ��������setResGetDevUser
 ��������ȡ�豸�û�Ӧ��
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  *uName,
    _UInt16 power
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResGetDevUser(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  *uName,
        _UInt32 nameLen,
        _UInt16 power
        );
/*�޸��豸�û�*/

/*
 ��������setReqModDevUser
 �������޸��豸�û�����
 ������
    _UInt32 devIdH,      �豸��� ��λ4�ֽ�
    _UInt32 devIdL,      �豸��� ��λ4�ֽ�
    _UInt8  *uName,
    _UInt8  *uPasswd,
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
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
        );

/*
 ��������setResModDevUser
 �������޸��豸�û�Ӧ��
 ������
    _UInt32 devIdH,   �豸��� ��λ4�ֽ�
    _UInt32 devIdL,   �豸��� ��λ4�ֽ�
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResModDevUser(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*����ʱ��*/

/*
 ��������setReqSetTime
 ����������ʱ������
 ������
     _UInt32 devIdH,   �豸��� ��λ4�ֽ�
    _UInt32 devIdL     �豸��� ��λ4�ֽ�
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqSetTime(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        );

/*
 ��������setResSetTime
 ����������ʱ��Ӧ��
 ������
    _UInt32 devIdH,   �豸��� ��λ4�ֽ�
    _UInt32 devIdL,   �豸��� ��λ4�ֽ�
    _UInt32 time
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResSetTime(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 time
        );
/*��̨����*/

/*
 ��������setReqYunTaiSet
 ��������̨��������
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt8  command,
    _UInt8  rate
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqYunTaiSet(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt8  command,
        _UInt8  rate
        );

/*
 ��������setResYunTaiSet
 ��������̨����Ӧ��
 ������
     _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,   �豸��� ��λ4�ֽ�
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResYunTaiSet(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*��ȡ��̨*/

/*
 ��������setReqGetYunTaiInfo
 ��������ȡ��̨����
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  chId
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqGetYunTaiInfo(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId
        );

/*
 ��������setResGetYunTaiInfo
 ��������ȡ��̨Ӧ��
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt32 baud,
    _UInt32 addr,
    _UInt8  pType
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResGetYunTaiInfo(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt32 baud,
        _UInt32 addr,
        _UInt8  pType
        );
/*������̨*/

/*
 ��������setReqControlYunTai
 ������������̨����
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt8  command,
    _UInt8  rate
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqControlYunTai(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt8  command,
        _UInt8  rate
        );

/*
 ��������setResControlYunTai
 ������������̨Ӧ��
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResControlYunTai(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt8  result
        );
/*��ȡԤ�õ�*/

/*
 ��������setReqGetPreset
 ��������ȡԤ�õ�����
 ������
    _UInt32 devIdH,   �豸��� ��λ4�ֽ�
    _UInt32 devIdL,   �豸��� ��λ4�ֽ�
    _UInt8  chId
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqGetPreset(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId
        );

/*
 ��������setResGetPreset
 ��������ȡԤ�õ�Ӧ��
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt16 *proset
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResGetPreset(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt32 pLen,
        _UInt16 *proset
        );
/**/

/*
 ��������setReqModPreset
 �������޸�Ԥ�õ�����
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt8  cType,
    _UInt16 point
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqModPreset(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt8  cType,
        _UInt16 point
        );

/*
 ��������setResModPreset
 �������޸�Ԥ�õ�Ӧ��
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResModPreset(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt8  result
        );
/**/

/*
 ��������setReqGetCruiseConf
 ��������ȡѲ����������
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  chId
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqGetCruiseConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId
        );

/*
 ��������setResGetCruiseConf
 ��������ȡѲ������Ӧ��
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt16 *list
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResGetCruiseConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt32 listLen,
        _UInt16 *list
        );
/**/

/*
 ��������setReqModCruiseConf
 �������޸�Ѳ����������
 ������
    UInt32 devIdH,   �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt16 *list
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqModCruiseConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt32 listLen,
        _UInt16 *list
        );

/*
 ��������setResModCruiseConf
 �������޸�Ѳ������Ӧ��
 ������
    _UInt32 devIdH,   �豸��� ��λ4�ֽ�
    _UInt32 devIdL,   �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResModCruiseConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt8  result
        );
/**/

/*
 ��������setReqGetEmailConf
 ��������ȡ������������
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL   �豸��� ��λ4�ֽ�
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqGetEmailConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        );

/*
 ��������setResGetEmailConf
 ��������ȡ��������Ӧ��
 ������
    HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt8  *eServer,
    _UInt32 *serverLen,
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
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
        );
/**/

/*
 ��������setReqModEmailConf
 �������޸�������������
 ������
    _UInt32 devIdH,   �豸��� ��λ4�ֽ�
  _UInt32 devIdL,     �豸��� ��λ4�ֽ�
  _UInt8 eServer,
  _UInt16 port,
  _UInt8 sType,
  _UInt8 *sName,
  _UInt8 *sPasswd,
  _UInt32 timeOut,
  _UInt8 *recver1,
  _UInt8 *recver2,
  _UInt8 *recver3,
  _UInt8 *recver4
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
        );

/*
 ��������setResModEmailConf
 �������޸���������Ӧ��
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8 chId,
    _UInt8 result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResModEmailConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8 chId,
        _UInt8 result
        );
/*������������*/

/*
 ��������setReqTestEmailConf
 ����������������������
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL   �豸��� ��λ4�ֽ�
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqTestEmailConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        );

/*
 ��������setResTestEmailConf
 ������������������Ӧ��
 ������
    _UInt32 devIdH,   �豸��� ��λ4�ֽ�
    _UInt32 devIdL,   �豸��� ��λ4�ֽ�
    _UInt8 result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResTestEmailConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8 result
        );
/*ң�ؿ�������*/

/*
 ��������setReqRemoteControlSet
 ������ң�ؿ�����������
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8 wSwitch
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqRemoteControlSet(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8 wSwitch
        );

/*
 ��������setResRemoteControlSet
 ������ң�ؿ�������Ӧ��
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResRemoteControlSet(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/**/

/*
 ��������setReqRemoteControlGet
 ������ң�ؿ���״̬��ȡ����
 ������
    _UInt32 devIdH,   �豸��� ��λ4�ֽ�
    _UInt32 devIdL,   �豸��� ��λ4�ֽ�
    _UInt8  wSwitch
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqRemoteControlGet(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wSwitch
        );

/*
 ��������setResRemoteControlGet
 ������ң�ؿ���״̬��ȡӦ��
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  sState
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResRemoteControlGet(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  sState
        );
/**/

/*
 ��������setReqSetHardDiskParm
 ����������Ӳ�̲�������
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
   _UInt8   hdSize
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqSetHardDiskParm(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8   hdSize
        );

/*
 ��������setResSetHardDiskParm
 ����������Ӳ�̲���Ӧ��
 ������
    _UInt32 devIdH,   �豸��� ��λ4�ֽ�
    _UInt32 devIdL,   �豸��� ��λ4�ֽ�
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResSetHardDiskParm(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*��ʽ��*/

/*
 ��������setReqFormat
 ��������ʽ������
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  operation
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqFormat(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  operation
        );

/*
 ��������setResFormat
 ��������ʽ��Ӧ��
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResFormat(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/**/

/*
 ��������setReqVideoFull
 ������¼��������
 ������
     _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,   �豸��� ��λ4�ֽ�
    _UInt8  vFull
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqVideoFull(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  vFull
        );

/*
 ��������setResVideoFull
 ������¼����Ӧ��
 ������
    _UInt32 devIdH,    �豸��� ��λ4�ֽ�
    _UInt32 devIdL,    �豸��� ��λ4�ֽ�
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResVideoFull(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/**/

/*
 ��������setReqTalk
 �������Խ�����
 ������
    _UInt16 rPort,
    _UInt8  code
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqTalk(
        HandlePtr ptr,
        _UInt16 rPort,
        _UInt8  code
        );

/*
 ��������setResTalk
 �������Խ�Ӧ��
 ������
     _UInt8 result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResTalk(
        HandlePtr ptr,
        _UInt8 result
        );
/**/

/*
 ��������setReqAudioDownload
 ��������Ƶ��������
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt32 sTime,
    _UInt32 eTime,
    _UInt8  *fName
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqAudioDownload(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt32 sTime,
        _UInt32 eTime,
        _UInt8  *fName,
        _UInt32 nameLen
        );

/*
 ��������setResAudioDownload
 ��������Ƶ����Ӧ��
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt32 sTime,
    _UInt32 eTime,
    _UInt8  *path,
    _UInt8  *fName
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
        );
/**/

/*
 ��������setReqVideoDownload
 ��������Ƶ��������
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt32 sTime,
    _UInt32 eTime,
    _UInt8  *fName
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqVideoDownload(
    HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt8  chId,
    _UInt32 sTime,
    _UInt32 eTime,
    _UInt8  *fName,
    _UInt32 nameLen
        );

/*
 ��������setResVideoDownload
 ��������Ƶ����Ӧ��
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt32 sTime,
    _UInt32 eTime,
    _UInt8  *path,
    _UInt8  *fName
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
        );
/*ˢͼ*/

/*
 ��������setReqRefresh
 ������ˢͼ����
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt8  chId
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqRefresh(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId
        );

/*
 ��������setResRefresh
 ������ˢͼӦ��
 ������
     _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResRefresh(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*��Ƶ���Ų���*/

/*
 ��������setReqVideoPlay
 ��������Ƶ���Ų�������
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt32 stream,
    _UInt32 time,
    _UInt16 port,
    _UInt8  oType,
    _UInt8  extend
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
        );

/*
 ��������setResVideoPlay
 ��������Ƶ���Ų���Ӧ��
 ������
    _UInt32 devIdH,    �豸��� ��λ4�ֽ�
    _UInt32 devIdL,    �豸��� ��λ4�ֽ�
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResVideoPlay(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/**/

/*
 ��������setReqGetVideoParms
 ��������ȡ��Ƶ��������
 ������
    _UInt32 devIdH,   �豸��� ��λ4�ֽ�
    _UInt32 devIdL,   �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt16 stream
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqGetVideoParms(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt16 stream
        );

/*
 ��������setResGetVideoParms
 ��������ȡ��Ƶ����Ӧ��
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt16 stream,
    _UInt16 width,
    _UInt16 height,
    _UInt16 sRate,
    _UInt16 fRate
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
        );
/**/

/*
 ��������setReqSetVideoParms
 ������������Ƶ��������
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt16 stream,
    _UInt16 width,
    _UInt16 height,
    _UInt16 sRate,
    _UInt16 fRate
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
        );

/*
 ��������setResSetVideoParms
 ������������Ƶ����Ӧ��
 ������
    _UInt32 devIdH,    �豸��� ��λ4�ֽ�
    _UInt32 devIdL,    �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt16 stream,
    _UInt8  type
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResSetVideoParms(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt16 stream,
        _UInt8  type
        );
/**/

/*
 ��������setReqVideoOpen
 ��������Ƶ�򿪲�������
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt8  operation,
    _UInt8  chId,
    _UInt16 port
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqVideoOpen(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  operation,
        _UInt8  chId,
        _UInt16 port
        );

/*
 ��������setResVideoOpen
 ��������Ƶ�򿪲���Ӧ��
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  chId,
    _UInt16 stream
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResVideoOpen(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt16 stream
        );
/**/

/*
 ��������setReqDevRemoteRestart
 �������豸Զ����������
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  rRestart
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqDevRemoteRestart(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  rRestart
        );

/*
 ��������setResDevRemoteRestart
 �������豸Զ������Ӧ��
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResDevRemoteRestart(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/**/

/*
 ��������setReqDevUpgrade
 �������豸��������
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  *fContent
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqDevUpgrade(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  *fContent,/*�˴�Ϊ�ļ����ݣ�ÿ��1KB���ݣ��粻������������1KB�԰�1KB���ͣ������һ�ֽ����ݺ��'\0'*/
        _UInt32 contentLen
        );

/*
 ��������setResDevUpgrade
 �������豸����Ӧ��
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  *fName
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResDevUpgrade(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  *fName,
        _UInt32 nameLen
        );
/**/
///////////////////////////////////// ��������ṹ/////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*��Ч����*/
/*Э��汾��ѯ*/
STRUCT
{
    _UInt32 devIdH; /*�豸��� �ָ�λ4�ֽ� ��λ4�ֽ�*/
    _UInt32 devIdL;
    _UInt32 proVer; /*Э��汾��*/
}ReqVersion;

STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt32 proVer;
}ResVersion;
/*����*/ /*�豸��������Ӧ*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt32 cumulative;
}ReqDLive;
/*�豸����*/
STRUCT
{
    _UInt32 proType;
    _UInt32 devType;
}ReqFindDev;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt32 devType;
    _UInt32 chNum;
    _UInt32 netIp;
    _UInt32 netDns;
    _UInt32 netGateWay;
    _UInt32 netMask;
    _UInt8  netMac[20];
    _UInt8  buf[128];
}ResFindDev;
/*�豸������*/
/*�豸����*/
/*�豸ά��*/
/*��ȡ������Ϣ*/
/*�ͻ���������*/
/*�û�*/
/*�豸��Ϣ*/
/*�ͻ�������*/
/*��ȡ��������Ӧ��Ϣ*/
/*����*/
/*���ݷ���*/
STRUCT
{
    _UInt8 data[1*1024];
}ResData;
/*��Ƶ����*/
STRUCT
{
    _UInt8 vData[100*1024];
}ResVideoData;
/*��ȡ��ʷ����*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt32 date;
    _UInt32 sTime;
    _UInt32 eTime;
}ReqGetHistordata;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResGetHistordata;
/*�û���¼*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  name[32];
    _UInt8  passwd[32];
}ReqUserLogin;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResUserLogin;
/*��̨*/
/////////////////
/*�豸����*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  devType;
    _UInt8  chType;
    _UInt8  connType;
    _UInt8  sigStrength;
}ReqDevConn;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8 result;
}ResDevConn;
/*�豸����*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
}ReqDevDisConn;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResDevDisConn;
/*��ȡ����������*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt32 terId;
    _UInt8  chId;
}ReqGetSensorConf;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt32 terId;
    _UInt8  chId;
    _UInt32 minThreshlod;
    _UInt32 maxThreshlod;
    _UInt32 maxRefer;
    _UInt32 minRefer;
    _UInt32 range;
}ResGetSensorConf;
/*�޸Ĵ���������*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt32 terId;
    _UInt8  chId;
    _UInt32 minThreshlod;
    _UInt32 maxThreshlod;
    _UInt32 maxRefer;
    _UInt32 minRefer;
}ReqModSensorConf;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt32 terId;
    _UInt8  chId;
    _UInt8  result;
}ResModSensorConf;
/*��ʷ�����ϱ�ʱ����*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt16 time;
}ReqHisDataReportTime;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResHisDataReportTime;
/*485����*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt32 terId;
    _UInt16 rTime;
    _UInt32 baud;
    _UInt32 dLen;
    _UInt8  sFlags;
    _UInt32 eoCheck;
}ReqFEFConf;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResFEFConf;
/*232����*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt32 baud;
    _UInt32 dLen;
    _UInt8  sFlags;
    _UInt32 eoCheck;
}ReqTTTConf;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResTTTConf;

/*���ݲ�¼ ������*/     //���ݲ�¼Ҳ�޸�Ϊ�̶��ֳ�
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  dType;
    _UInt32 pTime;
    _UInt8  sw;
    _UInt32 buf1[8]; //�˴���һ��Ϊ8��������0-8
    _UInt32 TTTNum;
    _UFloat buf2[128]; /*��С���� TTTNum *4 */
    _UInt32 len;
    _UFloat buf3[128]; /*���Ȳ�ȷ��*/
}ResDataMakeUp;
/*�����������Զ��ϱ�*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt8  sName[32];
    _UInt8  sType;
    _UInt32 minThreshlod;
    _UInt32 maxThreshlod;
    _UInt32 maxRefer;
    _UInt32 minRefer;
    _UInt32 range;
}ReqSensorAutoReport;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt8  result;
}ResSensorAutoReport;
/*��ȡ��������*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  wType;
    _UInt8  chId;
}ReqGetWarnPlace;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  wType;
    _UInt8  chId;
    _UInt8  alarm;
    _UInt8  email;
    _UInt8  screenshot;
    _UInt8  capturePic;
    _UInt8  callPreset;
    _UInt8  PreChId;
    _UInt8  PreId;
    _UInt8  sendToClient;
    _UInt8  startVideo;
    _UInt8  result;
}ResGetWarnPlace;
/*�޸ı�������*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  wType;
    _UInt8  warnOther;
    _UInt8  chId;
    _UInt8  alarm;
    _UInt8  email;
    _UInt8  screenshot;
    _UInt8  capturePic;
    _UInt8  callPreset;
    _UInt8  PreChId;
    _UInt8  PreId;
    _UInt8  sendToClient;
    _UInt8  startVideo;
}ReqModWarnPlace;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResModWarnPlace;
/*�������*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  wType;
    _UInt8  chId;
}ReqWarnClear;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResWarnClear;
/*��ȡ����ԤԼ*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  wType;
    _UInt8  chId;
}ReqGetWarnOrder;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  wType;
    _UInt8  chId;
    _UInt32 sTime;
    _UInt32 eTime;
}ResGetWarnOrder;
/*�޸ı���ԤԼ*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  wType;
    _UInt8  chId;
    _UInt32 sTime;
    _UInt32 eTime;
}ReqModWarnOrder;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8 chId;
}ResModWarnOrder;
/*��ͨ����*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  wType;
    _UInt8  chId;
    _UInt8  wContent[1024];
}ReqGeneralWarn;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResGeneralWarn;
/*���ݱ���*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  devName[32];
    _UInt8  wType;
    _UInt8  chId;
    _UInt32 sVal;
    _UInt32 minVal;
    _UInt32 maxVal;
    _UInt8  dType;
    _UInt8  tName;
    _UInt32 unit;
    _UInt32 time;
}ReqDataWarn;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResDataWarn;
/*��ȡ�豸����״̬*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
}ReqGetNetState;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  netType;
    _UInt32 ip;
    _UInt32 dns;
    _UInt32 mask;
    _UInt32 gateway;
    _UInt8  mac[20];
    _UInt8  dhcp;
}ResGetNetState;
/*�����豸����״̬*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  netType;
    _UInt32 ip;
    _UInt32 dns;
    _UInt32 mask;
    _UInt32 gateway;
    _UInt8  mac[20];
    _UInt8  dhcp;
}ReqSetNetState;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResSetNetState;
/*3G ��ȡ����״̬*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  nType;
    _UInt8  cType;
}ReqGetNetState3G;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  name[16];
    _UInt8  passwd[16];
    _UInt8  apn;
}ResGetNetState3G;
/*Զ������ͨ��*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
}ReqRemoteDisktop;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
}ResRemoteDistop;
/*��ȡ�豸�û� �˴����ò���ȫ*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
}ReqGetDevUser;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  uName[16];
    _UInt16 power;
}ResGetDevUser;
/*�޸��豸�û�*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  uName[16];
    _UInt8  uPasswd[16];
    _UInt8  pVideo;
    _UInt8  pConnection;
    _UInt8  pYTControl;
    _UInt8  pShutDown;
    _UInt8  pCapturePic;
    _UInt8  pSystemSet;
    _UInt8  pVideoChange;
    _UInt8  pUserManager;
    _UInt8  pPicChange;
    _UInt8  pRemoteManager;
    _UInt8  pAudioListen;
}ReqModDevUser;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResModDevUser;
/*����ʱ��*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
}ReqSetTime;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt32 time;
}ResSetTime;
/*��̨����*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt8  command;
    _UInt8  rate;
}ReqYunTaiSet;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResYunTaiSet;
/*��ȡ��̨*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
}ReqGetYunTaiInfo;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt32 baud;
    _UInt32 addr;
    _UInt8  pType;
}ResGetYunTaiInfo;
/*������̨*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt8  command;
    _UInt8  rate;
}ReqControlYunTai;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt8  result;
}ResControlYunTai;
/*��ȡԤ�õ�*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
}ReqGetPreset;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt16 proset[256];
}ResGetPreset;
/*�޸�Ԥ�õ�*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt8  cType;
    _UInt16 point;
}ReqModPreset;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt8  result;
}ResModPreset;
/*��ȡѲ������*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
}ReqGetCruiseConf;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt16 list[100];
}ResGetCruiseConf;
/*�޸�Ѳ������*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt16 list[100];
}ReqModCruiseConf;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt8  result;
}ResModCruiseConf;
/*��ȡ��������*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
}ReqGetEmailConf;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  eServer[32];
    _UInt16 port;
    _UInt8  sType;
    _UInt8  sName[16];
    _UInt8  sPasswd[16];
    _UInt32 timeOut;
    _UInt8  recver1[32];
    _UInt8  recver2[32];
    _UInt8  recver3[32];
    _UInt8  recver4[32];
}ResGetEmailConf;
/*�޸���������*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8 eServer[32];
    _UInt16 port;
    _UInt8 sType;
    _UInt8 sName[16];
    _UInt8 sPasswd[16];
    _UInt32 timeOut;
    _UInt8 recver1[32];
    _UInt8 recver2[32];
    _UInt8 recver3[32];
    _UInt8 recver4[32];
}ReqModEmailConf;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8 chId;
    _UInt8 result;
}ResModEmailConf;
/*������������*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
}ReqTestEmailConf;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8 result;
}ResTestEmailConf;
/*ң�ؿ�������*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8 wSwitch;
}ReqRemoteControlSet;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResRemoteControlSet;
/*ң�ؿ���״̬��ȡ*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  wSwitch;
}ReqRemoteControlGet;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  sState;
}ResRemoteControlGet;
/*����Ӳ�̲���*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8   hdSize;
}ReqSetHardDiskParm;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResSetHardDiskParm;
/*��ʽ��*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  operation;
}ReqFormat;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResFormat;
/*¼����*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  vFull;
}ReqVideoFull;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResVideoFull;
/*�Խ�*/
STRUCT
{
    _UInt16 rPort;
    _UInt8  code;
}ReqTalk;
STRUCT
{
    _UInt8 result;
}ResTalk;
/*��Ƶ����*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt32 sTime;
    _UInt32 eTime;
    _UInt8  fName[256];
}ReqAudioDownload;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt32 sTime;
    _UInt32 eTime;
    _UInt8  path[256];
    _UInt8  fName[256];
}ResAudioDownload;
/*��Ƶ����*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt32 sTime;
    _UInt32 eTime;
    _UInt8  fName[256];
}ReqVideoDownload;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt32 sTime;
    _UInt32 eTime;
    _UInt8  path[256];
    _UInt8  fName[256];
}ResVideoDownload;
/*ˢͼ*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
}ReqRefresh;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResRefresh;
/*��Ƶ���Ų���*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt32 stream;
    _UInt32 time;
    _UInt16 port;
    _UInt8  oType;
    _UInt8  extend;
}ReqVideoPlay;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResVideoPlay;
/*��ȡ��Ƶ����*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt16 stream;
}ReqGetVideoParms;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt16 stream;
    _UInt16 width;
    _UInt16 height;
    _UInt16 sRate;
    _UInt16 fRate;
}ResGetVideoParms;
/*������Ƶ����*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt16 stream;
    _UInt16 width;
    _UInt16 height;
    _UInt16 sRate;
    _UInt16 fRate;
}ReqSetVideoParms;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt16 stream;
    _UInt8  type;
}ResSetVideoParms;
/*��Ƶ�򿪲���*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  operation;
    _UInt8  chId;
    _UInt16 port;
}ReqVideoOpen;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  chId;
    _UInt16 stream;
}ResVideoOpen;
/*�豸Զ������*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  rRestart;
}ReqDevRemoteRestart;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResDevRemoteRestart;
/*�豸����*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  fContent[1024]; /*�˴�Ϊ�ļ����ݣ�ÿ��1KB���ݣ��粻������������1KB�԰�1KB���ͣ������һ�ֽ����ݺ��'\0'*/
}ReqDevUpgrade;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  fName[256];
}ResDevUpgrade;

#endif
