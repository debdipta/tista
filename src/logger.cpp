#include "logger.h"
#include <stdio.h>
#include <stdlib.h> 
#include <errno.h>
#include <stdarg.h>

extern int errno;

void create_log_file(FILE **, const char*);

logger* logger::__instance = NULL;

logger::logger()
{
    __logpath = "/tmp/logger/logger.log";
    create_log_file(& __fp_log ,__logpath );
}

logger::~logger()
{
    if( __fp_log )  {
        fclose(__fp_log);
        __fp_log = NULL;
    }
    if(__instance)  {
        delete __instance;
        __instance = NULL;
    }
}

void __singal(const char *_exit_str )
{
    printf(_exit_str);
    exit(0);
}

void create_log_file( FILE **__fp_log,
                      const char* __logpath)
{
    *__fp_log = fopen(__logpath, "ab+");
    if(NULL == *__fp_log) { 
        __singal("Error opening log file \n");
    }
}

void logger::write_file( const char* _msg, ... )
{
    va_list args;

    va_start(args, _msg);
    if(NULL != __fp_log)    {
        vfprintf(__fp_log, _msg, args);
    }
    va_end(args);
}

logger* logger::getInstance()
{
    if(!__instance)
        __instance = new logger();
    return __instance;
}
