#include "includes/fonts.h"

const uint8_t font_lowercase[26][8] = {
    // Bitmap for 'a'
    {0x00, 0x00, 0x3C, 0x04, 0x3C, 0x44, 0x3C, 0x00},
    // Bitmap for 'b'
    {0x00, 0x40, 0x40, 0x7C, 0x44, 0x44, 0x78, 0x00},
    // Bitmap for 'c'
    {0x00, 0x00, 0x3C, 0x40, 0x40, 0x40, 0x3C, 0x00},
    // Bitmap for 'd'
    {0x00, 0x04, 0x04, 0x3C, 0x44, 0x44, 0x3C, 0x00},
    // Bitmap for 'e'
    {0x00, 0x00, 0x3C, 0x44, 0x7C, 0x40, 0x3C, 0x00},
    // Bitmap for 'f'
    {0x00, 0x0C, 0x10, 0x3C, 0x10, 0x10, 0x10, 0x00},
    // Bitmap for 'g'
    {0x00, 0x00, 0x3C, 0x44, 0x3C, 0x04, 0x3C, 0x00},
    // Bitmap for 'h'
    {0x00, 0x40, 0x40, 0x7C, 0x44, 0x44, 0x44, 0x00},
    // Bitmap for 'i'
    {0x00, 0x10, 0x00, 0x30, 0x10, 0x10, 0x38, 0x00},
    // Bitmap for 'j'
    {0x00, 0x04, 0x00, 0x0C, 0x04, 0x44, 0x3C, 0x00},
    // Bitmap for 'k'
    {0x00, 0x40, 0x40, 0x48, 0x70, 0x48, 0x44, 0x00},
    // Bitmap for 'l'
    {0x00, 0x30, 0x10, 0x10, 0x10, 0x10, 0x38, 0x00},
    // Bitmap for 'm'
    {0x00, 0x00, 0x6C, 0x54, 0x54, 0x54, 0x44, 0x00},
    // Bitmap for 'n'
    {0x00, 0x00, 0x5C, 0x64, 0x44, 0x44, 0x44, 0x00},
    // Bitmap for 'o'
    {0x00, 0x00, 0x3C, 0x44, 0x44, 0x44, 0x3C, 0x00},
    // Bitmap for 'p'
    {0x00, 0x00, 0x78, 0x44, 0x78, 0x40, 0x40, 0x00},
    // Bitmap for 'q'
    {0x00, 0x00, 0x3C, 0x44, 0x3C, 0x04, 0x04, 0x00},
    // Bitmap for 'r'
    {0x00, 0x00, 0x5C, 0x64, 0x40, 0x40, 0x40, 0x00},
    // Bitmap for 's'
    {0x00, 0x00, 0x3C, 0x40, 0x3C, 0x04, 0x78, 0x00},
    // Bitmap for 't'
    {0x00, 0x10, 0x10, 0x7C, 0x10, 0x10, 0x0C, 0x00},
    // Bitmap for 'u'
    {0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x3C, 0x00},
    // Bitmap for 'v'
    {0x00, 0x00, 0x44, 0x44, 0x44, 0x28, 0x10, 0x00},
    // Bitmap for 'w'
    {0x00, 0x00, 0x44, 0x54, 0x54, 0x54, 0x28, 0x00},
    // Bitmap for 'x'
    {0x00, 0x00, 0x44, 0x28, 0x10, 0x28, 0x44, 0x00},
    // Bitmap for 'y'
    {0x00, 0x00, 0x44, 0x44, 0x3C, 0x04, 0x38, 0x00},
    // Bitmap for 'z'
    {0x00, 0x00, 0x7C, 0x08, 0x10, 0x20, 0x7C, 0x00},
};


 const uint8_t font_uppercase[26][16] = {
    // Bitmap for 'A'
    {0x00, 0x00, 0x38, 0x44, 0x7C, 0x44, 0x44, 0x00, 0x00, 0x00, 0x38, 0x44, 0x7C, 0x44, 0x44, 0x00},
    // Bitmap for 'B'
    {0x00, 0x00, 0x78, 0x44, 0x78, 0x44, 0x78, 0x00, 0x00, 0x00, 0x78, 0x44, 0x78, 0x44, 0x78, 0x00},
    // Bitmap for 'C'
    {0x00, 0x00, 0x3C, 0x40, 0x40, 0x40, 0x3C, 0x00, 0x00, 0x00, 0x3C, 0x40, 0x40, 0x40, 0x3C, 0x00},
    // Bitmap for 'D'
    {0x00, 0x00, 0x78, 0x44, 0x44, 0x44, 0x78, 0x00, 0x00, 0x00, 0x78, 0x44, 0x44, 0x44, 0x78, 0x00},
    // Bitmap for 'E'
    {0x00, 0x00, 0x7C, 0x40, 0x78, 0x40, 0x7C, 0x00, 0x00, 0x00, 0x7C, 0x40, 0x78, 0x40, 0x7C, 0x00},
    // Bitmap for 'F'
    {0x00, 0x00, 0x7C, 0x40, 0x78, 0x40, 0x40, 0x00, 0x00, 0x00, 0x7C, 0x40, 0x78, 0x40, 0x40, 0x00},
    // Bitmap for 'G'
    {0x00, 0x00, 0x3C, 0x40, 0x4C, 0x44, 0x3C, 0x00, 0x00, 0x00, 0x3C, 0x40, 0x4C, 0x44, 0x3C, 0x00},
    // Bitmap for 'H'
    {0x00, 0x00, 0x44, 0x44, 0x7C, 0x44, 0x44, 0x00, 0x00, 0x00, 0x44, 0x44, 0x7C, 0x44, 0x44, 0x00},
    // Bitmap for 'I'
    {0x00, 0x00, 0x38, 0x10, 0x10, 0x10, 0x38, 0x00, 0x00, 0x00, 0x38, 0x10, 0x10, 0x10, 0x38, 0x00},
    // Bitmap for 'J'
    {0x00, 0x00, 0x1C, 0x08, 0x08, 0x48, 0x30, 0x00, 0x00, 0x00, 0x1C, 0x08, 0x08, 0x48, 0x30, 0x00},
    // Bitmap for 'K'
    {0x00, 0x00, 0x44, 0x48, 0x70, 0x48, 0x44, 0x00, 0x00, 0x00, 0x44, 0x48, 0x70, 0x48, 0x44, 0x00},
    // Bitmap for 'L'
    {0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x7C, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x7C, 0x00},
    // Bitmap for 'M'
    {0x00, 0x00, 0x44, 0x6C, 0x54, 0x54, 0x44, 0x00, 0x00, 0x00, 0x44, 0x6C, 0x54, 0x54, 0x44, 0x00},
    // Bitmap for 'N'
    {0x00, 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44, 0x00, 0x00, 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44, 0x00},
    // Bitmap for 'O'
    {0x00, 0x00, 0x38, 0x44, 0x44, 0x44, 0x38, 0x00, 0x00, 0x00, 0x38, 0x44, 0x44, 0x44, 0x38, 0x00},
    // Bitmap for 'P'
    {0x00, 0x00, 0x78, 0x44, 0x78, 0x40, 0x40, 0x00, 0x00, 0x00, 0x78, 0x44, 0x78, 0x40, 0x40, 0x00},
    // Bitmap for 'Q'
    {0x00, 0x00, 0x38, 0x44, 0x44, 0x54, 0x38, 0x04, 0x00, 0x00, 0x38, 0x44, 0x44, 0x54, 0x38, 0x04},
    // Bitmap for 'R'
    {0x00, 0x00, 0x78, 0x44, 0x78, 0x48, 0x44, 0x00, 0x00, 0x00, 0x78, 0x44, 0x78, 0x48, 0x44, 0x00},
    // Bitmap for 'S'
    {0x00, 0x00, 0x3C, 0x40, 0x38, 0x04, 0x78, 0x00, 0x00, 0x00, 0x3C, 0x40, 0x38, 0x04, 0x78, 0x00},
    // Bitmap for 'T'
    {0x00, 0x00, 0x7C, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x7C, 0x10, 0x10, 0x10, 0x10, 0x00},
    // Bitmap for 'U'
    {0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x38, 0x00, 0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x38, 0x00},
    // Bitmap for 'V'
    {0x00, 0x00, 0x44, 0x44, 0x44, 0x28, 0x10, 0x00, 0x00, 0x00, 0x44, 0x44, 0x44, 0x28, 0x10, 0x00},
    // Bitmap for 'W'
    {0x00, 0x00, 0x44, 0x54, 0x54, 0x54, 0x28, 0x00, 0x00, 0x00, 0x44, 0x54, 0x54, 0x54, 0x28, 0x00},
    // Bitmap for 'X'
    {0x00, 0x00, 0x44, 0x28, 0x10, 0x28, 0x44, 0x00, 0x00, 0x00, 0x44, 0x28, 0x10, 0x28, 0x44, 0x00},
    // Bitmap for 'Y'
    {0x00, 0x00, 0x44, 0x28, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x44, 0x28, 0x10, 0x10, 0x10, 0x00},
    // Bitmap for 'Z'
    {0x00, 0x00, 0x7C, 0x08, 0x10, 0x20, 0x7C, 0x00, 0x00, 0x00, 0x7C, 0x08, 0x10, 0x20, 0x7C, 0x00}
};


