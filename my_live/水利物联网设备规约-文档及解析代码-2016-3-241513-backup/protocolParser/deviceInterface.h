#ifndef _DEVICEINTERFACE_
#define _DEVICEINTERFACE_
#include "global.h"
/////////////////////////////////////////////////////////////////////////////////
/*
 *   添加数据,从网络获取数据
 *   该函数用于从网络获取数据
 *   用法:read(
    HandlePtr ptr,)->GetMessageFromNet
 */
/*
 函数名：GetMessageFromNet
 描述：添加数据,从网络获取数据
       该函数用于从网络获取数据
       用法:read(
    HandlePtr ptr,)->GetMessageFromNet
 参数：
    HandlePtr ptr,char *buf,int len
 返回值： 0 失败 1 成功
*/
_UBool GetMessageFromNet(
        HandlePtr ptr,
        char *buf,
        int len
        );

/*无效命令*/
/*协议版本查询*/

/*
 函数名：setReqVersion
 描述：协议版本查询请求
 参数：
    _UInt32 devIdH 设备编号 分高位4字节 低位4字节
    _UInt32 devIdL 设备编号 低位4字节
    _UInt32 proVer 协议版本号
 返回值： 0 失败 1 成功
*/
_UBool setReqVersion(
        HandlePtr ptr,
        _UInt32 devIdH, /*设备编号 分高位4字节*/
        _UInt32 devIdL, //
        _UInt32 proVer /*协议版本号*/
        );

/*
 函数名：setResVersion
 描述：协议版本查询应答
 参数：
    _UInt32 devIdH,   设备编号 高位4字节
    _UInt32 devIdL,   设备编号 低位4字节
    _UInt32 proVer    协议版本号
 返回值： 0 失败 1 成功
*/
_UBool setResVersion(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 proVer
        );
/*心跳*/ /*设备心跳无响应*/

/*
 函数名：setReqDLive
 描述：心跳 （设备心跳无响应）
 参数：
   _UInt32 devIdH, 设备编号 高位4字节
   _UInt32 devIdL, 设备编号 低位4字节
   _UInt32 leiJi
 返回值： 0 失败 1 成功
*/
_UBool setReqDLive(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 Cumulative
        );
/*设备检索*/

/*
 函数名：setReqFindDev
 描述：设备检索请求 (
    HandlePtr ptr,基于UDP)
 参数：
    _UInt32 proType,
    _UInt32 devType
 返回值： 0 失败 1 成功
*/
_UBool setReqFindDev(
        HandlePtr ptr,
        _UInt32 proType,
        _UInt32 devType
        );

/*
 函数名：setResFindDev
 描述：设备检索应答 (
    HandlePtr ptr,基于UDP)
 参数：
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
 返回值： 0 失败 1 成功
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

/*
 函数名：setResData
 描述：数据发送
 参数：
    _UInt8 *data
    _UInt32 dataLen
 返回值： 0 失败 1 成功
*/
_UBool setResData(
        HandlePtr ptr,
        _UInt8 *data,
        _UInt32 dataLen
        );

/*
 函数名：setResVideoData
 描述：视频数据发送
 参数：
    _UInt8 *vData
    _UInt32 vLen
 返回值： 0 失败 1 成功
*/
_UBool setResVideoData(
        HandlePtr ptr,
        _UInt8 *vData,
        _UInt32 vLen
        );
/*获取历史数据*/

/*
 函数名：setReqGetHistordata
 描述：获取历史数据
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt8  chId,
    _UInt32 date,
    _UInt32 sTime,
    _UInt32 eTime
 返回值： 0 失败 1 成功
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
 函数名：setResGetHistordata
 描述：
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResGetHistordata(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*用户登录*/

/*
 函数名：setReqUserLogin
 描述：用户登录请求
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt8  *name,
    _UInt8  *passwd
 返回值： 0 失败 1 成功
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
 函数名：setResUserLogin
 描述：用户登录响应
 参数：
   _UInt32 devIdH, 设备编号 高位4字节
   _UInt32 devIdL, 设备编号 低位4字节
   _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResUserLogin(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*云台*/
/////////////////
/**/

