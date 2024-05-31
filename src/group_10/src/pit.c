/* Edited from https://archive.is/8W6ew by James Molloy */
#include "pit.h"
#include "terminal.h"
#include "io.h"
#include "isr.h"

static uint32_t tick = 0;

static void timer_callback(registers_t regs)
{
   tick++;
}

void init_pit(){
    register_interrupt_handler(IRQ0, &timer_callback);

    outb(PIT_CMD_PORT, 0x36);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    uint8_t l = (uint8_t)(DIVIDER & 0xFF);
    uint8_t h = (uint8_t)((DIVIDER >> 8) & 0xFF );

    // Send the frequency divisor.
    outb(PIT_CHANNEL0_PORT, l);
    outb(PIT_CHANNEL0_PORT, h);
}



// Implemented from teachers solution guide

void sleep_interrupt(uint32_t milliseconds){
    uint32_t current_tick = tick;
    uint32_t ticks_to_wait = milliseconds * TICKS_PER_MS;
    uint32_t end_ticks = current_tick + ticks_to_wait;

    while (current_tick < end_ticks) {
        // Enable interrupts (sti)
        asm volatile("sti");
        // Halt the CPU until the next interrupt (hlt)
        asm volatile("hlt");
        current_tick = tick;
    }
}

void sleep_busy(uint32_t milliseconds){
    uint32_t start_tick = tick;
    uint32_t ticks_to_wait = milliseconds * TICKS_PER_MS;
    uint32_t elapsed_ticks = 0;
    
    while (elapsed_ticks < ticks_to_wait) {
        while (tick == start_tick + elapsed_ticks) {};
        elapsed_ticks++;
    }    
}