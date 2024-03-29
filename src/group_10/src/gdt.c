/* Edited from https://archive.is/L3pyA by James Molloy */
#include "gdt.h"

struct gdt_entry gdt_entries[5];
struct gdt_pointer gdt_ptr;

// Forward declaration of the assembly function to load the new GDT.
extern void gdt_flush(uint32_t);

// Function to set a single GDT entry.
static void set_gdt_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low = (limit & 0xFFFF);
    gdt_entries[num].granularity = ((limit >> 16) & 0x0F);

    gdt_entries[num].granularity |= (granularity & 0xF0);
    gdt_entries[num].access = access;
}

// Function to initialize the GDT.
void init_gdt() {
    gdt_ptr.limit = (sizeof(struct gdt_entry) * 5) - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    // Set up the GDT entries.
    set_gdt_entry(0, 0, 0, 0, 0);                    // Null segment
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);     // Code segment
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);     // Data segment
    // You can add more segments as needed here.

    gdt_flush((uint32_t)&gdt_ptr);
}