#include "STPusherLog.h"
#include "STPusher.h"
#include "STPusherLogSession.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

static STPusher *logPusher=NULL;
void initLog(void *tPusher)
{
	logPusher=(STPusher *)tPusher;
}

int log_sprintf(char *buffer, char *fmt,...)
{
	static OSMutex sMutex;
	OSMutexLocker mutexLocker(&sMutex);

	return 1;
}

int log_printf(char *fmt,...)
{
	static OSMutex sMutex;
	OSMutexLocker mutexLocker(&sMutex);
    va_list args;
    va_start(args,fmt);
	int result=logPusher->getLogSession()->LogPrintf(fmt,args);
	va_end(args);
	return result;	
}

int log_fprintf(FILE *file, char *fmt, ...)
{
	static OSMutex sMutex;
	OSMutexLocker mutexLocker(&sMutex);
    va_list args;
    va_start(args,fmt);
	int result=logPusher->getLogSession()->LogFprintf(file,fmt,args);
	va_end(args);
	return result;
}

int log_snprintf(char *str, size_t size, const char *format, ...)
{
	static OSMutex sMutex;
	OSMutexLocker mutexLocker(&sMutex);

	return 1;
}
