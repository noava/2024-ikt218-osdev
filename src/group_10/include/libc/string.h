#pragma once

#include "libc/stddef.h"
#include "libc/stdint.h"

size_t strlen(const char* str);

void* memset(void* ptr, int value, size_t num);
