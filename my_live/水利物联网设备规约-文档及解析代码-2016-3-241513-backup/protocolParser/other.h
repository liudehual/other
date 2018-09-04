#ifndef _OTHER_H_
#define _OTHER_H_

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


/*�û���¼*/
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
    /*����֡ͷ*/
    /*_UInt8 **/pos=currentPos;
    //δʹ��
    //setHeader(pos,len,0x00,user_login,0x00,0x00);
    /*�����û�����*/
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
    /*����֡ͷ*/
    /*_UInt8 **/pos=currentPos;
    //δʹ��
    //setHeader(pos,len,0x00,user_login,0x00,0x01);
    /*�����û�����*/
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
/*�������ַ�����*/


/*
 ��������setReqServerHandOutWarn
 �������������ַ���������
 ������
    HandlePtr ptr,
    _UInt32 devIdH,
    _UInt32 devIdL,
    _UInt8  wType,
    _UInt8  chId,
    _UInt8  *wMessage,
    _UInt32 messageLen
 ����ֵ�� 0 ʧ�� 1 �ɹ�
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
 ��������setResServerHandOutWarn
 �������������ַ�����Ӧ��
 ������
    UInt32 devIdH, �豸��� ��λ4�ֽ�
   _UInt32 devIdL, �豸��� ��λ4�ֽ�
   _UInt8  result
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResServerHandOutWarn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );

/**/


/*
 ��������setReqServerThrowWarn
 �������������׳��洢��������
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt8  wType,
    _UInt8  chId,
    _UInt8  *wMessage
 ����ֵ�� 0 ʧ�� 1 �ɹ�
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
 ��������setResServerThrowWarn
 �������������׳��洢����Ӧ��
 ������
    _UInt32 devIdH, �豸��� ��λ4�ֽ�
    _UInt32 devIdL, �豸��� ��λ4�ֽ�
    _UInt8  result  ִ�н��
 ����ֵ�� 0 ʧ�� 1 �ɹ�
*/
_UBool setResServerThrowWarn(
        HandlePtr ptr,
        _UInt32 devIdH,
        _UInt32 devIdL,
        _UInt8  result
        );

/*�������ַ�����*/
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

/*�������׳��洢����*/
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

/*�������ַ�����*/
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
    /*����֡ͷ*/
    /*_UInt8 **/pos=currentPos;
    //δʹ��
        //setHeader(pos,len,0x00,warn,server_send_warn,0x00);

    /*�����û�����*/
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
    /*����֡ͷ*/
    /*_UInt8 **/pos=currentPos;
    //δʹ��
    //setHeader(pos,len,0x00,warn,server_send_warn,0x01);


    /*�����û�����*/
    //pos+=FRAME_HEAD_FIXED_FILED;
    ow.devIdH=devIdH;  ow.devIdL=devIdL;
    ow.result=result;
    //addDataToBuf((_SInt8 *)pos,(_SInt8 *)&ow,len);

    packagingData(pos,NULL,len,0,ptr->station,0,FRAME_FIXED_FIELD);
		//setEnd(pos,len+FRAME_TAIL_FIXED_FILED);
    return True;
}
/*�������׳��洢����*/
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

    /*����֡ͷ*/
    /*_UInt8 **/pos=currentPos;
    //δʹ��
    //setHeader(pos,len,0x00,warn,server_throw_mem_warn,0x00);

    /*�����û�����*/
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
    /*����֡ͷ*/
    /*_UInt8 **/pos=currentPos;
    //δʹ��
    //setHeader(pos,len,0x00,warn,server_throw_mem_warn,0x01);

    /*�����û�����*/
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