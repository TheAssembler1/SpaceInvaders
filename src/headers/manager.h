#ifndef MANAGER_H
#define MANAGER_H

void init_manager();
void deinit_manager();

void init_test_manager();
void deinit_test_manager();

#define A_KEY 0x0
#define D_KEY 0x1
#define SPACE 0x2
#define INSERT_COIN 0x3
#define NUM_INPUTS 0x4

extern bool inputs[NUM_INPUTS];

#endif //MANAGER_H
