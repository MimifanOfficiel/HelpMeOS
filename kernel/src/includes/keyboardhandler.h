#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "limine.h"
#include "includes/fonts.h"
#include "storage.h"

// Function to read from a port
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}

// Scancode to ASCII conversion table
extern const char scancode_to_ascii[];
extern size_t start_x;
extern size_t start_y;
extern size_t currentX;
extern size_t currentY;




void draw_character(struct limine_framebuffer *framebuffer, const uint8_t *bitmap, uint32_t color);
void draw_string(struct limine_framebuffer *framebuffer, const char *str, uint32_t color);
void clear_screen(struct limine_framebuffer *framebuffer);
void clear_line(struct limine_framebuffer *framebuffer, size_t y);
void clear_word(struct limine_framebuffer *framebuffer, size_t x, size_t y);
void clear_character(struct limine_framebuffer *framebuffer, size_t x, size_t y);
void handle_keyboard(struct limine_framebuffer* framebuffer);

#endif // KEYBOARDHANDLER_H