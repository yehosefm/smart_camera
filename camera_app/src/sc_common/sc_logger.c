#include "stdio.h"
#include "sc_logger.h"


static LoggerLevels logger_level = L_DEBUG;

char *get_level_str(LoggerLevels l){
    switch (l)
    {
    case L_DEBUG:
        return "DEBUG";
    case L_INFO:
        return "INFO";
    case L__WARN:
        return "WARN";
    case L_ERROR:
        return "ERROR";
    default:
        break;
    }
}

void set_logger_level(LoggerLevels l){
    logger_level = l;
}


void logger_log(LoggerLevels l,const char * file_name, 
                int line_num, const  char *func_name, const char *format, ...) {
    if(l >= logger_level){
        va_list arglist;
        printf( "%s %s %d %s: ", get_level_str(l), file_name, line_num, func_name);
        va_start( arglist, format );
        vprintf( format, arglist );
        printf("\n");
        va_end( arglist );
    }
}