/* Edited from https://archive.is/L3pyA and https://archive.is/8W6ew by James Molloy */
#include "libc/stdint.h"
#include "libc/string.h"
#include "descriptor_tables.h"
#include "terminal.h"
#include "isr.h"
#include "io.h"

extern void gdt_flush(uint32_t gdtPtr);
extern void idt_flush(uint32_t idtPtr);

static void set_gdt_entry(uint32_t,uint32_t,uint32_t,uint8_t,uint8_t);
static void set_idt_entry(uint8_t,uint32_t,uint16_t,uint8_t);

struct gdt_entry gdt_entries[5];
struct gdt_pointer gdt_ptr;
struct idt_entry idt_entries[256];
struct idt_pointer idt_ptr;

void init_descriptor_tables() {
    terminalPrint(16, "Initializing Descriptor Tables\n");
    init_gdt();
    init_idt();
    init_irq();
    asm volatile("sti");
}

// GDT
extern void gdt_flush(uint32_t);

static void set_gdt_entry(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low = (limit & 0xFFFF);
    gdt_entries[num].granularity = ((limit >> 16) & 0x0F);

    gdt_entries[num].granularity |= (granularity & 0xF0);
    gdt_entries[num].access = access;
}

void init_gdt() {
    gdt_ptr.limit = (sizeof(struct gdt_entry) * 5) - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    set_gdt_entry(0, 0, 0, 0, 0);                    // Null segment
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);     // Code segment
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);     // Data segment
    // We can add more segments here.

    gdt_flush((uint32_t)&gdt_ptr);
}

// IDT
extern void idt_flush(uint32_t);

static void set_idt_entry(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

    idt_entries[num].sel     = sel;
    idt_entries[num].always0 = 0;
    // We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    idt_entries[num].flags   = flags /* | 0x60 */;
}

void init_idt()
{
    idt_ptr.limit = sizeof(struct idt_entry) * 256 -1;
    idt_ptr.base  = (uint32_t)&idt_entries;

    memset(&idt_entries, 0, sizeof(struct idt_entry)*256);

    set_idt_entry( 0, (uint32_t)isr0, 0x08, 0x8E);
    set_idt_entry( 1, (uint32_t)isr1, 0x08, 0x8E);
    set_idt_entry( 2, (uint32_t)isr2, 0x08, 0x8E);
    set_idt_entry( 3, (uint32_t)isr3, 0x08, 0x8E);
    set_idt_entry( 4, (uint32_t)isr4, 0x08, 0x8E);
    set_idt_entry( 5, (uint32_t)isr5, 0x08, 0x8E);
    set_idt_entry( 6, (uint32_t)isr6, 0x08, 0x8E);
    set_idt_entry( 7, (uint32_t)isr7, 0x08, 0x8E);
    set_idt_entry( 8, (uint32_t)isr8, 0x08, 0x8E);
    set_idt_entry( 9, (uint32_t)isr9, 0x08, 0x8E);
    set_idt_entry(10, (uint32_t)isr10, 0x08, 0x8E);
    set_idt_entry(11, (uint32_t)isr11, 0x08, 0x8E);
    set_idt_entry(12, (uint32_t)isr12, 0x08, 0x8E);
    set_idt_entry(13, (uint32_t)isr13, 0x08, 0x8E);
    set_idt_entry(14, (uint32_t)isr14, 0x08, 0x8E);
    set_idt_entry(15, (uint32_t)isr15, 0x08, 0x8E);
    set_idt_entry(16, (uint32_t)isr16, 0x08, 0x8E);
    set_idt_entry(17, (uint32_t)isr17, 0x08, 0x8E);
    set_idt_entry(18, (uint32_t)isr18, 0x08, 0x8E);
    set_idt_entry(19, (uint32_t)isr19, 0x08, 0x8E);
    set_idt_entry(20, (uint32_t)isr20, 0x08, 0x8E);
    set_idt_entry(21, (uint32_t)isr21, 0x08, 0x8E);
    set_idt_entry(22, (uint32_t)isr22, 0x08, 0x8E);
    set_idt_entry(23, (uint32_t)isr23, 0x08, 0x8E);
    set_idt_entry(24, (uint32_t)isr24, 0x08, 0x8E);
    set_idt_entry(25, (uint32_t)isr25, 0x08, 0x8E);
    set_idt_entry(26, (uint32_t)isr26, 0x08, 0x8E);
    set_idt_entry(27, (uint32_t)isr27, 0x08, 0x8E);
    set_idt_entry(28, (uint32_t)isr28, 0x08, 0x8E);
    set_idt_entry(29, (uint32_t)isr29, 0x08, 0x8E);
    set_idt_entry(30, (uint32_t)isr30, 0x08, 0x8E);
    set_idt_entry(31, (uint32_t)isr31, 0x08, 0x8E);

    idt_flush((uint32_t)&idt_ptr);
}

// IRQ
void init_irq()
{
    // Remap the irq table.
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);


    set_idt_entry(32, (uint32_t)irq0, 0x08, 0x8E);
    set_idt_entry(33, (uint32_t)irq1, 0x08, 0x8E);
    set_idt_entry(34, (uint32_t)irq2, 0x08, 0x8E);
    set_idt_entry(35, (uint32_t)irq3, 0x08, 0x8E);
    set_idt_entry(36, (uint32_t)irq4, 0x08, 0x8E);
    set_idt_entry(37, (uint32_t)irq5, 0x08, 0x8E);
    set_idt_entry(38, (uint32_t)irq6, 0x08, 0x8E);
    set_idt_entry(39, (uint32_t)irq7, 0x08, 0x8E);
    set_idt_entry(40, (uint32_t)irq8, 0x08, 0x8E);
    set_idt_entry(41, (uint32_t)irq9, 0x08, 0x8E);
    set_idt_entry(42, (uint32_t)irq10, 0x08, 0x8E);
    set_idt_entry(43, (uint32_t)irq11, 0x08, 0x8E);
    set_idt_entry(44, (uint32_t)irq12, 0x08, 0x8E);
    set_idt_entry(45, (uint32_t)irq13, 0x08, 0x8E);
    set_idt_entry(46, (uint32_t)irq14, 0x08, 0x8E);
    set_idt_entry(47, (uint32_t)irq15, 0x08, 0x8E);
}