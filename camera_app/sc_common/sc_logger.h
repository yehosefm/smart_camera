#include <stdarg.h>

#ifndef LOGGER_H_
#define LOGGER_H_

typedef enum {
    L_DEBUG,
    L_INFO,
    L__WARN,
    L_ERROR,
} LoggerLevels;


#define LOGGER_LOG(level, ...) \
    logger_log(level, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)


void set_logger_level(LoggerLevels l);


void logger_log(LoggerLevels l,const char * file_name, 
                int line_num, const char *func_name,const char *format, ...);


#endif //LOGGER_H_