/*
 函数名：setReqDevConn
 描述: 设备上线
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt8  devType,
    _UInt8  chType,
    _UInt8  connType,
    _UInt8  sigStrength
 返回值： 0 失败 1 成功
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
 函数名：setResDevConn
 描述：设备上线
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt8 result
 返回值： 0 失败 1 成功
*/
_UBool setResDevConn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8 result
        );
/*设备下线*/

/*
 函数名：setReqDevDisConn
 描述： 设备下线
 参数：
    _UInt32 devIdH,
    _UInt32 devIdL
 返回值： 0 失败 1 成功
*/
_UBool setReqDevDisConn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        );

/*
 函数名：setResDevDisConn
 描述： 设备下线
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResDevDisConn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*获取传感器配置*/

/*
 函数名：setReqGetSensorConf
 描述：获取传感器配置请求
 参数：
   _UInt32 devIdH, 设备编号 高位4字节
   _UInt32 devIdL, 设备编号 低位4字节
   _UInt32 terId,
   _UInt8  chId
 返回值： 0 失败 1 成功
*/
_UBool setReqGetSensorConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 terId,
        _UInt8  chId
        );

/*
 函数名：setResGetSensorConf
 描述：获取传感器配置应答
 参数：
   _UInt32 devIdH, 设备编号 高位4字节
   _UInt32 devIdL, 设备编号 低位4字节
   _UInt32 terId,
   _UInt8  chId,
   _UInt32 minThreshlod,
   _UInt32 maxThreshlod,
   _UInt32 maxRefer,
   _UInt32 minRefer,
   _UInt32 range
 返回值： 0 失败 1 成功
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
/*修改传感器配置*/

/*
 函数名：setReqModSensorConf
 描述：修改传感器配置请求
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
   _UInt32 devIdL,  设备编号 低位4字节
   _UInt32 terId,
   _UInt8  chId,
   _UInt32 minThreshlod,
   _UInt32 maxThreshlod,
   _UInt32 maxRefer,
   _UInt32 minRefer
 返回值： 0 失败 1 成功
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
 函数名：setResModSensorConf
 描述：修改传感器配置应答
 参数：
   _UInt32 devIdH, 设备编号 高位4字节
   _UInt32 devIdL, 设备编号 低位4字节
   _UInt32 terId,
   _UInt8  chId,
   _UInt8  result
 返回值： 0 失败 1 成功
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
 函数名：setReqHisDataReportTime
 描述：历史数据上报时间间隔请求
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt16 time
 返回值： 0 失败 1 成功
*/
_UBool setReqHisDataReportTime(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt16 time
        );

/*
 函数名：setResHisDataReportTime
 描述：历史数据上报时间间隔应答
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
   _UInt32 devIdL,  设备编号 低位4字节
   _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResHisDataReportTime(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );

/*
 函数名：setReqFEFConf
 描述：485配置请求
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt32 terId,
    _UInt16 rTime,
    _UInt32 baud,
    _UInt32 dLen,
    _UInt8  sFlags,
    _UInt32 eoCheck
 返回值： 0 失败 1 成功
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
 函数名：setResFEFConf
 描述：485配置应答
 参数：
     _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResFEFConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*232配置*/

/*
 函数名：setReqTTTConf
 描述：232配置请求
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt32 baud,
    _UInt32 dLen,
    _UInt8  sFlags,
    _UInt32 eoCheck
 返回值： 0 失败 1 成功
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
 函数名：setResTTTConf
 描述：232配置应答
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResTTTConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*数据补录 无请求*/

/*
 函数名：setResDataMakeUp
 描述：数据补录 无请求(此处建议以流的方式处理)
 参数：
    _HandlePtr ptr,
        _UInt32 devIdH,       设备编号 高位4字节
        _UInt32 devIdL,        设备编号 低位4字节
        _UInt8  dType,
        _UInt32 pTime,
        _UInt32 *buf1,
        _UInt32 buf1Len,      指buf1中整数的个数
        _UFloat *buf2,
        _UInt32 buf2Len,      指buf2中整数的个数
        _UFloat *buf3 ,
        _UInt32 buf3Len       指buf3中整数的个数
 返回值： 0 失败 1 成功
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
/*传感器配置自动上报*/

/*
 函数名：setReqSensorAutoReport
 描述：传感器配置自动上报请求
 参数：
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
 返回值： 0 失败 1 成功
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
 函数名：setResSensorAutoReport
 描述：传感器配置自动上报应答
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt8  chId,
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResSensorAutoReport(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt8  result
        );
/*获取报警设置*/

