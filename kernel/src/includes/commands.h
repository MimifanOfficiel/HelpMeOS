#ifndef COMMANDS_H
#define COMMANDS_H

#include <stddef.h>
#include <limine.h>


// Function to exit the OS
void exit(void);

// Function to list files in the current directory
void listFiles(void);

// Function to change the current directory
void changeDirectory(const char* path);

// Function to display the current directory
void printWorkingDirectory(void);

// Function to execute a command
void executeCommand(struct limine_framebuffer* framebuffer, const char* command);

// Function to parse input command
char** parseCommand(struct limine_framebuffer* framebuffer, const char* input, size_t* count);

#endif // COMMANDS_H
