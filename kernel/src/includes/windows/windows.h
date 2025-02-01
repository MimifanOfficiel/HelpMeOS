#ifndef WiND0WS_H
#define WiND0WS_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "limine.h"
#include "../textEdition.h"

uint8_t inb(uint16_t port);
extern int cursor_x;
extern int cursor_y;

struct Window {
    int x, y;
    int width, height;
    uint32_t background_color;
    uint32_t border_color; // Color of the window border
    int border_size;       // Thickness of the border
    const char *title;     // Title of the window
};


void draw_pixel(struct limine_framebuffer *framebuffer, int width, int x, int y, uint32_t color);
void draw_rectangle(struct limine_framebuffer *framebuffer, int width, int x, int y, int w, int h, uint32_t color);

void draw_title(struct limine_framebuffer *framebuffer, int screen_width, struct Window *window);
void draw_window(struct limine_framebuffer *framebuffer, int screen_width, struct Window *window);




#endif