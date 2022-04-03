#include <headers.h>

int main(int argc, char* argv[]) {
    init_manager();
    deinit_manager();

    //should never hit here should return inside deinit_manager
    log_error("returning from main");
    return -1;
}