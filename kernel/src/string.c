#include "includes/string.h"
#include "includes/storage.h"
#include <stddef.h>


size_t strlen(const char *str) {
    const char *s = str;
    while (*s) s++;
    return s - str;
}

char *strcpy(char *dest, const char *src) {
    char *d = dest;
    while ((*d++ = *src++));
    return dest;
}

char *strcat(char *dest, const char *src) {
    char *d = dest;
    while (*d) d++;
    while ((*d++ = *src++));
    return dest;
}

int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

char *strchr(const char *str, int c) {
    while (*str) {
        if (*str == (char)c) return (char *)str;
        str++;
    }
    return c == 0 ? (char *)str : NULL;
}

char *strrchr(const char *str, int c) {
    const char *last = NULL;
    while (*str) {
        if (*str == (char)c) last = str;
        str++;
    }
    return c == 0 ? (char *)str : (char *)last;
}

char *strstr(const char *haystack, const char *needle) {
    if (!*needle) return (char *)haystack;
    for (; *haystack; haystack++) {
        if ((*haystack == *needle) && !strncmp(haystack, needle, strlen(needle))) {
            return (char *)haystack;
        }
    }
    return NULL;
}


int strncmp(const char *str1, const char *str2, size_t n) {
    while (n && *str1 && (*str1 == *str2)) {
        str1++;
        str2++;
        n--;
    }
    if (n == 0) {
        return 0;
    } else {
        return *(unsigned char *)str1 - *(unsigned char *)str2;
    }
}


char *strtok(char *str, const char *delim) {
    static char *last;
    if (str) {
        last = str;
    } else if (!last) {
        return NULL;
    }

    str = last + strspn(last, delim);
    if (*str == '\0') {
        last = NULL;
        return NULL;
    }

    last = str + strcspn(str, delim);
    if (*last) {
        *last++ = '\0';
    } else {
        last = NULL;
    }

    return str;
}

char *strdup(const char *str) {
    size_t len = strlen(str) + 1;
    char *copy = malloc(len);
    if (copy) {
        memcpy(copy, str, len);
    }
    return copy;
}

size_t strspn(const char *str1, const char *str2) {
    const char *s1 = str1;
    const char *s2;
    while (*s1) {
        for (s2 = str2; *s2; s2++) {
            if (*s1 == *s2) break;
        }
        if (!*s2) break;
        s1++;
    }
    return s1 - str1;
}

size_t strcspn(const char *str1, const char *str2) {
    const char *s1 = str1;
    const char *s2;
    while (*s1) {
        for (s2 = str2; *s2; s2++) {
            if (*s1 == *s2) return s1 - str1;
        }
        s1++;
    }
    return s1 - str1;
}
