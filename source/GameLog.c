#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "GameLog.h"

#define FMT_TIME_MAXLEN     20
#define __logargs__(msg) ({va_list args; va_start(args, msg); args;})
#define __fmttime__(b) ({b = (char*)malloc(sizeof(char) * FMT_TIME_MAXLEN); time_t t; time(&t); struct tm *info = localtime(&t); strftime(b, FMT_TIME_MAXLEN, "%Y-%m-%d %X", info);})

typedef enum
{
    LOG_LEVEL_NONE = 0,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING, 
    LOG_LEVEL_TRACE,
} LogLevel;

static const char *LogLevelName[] = {
    "NONE",
    "DEBUG",
    "INFO",
    "ERROR",
    "WARNING",
    "TRACE",
};

static void _log(LogLevel, const char *, va_list);

static void _log(LogLevel level, const char *message, va_list args)
{
    char *strtime;
    __fmttime__(strtime);

    printf("%s ", strtime);
    printf("[%s] - ", LogLevelName[level]);    
    vprintf(message, args);
    printf("\n");
}

void DK_GameLogDebug(const char *message, ...)
{
#if defined(DK_DEBUG)    
    _log(LOG_LEVEL_DEBUG, message, __logargs__(message));
#endif
}

void DK_GameLogInfo(const char *message, ...)
{
    _log(LOG_LEVEL_INFO, message, __logargs__(message));
}

void DK_GameLogError(const char *message, ...)
{
    _log(LOG_LEVEL_ERROR, message, __logargs__(message));
}

void DK_GameLogWarninig(const char *message, ...)
{
    _log(LOG_LEVEL_WARNING, message, __logargs__(message));
}

void DK_GameLogTrace(const char *message, ...)
{
    _log(LOG_LEVEL_TRACE, message, __logargs__(message));
}
