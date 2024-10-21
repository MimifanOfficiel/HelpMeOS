#include "includes/terminal/terminal.h"


// Default values for starting coordinates of the terminal
size_t start_x = 20, start_y = 30;

// Current x and y values
size_t currentX = 20, currentY = 30;

const size_t lineSize = 8;
const size_t charSpacing = 8;
const uint32_t textColor = 0x0058FF00;
const char* prefix = "HelpMe OS > ";


// Scancodes for keyboard handling
const char scancode_to_ascii[] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', 
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 
    'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0 
};





// Function to handle keyboard input
void handle_terminal_keyboard(struct limine_framebuffer* framebuffer) {
    size_t last_x_positions[framebuffer->height / charSpacing]; // Array to store the last x positions of each line
    for (size_t i = 0; i < framebuffer->height / lineSize; i++) {
        last_x_positions[i] = start_x;
    }

    uint8_t last_scancode = 0;
    uint32_t press_time = 0;
    uint32_t delay = 2300000; // Adjust this value to set the delay

    char input_buffer[256] = {0}; // Buffer to store the input string
    size_t input_length = 0;

    draw_string(framebuffer, "\n", start_x, &currentX, &currentY, 0x000);
    draw_string(framebuffer, prefix, start_x, &currentX, &currentY, textColor);

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
                    const char** tokens = (const char**)command; // Convert the command to a const char**
                    executeCommand(framebuffer, tokens[0], tokens); // Execute the command
                }

                input_buffer[0] = '\0'; // Clear the input buffer


                input_length = 0; // Reset the input buffer
                currentY += lineSize; // Déplacez y vers le bas de 8
                currentX = start_x; // Réinitialiser x à la position de départ

                draw_string(framebuffer, prefix, start_x, &currentX, &currentY, textColor);

            } else if (ascii == '\b') { // Vérifiez si la touche Backspace est enfoncée
                if (input_length > 0) {
                    input_length--; // Remove the last character from the input buffer
                    clear_character(framebuffer, currentX, currentY);
                    if (currentX > start_x) {
                        currentX -= charSpacing; // Reculer la position pour supprimer le caractère
                    } else if (currentY > start_y) {
                        currentY -= lineSize; // Reculer à la ligne précédente
                        currentX = last_x_positions[currentY / lineSize]; // Aller à la dernière position x de la ligne précédente
                    }
                    // Effacer le caractère en dessinant un rectangle vide
                    clear_character(framebuffer, currentX, currentY);
                }
            } else {
                const uint8_t *bitmap = get_bitmap_for_char(ascii); // Utilisez la fonction pour obtenir le bitmap du caractère
                if (bitmap) {
                    clear_character(framebuffer, currentX, currentY);
                    draw_character(framebuffer, bitmap, &currentX, &currentY, textColor); // Dessiner le caractère
                    input_buffer[input_length++] = ascii; // Add the character to the input buffer
                    currentX += charSpacing; // Avancez la position pour le prochain caractère
                    if (currentX >= framebuffer->width - charSpacing) { // Check if we need to move to the next line
                        currentX = start_x; // Reset x to the start position
                        currentY += lineSize; // Move to the next line
                    }
                    last_x_positions[currentY / charSpacing] = currentX-charSpacing; // Store the last x position of the current line
                }
            }
            const uint8_t *underscore = get_bitmap_for_char('_');
            draw_character(framebuffer, underscore, &currentX, &currentY, textColor);
        }
    }
}