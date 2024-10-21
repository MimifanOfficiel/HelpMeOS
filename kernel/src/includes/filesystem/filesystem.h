#ifndef FsSystem
#define FsSystem

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "../storage.h"

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


extern FileSystem* rootFileSystem;

FileSystem* createFileSystem(size_t fatSize);
void destroyFileSystem(FileSystem* fs);
int createFile(FileSystem* fs, const char* filename, size_t length);
int deleteFile(FileSystem* fs, const char* filename);
File* openFile(FileSystem* fs, const char* filename);
void closeFile(File* file);
int readFile(FileSystem* fs, File* file, void* buffer, size_t length);
int writeFile(FileSystem* fs, File* file, const void* buffer, size_t length);
char** listFiles(FileSystem* fs);



#endif