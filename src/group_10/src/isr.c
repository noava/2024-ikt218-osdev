// Edited from https://archive.is/L3pyA by James Molloy
#include "libc/stdint.h"
#include "isr.h"
#include "terminal.h"
#include "io.h"

void isr_handler(registers_t regs)
{
   terminalPrint("recieved interrupt: ");
   terminalPrintDec(regs.int_no);
   terminalPut('\n');
}

// This gets called from our ASM interrupt handler stub.
void irq_handler(registers_t regs)
{
   // Send an EOI (end of interrupt) signal to the PICs.
   // If this interrupt involved the slave.
   if (regs.int_no >= 40)
   {
       // Send reset signal to slave.
       outb(0xA0, 0x20);
   }
   // Send reset signal to master. (As well as slave, if necessary).
   outb(0x20, 0x20);

   if (interrupt_handlers[regs.int_no] != 0)
   {
       isr_t handler = interrupt_handlers[regs.int_no];
       handler(regs);
   }
}

isr_t interrupt_handlers[256];

void register_interrupt_handler(uint8_t n, isr_t handler)
{
  interrupt_handlers[n] = handler;
}