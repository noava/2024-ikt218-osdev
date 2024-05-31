#include "libc/stdio.h"
#include "libc/system.h"

void panic(const char* message) {
    printf("Kernel panic: %s\n", message);

    for (;;);
}
