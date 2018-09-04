#include "STPusherLogSession.h"
#include "OSMutex.h"
#include "STPusherLog.h"

STPusherLogSession::STPusherLogSession(void *r,void *p):STPusherObject(r,p),
										Task(),
										fMutex(new OSMutex)
{
	
}
STPusherLogSession::~STPusherLogSession()
{

}
SInt64 STPusherLogSession::Run()
{
	EventFlags events = this->GetEvents();
	if((events & Task::kKillEvent)){
		return -1;
	}
	
	return 1000;
}
int STPusherLogSession::LogPrintf(char *fmt,va_list args)
{
	if(fmt == NULL){
        return 1;
    }
    int result =::vprintf(fmt, args);
    return result;
}
int STPusherLogSession::LogFprintf(FILE *f,char *fmt,va_list args)
{
	if(f == NULL){
       return -1;
    }
    int result =::vfprintf(f, fmt, args);
    return result;
}

