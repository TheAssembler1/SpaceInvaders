#include <headers.h>

void init_manager(){
    init_cpu();
    init_mem();
}


void deinit_manager(){
    deinit_cpu();
    deinit_mem();
}