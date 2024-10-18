#ifndef STORAGE_H
#define STORAGE_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// Define the FileAllocationTable struct
typedef struct {
    int32_t* table;
    size_t size;
} FileAllocationTable;

FileAllocationTable* createFileAllocationTable(size_t size);
void destroyFileAllocationTable(FileAllocationTable* fat);
int allocate(FileAllocationTable* fat, size_t index, size_t length);
int deallocate(FileAllocationTable* fat, size_t index);
size_t getNextFreeBlock(const FileAllocationTable* fat);

// Define the DirectoryTable struct
typedef struct {
    char* filename;
    size_t startBlock;
    size_t length;
} DirectoryEntry;

typedef struct {
    DirectoryEntry* entries;
    size_t count;
    size_t capacity;
} DirectoryTable;

DirectoryTable* createDirectoryTable();
void destroyDirectoryTable(DirectoryTable* dt);
int addEntry(DirectoryTable* dt, const char* filename, size_t startBlock, size_t length);
int removeEntry(DirectoryTable* dt, const char* filename);
size_t findEntry(const DirectoryTable* dt, const char* filename);


// GCC and Clang reserve the right to generate calls to the following
// 4 functions even if they are not directly called.
// Implement them as the C specification mandates.
// DO NOT remove or rename these functions, or stuff will eventually break!
// They CAN be moved to a different .c file.

void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void* malloc(size_t size);
void* realloc(void* ptr, size_t size);

int memcmp(const void *s1, const void *s2, size_t n);

void free(void* ptr);




#endif // STORAGE_H