/*
 函数名：setReqGetWarnPlace
 描述：获取报警设置请求
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt8  wType,
    _UInt8  chId
 返回值： 0 失败 1 成功
*/
_UBool setReqGetWarnPlace(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wType,
        _UInt8  chId
        );

/*
 函数名：setResGetWarnPlace
 描述：获取报警设置应答
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
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
 返回值： 0 失败 1 成功
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
/*修改报警设置*/

/*
 函数名：setReqModWarnPlace
 描述：修改报警设置请求
 参数：
    _UInt32 devIdH,   设备编号 高位4字节
    _UInt32 devIdL,   设备编号 低位4字节
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
 返回值： 0 失败 1 成功
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
 函数名：setResModWarnPlace
 描述：修改报警设置应答
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResModWarnPlace(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*报警清除*/

/*
 函数名：setReqWarnClear
 描述：报警清除请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  wType,
    _UInt8  chId
 返回值： 0 失败 1 成功
*/
_UBool setReqWarnClear(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wType,
        _UInt8  chId
        );

/*
 函数名：setResWarnClear
 描述：报警清除应答
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResWarnClear(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*获取报警预约*/

/*
 函数名：setReqGetWarnOrder
 描述：获取报警预约请求
 参数：
    _UInt32 devIdH,       设备编号 高位4字节
    _UInt32 devIdL,       设备编号 低位4字节
    _UInt8  wType,
    _UInt8  chId
 返回值： 0 失败 1 成功
*/
_UBool setReqGetWarnOrder(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wType,
        _UInt8  chId
        );

/*
 函数名：setResGetWarnOrder
 描述：获取报警预约应答
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt8  wType,
    _UInt8  chId,
    _UInt32 sTime,
    _UInt32 eTime
 返回值： 0 失败 1 成功
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
/*修改报警预约*/

/*
 函数名：setReqModWarnOrder
 描述：修改报警预约请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  wType,
    _UInt8  chId,
    _UInt32 sTime,
    _UInt32 eTime
 返回值： 0 失败 1 成功
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
 函数名：setResModWarnOrder
 描述：修改报警预约应答
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt8 chId
 返回值： 0 失败 1 成功
*/
_UBool setResModWarnOrder(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8 chId
        );
/*普通报警*/

/*
 函数名：setReqGeneralWarn
 描述：普通报警请求
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt8  wType,
    _UInt8  chId,
    _UInt8  *wContent
 返回值： 0 失败 1 成功
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
 函数名：setResGeneralWarn
 描述：普通报警应答
 参数：
     _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResGeneralWarn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*数据报警*/

/*
 函数名：setReqDataWarn
 描述：数据报警请求
 参数：
    _UInt32 devIdH,   设备编号 高位4字节
    _UInt32 devIdL,   设备编号 低位4字节
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
 返回值： 0 失败 1 成功
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
 函数名：setResDataWarn
 描述：数据报警应答
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResDataWarn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*获取设备网络状态*/

/*
 函数名：setReqGetNetState
 描述：获取设备网络状态请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL   设备编号 低位4字节
 返回值： 0 失败 1 成功
*/
_UBool setReqGetNetState(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        );

/*
 函数名：setResGetNetState
 描述：获取设备网络状态应答
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  netType,
    _UInt32 ip,      此处将ip、dns、mask等用_UInt32 表示的方法有待商议
    _UInt32 dns,
    _UInt32 mask,
    _UInt32 gateway,
    _UInt8  *mac,
    _UInt32 macLen,
    _UInt8  dhcp
 返回值： 0 失败 1 成功
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
/*设置设备网络状态*/

/*
 函数名：setReqSetNetState
 描述：设置设备网络状态请求
 参数：
    _UInt32 devIdH,   设备编号 高位4字节
    _UInt32 devIdL,   设备编号 低位4字节
    _UInt8  netType,
    _UInt32 ip,
    _UInt32 dns,
    _UInt32 mask,
    _UInt32 gateway,
    _UInt8  *mac,
    _UInt8  dhcp
 返回值： 0 失败 1 成功
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
 函数名：setResSetNetState
 描述：设置设备网络状态应答
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResSetNetState(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*3G 获取网络状态*/

