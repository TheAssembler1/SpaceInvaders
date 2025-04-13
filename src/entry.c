#include <headers.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

// FIXME::this should be passed through args
#define TEST_MODE 0

void handle_sigint(int sig) {
    printf("\n[!] Caught signal %d (Ctrl+C), exiting cleanly.\n", sig);
    fflush(stdout);
    exit(0);
}

void setup_signal_handlers() {
    signal(SIGINT, handle_sigint);
}


int main(int argc, char* argv[]) {
    setup_signal_handlers();

    if (!TEST_MODE) {
        init_manager();
        deinit_manager();
    } else {
        init_test_manager();
        deinit_test_manager();
    }

    // should never hit here should return inside deinit_manager
    log_error("returning from main");

    return -1;
}
