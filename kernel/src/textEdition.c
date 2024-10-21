#include "includes/textEdition.h"

void draw_character(struct limine_framebuffer *framebuffer, const uint8_t *bitmap, size_t *x, size_t *y, uint32_t color) {
    volatile uint32_t *fb_ptr = (volatile uint32_t *)framebuffer->address; // Obtenez le pointeur du framebuffer 
    size_t pitch = framebuffer->pitch;

    for (size_t dy = 0; dy < 8; dy++) {
        for (size_t dx = 0; dx < 8; dx++) {
            if (bitmap[dy] & (1 << (7 - dx))) { // Vérifiez si le pixel doit être dessiné
                if (*y + dy < framebuffer->height && *x + dx < framebuffer->width) {
                    fb_ptr[(*y + dy) * (pitch / sizeof(uint32_t)) + (*x + dx)] = color;
                }
            }
        }
    }
}

void draw_string(struct limine_framebuffer *framebuffer, const char *str, size_t start_x, size_t *x, size_t *y, uint32_t color) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            *y += 8; // Move to the next line
            *x = start_x; // Reset x to the start position
        } else {
            const uint8_t *bitmap = get_bitmap_for_char(str[i]); // Utilisez la fonction pour obtenir le bitmap du caractère
            if (bitmap) {
                draw_character(framebuffer, bitmap, x, y, color); // Passer x et y comme pointeurs
                *x += 8; // Avancez la position pour le prochain caractère
            }
        }
    }
}


void clear_screen(struct limine_framebuffer *framebuffer) {
    volatile uint32_t *fb_ptr = framebuffer->address;
    for (size_t i = 0; i < framebuffer->height; i++) {
        for (size_t j = 0; j < framebuffer->width; j++) {
            fb_ptr[i * (framebuffer->pitch / sizeof(uint32_t)) + j] = 0x00000000;
        }
    }
}

void clear_line(struct limine_framebuffer *framebuffer, size_t y) {
    volatile uint32_t *fb_ptr = framebuffer->address;
    for (size_t i = 0; i < framebuffer->width; i++) {
        fb_ptr[y * (framebuffer->pitch / sizeof(uint32_t)) + i] = 0x00000000;
    }
}

void clear_word(struct limine_framebuffer *framebuffer, size_t x, size_t y) {
    volatile uint32_t *fb_ptr = framebuffer->address;
    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0; j < 8; j++) {
            fb_ptr[(y + i) * (framebuffer->pitch / sizeof(uint32_t)) + (x + j)] = 0x00000000;
        }
    }
}

void clear_character(struct limine_framebuffer *framebuffer, size_t x, size_t y) {
    volatile uint32_t *fb_ptr = framebuffer->address;
    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0; j < 8; j++) {
            fb_ptr[(y + i) * (framebuffer->pitch / sizeof(uint32_t)) + (x + j)] = 0x00000000;
        }
    }
}