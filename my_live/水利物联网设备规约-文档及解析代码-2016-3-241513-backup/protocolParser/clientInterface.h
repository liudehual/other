#ifndef _CLIENT_INTERFACE_
#define _CLIENT_INTERFACE_
#include "global.h"
/*
 函数名：setReqClientConn
 描述：客户端上线请求
 参数：
    _UInt8 *name,
    _UInt8 *passwd
 返回值： 0 失败 1 成功
*/
_UBool setReqClientConn(
    HandlePtr ptr,
    _UInt8 *name,
    _UInt32 nameLen,
    _UInt8 *passwd,
    _UInt32 passwdLen
    );


/*
 函数名：setResClientConn
 描述：客户端上线应答
 参数：
    _UInt8 result
 返回值： 0 失败 1 成功
*/
_UBool setResClientConn(
    HandlePtr ptr,
    _UInt8 result
    );

/**/


/*
 函数名：setReqClientDisConn
 描述：客户端下线请求
 参数：
    _UInt8  *name,
    _UInt8  *passwd,
    _UInt16 code,
    _UInt32 ip,
    _UInt16 port,
    _UInt8  natType
 返回值： 0 失败 1 成功
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
 函数名：setResClientDisConn
 描述：客户端下线应答
 参数：
    _UInt8  *name,
    _UInt8  power,
    _UInt32 province,
    _UInt32 city,
    _UInt32 country,
    _UInt32 town,
    _UInt32 village
 返回值： 0 失败 1 成功
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
 函数名：setReqUserRegister
 描述： 用户注册请求
 参数：
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
 返回值： 0 失败 1 成功
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
 函数名：setResUserRegister
 描述：用户注册应答
 参数：
     _UInt8 result
 返回值： 0 失败 1 成功
*/
_UBool setResUserRegister(
    HandlePtr ptr,
    _UInt8 result
    );

/**/


/*
 函数名：setReqGetUserInfo
 描述：用户信息获取请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  get
 返回值： 0 失败 1 成功
*/
_UBool setReqGetUserInfo(
    HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt8  get
    );


/*
 函数名：setResGetUserInfo
 描述：用户信息获取应答
 参数：
    HandlePtr ptr,
    _UInt8  *name,
    _UInt32 nameLen,
    _UInt8  *passwd,
    _UInt32 passwdLen,
    _UInt8  type,
    _UInt16 power,
    _UInt16 area,
    _UInt16 operation
 返回值： 0 失败 1 成功
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
 函数名：setReqAddUserInfo
 描述：用户信息增加请求
 参数：
    _UInt8 *name,
    _UInt8 *passwd,
    _UInt8 type,
    _UInt8 power,
    _UInt16 area,
    _UInt16 operaion
 返回值： 0 失败 1 成功
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
 函数名：setResAddUserInfo
 描述：用户信息增加应答
 参数：
    _UInt8 result
 返回值： 0 失败 1 成功
*/
_UBool setResAddUserInfo(
    HandlePtr ptr,
    _UInt8 result
    );

/**/


/*
 函数名：setReqDelUserInfo
 描述：用户信息删除请求
 参数：
    _UInt8 *name
 返回值： 0 失败 1 成功
*/
_UBool setReqDelUserInfo(
    HandlePtr ptr,
    _UInt8 *name,
    _UInt32 nameLen
    );


/*
 函数名：setResDelUserInfo
 描述：用户信息删除应答
 参数：
    _UInt8 result
 返回值： 0 失败 1 成功
*/
_UBool setResDelUserInfo(
    HandlePtr ptr,
    _UInt8 result
    );

/**/


/*
 函数名：setReqModUserInfo
 描述：用户信息修改请求
 参数：
    HandlePtr ptr,
    _UInt8 *name,
    _UInt32 nameLen,
    _UInt8 *passwd,
    _UInt32 passwdLen,
    _UInt8 type,
    _UInt8 power,
    _UInt16 area,
    _UInt16 operation
 返回值： 0 失败 1 成功
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
 函数名：setResModUserInfo
 描述：用户信息修改应答
 参数：
    _UInt8 result
 返回值： 0 失败 1 成功
*/
_UBool setResModUserInfo(
    HandlePtr ptr,
    _UInt8 result
    );

/**/
/*
 函数名：setReqGetDevInfo
 描述：设备信息获取请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  get
 返回值： 0 失败 1 成功
*/
_UBool setReqGetDevInfo(
    HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt8  get
    );


/*
 函数名：setResGetDevInfo
 描述：设备信息获取应答
 参数：
        HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt32 chId,
    _UInt8  devType,
    _UInt8  *ip,
    _UInt32 ipLen
 返回值： 0 失败 1 成功
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
 函数名：setReqDelDevInfo
 描述：设备信息删除请求
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL  设备编号 低位4字节
 返回值： 0 失败 1 成功
*/
_UBool setReqDelDevInfo(
    HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL

    );


/*
 函数名：setResDelDevInfo
 描述：设备信息删除应答
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResDelDevInfo(
    HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt8  result
    );

/**/


/*
 函数名：setReqModDevInfo
 描述：设备信息修改请求
 参数：
     _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  conf
 返回值： 0 失败 1 成功
*/
_UBool setReqModDevInfo(
    HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt8  conf

    );


/*
 函数名：setResModDevInfo
 描述：设备信息修改应答
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResModDevInfo(
    HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt8  result
    );

/*设备添加*/


/*
 函数名：setReqAddDev
 描述：设备添加请求
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
  _UInt32 devIdL,   设备编号 低位4字节
  _UInt32 chNum,
  _UInt8  dType,
  _UInt8  name,
  _UInt8  passwd,
  _UInt8  *ip
 返回值： 0 失败 1 成功
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
 函数名：setResAddDev
 描述：设备添加应答
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
   _UInt32 devIdL,  设备编号 低位4字节
   _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResAddDev(
    HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt8  result
    );
/*客户端上线*/
STRUCT
{
  _UInt8 name[16];
  _UInt8 passwd[16];
}ReqClientConn;
STRUCT
{
  _UInt8 result;
}ResClientConn;

/*客户端下线*/
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

/*用户注册*/
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

/*用户信息获取*/
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

/*用户信息增加*/
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

/*用户信息删除*/
STRUCT
{
  _UInt8 name[16];
}ReqDelUserInfo;
STRUCT
{
  _UInt8 result;
}ResDelUserInfo;

/*用户信息修改*/
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

/*设备信息获取*/
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

/*设备信息删除*/
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

/*设备信息修改*/
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

/*设备添加*/
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