const uint8_t font_numbers[10][8] = {
    // Bitmap for '0'
    {0x00, 0x3C, 0x44, 0x4C, 0x54, 0x64, 0x3C, 0x00},
    // Bitmap for '1'
    {0x00, 0x10, 0x30, 0x10, 0x10, 0x10, 0x38, 0x00},
    // Bitmap for '2'
    {0x00, 0x3C, 0x44, 0x08, 0x10, 0x20, 0x7C, 0x00},
    // Bitmap for '3'
    {0x00, 0x3C, 0x44, 0x0C, 0x04, 0x44, 0x3C, 0x00},
    // Bitmap for '4'
    {0x00, 0x08, 0x18, 0x28, 0x48, 0x7C, 0x08, 0x00},
    // Bitmap for '5'
    {0x00, 0x7C, 0x40, 0x78, 0x04, 0x44, 0x38, 0x00},
    // Bitmap for '6'
    {0x00, 0x3C, 0x40, 0x78, 0x44, 0x44, 0x38, 0x00},
    // Bitmap for '7'
    {0x00, 0x7C, 0x04, 0x08, 0x10, 0x20, 0x20, 0x00},
    // Bitmap for '8'
    {0x00, 0x38, 0x44, 0x38, 0x44, 0x44, 0x38, 0x00},
    // Bitmap for '9'
    {0x00, 0x38, 0x44, 0x44, 0x3C, 0x04, 0x38, 0x00}
};


