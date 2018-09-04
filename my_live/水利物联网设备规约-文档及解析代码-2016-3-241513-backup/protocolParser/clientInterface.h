#ifndef _CLIENT_INTERFACE_
#define _CLIENT_INTERFACE_
#include "global.h"
/*
 ��������setReqClientConn
 �������ͻ�����������
 ������
    _UInt8 *name,
    _UInt8 *passwd
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqClientConn(
    HandlePtr ptr,
    _UInt8 *name,
    _UInt32 nameLen,
    _UInt8 *passwd,
    _UInt32 passwdLen
    );


/*
 ��������setResClientConn
 �������ͻ�������Ӧ��
 ������
    _UInt8 result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResClientConn(
    HandlePtr ptr,
    _UInt8 result
    );

/**/


/*
 ��������setReqClientDisConn
 �������ͻ�����������
 ������
    _UInt8  *name,
    _UInt8  *passwd,
    _UInt16 code,
    _UInt32 ip,
    _UInt16 port,
    _UInt8  natType
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
    );


/*
 ��������setResClientDisConn
 �������ͻ�������Ӧ��
 ������
    _UInt8  *name,
    _UInt8  power,
    _UInt32 province,
    _UInt32 city,
    _UInt32 country,
    _UInt32 town,
    _UInt32 village
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
    );

/**/


/*
 ��������setReqUserRegister
 ������ �û�ע������
 ������
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
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
    );


/*
 ��������setResUserRegister
 �������û�ע��Ӧ��
 ������
     _UInt8 result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResUserRegister(
    HandlePtr ptr,
    _UInt8 result
    );

/**/


/*
 ��������setReqGetUserInfo
 �������û���Ϣ��ȡ����
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  get
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqGetUserInfo(
    HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt8  get
    );


/*
 ��������setResGetUserInfo
 �������û���Ϣ��ȡӦ��
 ������
    HandlePtr ptr,
    _UInt8  *name,
    _UInt32 nameLen,
    _UInt8  *passwd,
    _UInt32 passwdLen,
    _UInt8  type,
    _UInt16 power,
    _UInt16 area,
    _UInt16 operation
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
    );

/**/


/*
 ��������setReqAddUserInfo
 �������û���Ϣ��������
 ������
    _UInt8 *name,
    _UInt8 *passwd,
    _UInt8 type,
    _UInt8 power,
    _UInt16 area,
    _UInt16 operaion
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
    );


/*
 ��������setResAddUserInfo
 �������û���Ϣ����Ӧ��
 ������
    _UInt8 result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResAddUserInfo(
    HandlePtr ptr,
    _UInt8 result
    );

/**/


/*
 ��������setReqDelUserInfo
 �������û���Ϣɾ������
 ������
    _UInt8 *name
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqDelUserInfo(
    HandlePtr ptr,
    _UInt8 *name,
    _UInt32 nameLen
    );


/*
 ��������setResDelUserInfo
 �������û���Ϣɾ��Ӧ��
 ������
    _UInt8 result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResDelUserInfo(
    HandlePtr ptr,
    _UInt8 result
    );

/**/


/*
 ��������setReqModUserInfo
 �������û���Ϣ�޸�����
 ������
    HandlePtr ptr,
    _UInt8 *name,
    _UInt32 nameLen,
    _UInt8 *passwd,
    _UInt32 passwdLen,
    _UInt8 type,
    _UInt8 power,
    _UInt16 area,
    _UInt16 operation
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
    );


/*
 ��������setResModUserInfo
 �������û���Ϣ�޸�Ӧ��
 ������
    _UInt8 result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResModUserInfo(
    HandlePtr ptr,
    _UInt8 result
    );

/**/
/*
 ��������setReqGetDevInfo
 �������豸��Ϣ��ȡ����
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  get
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqGetDevInfo(
    HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt8  get
    );


/*
 ��������setResGetDevInfo
 �������豸��Ϣ��ȡӦ��
 ������
        HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt32 chId,
    _UInt8  devType,
    _UInt8  *ip,
    _UInt32 ipLen
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResGetDevInfo(
        HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt32 chId,
    _UInt8  devType,
    _UInt8  *ip,
    _UInt32 ipLen
    );

/**/


/*
 ��������setReqDelDevInfo
 �������豸��Ϣɾ������
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL  �豸��� ��λ4�ֽ�
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqDelDevInfo(
    HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL

    );


/*
 ��������setResDelDevInfo
 �������豸��Ϣɾ��Ӧ��
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResDelDevInfo(
    HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt8  result
    );

/**/


