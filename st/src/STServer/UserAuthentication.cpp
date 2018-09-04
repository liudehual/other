#include "UserAuthentication.h"
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Util.h"
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

UserAuthentication::UserAuthentication(void *r,void *p):Object(r,p)
{
	initDefaultAdminUser();

}
UserAuthentication::~UserAuthentication()
{

}
int UserAuthentication::userFileParser(char *fileName)
{

	if(fileName==NULL || strlen(fileName)==0){
		return -1;
	}
	FILE *fp=fopen(fileName,"r");
	if(fp==NULL){
		fprintf(stderr,"open user file error \n");
		return 0;
	}
	char *buffer=(char *)malloc(sizeof(char)*1024*2);
	size_t len=sizeof(char)*1024*2;
	ssize_t readLen;
	while((readLen=(ssize_t)getline(&buffer,&len,fp)) != EOF){
		
	}
	
	return 1;
}

char UserAuthentication::userLogin(char *userName,char *userPasswd)
{
	if(userName==NULL 
		|| strlen(userName)==0
		|| userPasswd==NULL
		|| strlen(userPasswd)==0){
		return -1;
	}
	OSMutexLocker theLocker(&fMutex);
	std::vector<UserInfo *>::iterator it;
	for(it=fUserVector.begin();it!=fUserVector.end();it++){
		/* 用户名不匹配*/
		if(strcmp(userName,(*it)->userName)!=0){
			continue;
		}
		/* 找到 */
		if(strcmp(userName,(*it)->userName)==0
			&& strcmp(userPasswd,(*it)->userPasswd)==0){
			(*it)->userLoginState=1;
			return 1;
		}
		/* 密码错误 */
		if(strcmp(userName,(*it)->userName)==0
			&& strcmp(userPasswd,(*it)->userPasswd)==0){
			return 3;
		}
	}
	/* 没找到，即用户未注册，返回零 */
	return 0;
}
char UserAuthentication::userLoginOut(unsigned userId)
{
	if(userId==0){
		return 1;
	}
	OSMutexLocker theLocker(&fMutex);
	std::vector<UserInfo *>::iterator it;
	for(it=fUserVector.begin();it!=fUserVector.end();it++){
		if(userId==(*it)->userId){
			(*it)->userLoginState=0;
			return 1;
		}
	}
	return 1;
}

char UserAuthentication::addUser(char *userName,char *userPasswd,int groupId)
{
	if(userName==NULL 
		|| strlen(userName)==0
		|| userPasswd==NULL
		|| strlen(userPasswd)==0){
		return 0;
	}
	OSMutexLocker theLocker(&fMutex);
	std::vector<UserInfo *>::iterator it;
	for(it=fUserVector.begin();it!=fUserVector.end();it++){
		if(strcmp(userName,(*it)->userName)==0){
			return 2;
		}
	}

	UserInfo *theInfo=new UserInfo;
	memset((char *)theInfo,'\0',sizeof(UserInfo));

	memcpy(theInfo->userName,userName,strlen(userName));
	memcpy(theInfo->userPasswd,userPasswd,strlen(userPasswd));
	theInfo->groupId=groupId;
	switch(groupId){
		case Admin_GROUP:{
			memcpy(theInfo->groupName,Admin_GRUP_NAME,strlen(Admin_GRUP_NAME));
			break;
		}
		case Genernal_GROUP:{
			memcpy(theInfo->groupName,Genernal_GROUP_NAME,strlen(Genernal_GROUP_NAME));
			break;
		}
		case Guest_GROUP:{
			memcpy(theInfo->groupName,Guest_GROUP_NAME,strlen(Guest_GROUP_NAME));
			break;
		}
		
	}
	theInfo->userId=_our_random32();
	theInfo->userLoginState=0;
	fUserVector.push_back(theInfo);
	return 1;
}
int UserAuthentication::initDefaultAdminUser()
{
	addUser("admin","admin",Admin_GROUP);
	return 1;
}
unsigned UserAuthentication::getUserId(char *userName)
{
	if(userName==NULL 
		|| strlen(userName)==0){
		return 0;
	}
	OSMutexLocker theLocker(&fMutex);
	std::vector<UserInfo *>::iterator it;
	for(it=fUserVector.begin();it!=fUserVector.end();it++){
		/* 用户名不匹配,接着找*/
		if(strcmp(userName,(*it)->userName)!=0){
			continue;
		}
		/* 找到 */
		if(strcmp(userName,(*it)->userName)==0
			&& (*it)->userLoginState==1){   
			return (*it)->userId;
		}
	}
	/* 用户没有注册或没有登录，userId 为无效值*/
	return 0;

}
int UserAuthentication::getAllUser(char *inBuffer,int inLen,int &outLen)
{
	if(inBuffer==NULL 
		|| inLen==0){
		return 0;
	}
	OSMutexLocker theLocker(&fMutex);
	char *pos=inBuffer;
	std::vector<UserInfo *>::iterator it;
	for(it=fUserVector.begin();it!=fUserVector.end();it++){
		memcpy(pos,(*it)->userName,64);
		unsigned uId=htonl((*it)->userId);
		memcpy(pos+64,(char *)&uId,sizeof(uId));
		pos+=68;
		outLen++;
	}
	/* 用户没有注册或没有登录，userId 为无效值*/
	return 1;
}

