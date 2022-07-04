#include <headers.h>

void init_manager(){
    log_trace("initializing cpu and mem");

    init_cpu();
    init_mem();

    cycle_cpu();
}


void deinit_manager(){
    log_trace("deinitializing cpu and mem");

    deinit_cpu();
    deinit_mem();

    //exiting here instead of in main
    exit(0);
}