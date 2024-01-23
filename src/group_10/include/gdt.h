#ifndef GDT_H
#define GDT_H

#include <stdint.h>

// Structure for a single GDT entry
struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

// Structure for the pointer to the GDT
struct gdt_pointer {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void init_gdt();

#endif // GDT_H
