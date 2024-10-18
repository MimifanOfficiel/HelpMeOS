#include "includes/keyboardhandler.h"
#include "includes/commands.h"

size_t start_x = 20, start_y = 30;
size_t currentX = 20, currentY = 30;

const char scancode_to_ascii[] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', 
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 
    'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0 
};

void draw_character(struct limine_framebuffer *framebuffer, const uint8_t *bitmap, uint32_t color) {
    volatile uint32_t *fb_ptr = (volatile uint32_t *)framebuffer->address; // Obtenez le pointeur du framebuffer
    size_t pitch = framebuffer->pitch;

    for (size_t dy = 0; dy < 8; dy++) {
        for (size_t dx = 0; dx < 8; dx++) {
            if (bitmap[dy] & (1 << (7 - dx))) { // Vérifiez si le pixel doit être dessiné
                if (currentY + dy < framebuffer->height && currentX + dx < framebuffer->width) {
                    fb_ptr[(currentY + dy) * (pitch / sizeof(uint32_t)) + (currentX + dx)] = color;
                }
            }
        }
    }
}

void draw_string(struct limine_framebuffer *framebuffer, const char *str, uint32_t color) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            currentY += 8; // Move to the next line
            currentX = start_x; // Reset x to the start position
        } else {
            const uint8_t *bitmap = get_bitmap_for_char(str[i]); // Utilisez la fonction pour obtenir le bitmap du caractère
            if (bitmap) {
                draw_character(framebuffer, bitmap, color); // Dessiner le caractère
                currentX += 8; // Avancez la position pour le prochain caractère
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

// Function to handle keyboard input
void handle_keyboard(struct limine_framebuffer* framebuffer) {
    size_t last_x_positions[framebuffer->height / 8]; // Array to store the last x positions of each line
    for (size_t i = 0; i < framebuffer->height / 8; i++) {
        last_x_positions[i] = start_x;
    }

    uint8_t last_scancode = 0;
    uint32_t press_time = 0;
    uint32_t delay = 2300000; // Adjust this value to set the delay

    char input_buffer[256] = {0}; // Buffer to store the input string
    size_t input_length = 0;

    draw_string(framebuffer, "\n", 0x000);
    draw_string(framebuffer, "HelpMe OS > ", 0x0058FF00);

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
                clear_character(framebuffer, currentX, currentY);

                input_buffer[input_length] = '\0'; // Null-terminate the input string
                
                char** command = parseCommand(framebuffer, input_buffer, &input_length); // Parse the input command

                if(command != NULL && input_length > 0) {
                    executeCommand(framebuffer, command[0]); // Execute the command
                }

                input_buffer[0] = '\0'; // Clear the input buffer


                input_length = 0; // Reset the input buffer
                currentY += 8; // Déplacez y vers le bas de 8
                currentX = start_x; // Réinitialiser x à la position de départ


                draw_string(framebuffer, "\n", 0x000);
                draw_string(framebuffer, "HelpMe OS > ", 0x0058FF00);

            } else if (ascii == '\b') { // Vérifiez si la touche Backspace est enfoncée
                if (input_length > 0) {
                    input_length--; // Remove the last character from the input buffer
                    clear_character(framebuffer, currentX, currentY);
                    if (currentX > start_x) {
                        currentX -= 8; // Reculer la position pour supprimer le caractère
                    } else if (currentY > start_y) {
                        currentY -= 8; // Reculer à la ligne précédente
                        currentX = last_x_positions[currentY / 8]; // Aller à la dernière position x de la ligne précédente
                    }
                    // Effacer le caractère en dessinant un rectangle vide
                    clear_character(framebuffer, currentX, currentY);
                }
            } else {
                const uint8_t *bitmap = get_bitmap_for_char(ascii); // Utilisez la fonction pour obtenir le bitmap du caractère
                if (bitmap) {
                    clear_character(framebuffer, currentX, currentY);
                    draw_character(framebuffer, bitmap, 0x0058FF00); // Dessiner le caractère
                    input_buffer[input_length++] = ascii; // Add the character to the input buffer
                    currentX += 8; // Avancez la position pour le prochain caractère
                    if (currentX >= framebuffer->width - 8) { // Check if we need to move to the next line
                        currentX = start_x; // Reset x to the start position
                        currentY += 8; // Move to the next line
                    }
                    last_x_positions[currentY / 8] = currentX-8; // Store the last x position of the current line
                }
            }
            const uint8_t *underscore = get_bitmap_for_char('_');
            draw_character(framebuffer, underscore, 0x0058FF00);
        }
    }
}