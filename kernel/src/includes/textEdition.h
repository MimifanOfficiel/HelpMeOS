#ifndef TxT_EdITion
#define TxT_EdITion

#include <stdint.h>
#include <stddef.h>
#include "fonts.h"
#include "limine.h"

void draw_character(struct limine_framebuffer *framebuffer, const uint8_t *bitmap, size_t *x, size_t *y, uint32_t color);
void draw_string(struct limine_framebuffer *framebuffer, const char *str, size_t start_x, size_t *x, size_t *y, uint32_t color);
void clear_screen(struct limine_framebuffer *framebuffer);
void clear_line(struct limine_framebuffer *framebuffer, size_t y);
void clear_word(struct limine_framebuffer *framebuffer, size_t x, size_t y);
void clear_character(struct limine_framebuffer *framebuffer, size_t x, size_t y);


#endif