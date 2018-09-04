#include "Log.h"
#include "Server.h"
#include "LogSession.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

static Server *logServer=NULL;
static OSMutex sMutex;

void initLog(void *tServer)
{
	logServer=(Server *)tServer;
}

int log_sprintf(char *buffer, char *fmt,...)
{
	OSMutexLocker mutexLocker(&sMutex);

	return 1;
}

int log_printf(char *fmt,...)
{
	
	OSMutexLocker mutexLocker(&sMutex);
    va_list args;
    va_start(args,fmt);
	int result=logServer->getLogSession()->LogPrintf(fmt,args);
	va_end(args);
	return result;	
}

int log_fprintf(FILE *file, char *fmt, ...)
{
	OSMutexLocker mutexLocker(&sMutex);
    va_list args;
    va_start(args,fmt);
	int result=logServer->getLogSession()->LogFprintf(file,fmt,args);
	va_end(args);
	return result;
}

int log_snprintf(char *str, size_t size, const char *format, ...)
{
	OSMutexLocker mutexLocker(&sMutex);

	return 1;
}
