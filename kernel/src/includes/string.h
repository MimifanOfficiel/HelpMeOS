#ifndef STRING_H
#define STRING_H

#include <stddef.h>

// Calculate the length of a string
size_t strlen(const char *str);

// Copy a string
char *strcpy(char *dest, const char *src);

// Concatenate two strings
char *strcat(char *dest, const char *src);

// Compare two strings
int strcmp(const char *str1, const char *str2);

// Find the first occurrence of a character in a string
char *strchr(const char *str, int c);

// Find the last occurrence of a character in a string
char *strrchr(const char *str, int c);

// Find the first occurrence of a substring in a string
char *strstr(const char *haystack, const char *needle);

// Compare two strings up to a specified number of characters
int strncmp(const char *str1, const char *str2, size_t n);

// Tokenize a string
char *strtok(char *str, const char *delim);

// Duplicate a string
char *strdup(const char *str);

// Calculate the length of the initial segment of str1 which consists entirely of characters in str2
size_t strspn(const char *str1, const char *str2);

// Calculate the length of the initial segment of str1 which consists entirely of characters not in str2
size_t strcspn(const char *str1, const char *str2);


#endif // STRING_H