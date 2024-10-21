#ifndef COMMANDS_H
#define COMMANDS_H

#include <stddef.h>
#include <limine.h>


// Function to exit the OS
void exit(void);

// Function to change the current directory
void changeDirectory(const char* path);

// Function to display the current directory
void printWorkingDirectory(void);

// Function to execute a command
void executeCommand(struct limine_framebuffer* framebuffer, const char* command, const char** tokens);

// Function to parse input command
char** parseCommand(struct limine_framebuffer* framebuffer, const char* input, size_t* count);




void _createFile(struct limine_framebuffer *framebuffer, const char** tokens);
void _listFiles(struct limine_framebuffer *framebuffer, const char** tokens);
void _removeFile(struct limine_framebuffer *framebuffer, const char** tokens);

#endif // COMMANDS_H
