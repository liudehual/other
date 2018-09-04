#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "deviceInterface.h"
#include "clientInterface.h"
#include "serverInterface.h"
void test(int mainCommand,int minorCommand,int reqOrRes,void *content,int len)
{

}
int main(void)
{
	Handle p;

	_UInt32 a[5]={1,2,3,4,5};
	_UInt32 b[5]={1,2,3,4,5};
	_UInt32 c[5]={1,2,3,4,5};
	//setResDataMakeUp(&p,123,123,1,123,5,a,5,b,5,c);

  //注册并初始化一些必要信息 必须
  if(!registerHandle(&p,1,1,16,21,test))return 0; 

  /*添加具体命令*/
  //setResAddDev(&p,123,456,(_UInt8)1);
  //setReqVersion(&p,234,678,100);
  //setReqServerHandOutWarn(&p,1234,8765,16,32,"this is Test",strlen("this is Test"));
  setReqFindDev(&p,123,345);

  /*重置缓冲区 每一次处理或者发送数据后需调用该函数*/
  resetBuffer(&p,eResetSendBuffer,10000);
  
  /*移除句柄 必须*/
  removeHandle(&p);
#if 0
  fprintf(stderr,"%s\n","end");
#endif

  getchar();
  return 0;
}

