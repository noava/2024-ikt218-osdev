#include "libc/string.h"
#include "libc/stddef.h"
#include "libc/stdint.h"

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void* memset(void* ptr, int value, size_t num) 
{
    unsigned char* p = ptr;
    for (size_t i = 0; i < num; ++i) {
        p[i] = (unsigned char)value;
    }
    return ptr;
}
