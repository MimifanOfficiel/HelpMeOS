#ifndef FONTS_H
#define FONTS_H

#include <stdint.h>
#include <stddef.h>

// Table des minuscules (8x8)
extern const uint8_t font_lowercase[26][8];

// Table des majuscules (16x8)
extern const uint8_t font_uppercase[26][16];

// Table des chiffres (8x8)
extern const uint8_t font_numbers[10][8];

// Bitmap for 'space' (8x8)
extern const uint8_t font_space[8];

// Table des caractères spéciaux (8x8)
extern const uint8_t font_special_chars[28][8];

const uint8_t* get_bitmap_for_char(char c);


#endif