/*
 函数名：setReqGetNetState3G
 描述：3G 获取网络状态请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  nType,
    _UInt8  cType
 返回值： 0 失败 1 成功
*/
_UBool setReqGetNetState3G(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  nType,
        _UInt8  cType
        );

/*
 函数名：setResGetNetState3G
 描述：3G 获取网络状态应答
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  *name,
    _UInt8  *passwd,
    _UInt8  apn
 返回值： 0 失败 1 成功
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
/*远程桌面通信*/

/*
 函数名：setReqRemoteDisktop
 描述：远程桌面通信请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL   设备编号 低位4字节
 返回值： 0 失败 1 成功
*/
_UBool setReqRemoteDisktop(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        );

/*
 函数名：setResRemoteDistop
 描述：远程桌面通信应答
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL  设备编号 低位4字节
 返回值： 0 失败 1 成功
*/
_UBool setResRemoteDistop(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        );
/*获取设备用户 此处设置不完全*/

/*
 函数名：setReqGetDevUser
 描述：获取设备用户请求 (
    HandlePtr ptr,此处设置不完全)
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL   设备编号 低位4字节
 返回值： 0 失败 1 成功
*/
_UBool setReqGetDevUser(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        );

/*
 函数名：setResGetDevUser
 描述：获取设备用户应答
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  *uName,
    _UInt16 power
 返回值： 0 失败 1 成功
*/
_UBool setResGetDevUser(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  *uName,
        _UInt32 nameLen,
        _UInt16 power
        );
/*修改设备用户*/

/*
 函数名：setReqModDevUser
 描述：修改设备用户请求
 参数：
    _UInt32 devIdH,      设备编号 高位4字节
    _UInt32 devIdL,      设备编号 低位4字节
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
 返回值： 0 失败 1 成功
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
 函数名：setResModDevUser
 描述：修改设备用户应答
 参数：
    _UInt32 devIdH,   设备编号 高位4字节
    _UInt32 devIdL,   设备编号 低位4字节
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResModDevUser(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*设置时间*/

/*
 函数名：setReqSetTime
 描述：设置时间请求
 参数：
     _UInt32 devIdH,   设备编号 高位4字节
    _UInt32 devIdL     设备编号 低位4字节
 返回值： 0 失败 1 成功
*/
_UBool setReqSetTime(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        );

/*
 函数名：setResSetTime
 描述：设置时间应答
 参数：
    _UInt32 devIdH,   设备编号 高位4字节
    _UInt32 devIdL,   设备编号 低位4字节
    _UInt32 time
 返回值： 0 失败 1 成功
*/
_UBool setResSetTime(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt32 time
        );
/*云台设置*/

/*
 函数名：setReqYunTaiSet
 描述：云台设置请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  chId,
    _UInt8  command,
    _UInt8  rate
 返回值： 0 失败 1 成功
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
 函数名：setResYunTaiSet
 描述：云台设置应答
 参数：
     _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,   设备编号 低位4字节
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResYunTaiSet(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*获取云台*/

/*
 函数名：setReqGetYunTaiInfo
 描述：获取云台请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  chId
 返回值： 0 失败 1 成功
*/
_UBool setReqGetYunTaiInfo(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId
        );

/*
 函数名：setResGetYunTaiInfo
 描述：获取云台应答
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt8  chId,
    _UInt32 baud,
    _UInt32 addr,
    _UInt8  pType
 返回值： 0 失败 1 成功
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
/*控制云台*/

/*
 函数名：setReqControlYunTai
 描述：控制云台请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  chId,
    _UInt8  command,
    _UInt8  rate
 返回值： 0 失败 1 成功
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
 函数名：setResControlYunTai
 描述：控制云台应答
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  chId,
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResControlYunTai(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt8  result
        );
/*获取预置点*/

/*
 函数名：setReqGetPreset
 描述：获取预置点请求
 参数：
    _UInt32 devIdH,   设备编号 高位4字节
    _UInt32 devIdL,   设备编号 低位4字节
    _UInt8  chId
 返回值： 0 失败 1 成功
*/
_UBool setReqGetPreset(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId
        );

