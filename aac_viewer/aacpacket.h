/**
  adts aac packet
*/
#ifndef AACPACKET_H
#define AACPACKET_H

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

class AACPacket
{
public:
  AACPacket();
  virtual ~AACPacket();
public:
  std::string get_syncword();
  std::string get_id();
  std::string get_layer();
  std::string get_protection_absent();
  std::string get_profile();
  std::string get_sampling_frequency_index();
  std::string get_private_bit();
  std::string get_channel_configuration();
  std::string get_original_copy();
  std::string get_home();

  std::string get_copyright_identification_bit();
  std::string get_copyright_identification_start();
  std::string get_aac_frame_length();
  std::string get_adts_buffer_fullness();
  std::string get_number_of_raw_data_blocks_in_frame();

  void set_syncword(std::string par_syncword);
  void set_id(int par_id);
  void set_layer(int par_layer);
  void set_protection_absent(int par_protection_absent);
  void set_profile(int par_profile);
  void set_sampling_frequency_index(int par_sampling_frequency_index);
  void set_private_bit(int par_private_bit);
  void set_channel_configuration(int par_channel_configuration);
  void set_original_copy(int par_original_copy);
  void set_home(int par_home);

  void set_copyright_identification_bit(int par_copyright_identification_bit);
  void set_copyright_identification_start(int par_copyright_identification_start);
  void set_aac_frame_length(int par_aac_frame_length);
  void set_adts_buffer_fullness(int par_adts_buffer_fullness);
  void set_number_of_raw_data_blocks_in_frame(int par_number_of_raw_data_blocks_in_frame);


  void copy_aac_data_2_cache(char *inBuf,int inLen);

private:
  /// ADTS 固定头
  std::string syncword; /// 同步字0xfff，说明一个ADTS帧的开始
  std::string id; /// ID比较奇怪,标准文档中是这么说的”MPEG identifier, set to ‘1’. See ISO/IEC 11172-3″,但我写0了,也可以
  std::string layer; /// 一般设置为0
  std::string protection_absent; /// 是否误码校验
  std::string profile; /// 表示使用哪个级别的AAC，如01 Low Complexity(LC)--- AACLC
  std::string sampling_frequency_index; /// 表示使用的采样率下标0x3 48k ,0x4 44.1k, 0x5 32k
  std::string private_bit; /// 一般设置为0
  std::string channel_configuration; /// 表示声道数
  std::string original_copy; /// 一般设置为0
  std::string home; /// 一般设置为0

  /// ADTS 可变头
  std::string copyright_identification_bit; /// 一般设置为0
  std::string copyright_identification_start; /// 一般设置为0
  std::string aac_frame_length; /// 一个ADTS帧的长度包括ADTS头和raw data block
  std::string adts_buffer_fullness; /// 0x7FF 说明是码率可变的码流
  std::string number_of_raw_data_blocks_in_frame; /// 表示ADTS帧中有number_of_raw_data_blocks_in_frame + 1个AAC原始帧.

  char *data; /// AAC 数据
  int data_len; /// AAC 数据长度
};

#endif // AACPACKET_H
