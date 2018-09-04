#include "Util.h"
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
UInt32 ConvertStringToAddr(const char* inAddrStr)
{
    return ntohl(::inet_addr(inAddrStr));
}
void UInt32ToStringIp(unsigned int theIntIp,char *theStrIp)
{
	unsigned char* p = (unsigned char *)&theIntIp;
	sprintf(theStrIp, "%u.%u.%u.%u", p[3]&0xff,p[2]&0xff,p[1]&0xff,p[0]&0xff);
}
char checkSum(unsigned char *buf,int len)
{
	unsigned char sum=0;
	for(int i=0;i<len;i++){
		sum+=buf[i];
	}
	return sum;

}
long our_random() 
{
#if defined(__WIN32__) || defined(_WIN32)
  return rand();
#else
  return random();
#endif
}
unsigned int  _our_random32()
{
  // Return a 32-bit random number.
  // Because "our_random()" returns a 31-bit random number, we call it a second
  // time, to generate the high bit:
  long random1 = our_random();
  long random2 = our_random();
  return (unsigned int)((random2<<31) | random1);
}

