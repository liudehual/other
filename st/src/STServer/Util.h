#ifndef __UTIL_H__
#define __UTIL_H__
#include "OS.h"
unsigned int  _our_random32();

UInt32 ConvertStringToAddr(const char* inAddrStr);
void UInt32ToStringIp(unsigned int theIntIp,char *theStrIp);
char checkSum(unsigned char *buf,int len);

#endif