/*
 ��������setReqModDevInfo
 �������豸��Ϣ�޸�����
 ������
     _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  conf
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setReqModDevInfo(
    HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt8  conf

    );


/*
 ��������setResModDevInfo
 �������豸��Ϣ�޸�Ӧ��
 ������
    _UInt32 devIdH,  �豸��� ��λ4�ֽ�
    _UInt32 devIdL,  �豸��� ��λ4�ֽ�
    _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResModDevInfo(
    HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt8  result
    );

/*�豸���*/


/*
 ��������setReqAddDev
 �������豸�������
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
  _UInt32 devIdL,   �豸��� ��λ4�ֽ�
  _UInt32 chNum,
  _UInt8  dType,
  _UInt8  name,
  _UInt8  passwd,
  _UInt8  *ip
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
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
    );


/*
 ��������setResAddDev
 �������豸���Ӧ��
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
   _UInt32 devIdL,  �豸��� ��λ4�ֽ�
   _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResAddDev(
    HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt8  result
    );
/*�ͻ�������*/
STRUCT
{
  _UInt8 name[16];
  _UInt8 passwd[16];
}ReqClientConn;
STRUCT
{
  _UInt8 result;
}ResClientConn;

/*�ͻ�������*/
STRUCT
{
  _UInt8  name[16];
  _UInt8  passwd[16];
  _UInt16 code;
  _UInt32 ip;
  _UInt16 port;
  _UInt8  natType;
}ReqClientDisConn;
STRUCT
{
  _UInt8  name[16];
  _UInt8  power;
  _UInt32 province;
  _UInt32 city;
  _UInt32 country;
  _UInt32 town;
  _UInt32 village;
}ResClientDisConn;

/*�û�ע��*/
STRUCT
{
  _UInt32 devIdH;
  _UInt32 devIdL;
  _UInt8  loginName[16];
  _UInt8  loginPasswd[16];
  _UInt8  email[32];
  _UInt8  phone[16];
}ReqUserRegister;
STRUCT
{
  _UInt8 result;
}ResUserRegister;

/*�û���Ϣ��ȡ*/
STRUCT
{
  _UInt32 devIdH;
  _UInt32 devIdL;
  _UInt8  get;
}ReqGetUserInfo;
STRUCT
{
  _UInt8  name[16];
  _UInt8  passwd[16];
  _UInt8  type;
  _UInt16 power;
  _UInt16 area;
  _UInt16 operation;
}ResGetUserInfo;

/*�û���Ϣ����*/
STRUCT
{
  _UInt8 name[16];
  _UInt8 passwd[16];
  _UInt8 type;
  _UInt8 power;
  _UInt16 area;
  _UInt16 operaion;
}ReqAddUserInfo;
STRUCT
{
  _UInt8 result;
}ResAddUserInfo;

/*�û���Ϣɾ��*/
STRUCT
{
  _UInt8 name[16];
}ReqDelUserInfo;
STRUCT
{
  _UInt8 result;
}ResDelUserInfo;

/*�û���Ϣ�޸�*/
STRUCT
{
  _UInt8 name[16];
  _UInt8 passwd[16];
  _UInt8 type;
  _UInt8 power;
  _UInt16 area;
  _UInt16 operaion;
}ReqModUserInfo;
STRUCT
{
  _UInt8 result;
}ResModUserInfo;

/*�豸��Ϣ��ȡ*/
STRUCT
{
  _UInt32 devIdH;
  _UInt32 devIdL;
  _UInt8  get;
}ReqGetDevInfo;
STRUCT
{
  _UInt32 devIdH;
  _UInt32 devIdL;
  _UInt32 chId;
  _UInt8  devType;
  _UInt8  ip[32];
}ResGetDevInfo;

/*�豸��Ϣɾ��*/
STRUCT
{
  _UInt32 devIdH;
  _UInt32 devIdL;

}ReqDelDevInfo;
STRUCT
{
  _UInt32 devIdH;
  _UInt32 devIdL;
  _UInt8  result;
}ResDelDevInfo;

/*�豸��Ϣ�޸�*/
STRUCT
{
  _UInt32 devIdH;
  _UInt32 devIdL;
  _UInt8  conf;

}ReqModDevInfo;
STRUCT
{
  _UInt32 devIdH;
  _UInt32 devIdL;
  _UInt8  result;
}ResModDevInfo;

/*�豸���*/
STRUCT
{
  _UInt32 devIdH;
  _UInt32 devIdL;
  _UInt32 chNum;
  _UInt8  dType;
  _UInt8  name[32];
  _UInt8  passwd[32];
  _UInt8  ip[16];
}ReqAddDev;
STRUCT
{
  _UInt32 devIdH;
  _UInt32 devIdL;
  _UInt8  result;
}ResAddDev;
#endif
