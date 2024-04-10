#include "libc/stdint.h"

void terminalPrint(int colour, const char * string);

void terminalPrintDec(uint32_t num);

void terminalClear();

void terminalPut(char c);
