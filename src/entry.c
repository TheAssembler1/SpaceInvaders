#include <headers.h>

//FIXME::this should be passed through args
#define TEST_MODE 0

int main(int argc, char* argv[]) {
    if (!TEST_MODE) {
        init_manager();
        deinit_manager();
    }
    else {
        init_test_manager();
        deinit_test_manager();
    }

    //should never hit here should return inside deinit_manager
    log_error("returning from main");

    return -1;
}