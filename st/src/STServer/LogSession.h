#ifndef __LOG_SESSION_H__
#define __LOG_SESSION_H__
#include "Task.h"
#include "OSMutex.h"
#include "Object.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

class LogSession:public Object,public Task
{
	public:
		LogSession(void *r,void *p);
		~LogSession();
		virtual SInt64 Run();
	
		int LogPrintf(char *fmt,va_list args);
		int LogFprintf(FILE *f,char *fmt,va_list args);
		OSMutex *getMutex(){return fMutex;}
	private:
		OSMutex *fMutex;	
		
};

#endif
