#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>
#include <stdlib.h>

void initLog(void *tPusher);
int log_sprintf(char *buffer, const char *fmt,...);
int log_fprintf(FILE *file, char *fmt, ...);
int log_snprintf(char *str, size_t size, const char *format, ...);
int log_printf(char *fmt,...);

#endif
