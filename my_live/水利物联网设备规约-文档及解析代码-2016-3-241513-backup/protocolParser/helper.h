#ifndef _HELPER_H_
#define _HELPER_H_
#include "global.h"
/*
	������: packagingHeader
	����: ���ݹ�������װЭ��ͷ
	����: 
	      buf ������ָ��
	      len �������û����ݳ���
		  funCode ������
		  stationType ��վ(�豸�ˣ��ͻ���)����վ(�����)
		  ReqOrRes 0 ���� 1 Ӧ��
*/
void packagingData(_UInt8 *buf,void *userData,_UInt32 userDatalen,_UInt16 funCode,_UInt8 stationType,_UInt8 ReqOrRes,_UInt32 FrameFixLen);
void unpackagingData();

void packageingHeader(Frame *f, _UInt8  start1,   //֡��ʼ
                                _UInt16   len,    //֡����
                                _UInt8  start2,   //֡��ʼ
                                _UInt8  res,      //res ����
                                _UInt8  prm,      //prm
                                _UInt8  fcbAcd,   //FCB ACD
                                _UInt8  fcvDfc,   //FCD DFC
                                _UInt8  funCode,  //������
                                _UInt8  addr,     //��ַ��
                                _UInt8  type,     //���ͱ�ʶ
                                //�ɱ��޶���
                                _UInt8  sort,     //�Ƿ�˳���ŷ�
                                _UInt8  eleNum,   //Ԫ�ظ���
                                //����ԭ��
                                _UInt8  t,        //ʵ�� 1 δʵ�� 0
                                _UInt8  pn,       //����ȷ�� 0 �϶�ȷ�� 1 
                                _UInt8  other,    //���� Ĭ��0
                                _UInt8  nUse,     //���� 
                                _UInt8  publicAddr, //������ַ
                                _UInt16  informosome ); // ��Ϣ���ַ
                                /*
	������: packagingHeader
	����: ���ݹ�������װЭ��ͷ
	����: 
			buf			������ָ��
			uFunCode		������
			uDirection	���䷽��(0, ��ʾ�����ն���ƽ̨���䱨�ģ�1, ��ʾ����ƽ̨���ն˴��䱨��)
			uInfoNum		��ϢԪ�ظ���
			uCause		����ԭ��
			uInfoAddr		��Ϣ���ַ

*/
void SetInfo( _UInt8 *buf, void *userData, _UInt32 userDatalen, _UInt8 ReqOrRes, _UInt32 FrameFixLen, 
			  _UInt8 uFunCode, _UInt8 uDirection, _UInt8 uInfoNum, _UInt8 uCause, _UInt16 uInfoAddr);
#endif