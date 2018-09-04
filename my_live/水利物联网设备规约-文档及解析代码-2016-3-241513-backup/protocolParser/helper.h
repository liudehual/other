#ifndef _HELPER_H_
#define _HELPER_H_
#include "global.h"
/*
	函数名: packagingHeader
	描述: 根据功能码组装协议头
	参数: 
	      buf 缓冲区指针
	      len 待发送用户数据长度
		  funCode 功能码
		  stationType 子站(设备端，客户端)或主站(服务端)
		  ReqOrRes 0 请求 1 应答
*/
void packagingData(_UInt8 *buf,void *userData,_UInt32 userDatalen,_UInt16 funCode,_UInt8 stationType,_UInt8 ReqOrRes,_UInt32 FrameFixLen);
void unpackagingData();

void packageingHeader(Frame *f, _UInt8  start1,   //帧开始
                                _UInt16   len,    //帧长度
                                _UInt8  start2,   //帧开始
                                _UInt8  res,      //res 备用
                                _UInt8  prm,      //prm
                                _UInt8  fcbAcd,   //FCB ACD
                                _UInt8  fcvDfc,   //FCD DFC
                                _UInt8  funCode,  //功能码
                                _UInt8  addr,     //地址域
                                _UInt8  type,     //类型标识
                                //可变限定词
                                _UInt8  sort,     //是否按顺序排放
                                _UInt8  eleNum,   //元素个数
                                //传输原因
                                _UInt8  t,        //实验 1 未实验 0
                                _UInt8  pn,       //否认确认 0 肯定确认 1 
                                _UInt8  other,    //其他 默认0
                                _UInt8  nUse,     //无用 
                                _UInt8  publicAddr, //公共地址
                                _UInt16  informosome ); // 信息体地址
                                /*
	函数名: packagingHeader
	描述: 根据功能码组装协议头
	参数: 
			buf			缓冲区指针
			uFunCode		功能码
			uDirection	传输方向(0, 表示是由终端向平台传输报文；1, 表示是由平台向终端传输报文)
			uInfoNum		信息元素个数
			uCause		传送原因
			uInfoAddr		信息体地址

*/
void SetInfo( _UInt8 *buf, void *userData, _UInt32 userDatalen, _UInt8 ReqOrRes, _UInt32 FrameFixLen, 
			  _UInt8 uFunCode, _UInt8 uDirection, _UInt8 uInfoNum, _UInt8 uCause, _UInt16 uInfoAddr);
#endif