#include "includes/storage.h"
#include "includes/string.h"

#define BUFFER_SIZE (1024 * 1024) // 1 MB

static uint8_t buffer[BUFFER_SIZE]; // Static buffer
static size_t used_offset = 0;      // Tracks used memory


FileAllocationTable* createFileAllocationTable(size_t size) {
    FileAllocationTable* fat = malloc(sizeof(FileAllocationTable));
    fat->table = malloc(size * sizeof(int32_t));
    fat->size = size;
    memset(fat->table, 0, size * sizeof(int32_t));
    return fat;
}

void destroyFileAllocationTable(FileAllocationTable* fat) {
    free(fat->table);
    free(fat);
}

int allocate(FileAllocationTable* fat, size_t index, size_t length) {
    if (index + length > fat->size) {
        return -1;
    }

    for (size_t i = 0; i < length; i++) {
        if (fat->table[index + i] != 0) {
            return -1;
        }
    }

    for (size_t i = 0; i < length; i++) {
        fat->table[index + i] = 1;
    }

    return 0;
}

int deallocate(FileAllocationTable* fat, size_t index) {
    if (index >= fat->size) {
        return -1;
    }

    fat->table[index] = 0;
    return 0;
}

size_t getNextFreeBlock(const FileAllocationTable* fat) {
    for (size_t i = 0; i < fat->size; i++) {
        if (fat->table[i] == 0) {
            return i;
        }
    }

    return -1;
}

DirectoryTable* createDirectoryTable() {
    DirectoryTable* dt = malloc(sizeof(DirectoryTable));
    dt->entries = malloc(16 * sizeof(DirectoryEntry));
    dt->count = 0;
    dt->capacity = 16;
    return dt;
}

void destroyDirectoryTable(DirectoryTable* dt) {
    for (size_t i = 0; i < dt->count; i++) {
        free(dt->entries[i].filename);
    }
    free(dt->entries);
    free(dt);
}

int addEntry(DirectoryTable* dt, const char* filename, size_t startBlock, size_t length) {
    if (dt->count == dt->capacity) {
        dt->capacity *= 2;
        dt->entries = realloc(dt->entries, dt->capacity * sizeof(DirectoryEntry));
    }

    dt->entries[dt->count].filename = malloc(strlen(filename) + 1);
    strcpy(dt->entries[dt->count].filename, filename);
    dt->entries[dt->count].startBlock = startBlock;
    dt->entries[dt->count].length = length;
    dt->count++;
    return 0;
}

int removeEntry(DirectoryTable* dt, const char* filename) {
    size_t index = findEntry(dt, filename);
    if (index == (size_t)-1) {
        return -1;
    }

    free(dt->entries[index].filename);
    for (size_t i = index; i < dt->count - 1; i++) {
        dt->entries[i] = dt->entries[i + 1];
    }
    dt->count--;
    return 0;
}

size_t findEntry(const DirectoryTable* dt, const char* filename) {
    for (size_t i = 0; i < dt->count; i++) {
        if (strcmp(dt->entries[i].filename, filename) == 0) {
            return i;
        }
    }

    return -1;
}

// Define the File struct
typedef struct {
    char* filename;
    size_t startBlock;
    size_t length;
} File;

// Define the FileSystem struct
typedef struct {
    FileAllocationTable* fat;
    DirectoryTable* dt;
} FileSystem;

FileSystem* createFileSystem(size_t fatSize) {
    FileSystem* fs = malloc(sizeof(FileSystem));
    fs->fat = createFileAllocationTable(fatSize);
    fs->dt = createDirectoryTable();
    return fs;
}

void destroyFileSystem(FileSystem* fs) {
    destroyFileAllocationTable(fs->fat);
    destroyDirectoryTable(fs->dt);
    free(fs);
}

int createFile(FileSystem* fs, const char* filename, size_t length) {
    size_t startBlock = getNextFreeBlock(fs->fat);
    if (startBlock == (size_t)-1) {
        return -1;
    }

    if (addEntry(fs->dt, filename, startBlock, length) == -1) {
        return -1;
    }

    if (allocate(fs->fat, startBlock, length) == -1) {
        return -1;
    }

    return 0;
}

int deleteFile(FileSystem* fs, const char* filename) {
    size_t index = findEntry(fs->dt, filename);
    if (index == (size_t)-1) {
        return -1;
    }

    if (deallocate(fs->fat, fs->dt->entries[index].startBlock) == -1) {
        return -1;
    }

    if (removeEntry(fs->dt, filename) == -1) {
        return -1;
    }

    return 0;
}

File* openFile(FileSystem* fs, const char* filename) {
    size_t index = findEntry(fs->dt, filename);
    if (index == (size_t)-1) {
        return NULL;
    }

    File* file = malloc(sizeof(File));
    file->filename = malloc(strlen(filename) + 1);
    strcpy(file->filename, filename);
    file->startBlock = fs->dt->entries[index].startBlock;
    file->length = fs->dt->entries[index].length;
    return file;
}

void closeFile(File* file) {
    free(file->filename);
    free(file);
}

int readFile(FileSystem* fs, File* file, void* buffer, size_t length) {
    if (length > file->length) {
        return -1;
    }

    memcpy(buffer, fs->fat->table + file->startBlock, length);
    return 0;
}

int writeFile(FileSystem* fs, File* file, const void* buffer, size_t length) {
    if (length > file->length) {
        return -1;
    }

    memcpy(fs->fat->table + file->startBlock, buffer, length);
    return 0;
}




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

    // Move the data if necessary
    memmove(&buffer[original_offset], ptr, used_offset - original_offset);

    // Update the used offset
    used_offset = original_offset + size; // Update the used size

    return &buffer[original_offset]; // Return the pointer to the new memory
}


void free(void* ptr) {
    // To change once I made a better malloc implementation
    
    // In this simple implementation, free does not actually reclaim memory
    // It just sets the pointer to NULL for safety
    ptr = NULL;
}