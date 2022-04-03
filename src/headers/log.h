#ifndef LOG_H
#define LOG_H

//returns the local date/time formatted as 2014-03-19 11:11:52
char* get_formated_time();

//remove path from filename
#ifdef UNIX
#define __SHORT_FILE__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#elif defined(WINDOWS)
#define __SHORT_FILE__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#endif

//main log macro
#define __LOG__(format, loglevel, ...) printf("%s %-5s [%s] [%s:%d] " format "\n", get_formated_time(), loglevel, __func__, __SHORT_FILE__, __LINE__, ## __VA_ARGS__)

//specific log macros with 
#define log_debug(format, ...) __LOG__(format, "DEBUG", ## __VA_ARGS__)
#define log_TRACE(format, ...) __LOG__(format, "TRACE", ## __VA_ARGS__)
#define log_warn(format, ...) __LOG__(format, "WARN", ## __VA_ARGS__)
#define log_error(format, ...) __LOG__(format, "ERROR", ## __VA_ARGS__)
#define log_info(format, ...) __LOG__(format, "INFO", ## __VA_ARGS__)

#endif //LOG_H