#include "includes/filesystem/filesystem.h"
#include "includes/string.h"

FileSystem* rootFileSystem = NULL;

FileAllocationTable* createFileAllocationTable(size_t size) {
    FileAllocationTable* fat = (FileAllocationTable*)malloc(sizeof(FileAllocationTable));
    if (!fat) return NULL;
    fat->table = (int32_t*)malloc(size * sizeof(int32_t));
    if (!fat->table) {
        free(fat);
        return NULL;
    }
    fat->size = size;
    memset(fat->table, -1, size * sizeof(int32_t)); // Initialize all entries to -1 (free)
    return fat;
}

void destroyFileAllocationTable(FileAllocationTable* fat) {
    if (fat) {
        free(fat->table);
        free(fat);
    }
}

int allocate(FileAllocationTable* fat, size_t index, size_t length) {
    if (index + length > fat->size) return -1;
    for (size_t i = 0; i < length; ++i) {
        if (fat->table[index + i] != -1) return -1; // Block already allocated
    }
    for (size_t i = 0; i < length; ++i) {
        fat->table[index + i] = (i == length - 1) ? -1 : (int32_t)(index + i + 1);
    }
    return 0;
}

int deallocate(FileAllocationTable* fat, size_t index) {
    if (index >= fat->size || fat->table[index] == -1) return -1;
    while (index != (size_t)-1) {
        int32_t next = fat->table[index];
        fat->table[index] = -1;
        index = next;
    }
    return 0;
}

size_t getNextFreeBlock(const FileAllocationTable* fat) {
    for (size_t i = 0; i < fat->size; ++i) {
        if (fat->table[i] == -1) return i;
    }
    return (size_t)-1; // No free block found
}

DirectoryTable* createDirectoryTable() {
    DirectoryTable* dt = (DirectoryTable*)malloc(sizeof(DirectoryTable));
    if (!dt) return NULL;
    dt->entries = (DirectoryEntry*)malloc(10 * sizeof(DirectoryEntry));
    if (!dt->entries) {
        free(dt);
        return NULL;
    }
    dt->count = 0;
    dt->capacity = 10;
    return dt;
}

void destroyDirectoryTable(DirectoryTable* dt) {
    if (dt) {
        for (size_t i = 0; i < dt->count; ++i) {
            free(dt->entries[i].filename);
        }
        free(dt->entries);
        free(dt);
    }
}

int addEntry(DirectoryTable* dt, const char* filename, size_t startBlock, size_t length) {
    if (dt->count >= dt->capacity) {
        dt->capacity *= 2;
        DirectoryEntry* newEntries = (DirectoryEntry*)realloc(dt->entries, dt->capacity * sizeof(DirectoryEntry));
        if (!newEntries) return -1;
        dt->entries = newEntries;
    }
    dt->entries[dt->count].filename = strdup(filename);
    if (!dt->entries[dt->count].filename) return -1;
    dt->entries[dt->count].startBlock = startBlock;
    dt->entries[dt->count].length = length;
    dt->count++;
    return 0;
}

int removeEntry(DirectoryTable* dt, const char* filename) {
    for (size_t i = 0; i < dt->count; ++i) {
        if (strcmp(dt->entries[i].filename, filename) == 0) {
            free(dt->entries[i].filename);
            dt->entries[i] = dt->entries[dt->count - 1];
            dt->count--;
            return 0;
        }
    }
    return -1;
}

size_t findEntry(const DirectoryTable* dt, const char* filename) {
    for (size_t i = 0; i < dt->count; ++i) {
        if (strcmp(dt->entries[i].filename, filename) == 0) {
            return i;
        }
    }
    return (size_t)-1;
}


FileSystem* createFileSystem(size_t fatSize) {
    FileSystem* fs = (FileSystem*)malloc(sizeof(FileSystem));
    if (!fs) return NULL;
    fs->fat = createFileAllocationTable(fatSize);
    if (!fs->fat) {
        free(fs);
        return NULL;
    }
    fs->dt = createDirectoryTable();
    if (!fs->dt) {
        destroyFileAllocationTable(fs->fat);
        free(fs);
        return NULL;
    }
    return fs;
}