/*
 函数名：setResGetPreset
 描述：获取预置点应答
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  chId,
    _UInt16 *proset
 返回值： 0 失败 1 成功
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
 函数名：setReqModPreset
 描述：修改预置点请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  chId,
    _UInt8  cType,
    _UInt16 point
 返回值： 0 失败 1 成功
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
 函数名：setResModPreset
 描述：修改预置点应答
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  chId,
    _UInt8  result
 返回值： 0 失败 1 成功
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
 函数名：setReqGetCruiseConf
 描述：获取巡航配置请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  chId
 返回值： 0 失败 1 成功
*/
_UBool setReqGetCruiseConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId
        );

/*
 函数名：setResGetCruiseConf
 描述：获取巡航配置应答
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  chId,
    _UInt16 *list
 返回值： 0 失败 1 成功
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
 函数名：setReqModCruiseConf
 描述：修改巡航配置请求
 参数：
    UInt32 devIdH,   设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  chId,
    _UInt16 *list
 返回值： 0 失败 1 成功
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
 函数名：setResModCruiseConf
 描述：修改巡航配置应答
 参数：
    _UInt32 devIdH,   设备编号 高位4字节
    _UInt32 devIdL,   设备编号 低位4字节
    _UInt8  chId,
    _UInt8  result
 返回值： 0 失败 1 成功
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
 函数名：setReqGetEmailConf
 描述：获取邮箱配置请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL   设备编号 低位4字节
 返回值： 0 失败 1 成功
*/
_UBool setReqGetEmailConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        );

/*
 函数名：setResGetEmailConf
 描述：获取邮箱配置应答
 参数：
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
 返回值： 0 失败 1 成功
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
 函数名：setReqModEmailConf
 描述：修改邮箱配置请求
 参数：
    _UInt32 devIdH,   设备编号 高位4字节
  _UInt32 devIdL,     设备编号 低位4字节
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
 返回值： 0 失败 1 成功
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
 函数名：setResModEmailConf
 描述：修改邮箱配置应答
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8 chId,
    _UInt8 result
 返回值： 0 失败 1 成功
*/
_UBool setResModEmailConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8 chId,
        _UInt8 result
        );
/*测试邮箱配置*/

/*
 函数名：setReqTestEmailConf
 描述：测试邮箱配置请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL   设备编号 低位4字节
 返回值： 0 失败 1 成功
*/
_UBool setReqTestEmailConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL
        );

/*
 函数名：setResTestEmailConf
 描述：测试邮箱配置应答
 参数：
    _UInt32 devIdH,   设备编号 高位4字节
    _UInt32 devIdL,   设备编号 低位4字节
    _UInt8 result
 返回值： 0 失败 1 成功
*/
_UBool setResTestEmailConf(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8 result
        );
/*遥控开关设置*/

/*
 函数名：setReqRemoteControlSet
 描述：遥控开关设置请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8 wSwitch
 返回值： 0 失败 1 成功
*/
_UBool setReqRemoteControlSet(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8 wSwitch
        );

/*
 函数名：setResRemoteControlSet
 描述：遥控开关设置应答
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResRemoteControlSet(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/**/

/*
 函数名：setReqRemoteControlGet
 描述：遥控开关状态获取请求
 参数：
    _UInt32 devIdH,   设备编号 高位4字节
    _UInt32 devIdL,   设备编号 低位4字节
    _UInt8  wSwitch
 返回值： 0 失败 1 成功
*/
_UBool setReqRemoteControlGet(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wSwitch
        );

/*
 函数名：setResRemoteControlGet
 描述：遥控开关状态获取应答
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  sState
 返回值： 0 失败 1 成功
*/
_UBool setResRemoteControlGet(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  sState
        );
/**/

/*
 函数名：setReqSetHardDiskParm
 描述：设置硬盘参数请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
   _UInt8   hdSize
 返回值： 0 失败 1 成功
*/
_UBool setReqSetHardDiskParm(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8   hdSize
        );

/*
 函数名：setResSetHardDiskParm
 描述：设置硬盘参数应答
 参数：
    _UInt32 devIdH,   设备编号 高位4字节
    _UInt32 devIdL,   设备编号 低位4字节
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResSetHardDiskParm(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*格式化*/

/*
 函数名：setReqFormat
 描述：格式化请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  operation
 返回值： 0 失败 1 成功
*/
_UBool setReqFormat(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  operation
        );

/*
 函数名：setResFormat
 描述：格式化应答
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResFormat(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/**/

