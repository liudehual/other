/*
	
*/

#ifndef __USER_FILE_PARSER_H__
#define __USER_FILE_PARSER_H__

#include "Object.h"
#include "OSQueue.h"
#include <vector>
#include "OSMutex.h"

/* ��ID */
#define Admin_GROUP     0       /* ����Ա�� */
#define Genernal_GROUP  1       /* ��ͨ�û��� */
#define Guest_GROUP     2       /* �ÿ��� */

/* ���� */
#define Admin_GRUP_NAME 		"admin"
#define Genernal_GROUP_NAME 	"genernal"
#define Guest_GROUP_NAME 		"guest"

typedef struct
{
	int  userId;           /* �û�ID */
	char userName[64];     /* �û��� */
	char userPasswd[256];  /* MD5���ܺ������ */
	int  groupId;          /* �û�������ID */
	char groupName[64];    /* �û����ڵ��� */
	int userLoginState;           /* �û���¼״̬ 0 δ��¼ 1 ��¼ */
}UserInfo;

typedef struct
{
	int groupId;						  /* ��ID */
	char groupName[64];                   /* ���� */
	std::vector<UserInfo *> fUserVector;  /* ����ӵ�е��û��� */
	int maxUserNums; 					  /* ��������ӵ�е������û����� */
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
		std::vector<UserInfo *> fUserVector;	/* ���е��û� */
		std::vector<GroupInfo *> fGroupVector;  /* �����û��� */

		OSMutex fMutex;
};

#endif
