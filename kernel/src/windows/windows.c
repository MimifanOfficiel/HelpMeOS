#include "includes/windows/windows.h"

uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}


void draw_pixel(struct limine_framebuffer *framebuffer, int width, int x, int y, uint32_t color) {
    volatile uint32_t *fb_ptr = (volatile uint32_t *)framebuffer->address;
    fb_ptr[y * width + x] = color;
}

void draw_rectangle(struct limine_framebuffer *framebuffer, int width, int x, int y, int w, int h, uint32_t color) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            draw_pixel(framebuffer, width, x + j, y + i, color);
        }
    }
}


void draw_title(struct limine_framebuffer *framebuffer, int screen_width, struct Window *window) {
    // Set the title height (a simple fixed height for now)
    int title_height = 8; // For example, 16 pixels tall
    uint32_t title_color = 0x000; // White title text


    // Draw the title background (optional, you could give it a different background color)
    draw_rectangle(framebuffer, screen_width, window->x, window->y - title_height, window->width, title_height, window->border_color);
    draw_string(framebuffer, window->title, window->x, &(window->x)+20, &(window->y) - title_height, title_color);
}



void draw_window(struct limine_framebuffer *framebuffer, int screen_width, struct Window *window) {
    draw_rectangle(framebuffer, screen_width,
                   window->x - window->border_size, window->y - window->border_size, 
                   window->width + 2 * window->border_size, window->height + 2 * window->border_size,
                   window->border_color);

    // Draw the window (inner rectangle)
    draw_rectangle(framebuffer, screen_width, window->x, window->y, window->width, window->height, window->background_color);

    // Draw the title (if available)
    if (window->title != NULL) {
        draw_title(framebuffer, screen_width, window);
    }

}