/*
 函数名：setReqVideoFull
 描述：录像满请求
 参数：
     _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,   设备编号 低位4字节
    _UInt8  vFull
 返回值： 0 失败 1 成功
*/
_UBool setReqVideoFull(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  vFull
        );

/*
 函数名：setResVideoFull
 描述：录像满应答
 参数：
    _UInt32 devIdH,    设备编号 高位4字节
    _UInt32 devIdL,    设备编号 低位4字节
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResVideoFull(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/**/

/*
 函数名：setReqTalk
 描述：对讲请求
 参数：
    _UInt16 rPort,
    _UInt8  code
 返回值： 0 失败 1 成功
*/
_UBool setReqTalk(
        HandlePtr ptr,
        _UInt16 rPort,
        _UInt8  code
        );

/*
 函数名：setResTalk
 描述：对讲应答
 参数：
     _UInt8 result
 返回值： 0 失败 1 成功
*/
_UBool setResTalk(
        HandlePtr ptr,
        _UInt8 result
        );
/**/

/*
 函数名：setReqAudioDownload
 描述：音频下载请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  chId,
    _UInt32 sTime,
    _UInt32 eTime,
    _UInt8  *fName
 返回值： 0 失败 1 成功
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
 函数名：setResAudioDownload
 描述：音频下载应答
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  chId,
    _UInt32 sTime,
    _UInt32 eTime,
    _UInt8  *path,
    _UInt8  *fName
 返回值： 0 失败 1 成功
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
 函数名：setReqVideoDownload
 描述：视频下载请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  chId,
    _UInt32 sTime,
    _UInt32 eTime,
    _UInt8  *fName
 返回值： 0 失败 1 成功
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
 函数名：setResVideoDownload
 描述：视频下载应答
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt8  chId,
    _UInt32 sTime,
    _UInt32 eTime,
    _UInt8  *path,
    _UInt8  *fName
 返回值： 0 失败 1 成功
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
/*刷图*/

/*
 函数名：setReqRefresh
 描述：刷图请求
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt8  chId
 返回值： 0 失败 1 成功
*/
_UBool setReqRefresh(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId
        );

/*
 函数名：setResRefresh
 描述：刷图应答
 参数：
     _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResRefresh(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/*视频播放操作*/

/*
 函数名：setReqVideoPlay
 描述：视频播放操作请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  chId,
    _UInt32 stream,
    _UInt32 time,
    _UInt16 port,
    _UInt8  oType,
    _UInt8  extend
 返回值： 0 失败 1 成功
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
 函数名：setResVideoPlay
 描述：视频播放操作应答
 参数：
    _UInt32 devIdH,    设备编号 高位4字节
    _UInt32 devIdL,    设备编号 低位4字节
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResVideoPlay(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/**/

/*
 函数名：setReqGetVideoParms
 描述：获取视频参数请求
 参数：
    _UInt32 devIdH,   设备编号 高位4字节
    _UInt32 devIdL,   设备编号 低位4字节
    _UInt8  chId,
    _UInt16 stream
 返回值： 0 失败 1 成功
*/
_UBool setReqGetVideoParms(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  chId,
        _UInt16 stream
        );

/*
 函数名：setResGetVideoParms
 描述：获取视频参数应答
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt8  chId,
    _UInt16 stream,
    _UInt16 width,
    _UInt16 height,
    _UInt16 sRate,
    _UInt16 fRate
 返回值： 0 失败 1 成功
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
 函数名：setReqSetVideoParms
 描述：设置视频参数请求
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt8  chId,
    _UInt16 stream,
    _UInt16 width,
    _UInt16 height,
    _UInt16 sRate,
    _UInt16 fRate
 返回值： 0 失败 1 成功
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
 函数名：setResSetVideoParms
 描述：设置视频参数应答
 参数：
    _UInt32 devIdH,    设备编号 高位4字节
    _UInt32 devIdL,    设备编号 低位4字节
    _UInt8  chId,
    _UInt16 stream,
    _UInt8  type
 返回值： 0 失败 1 成功
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
 函数名：setReqVideoOpen
 描述：视频打开操作请求
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt8  operation,
    _UInt8  chId,
    _UInt16 port
 返回值： 0 失败 1 成功
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
 函数名：setResVideoOpen
 描述：视频打开操作应答
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  chId,
    _UInt16 stream
 返回值： 0 失败 1 成功
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
 函数名：setReqDevRemoteRestart
 描述：设备远程重启请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  rRestart
 返回值： 0 失败 1 成功
*/
_UBool setReqDevRemoteRestart(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  rRestart
        );

