// Implemented from teachers solution guide
#include "libc/system.h"

__attribute__((noreturn)) void panic(const char*);
void* _impure_ptr = NULL;