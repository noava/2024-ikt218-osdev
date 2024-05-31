#include "libc/stdint.h"
#include "time.h"

void terminalPrint(const char * string);

void terminalPrintWithDelay(const char *string, int delayTime);

void HelloWorld(const char * string);

void terminalSetColor(uint8_t fore, uint8_t back);

void terminalPrintDec(uint32_t num);

void terminalClear();

void terminalPut(char c);
