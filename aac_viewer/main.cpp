#include <iostream>
#include "aacparser.h"

using namespace std;
long long filesize(FILE *fp)
{
  fseek(fp, SEEK_SET, 0);
  fseek(fp, 0L, SEEK_END);
  int length=ftell(fp);
  fseek(fp, SEEK_SET, 0);
  return length;
}
int main(int argc,char *argv[])
{
  FILE *fp=NULL;
  fp=fopen("ny.aac","rb");
  int size=filesize(fp);
  char *buf=new char[size];

  int nread;

  if ((nread = fread(buf,size,sizeof(char),fp)) < 0) {
      return 0;
    }


  fprintf(stderr,"%02X %02X \n",(unsigned char)buf[0],(unsigned char)buf[1]);
  AACParser parser;
  int outLen=0;
  parser.parse_aac_data(buf,size,outLen);
  int map_size=parser.getPacketNumbers();
  fprintf(stderr,"map size %d \n",map_size);
  AACPacket * theLastPacket=parser.getPacketByIndex(map_size-1);
  if(theLastPacket){
      fprintf(stderr," frame len %s \n",theLastPacket->get_aac_frame_length().c_str());
    }
  theLastPacket=parser.getPacketByIndex(map_size-2);
  if(theLastPacket){
      fprintf(stderr," frame len %s \n",theLastPacket->get_aac_frame_length().c_str());
    }


  std::cout<<theLastPacket->get_channel_configuration()<<std::endl;
  getchar();
  return 0;
}
