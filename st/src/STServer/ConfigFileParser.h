#ifndef __PROFILE_PARSER_H__
#define __PROFILE_PARSER_H__
#include "Object.h"
#include <vector>


/* 
	�����ļ�
	�����Զ�����Ĭ�����ù���
*/
class ConfigFileParser:public Object
{
	public:
		ConfigFileParser(void *r,void *p);
		~ConfigFileParser();
		virtual int parserConfigfile(char *fileName);
		virtual int exportDefaultProfile();
	private:
		
};

#endif