/*
 函数名：setResDevRemoteRestart
 描述：设备远程重启应答
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResDevRemoteRestart(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );
/**/

/*
 函数名：setReqDevUpgrade
 描述：设备升级请求
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  *fContent
 返回值： 0 失败 1 成功
*/
_UBool setReqDevUpgrade(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  *fContent,/*此处为文件内容，每次1KB数据，如不能数据量不足1KB仍按1KB发送，在最后一字节数据后加'\0'*/
        _UInt32 contentLen
        );

/*
 函数名：setResDevUpgrade
 描述：设备升级应答
 参数：
    _UInt32 devIdH,  设备编号 高位4字节
    _UInt32 devIdL,  设备编号 低位4字节
    _UInt8  *fName
 返回值： 0 失败 1 成功
*/
_UBool setResDevUpgrade(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  *fName,
        _UInt32 nameLen
        );
/**/
///////////////////////////////////// 具体命令结构/////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*无效命令*/
/*协议版本查询*/
STRUCT
{
    _UInt32 devIdH; /*设备编号 分高位4字节 低位4字节*/
    _UInt32 devIdL;
    _UInt32 proVer; /*协议版本号*/
}ReqVersion;

STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt32 proVer;
}ResVersion;
/*心跳*/ /*设备心跳无响应*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt32 cumulative;
}ReqDLive;
/*设备检索*/
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
STRUCT
{
    _UInt8 data[1*1024];
}ResData;
/*视频发送*/
STRUCT
{
    _UInt8 vData[100*1024];
}ResVideoData;
/*获取历史数据*/
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
/*用户登录*/
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
/*云台*/
/////////////////
/*设备上线*/
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
/*设备下线*/
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
/*获取传感器配置*/
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
/*修改传感器配置*/
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
/*历史数据上报时间间隔*/
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
/*485配置*/
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
/*232配置*/
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

/*数据补录 无请求*/     //数据补录也修改为固定字长
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  dType;
    _UInt32 pTime;
    _UInt8  sw;
    _UInt32 buf1[8]; //此处不一定为8个，数量0-8
    _UInt32 TTTNum;
    _UFloat buf2[128]; /*大小等于 TTTNum *4 */
    _UInt32 len;
    _UFloat buf3[128]; /*长度不确定*/
}ResDataMakeUp;
/*传感器配置自动上报*/
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
/*获取报警设置*/
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
/*修改报警设置*/
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
/*报警清除*/
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
/*获取报警预约*/
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
/*修改报警预约*/
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
/*普通报警*/
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
/*数据报警*/
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
/*获取设备网络状态*/
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
/*设置设备网络状态*/
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
/*3G 获取网络状态*/
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
/*远程桌面通信*/
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
/*获取设备用户 此处设置不完全*/
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
/*修改设备用户*/
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
/*设置时间*/
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
/*云台设置*/
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
/*获取云台*/
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
/*控制云台*/
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
/*获取预置点*/
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
/*修改预置点*/
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
/*获取巡航配置*/
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
/*修改巡航配置*/
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
/*获取邮箱配置*/
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
/*修改邮箱配置*/
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
/*测试邮箱配置*/
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
/*遥控开关设置*/
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
/*遥控开关状态获取*/
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
/*设置硬盘参数*/
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
/*格式化*/
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
/*录像满*/
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
/*对讲*/
STRUCT
{
    _UInt16 rPort;
    _UInt8  code;
}ReqTalk;
STRUCT
{
    _UInt8 result;
}ResTalk;
/*音频下载*/
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
/*视频下载*/
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
/*刷图*/
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
/*视频播放操作*/
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
/*获取视频参数*/
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
/*设置视频参数*/
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
/*视频打开操作*/
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
/*设备远程重启*/
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
/*设备升级*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  fContent[1024]; /*此处为文件内容，每次1KB数据，如不能数据量不足1KB仍按1KB发送，在最后一字节数据后加'\0'*/
}ReqDevUpgrade;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  fName[256];
}ResDevUpgrade;

#endif
