#include "keyboard.h"
#include "terminal.h"
#include "io.h"

void keyboard_handler(registers_t regs) {
    // Read the scancode from the keyboard controller
    uint8_t scancode = inb(0x60);
    
    // Translate the scancode to ASCII using a lookup table
    // Example lookup table (you may need to adjust this):
    static const char scancodes[] = {
        0,  0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
        '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 
        0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 
        'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 
        0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', 
        '3', '0', '.'
    };
    
    // Get the ASCII character corresponding to the scancode
    char character = scancodes[scancode];
    
    // Print the ASCII character to the screen
    if (character != 0) {
        terminalPut(character);
    }
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_handler);
}