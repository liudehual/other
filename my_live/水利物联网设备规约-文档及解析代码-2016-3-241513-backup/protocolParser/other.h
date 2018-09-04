#ifndef _OTHER_H_
#define _OTHER_H_

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


/*用户登录*/
_UBool setReqUserLogin(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  *name,
        _UInt32 nameLen,
        _UInt8  *passwd,
        _UInt32 passwdLen
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqUserLogin login;
    if(ptr==NULL || name==NULL || passwd ==NULL)return False;
    if(nameLen>sizeof(login.name)) return False;
    if(passwdLen>sizeof(login.passwd))return False;
    /*_UInt32 */len=sizeof(ReqUserLogin);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
    //setHeader(pos,len,0x00,user_login,0x00,0x00);
    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    login.devIdH=devIdH;  login.devIdL=devIdL;
    memcpy(login.name,name,nameLen);
    memcpy(login.passwd,passwd,passwdLen);
    //addDataToBuf(pos,(_SInt8 *)&login,len);
    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResUserLogin(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResUserLogin login;
    if(ptr==NULL)return False;
    /*_UInt32 */len=sizeof(ResUserLogin);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL)return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
    //setHeader(pos,len,0x00,user_login,0x00,0x01);
    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    login.devIdH=devIdH;  login.devIdL=devIdL;
    login.result=result;
    //addDataToBuf(pos,(_SInt8 *)&login,len);
    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*服务器分发报警*/


/*
 函数名：setReqServerHandOutWarn
 描述：服务器分发报警请求
 参数：
    HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt8  wType,
    _UInt8  chId,
    _UInt8  *wMessage,
    _UInt32 messageLen
 返回值： 0 失败 1 成功
*/
_UBool setReqServerHandOutWarn(
    HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt8  wType,
    _UInt8  chId,
    _UInt8  *wMessage,
    _UInt32 messageLen
        );


/*
 函数名：setResServerHandOutWarn
 描述：服务器分发报警应答
 参数：
    UInt32 devIdH, 设备编号 高位4字节
   _UInt32 devIdL, 设备编号 低位4字节
   _UInt8  result
 返回值： 0 失败 1 成功
*/
_UBool setResServerHandOutWarn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );

/**/


/*
 函数名：setReqServerThrowWarn
 描述：服务器抛出存储报警请求
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt8  wType,
    _UInt8  chId,
    _UInt8  *wMessage
 返回值： 0 失败 1 成功
*/
_UBool setReqServerThrowWarn(
         HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt8  wType,
    _UInt8  chId,
    _UInt8  *wMessage,
    _UInt32 messageLen
        );

        
/*
 函数名：setResServerThrowWarn
 描述：服务器抛出存储报警应答
 参数：
    _UInt32 devIdH, 设备编号 高位4字节
    _UInt32 devIdL, 设备编号 低位4字节
    _UInt8  result  执行结果
 返回值： 0 失败 1 成功
*/
_UBool setResServerThrowWarn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );

/*服务器分发报警*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  wType;
    _UInt8  chId;
    _UInt8  wMessage[10000];
}ReqServerHandOutWarn;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResServerHandOutWarn;

/*服务器抛出存储报警*/
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  wType;
    _UInt8  chId;
    _UInt8  wMessage[5*1024];
}ReqServerThrowWarn;
STRUCT
{
    _UInt32 devIdH;
    _UInt32 devIdL;
    _UInt8  result;
}ResServerThrowWarn;

/*服务器分发报警*/
_UBool setReqServerHandOutWarn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wType,
        _UInt8  chId,
        _UInt8  *wMessage,
        _UInt32 messageLen
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqServerHandOutWarn oWarn;
    if(ptr==NULL || wMessage==NULL) return False;
    if(messageLen>sizeof(oWarn.wMessage)) return False;

    /*_UInt32 */len=sizeof(ReqServerHandOutWarn);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
        //setHeader(pos,len,0x00,warn,server_send_warn,0x00);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    oWarn.chId=chId;            oWarn.devIdH=devIdH;
    oWarn.devIdL=devIdL;
    memcpy(oWarn.wMessage,wMessage,messageLen);
    oWarn.wType=wType;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&oWarn,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResServerHandOutWarn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResServerHandOutWarn ow;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResServerHandOutWarn);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
    //setHeader(pos,len,0x00,warn,server_send_warn,0x01);


    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    ow.devIdH=devIdH;  ow.devIdL=devIdL;
    ow.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&ow,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*服务器抛出存储报警*/
_UBool setReqServerThrowWarn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  wType,
        _UInt8  chId,
        _UInt8  *wMessage,
        _UInt32 messageLen
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ReqServerThrowWarn tw;
    if(ptr==NULL || wMessage==NULL) return False;
    if(messageLen>sizeof(tw.wMessage)) return False;

    /*_UInt32 */len=sizeof(ReqServerThrowWarn);
    /*_UInt8 **/currentPos=preProcess(ptr,len);

    if(currentPos==NULL) return False;

    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
    //setHeader(pos,len,0x00,warn,server_throw_mem_warn,0x00);

    /*处理用户数据*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    tw.chId=chId;  tw.devIdH=devIdH;
    tw.devIdL=devIdL;
    memcpy(tw.wMessage,wMessage,messageLen);
    tw.wType=wType;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&tw,len);

    //setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
_UBool setResServerThrowWarn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        )
{
    _UInt32 len;
    _UInt8 *currentPos;
    _UInt8 *pos;
    ResServerThrowWarn tw;
    if(ptr==NULL) return False;
    /*_UInt32 */len=sizeof(ResServerThrowWarn);
    /*_UInt8 **/currentPos=preProcess(ptr,len);
    if(currentPos==NULL) return False;
    /*处理帧头*/
    /*_UInt8 **/pos=currentPos;
    //未使用
    //setHeader(pos,len,0x00,warn,server_throw_mem_warn,0x01);

    /*处理用户数据*/
    pos+=FRAME_HEAD_FIXED_FILED;
    tw.devIdH=devIdH;  tw.devIdL=devIdL;
    tw.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&tw,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif