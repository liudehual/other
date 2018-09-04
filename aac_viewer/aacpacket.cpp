#include "aacpacket.h"

/// sampling_frequency_index 字段
static char * sample_freq[]=
{
  "9600","88200","64000","48000",
  "44100","32000","24000","22050",
  "16000","12000","11025","8000",
  "7350","Reserved","Reservec",
  "frequency is written explictly"
};

/// channel_configuration 字段
static char *channel_conf[]=
{
  "Defined in AOT Specifc Config","1","2","3",
  "4","5","6","7",
  "Reserved","Reserved","Reserved","Reserved",
  "Reserved","Reserved","Reserved","Reserved"
};

/// id 字段
static char *version_id[]=
{
  "MPEG-4",
  "MPEG-2"
};

AACPacket::AACPacket()
{

}

AACPacket::~AACPacket()
{

}

/// ADTS 固定头
std::string AACPacket::get_syncword()
{
  return syncword;
}

std::string AACPacket::get_id()
{
  return id;
}

std::string AACPacket::get_layer()
{
  return layer;
}

std::string AACPacket::get_protection_absent()
{
  return protection_absent;
}

std::string AACPacket::get_profile()
{
  return profile;
}

std::string AACPacket::get_sampling_frequency_index()
{
  return sampling_frequency_index;
}

std::string AACPacket::get_private_bit()
{
  return private_bit;
}

std::string AACPacket::get_channel_configuration()
{
  return channel_configuration;
}

std::string AACPacket::get_original_copy()
{
  return original_copy;
}

std::string AACPacket::get_home()
{
  return home;
}

std::string AACPacket::get_copyright_identification_bit()
{
  return copyright_identification_bit;
}

std::string AACPacket::get_copyright_identification_start()
{
  return copyright_identification_start;
}

std::string AACPacket::get_aac_frame_length()
{
  return aac_frame_length;
}

std::string AACPacket::get_adts_buffer_fullness()
{
  return adts_buffer_fullness;
}

std::string AACPacket::get_number_of_raw_data_blocks_in_frame()
{
  return number_of_raw_data_blocks_in_frame;
}

void AACPacket::set_syncword(std::string par_syncword)
{
  syncword=par_syncword;
}

void AACPacket::set_id(int par_id)
{
  std::stringstream ss;
  ss<<par_id;
  ss>>id;
}

void AACPacket::set_layer(int par_layer)
{
  std::stringstream ss;
  ss<<par_layer;
  ss>>layer;
}
void AACPacket::set_protection_absent(int par_protection_absent)
{
  std::stringstream ss;
  ss<<par_protection_absent;
  ss>>protection_absent;
}

void AACPacket::set_profile(int par_profile)
{
  std::stringstream ss;
  ss<<par_profile;
  ss>>profile;
}

void AACPacket::set_sampling_frequency_index(int par_sampling_frequency_index)
{
  std::stringstream ss;
  ss<<par_sampling_frequency_index;
  ss>>sampling_frequency_index;
}

void AACPacket::set_private_bit(int par_private_bit)
{
  std::stringstream ss;
  ss<<par_private_bit;
  ss>>private_bit;

}

void AACPacket::set_channel_configuration(int par_channel_configuration)
{
  std::stringstream ss;
  ss<<par_channel_configuration;
  ss>>channel_configuration;
}

void AACPacket::set_original_copy(int par_original_copy)
{
  std::stringstream ss;
  ss<<par_original_copy;
  ss>>original_copy;
}

void AACPacket::set_home(int par_home)
{
  std::stringstream ss;
  ss<<par_home;
  ss>>home;
}

void AACPacket::set_copyright_identification_bit(int par_copyright_identification_bit)
{
  std::stringstream ss;
  ss<<par_copyright_identification_bit;
  ss>>copyright_identification_bit;
}

void AACPacket::set_copyright_identification_start(int par_copyright_identification_start)
{
  std::stringstream ss;
  ss<<par_copyright_identification_start;
  ss>>copyright_identification_start;
}

void AACPacket::set_aac_frame_length(int par_aac_frame_length)
{
  std::stringstream ss;
  ss<<par_aac_frame_length;
  ss>>aac_frame_length;
}

void AACPacket::set_adts_buffer_fullness(int par_adts_buffer_fullness)
{
  std::stringstream ss;
  ss<<par_adts_buffer_fullness;
  ss>>adts_buffer_fullness;
}

void AACPacket::set_number_of_raw_data_blocks_in_frame(int par_number_of_raw_data_blocks_in_frame)
{
  std::stringstream ss;
  ss<<par_number_of_raw_data_blocks_in_frame;
  ss>>number_of_raw_data_blocks_in_frame;
}

void AACPacket::copy_aac_data_2_cache(char *inBuf,int inLen)
{
  if(inBuf==NULL || inLen<=0){
      return;
    }
  data=new char[inLen];
  memcpy(data,inBuf,inLen);
}
