#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>
#include "fonts.h"

// Function to read from a port
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}

// Scancode to ASCII conversion table
const char scancode_to_ascii[] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', 
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 
    'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0 
};



void draw_character(struct limine_framebuffer *framebuffer, const uint8_t *bitmap, size_t x, size_t y, uint32_t color) {
    volatile uint32_t *fb_ptr = (volatile uint32_t *)framebuffer->address; // Obtenez le pointeur du framebuffer
    size_t pitch = framebuffer->pitch;

    for (size_t dy = 0; dy < 8; dy++) {
        for (size_t dx = 0; dx < 8; dx++) {
            if (bitmap[dy] & (1 << (7 - dx))) { // Vérifiez si le pixel doit être dessiné
                if (y + dy < framebuffer->height && x + dx < framebuffer->width) {
                    fb_ptr[(y + dy) * (pitch / sizeof(uint32_t)) + (x + dx)] = color;
                }
            }
        }
    }
}


void draw_string(struct limine_framebuffer *framebuffer, const char *str, size_t x, size_t y, uint32_t color) {
    size_t start_x = x;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            y += 8; // Move to the next line
            x = start_x; // Reset x to the start position
        } else {
            const uint8_t *bitmap = get_bitmap_for_char(str[i]); // Utilisez la fonction pour obtenir le bitmap du caractère
            if (bitmap) {
                draw_character(framebuffer, bitmap, x, y, color); // Dessiner le caractère
                x += 8; // Avancez la position pour le prochain caractère
            }
        }
    }
}


// Function to handle keyboard input
void handle_keyboard(struct limine_framebuffer* framebuffer) {
    const size_t start_x = 20, start_y = 70;
    size_t x = start_x;
    size_t y = start_y;
    size_t last_x_positions[framebuffer->height / 8]; // Array to store the last x positions of each line
    for (size_t i = 0; i < framebuffer->height / 8; i++) {
        last_x_positions[i] = start_x;
    }

    uint8_t last_scancode = 0;
    uint32_t press_time = 0;
    uint32_t delay = 2000000; // Adjust this value to set the delay

    while (1) {
        uint8_t scancode = inb(0x60); // Lire le scancode
        if (scancode != last_scancode) {
            last_scancode = scancode;
            press_time = 0;
        } else {
            press_time++;
        }

        if (scancode < 0x80 && press_time % delay == 0) { // Vérifiez si la touche est enfoncée et appliquez le délai
            char ascii = scancode_to_ascii[scancode]; // Convertir le scancode en ASCII
            if (ascii == '\n') { // Vérifiez si la touche Entrée est enfoncée
                y += 8; // Déplacez y vers le bas de 8
                x = start_x; // Réinitialiser x à la position de départ
            } else if (ascii == '\b') { // Vérifiez si la touche Backspace est enfoncée
                if (x > start_x) {
                    x -= 8; // Reculer la position pour supprimer le caractère
                } else if (y > start_y) {
                    y -= 8; // Reculer à la ligne précédente
                    x = last_x_positions[y / 8]; // Aller à la dernière position x de la ligne précédente
                }
                // Effacer le caractère en dessinant un rectangle vide
                for (size_t dy = 0; dy < 8; dy++) {
                    for (size_t dx = 0; dx < 8; dx++) {
                        if (y + dy < framebuffer->height && x + dx < framebuffer->width) {
                            ((volatile uint32_t *)framebuffer->address)[(y + dy) * (framebuffer->pitch / sizeof(uint32_t)) + (x + dx)] = 0x00000000;
                        }
                    }
                }
            } else {
                const uint8_t *bitmap = get_bitmap_for_char(ascii); // Utilisez la fonction pour obtenir le bitmap du caractère
                if (bitmap) {
                    draw_character(framebuffer, bitmap, x, y, 0x0058FF00); // Dessiner le caractère
                    x += 8; // Avancez la position pour le prochain caractère
                    if (x >= framebuffer->width - 8) { // Check if we need to move to the next line
                        x = start_x; // Reset x to the start position
                        y += 8; // Move to the next line
                    }
                    last_x_positions[y / 8] = x-8; // Store the last x position of the current line
                }
            }
        }
    }
}

#endif // KEYBOARDHANDLER_H