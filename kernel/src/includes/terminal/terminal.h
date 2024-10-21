#ifndef HoS_TerMIn4l
#define HoS_TerMIn4l

#include <stdint.h>
#include "limine.h"
#include "../fonts.h"
#include "../storage.h"
#include "../textEdition.h"
#include "commands.h"


// Scancode to ASCII conversion table
extern const char scancode_to_ascii[];
extern size_t start_x;
extern size_t start_y;
extern size_t currentX;
extern size_t currentY;
extern const size_t lineHeight;
extern const size_t charSpacing;
extern const uint32_t textColor;
extern const char* prefix;

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}

void handle_terminal_keyboard(struct limine_framebuffer *framebuffer);


#endif