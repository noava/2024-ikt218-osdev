/* Edited from https://archive.is/L3pyA by James Molloy */
#include "terminal.h"
#include "libc/stdint.h"

#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200

static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

void terminalPrint(int colour, const char *string)
{
    while(*string != 0)
    {
        terminalPut(*string);
        string++;
    }
}

// Function to convert an integer to a string in decimal format
void terminalPrintDec(uint32_t num) {
    char buffer[32];

    // Check for negative numbers
    int isNegative = 0;
    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    // Convert the number to a string in reverse order
    int i = 0;
    do {
        buffer[i++] = num % 10 + '0';
        num /= 10;
    } while (num != 0);

    // Add '-' sign for negative numbers
    if (isNegative) {
        buffer[i++] = '-';
    }

    // Null-terminate the string
    buffer[i] = '\0';

    // Reverse the string
    int length = i;
    for (int j = 0; j < length / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[length - j - 1];
        buffer[length - j - 1] = temp;
    }

    terminalPrint(15, buffer);
}

static inline void outb(uint16_t port, uint8_t value) {
    asm volatile ("outb %1, %0" : : "dN"(port), "a"(value));
}

static void move_cursor()
{
    // The screen is 80 characters wide...
    uint16_t cursorLocation = cursor_y * 80 + cursor_x;
    outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
    outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
    outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
    outb(0x3D5, cursorLocation);      // Send the low cursor byte.
}

void terminalClear()
{
    uint8_t *vga = (uint8_t*) VGA_ADDRESS;
    for (int i = 0; i < BUFSIZE; i++)
    {
        vga[i] = 0;
    }

    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}

// Writes a single character out to the screen.
void terminalPut(char c)
{
    // The background colour is black (0), the foreground is white (15).
    uint8_t backColour = 0;
    uint8_t foreColour = 15;

    // The attribute byte is made up of two nibbles - the lower being the
    // foreground colour, and the upper the background colour.
    uint8_t  attributeByte = (backColour << 4) | (foreColour & 0x0F);
    // The attribute byte is the top 8 bits of the word we have to send to the
    // VGA board.
    uint16_t attribute = attributeByte << 8;
    uint16_t *location;

    uint16_t* video_memory = (uint16_t*)VGA_ADDRESS;

    // Handle a backspace, by moving the cursor back one space
    if (c == 0x08 && cursor_x)
    {
        cursor_x--;
    }

    // Handle a tab by increasing the cursor's X, but only to a point
    // where it is divisible by 8.
    else if (c == 0x09)
    {
        cursor_x = (cursor_x+8) & ~(8-1);
    }

    // Handle carriage return
    else if (c == '\r')
    {
        cursor_x = 0;
    }

    // Handle newline by moving cursor back to left and increasing the row
    else if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    // Handle any other printable character.
    else if(c >= ' ')
    {
        location = video_memory + (cursor_y*80 + cursor_x);
        *location = c | attribute;
        cursor_x++;
    }

    // Check if we need to insert a new line because we have reached the end
    // of the screen.
    if (cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y ++;
    }

    move_cursor();
}