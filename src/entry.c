#include "log/log.h"
#include <stdint.h>

int main(int argc, char* argv[]){
    for(uint8_t i = 0; i < argc; i++){
        log_info("argv[%d] %s", i, argv[i]);
    }
    
    return 0;
}
