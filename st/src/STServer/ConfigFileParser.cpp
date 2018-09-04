#include "ConfigFileParser.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

ConfigFileParser::ConfigFileParser(void *r,void *p):Object(r,p)
{

}
ConfigFileParser::~ConfigFileParser()
{

}
int ConfigFileParser::parserConfigfile(char *fileName)
{
	if(fileName==NULL 
		|| strlen(fileName)==0){
		exportDefaultProfile();
		return 0;
	}
	FILE *fp=fopen(fileName,"r");
	if(fp==NULL){
		fprintf(stderr,"open Config file error \n");
		return 0;
	}
	char *configBuffer=(char *)malloc(sizeof(char)*1024*2);
	size_t bufferLen=sizeof(char)*1024*2;
	ssize_t readLen=0;
	while((readLen=(ssize_t)getline(&configBuffer,&bufferLen,fp)) != EOF){
	
		if(configBuffer[0]=='#'){ /* ×¢ÊÍ */
			continue;
		}
		
	}
	/* Ä¬ÈÏ½âÎö */
}
int ConfigFileParser::exportDefaultProfile()
{
	
}