const uint8_t font_space[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t font_special_chars[28][8] = {
    // Bitmap for '!'
    {0x00, 0x10, 0x10, 0x10, 0x10, 0x00, 0x10, 0x00},
    // Bitmap for '?'
    {0x00, 0x38, 0x44, 0x08, 0x10, 0x00, 0x10, 0x00},
    // Bitmap for '.'
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00},
    // Bitmap for ','
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x20},
    // Bitmap for ':'
    {0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00},
    // Bitmap for ';'
    {0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x10, 0x20},
    // Bitmap for '/'
    {0x00, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00, 0x00},
    // Bitmap for '\'
    {0x00, 0x40, 0x20, 0x10, 0x08, 0x04, 0x00, 0x00},
    // Bitmap for '('
    {0x00, 0x08, 0x10, 0x10, 0x10, 0x08, 0x00, 0x00},
    // Bitmap for ')'
    {0x00, 0x10, 0x08, 0x08, 0x08, 0x10, 0x00, 0x00},
    // Bitmap for '['
    {0x00, 0x38, 0x20, 0x20, 0x20, 0x38, 0x00, 0x00},
    // Bitmap for ']'
    {0x00, 0x1C, 0x04, 0x04, 0x04, 0x1C, 0x00, 0x00},
    // Bitmap for '{'
    {0x00, 0x08, 0x10, 0x20, 0x10, 0x08, 0x00, 0x00},
    // Bitmap for '}'
    {0x00, 0x10, 0x08, 0x04, 0x08, 0x10, 0x00, 0x00},
    // Bitmap for '<'
    {0x00, 0x00, 0x08, 0x10, 0x20, 0x10, 0x08, 0x00},
    // Bitmap for '>'
    {0x00, 0x00, 0x20, 0x10, 0x08, 0x10, 0x20, 0x00},
    // Bitmap for '='
    {0x00, 0x00, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x00},
    // Bitmap for '+'
    {0x00, 0x00, 0x10, 0x10, 0x7C, 0x10, 0x10, 0x00},
    // Bitmap for '-'
    {0x00, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00},
    // Bitmap for '*'
    {0x00, 0x00, 0x00, 0x28, 0x10, 0x28, 0x00, 0x00},
    // Bitmap for '@'
    {0x00, 0x00, 0x3C, 0x44, 0x5C, 0x40, 0x3C, 0x00},
    // Bitmap for '#'
    {0x00, 0x00, 0x28, 0x7C, 0x28, 0x7C, 0x28, 0x00},
    // Bitmap for '$'
    {0x00, 0x10, 0x38, 0x40, 0x38, 0x04, 0x38, 0x10},
    // Bitmap for '%'
    {0x00, 0x44, 0x48, 0x10, 0x20, 0x24, 0x44, 0x00},
    // Bitmap for '^'
    {0x00, 0x10, 0x28, 0x44, 0x00, 0x00, 0x00, 0x00},
    // Bitmap for '&'
    {0x00, 0x00, 0x38, 0x44, 0x38, 0x48, 0x34, 0x00},
    // Bitmap for '_'
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x00},
    // Bitmap for '|'
    {0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00}
};


