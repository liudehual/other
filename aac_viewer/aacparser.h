#ifndef AACPARSER_H
#define AACPARSER_H
#include <map>
#include "aacpacket.h"

class AACParser
{
public:
  AACParser();
  virtual ~AACParser();
  int parse_aac_data(char *inBuf,int inLen,int &outLen);
  AACPacket *getPacketByIndex(int index);
  int getPacketNumbers();
  int addPacketToMap(int i,AACPacket *packet);
private:
  std::map<int,AACPacket *> fAACContainer;
  int fPacketId;

};

#endif // AACPARSER_H
