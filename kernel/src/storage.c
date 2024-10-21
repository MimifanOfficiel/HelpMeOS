#include "includes/storage.h"
#include "includes/string.h"

#define BUFFER_SIZE (1024 * 1024) // 1 MB

static uint8_t buffer[BUFFER_SIZE]; // Static buffer
static size_t used_offset = 0;      // Tracks used memory



void *memcpy(void *dest, const void *src, size_t n) {
    uint8_t *pdest = (uint8_t *)dest;
    const uint8_t *psrc = (const uint8_t *)src;

    for (size_t i = 0; i < n; i++) {
        pdest[i] = psrc[i];
    }

    return dest;
}

void *memset(void *s, int c, size_t n) {
    uint8_t *p = (uint8_t *)s;

    for (size_t i = 0; i < n; i++) {
        p[i] = (uint8_t)c;
    }

    return s;
}

void *memmove(void *dest, const void *src, size_t n) {
    uint8_t *pdest = (uint8_t *)dest;
    const uint8_t *psrc = (const uint8_t *)src;

    if (src > dest) {
        for (size_t i = 0; i < n; i++) {
            pdest[i] = psrc[i];
        }
    } else if (src < dest) {
        for (size_t i = n; i > 0; i--) {
            pdest[i-1] = psrc[i-1];
        }
    }

    return dest;
}

int memcmp(const void *s1, const void *s2, size_t n) {
    const uint8_t *p1 = (const uint8_t *)s1;
    const uint8_t *p2 = (const uint8_t *)s2;

    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] < p2[i] ? -1 : 1;
        }
    }

    return 0;
}

void* malloc(size_t size) {
    if (used_offset + size > BUFFER_SIZE) {
        return NULL; // Not enough memory
    }
    
    void* ptr = &buffer[used_offset]; // Allocate from the buffer
    used_offset += size;               // Increment the used offset
    return ptr;
}


void* realloc(void* ptr, size_t size) {
    if (size == 0) {
        // Freeing behavior
        return NULL; // For this implementation, we cannot free memory
    }

    if (ptr == NULL) {
        return malloc(size); // Behave like malloc if ptr is NULL
    }

    // Find the original allocation
    uint8_t* original_ptr = (uint8_t*)ptr;
    size_t original_offset = original_ptr - buffer;

    // Check if the new size fits in the current buffer
    if (original_offset + size > BUFFER_SIZE) {
        return NULL; // Not enough memory
    }

    // If size is smaller or equal, just return the original pointer
    if (size <= (used_offset - original_offset)) {
        return ptr; // No need to move data
    }

    // Find a new position for the larger allocation
    size_t new_offset = used_offset;
    if (new_offset + size > BUFFER_SIZE) {
        return NULL; // Not enough memory
    }

    // Move the data to the new location
    memcpy(&buffer[new_offset], ptr, used_offset - original_offset);

    // Update the used offset
    used_offset = new_offset + size; // Update the used size

    return &buffer[new_offset]; // Return the pointer to the new memory
}



void free(void* ptr) {
    // To change once I made a better malloc implementation
    
    // In this simple implementation, free does not actually reclaim memory
    // It just sets the pointer to NULL for safety
    ptr = NULL;
}