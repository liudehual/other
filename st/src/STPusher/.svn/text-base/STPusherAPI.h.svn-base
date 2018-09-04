#ifndef __AUDIO_PUSHER_API_H__
#define __AUDIO_PUSHER_API_H__

#define VIDEO_TYPE  0x01
#define AUDIO_TYPE  0x02
struct Frame
{
	unsigned char *buffer;
	int bufferLen;       
	int type;  		/*video or audio*/

	/* 可扩展音频参数 */
};

/* 调用方注册回调函数，当推流器收到服务器转发过来的数据时会调用 */
typedef int (*callBackFunc)(Frame tFrame);

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" 
{
#endif

	/* 
		函数名: STPusher_Init
		描述: 初始化系统环境
		参数: 
			callBackFunc func 用户回调函数(不可为空)
			
		返回值: 1 成功 -1 失败
	*/	
	int STPusher_Init(callBackFunc func);

	/* 
		函数名: pusher_connect
		描述: 链接到服务器
		参数: 
			serverAddr 服务器ip地址
			serverPort 服务器监听端口
			userName   用户名
			userPassword 用户密码
			
		返回值: 1 成功 0 失败
	*/	
	int STPusher_connect(char *serverAddr,
						unsigned short serverPort,
						char *userName,
						char *userPassword);
						
	/* 
		函数名: pusher_pushFrame
		描述: 压入多媒体帧
		参数:  tFrame 帧描述结构
		返回值: 1 成功 0 失败

	*/
	int STPusher_pushFrame(Frame tFrame);

	/* 
		函数名: STPusher_RegisterToServer
		描述: 注册到服务器
		参数:  用户名、密码
		返回值: 1 成功 0 失败
	*/
	int STPusher_RegisterToServer(char *userName,		char *userPassword);

	/* 
		函数名: STPusher_loginToServer
		描述: 登录到服务器
		参数:  用户名、密码
		返回值: 1 成功 0 失败
	*/
	int STPusher_loginToServer(char *userName,		char *userPassword);

	/* 
		函数名: STPusher_GetUserList
		描述: 获取用户列表
		参数:  无
		返回值: 1 成功 0 失败
	*/
	int STPusher_GetUserList();

	/* 
		函数名: STPusher_StartPushFrame
		描述: 开始推流
		参数:  无
		返回值: 1 成功 0 失败
	*/
	int STPusher_StartPushFrame();

	int STPusher_StartPullFrame(unsigned id);

	/* 测试用 */
	unsigned STPusher_GetUerID(char *userName);
	
#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
