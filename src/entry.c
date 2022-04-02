#include <headers.h>

#define USAGE_MESSAGE "Correct Usage: $(TARGET_EXEC) [file_path] [true/false] [log_level]"

int main(int argc, char* argv[]){
    char* log_add_fp_str = NULL;
    char* log_set_quit_str = NULL;
    char* log_set_level_str = NULL;
    
    FILE* log_add_fp_fptr = NULL;

    int log_level;

    for(int i = 0; i < argc; i++)
        log_info("argv[%d] %s", i, argv[i]);
   
    log_info("setting wether to see logs");

    //setting weather to see the logs
    log_set_quit_str = argv[2]; 
    if(!strcmp(log_set_quit_str, "true")) 
        log_set_quiet(true);
    else if(!strcmp(log_set_quit_str, "false"))
        log_set_quiet(false);
    else{
        log_fatal(USAGE_MESSAGE); 
        return -1;
    }

    log_info("setting the log level");

    //setting the log level
    log_set_level_str = argv[3];
    if(!strcmp(log_set_level_str, "log_trace"))
        log_level = LOG_TRACE;
    else if(!strcmp(log_set_level_str, "log_debug"))
        log_level = LOG_DEBUG;
    else if(!strcmp(log_set_level_str, "log_info"))
        log_level = LOG_INFO;
    else if(!strcmp(log_set_level_str, "log_warn"))
        log_level = LOG_WARN;
    else if(!strcmp(log_set_level_str, "log_error"))
        log_level = LOG_ERROR;
    else if(!strcmp(log_set_level_str, "log_fatal"))
        log_level = LOG_FATAL;
    else{
        log_fatal(USAGE_MESSAGE);
        return -1;
    }
    log_set_level(log_level);
   
    log_info("setting the file to log to");
    
    //setting file to log to
    log_add_fp_str = argv[1];
    log_add_fp_fptr = fopen(log_add_fp_str, "wr");    
    if(log_add_fp(log_add_fp_fptr, log_level) < 0){
        log_fatal("failed setting up log file");
        return -1;
    }else
        log_debug("success setting up log file");

    //check we have a valid os
    #ifdef UNIX
    log_info("running on unx");
    #elif #defined(WINDOWS)
    log_info("running on windows")
    #else
    log_error("non valid os");
    return -1;
    #endif 

    init_manager();
    deinit_manager();

    //should never hit here should return inside deinit_manager
    log_error("returning from main");
    return -1;
}
