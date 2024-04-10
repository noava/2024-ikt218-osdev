// Edited from https://archive.is/L3pyA by James Molloy
#include "libc/stdint.h"
#include "isr.h"
#include "terminal.h"

void isr_handler(registers_t regs)
{
   terminalPrint(15, "recieved interrupt: ");
   terminalPrintDec(regs.int_no);
   terminalPut('\n');
}