void destroyFileSystem(FileSystem* fs) {
    if (fs) {
        destroyFileAllocationTable(fs->fat);
        destroyDirectoryTable(fs->dt);
        free(fs);
    }
}

int createFile(FileSystem* fs, const char* filename, size_t length) {
    size_t startBlock = getNextFreeBlock(fs->fat);
    if (startBlock == (size_t)-1 || allocate(fs->fat, startBlock, length) != 0) return -1;
    if (addEntry(fs->dt, filename, startBlock, length) != 0) {
        deallocate(fs->fat, startBlock);
        return -1;
    }
    return 0;
}

int deleteFile(FileSystem* fs, const char* filename) {
    size_t entryIndex = findEntry(fs->dt, filename);
    if (entryIndex == (size_t)-1) return -1;
    size_t startBlock = fs->dt->entries[entryIndex].startBlock;
    if (deallocate(fs->fat, startBlock) != 0) return -1;
    if (removeEntry(fs->dt, filename) != 0) return -1;
    return 0;
}

File* openFile(FileSystem* fs, const char* filename) {
    size_t entryIndex = findEntry(fs->dt, filename);
    if (entryIndex == (size_t)-1) return NULL;
    File* file = (File*)malloc(sizeof(File));
    if (!file) return NULL;
    file->filename = strdup(filename);
    if (!file->filename) {
        free(file);
        return NULL;
    }
    file->startBlock = fs->dt->entries[entryIndex].startBlock;
    file->length = fs->dt->entries[entryIndex].length;
    return file;
}

void closeFile(File* file) {
    if (file) {
        free(file->filename);
        free(file);
    }
}


int readFile(FileSystem* fs, File* file, void* buffer, size_t length) {
    if (length > file->length) return -1; // Trying to read beyond file length

    size_t blockIndex = file->startBlock;
    size_t bytesRead = 0;
    uint8_t* buf = (uint8_t*)buffer;

    while (blockIndex != (size_t)-1 && bytesRead < length) {
        // Assuming each block is of fixed size, e.g., 512 bytes
        size_t blockSize = 512;
        size_t bytesToRead = (length - bytesRead > blockSize) ? blockSize : (length - bytesRead);

        // Placeholder for actual block read logic
        // This would involve reading from the block at blockIndex
        // and copying the data into buf + bytesRead
        // For example: readBlock(fs, blockIndex, buf + bytesRead, bytesToRead);

        bytesRead += bytesToRead;
        blockIndex = fs->fat->table[blockIndex];
    }

    return (bytesRead == length) ? 0 : -1;
}


int writeFile(FileSystem* fs, File* file, const void* buffer, size_t length) {
    if (length > file->length) return -1; // Trying to write beyond file length

    size_t blockIndex = file->startBlock;
    size_t bytesWritten = 0;
    const uint8_t* buf = (const uint8_t*)buffer;

    while (blockIndex != (size_t)-1 && bytesWritten < length) {
        // Assuming each block is of fixed size, e.g., 512 bytes
        size_t blockSize = 512;
        size_t bytesToWrite = (length - bytesWritten > blockSize) ? blockSize : (length - bytesWritten);

        // Placeholder for actual block write logic
        // This would involve writing to the block at blockIndex
        // and copying the data from buf + bytesWritten
        // For example: writeBlock(fs, blockIndex, buf + bytesWritten, bytesToWrite);

        bytesWritten += bytesToWrite;
        blockIndex = fs->fat->table[blockIndex];
    }

    return (bytesWritten == length) ? 0 : -1;
}



char** listFiles(FileSystem* fs) {
    if (!fs || !fs->dt) return NULL;

    char** fileList = (char**)malloc((fs->dt->count + 1) * sizeof(char*));
    if (!fileList) return NULL;

    for (size_t i = 0; i < fs->dt->count; ++i) {
        fileList[i] = strdup(fs->dt->entries[i].filename);
        if (!fileList[i]) {
            for (size_t j = 0; j < i; ++j) {
                free(fileList[j]);
            }
            free(fileList);
            return NULL;
        }
    }
    fileList[fs->dt->count] = NULL; // Null-terminate the list

    return fileList;
}


