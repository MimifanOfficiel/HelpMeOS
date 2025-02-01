#ifndef COMMANDS_H
#define COMMANDS_H

#include <stddef.h>
#include <limine.h>

typedef enum {
    CMD_CREATEFILE,
    CMD_REMOVEFILE,
    CMD_LISTFILES,
    CMD_WRITEFILE,
    CMD_READFILE,

    CMD_COUNT
} Commands;



typedef struct {
    struct limine_framebuffer *framebuffer;
    const char** args;
} CommandParams;




// Function to exit the OS
void exit(void);

// Function to change the current directory
void changeDirectory(const char* path);


void execute_command(const char* command, CommandParams params);


// Function to parse input command
char** parseCommand(struct limine_framebuffer* framebuffer, const char* input, size_t* count);




void _createFile(CommandParams params);
void _listFiles(CommandParams params);
void _removeFile(CommandParams params);
void _writeFile(CommandParams params);
void _readFile(CommandParams params);

#endif // COMMANDS_H
