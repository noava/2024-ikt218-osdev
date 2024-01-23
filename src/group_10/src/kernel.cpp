#include "../include/terminal.h"

extern "C" int kernel_main(void);
int kernel_main(){

    clearTerminal();
    printf("/n");
    printf("Hello World");
    return 0;
}