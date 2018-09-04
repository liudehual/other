/*
	
*/

#ifndef __USER_FILE_PARSER_H__
#define __USER_FILE_PARSER_H__

#include "Object.h"
#include "OSQueue.h"
#include <vector>
#include "OSMutex.h"

/* 组ID */
#define Admin_GROUP     0       /* 管理员组 */
#define Genernal_GROUP  1       /* 普通用户组 */
#define Guest_GROUP     2       /* 访客组 */

/* 组名 */
#define Admin_GRUP_NAME 		"admin"
#define Genernal_GROUP_NAME 	"genernal"
#define Guest_GROUP_NAME 		"guest"

typedef struct
{
	int  userId;           /* 用户ID */
	char userName[64];     /* 用户名 */
	char userPasswd[256];  /* MD5加密后的数据 */
	int  groupId;          /* 用户所在组ID */
	char groupName[64];    /* 用户所在的组 */
	int userLoginState;           /* 用户登录状态 0 未登录 1 登录 */
}UserInfo;

typedef struct
{
	int groupId;						  /* 组ID */
	char groupName[64];                   /* 组名 */
	std::vector<UserInfo *> fUserVector;  /* 该组拥有的用户数 */
	int maxUserNums; 					  /* 该组允许拥有的最大的用户数量 */
}GroupInfo;

class UserAuthentication:public Object
{
	public:
		UserAuthentication(void *r,void *p);
		~UserAuthentication();
		virtual int userFileParser(char *fileName);
		char userLogin(char *userName,char *userPasswd);
		char userLoginOut(unsigned userId);
		char addUser(char *userName,char *userPasswd,int groupId);
		int initDefaultAdminUser();
		unsigned getUserId(char *userName);
		int getUserLoginState(char *userName);
		int getAllUser(char *inBuffer,int inLen,int &outLen);
	private:
		std::vector<UserInfo *> fUserVector;	/* 所有的用户 */
		std::vector<GroupInfo *> fGroupVector;  /* 所有用户组 */

		OSMutex fMutex;
};

#endif
