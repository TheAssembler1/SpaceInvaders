#include <headers.h>

#define TEST_BYTE_VALUE 0xFD
#define TEST_SHORT_VALUE 0xFDAB

//test will only check first 10 byte of memory
void test_read_write_mem(){
    log_info("testing read and write to and from mem");

    //testing byte read and writes
    for(int i = 0; i < 10; i++)
        write_byte_mem(i, TEST_BYTE_VALUE);

    for(int i = 0; i < 10; i++){
        if(TEST_BYTE_VALUE == read_byte_mem(i))
            log_info("SUCCESS::byte r/w | Expected Value:%x | Actual Value:%x", TEST_BYTE_VALUE, read_byte_mem(i));
        else
            log_error("FAILED::byte r/w | Expected Value:%x | Actual Value:%x", TEST_BYTE_VALUE, read_byte_mem(i));
    }

    //testing short read and writes
    for(int i = 0; i < 10; i += 2)
        write_short_mem(i, TEST_SHORT_VALUE);


    for(int i = 0; i < 10; i += 2){
        if(TEST_SHORT_VALUE == read_short_mem(i))
            log_info("SUCCESS::short r/w | Expected Value:%x | Actual Value:%x", TEST_SHORT_VALUE, read_short_mem(i));
        else
            log_error("FAILED::short r/w | Expected Value:%x | Actual Value:%x", TEST_SHORT_VALUE, read_short_mem(i));
    }
}

void test(registers* registers) {
    print_cpu(registers);
}