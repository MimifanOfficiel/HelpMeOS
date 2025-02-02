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

void itoa(int num, char *str, int base) {
    int i = 0;
    int is_negative = 0;

    // Handle 0 explicitly, otherwise empty string is printed for 0
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    // In standard itoa(), negative numbers are handled only with base 10
    if (num < 0 && base == 10) {
        is_negative = 1;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    // Append negative sign for negative numbers
    if (is_negative) {
        str[i++] = '-';
    }

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }
}


void draw_int(struct limine_framebuffer *framebuffer, int num, size_t start_x, size_t *x, size_t *y, uint32_t color) {
    char str[12]; // 12 caractères maximum pour un entier 32 bits
    itoa(num, str, 10); // Convertir l'entier en chaîne de caractères
    draw_string(framebuffer, str, start_x, x, y, color); // Dessiner la chaîne de caractères
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