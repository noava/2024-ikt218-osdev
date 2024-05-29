#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>
#include "../include/descriptor_tables.h"
#include "../include/terminal.h"
#include "../include/isr.h"
#include "../include/keyboard.h"
#include "../include/memory/memory.h"


struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();

extern uint32_t end;

int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    terminalClear();

    init_descriptor_tables();

    init_kernel_memory(&end);
    init_paging();
    print_memory_layout();

    init_keyboard();

    terminalClear();
    terminalPut('\n');

    terminalPrintDec(123);
    terminalPut('\n');
    terminalPrintDec(0x33);
    terminalPut('\n');
    terminalPut('\n');
    terminalPrint(15, "Welcome to group 10's kernel\n");
    terminalPut('\n');
    terminalPut('\n');
    
    // Call cpp kernel_main (defined in kernel.cpp)
    return kernel_main();
}