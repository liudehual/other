#ifndef __PROFILE_PARSER_H__
#define __PROFILE_PARSER_H__
#include "Object.h"
#include <vector>


/* 
	配置文件
	具有自动导出默认配置功能
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