const uint8_t* get_bitmap_for_char(char c) {
    switch(c) {
        case 'a' ... 'z':
            return font_lowercase[c - 'a'];
        case 'A' ... 'Z': 
            return font_uppercase[c - 'A'];
        case '0' ... '9':
            return font_numbers[c - '0'];
        case  ' ':
            return font_space;
        default:
            switch(c) {
                case '!':
                    return font_special_chars[0];
                case '?':
                    return font_special_chars[1];
                case '.':
                    return font_special_chars[2];
                case ',':
                    return font_special_chars[3];
                case ':':
                    return font_special_chars[4];
                case ';':
                    return font_special_chars[5];
                case '/':
                    return font_special_chars[6];
                case '\\':
                    return font_special_chars[7];
                case '(':
                    return font_special_chars[8];
                case ')':
                    return font_special_chars[9];
                case '[':
                    return font_special_chars[10];
                case ']':
                    return font_special_chars[11];
                case '{':
                    return font_special_chars[12];
                case '}':
                    return font_special_chars[13];
                case '<':
                    return font_special_chars[14];
                case '>':
                    return font_special_chars[15];
                case '=':
                    return font_special_chars[16];
                case '+':
                    return font_special_chars[17];
                case '-':
                    return font_special_chars[18];
                case '*':
                    return font_special_chars[19];
                case '@':
                    return font_special_chars[20];
                case '#':
                    return font_special_chars[21];
                case '$':
                    return font_special_chars[22];
                case '%':
                    return font_special_chars[23];
                case '^':
                    return font_special_chars[24];
                case '&':
                    return font_special_chars[25];
                case '_':
                    return font_special_chars[26];
                case '|':
                    return font_special_chars[27];
                default: 
                    return NULL;
            }
    }
}