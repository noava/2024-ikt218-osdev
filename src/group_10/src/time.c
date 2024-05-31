#include "libc/stdint.h"

void delay(int milliseconds) {
    for (int i = 0; i < milliseconds * 1000; i++) {
        asm volatile("nop");
    }
}