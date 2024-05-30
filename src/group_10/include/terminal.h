#include "libc/stdint.h"

void terminalPrint(const char * string);

void monitor_setcolor(uint8_t color);

void terminalPrintDec(uint32_t num);

void terminalClear();

void terminalPut(char c);
