#include "includes/commands.h"
#include "includes/keyboardhandler.h"

#include "includes/string.h"
#include "includes/storage.h"

void exit(void) {
    // Add any necessary cleanup code here
    // _exit(0);
}

void listFiles(void) {
    FileAllocationTable *fatTable = createFileAllocationTable(1024);
    DirectoryTable *dirTable = createDirectoryTable();

    // for (int i = 0; i < dirTable.entries; i++) {
    //     printf("%s\n", dirTable.entries[i].filename);
    // }
}

void changeDirectory(const char* path) {
    // Add code to change the current directory
    // chdir(path);
}

void printWorkingDirectory(void) {
    // char cwd[1024];
    // if (getcwd(cwd, sizeof(cwd)) != NULL) {
    //     printf("Current working directory: %s\n", cwd);
    // } else {
    //     perror("getcwd");
    // }
}

void executeCommand(struct limine_framebuffer* framebuffer, const char* command) {
    if (strcmp(command, "exit") == 0) {
        exit();
    } else if (strcmp(command, "hey") == 0) {
        draw_string(framebuffer, "Hey there!", 0x00FF);
    } else {
        draw_string(framebuffer, "Command not found", 0xFF0000);
    }
}

char** parseCommand(struct limine_framebuffer* framebuffer, const char* input, size_t* count) {
    // Add a leading space to handle cases where the input may not start with a delimiter
    char input_with_leading_space[strlen(input) + 1]; // +1 for the space and +1 for null terminator
    input_with_leading_space[0] = ' ';
    char** tokens = NULL;
    char* token;
    char* input_copy = strdup(input_with_leading_space); // Duplicate the input string
    size_t num_tokens = 0;

    if (input_copy == NULL) {
        draw_string(framebuffer, "\nMemory allocation failed", 0xFF0000);
        return NULL;
    }

    // Split the input string into tokens using space as a delimiter
    token = strtok(input_copy, " ");
    while (token != NULL) {
        // Resize the tokens array to hold the new token
        char** new_tokens = realloc(tokens, sizeof(char*) * (num_tokens + 1));
        if (new_tokens == NULL) {
            // Handle memory allocation failure
            draw_string(framebuffer, "\nMemory allocation failed", 0xFF0000);
            free(input_copy);
            free(tokens);
            return NULL;
        }
        tokens = new_tokens;

        // Allocate memory for the token and copy it
        tokens[num_tokens] = strdup(token);
        if (tokens[num_tokens] == NULL) {
            // Handle memory allocation failure
            draw_string(framebuffer, "\n 2nd Memory allocation failed", 0xFF0000);
            free(input_copy);
            for (size_t i = 0; i < num_tokens; i++) {
                free(tokens[i]); // Free previously allocated tokens
            }
            free(tokens);
            return NULL;
        }

        num_tokens++;
        token = strtok(NULL, " "); // Get the next token
    }

    free(input_copy); // Free the duplicated input string
    *count = num_tokens; // Set the count of tokens
    return tokens; // Return the array of tokens
}




