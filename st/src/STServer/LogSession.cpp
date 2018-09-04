#include "LogSession.h"
#include "OSMutex.h"
#include "Log.h"

LogSession::LogSession(void *r,void *p):Object(r,p),
										Task(),
										fMutex(new OSMutex)
{
	
}
LogSession::~LogSession()
{

}
SInt64 LogSession::Run()
{
	EventFlags events = this->GetEvents();
	if((events & Task::kKillEvent)){
		return -1;
	}
	
	return 1000;
}
int LogSession::LogPrintf(char *fmt,va_list args)
{
	if(fmt == NULL){
        return 1;
    }
    int result =  ::vprintf(fmt, args);
    return result;
}
int LogSession::LogFprintf(FILE *f,char *fmt,va_list args)
{
	if(f == NULL){
       return -1;
    }
    int result =  ::vfprintf(f, fmt, args);
    return result;
}

