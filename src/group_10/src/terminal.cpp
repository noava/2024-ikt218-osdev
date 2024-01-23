#include "terminal.h"
#include <stdint.h>

#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200


void printf(char * string)
{
    char * vgaBuffer = (char*)VGA_ADDRESS;
    while(*string != 0)
    {
        *vgaBuffer++ = *string++;
        *vgaBuffer++ = 15;
    }
}

void clearTerminal()
{
    uint8_t *vga = (uint8_t*) VGA_ADDRESS;
    for (int i = 0; i < BUFSIZE; i++)
    {
        vga[i] = 0;
    }
}