#include "aacparser.h"

static unsigned char syncword[]={0xFF,0xF0};

AACParser::AACParser():fPacketId(0)
{

}

AACParser::~AACParser()
{

}


int AACParser::parse_aac_data(char *inBuf,int inLen,int &outLen)
{
  unsigned char *pos=(unsigned char *)inBuf;
  unsigned char *end=(unsigned char *)&inBuf[inLen];


  while(1){
      if((unsigned char)pos[0]==syncword[0] && ((unsigned char)pos[1] & 0xF0)==syncword[1]){ /// 检查ADTS头(0xFFF)

          /// 解析ADTS头，共7字节长度
          int id=pos[1]>>3 & 0x01;
          int layer=pos[1]>>1 & 0x03;
          int protection_absent=pos[1] & 0x01;
          int profile=pos[2]>>6 & 0x03;
          int sampling_frequency_index=pos[2]>>2 & 0x0F;
          int private_bit=pos[2]>>1 & 0x01;
          int channel_configuration=(pos[2] & 0x01)<<2 | pos[3]>>6 & 0x03;
          int original_copy=pos[3]>>5 & 0x01;
          int home=pos[3]>>4 & 0x01;
          int copyright_identification_bit=pos[3]>>3 & 0x01;
          int copyright_identification_start=pos[3]>>2 & 0x01;
          int aac_frame_length=(int)((pos[3] & 0x03)<<13 | pos[4]<<3 | (pos[5]>>5) & 0x07);
          int adts_buffer_fullness=((unsigned short)(pos[5] & 0x1F))<<6 | ((unsigned short)(pos[6]>>2) & 0x7F);
          unsigned char number_of_raw_data_blocks_in_frame=(pos[6] & 0x03);

          fprintf(stderr,"aac frame len %d "
                         "id %u "
                         "profile %u "
                         "sampling_frequency_index %u "
                         "channel_configuration %u "
                         "adts_buffer_fullness %u \n",
                  aac_frame_length,
                  id,
                  profile,
                  sampling_frequency_index,
                  channel_configuration,
                  adts_buffer_fullness);

          AACPacket *thePacket=new AACPacket();
          thePacket->set_syncword(std::string((char *)syncword));
          thePacket->set_id(id);
          thePacket->set_layer(layer);
          thePacket->set_protection_absent(protection_absent);
          thePacket->set_profile(profile);
          thePacket->set_sampling_frequency_index(sampling_frequency_index);
          thePacket->set_private_bit(private_bit);
          thePacket->set_channel_configuration(channel_configuration);
          thePacket->set_original_copy(original_copy);
          thePacket->set_home(home);
          thePacket->set_copyright_identification_bit(copyright_identification_bit);
          thePacket->set_copyright_identification_start(copyright_identification_start);
          thePacket->set_aac_frame_length(aac_frame_length);
          thePacket->set_adts_buffer_fullness(adts_buffer_fullness);
          thePacket->set_number_of_raw_data_blocks_in_frame(number_of_raw_data_blocks_in_frame);

          thePacket->copy_aac_data_2_cache((char *)&pos[7],aac_frame_length-7);

          this->addPacketToMap(fPacketId++,thePacket);

          pos+=aac_frame_length;
          if(pos>=end){ /// 遍历完成或出错,跳出循环，终止查找
              break;
            }else{ /// 未完成，接着查找
              continue;
            }

        }else{ /// 不是标准格式，遍历查找
          pos++;
        }
    }
  return 1;
}

AACPacket *AACParser::getPacketByIndex(int index)
{
  if(fAACContainer.find(index)==fAACContainer.end()){
      return NULL;
    }
  return fAACContainer[index];
}
int AACParser::getPacketNumbers()
{
  return fAACContainer.size();
}
int AACParser::addPacketToMap(int i,AACPacket *packet)
{
  if(fAACContainer.find(i)!=fAACContainer.end()){
      return 0;
    }
  //  fAACContainer[i]=packet;
  fAACContainer.insert(std::make_pair(i,packet));
  return 1;
}
