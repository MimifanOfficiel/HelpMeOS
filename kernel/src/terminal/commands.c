#include "includes/terminal/commands.h"
#include "includes/terminal/terminal.h"

#include "includes/string.h"
#include "includes/storage.h"
#include "includes/filesystem/filesystem.h"

void exit(void) {
    // Add any necessary cleanup code here
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


void (*command_functions[CMD_COUNT])(CommandParams) = {
    _createFile,
    _removeFile,
    _listFiles
};

const char *command_strings[CMD_COUNT] = {
    "touch",
    "rm",
    "ls"
};


void execute_command(const char *command, CommandParams params) {
    for (int i = 0; i < CMD_COUNT; i++) {
        if (strcmp(command, command_strings[i]) == 0) {
            command_functions[i](params); // Call the corresponding function
            return;
        }
    }
    draw_string(params.framebuffer, "\nCommand not found", start_x, &currentX, &currentY, 0xFF0000);
}


void _createFile(CommandParams params) {
    
    if (params.args[1] == NULL) {
        draw_string(params.framebuffer, "\nInvalid command format", start_x, &currentX, &currentY, 0xFF0000);
        return;
    }

    const char* filename = params.args[1];
    if (filename == NULL) {
        draw_string(params.framebuffer, "\nFilename not specified", start_x, &currentX, &currentY, 0xFF0000);
        return;
    }

    

    if (createFile(rootFileSystem, filename, 128) == 0) {
        draw_string(params.framebuffer, "\nFile created successfully", start_x, &currentX, &currentY, 0x00FF00);
    } else {
        draw_string(params.framebuffer, "\nFailed to create file", start_x, &currentX, &currentY, 0xFF0000);
    }
}


void _listFiles(CommandParams params) {
    
    if (rootFileSystem == NULL) {
        draw_string(params.framebuffer, "\nFailed to access filesystem", start_x, &currentX, &currentY, 0xFF0000);
        return;
    }

    char **fileList = listFiles(rootFileSystem);
    if (fileList == NULL) {
        draw_string(params.framebuffer, "\nNo files found", start_x, &currentX, &currentY, 0xFF0000);
        return;
    }

    draw_string(params.framebuffer, "\nFiles in current directory:", start_x, &currentX, &currentY, 0x00FF00);
    for (int i = 0; fileList[i] != NULL; i++) {
        draw_string(params.framebuffer, "\n", start_x, &currentX, &currentY, textColor);
        draw_string(params.framebuffer, fileList[i], start_x, &currentX, &currentY, textColor);
    }

}


void _removeFile(CommandParams params) {
    if (rootFileSystem == NULL) {
        draw_string(params.framebuffer, "\nFailed to access filesystem", start_x, &currentX, &currentY, 0xFF0000);
        return;
    }

    const char* filename = params.args[1];
    if (filename == NULL) {
        draw_string(params.framebuffer, "\nFilename not specified", start_x, &currentX, &currentY, 0xFF0000);
        return;
    }

    if (deleteFile(rootFileSystem, filename) == 0) {
        draw_string(params.framebuffer, "\nFile removed successfully", start_x, &currentX, &currentY, 0x00FF00);
    } else {
        draw_string(params.framebuffer, "\nFailed to remove file", start_x, &currentX, &currentY, 0xFF0000);
    }
}



// void executeCommand(struct limine_framebuffer* framebuffer, const char* command, const char** tokens) {
//     if (strcmp(command, "exit") == 0) {
//         exit();
//     } else if (strcmp(command, "touch") == 0) {
//         _createFile(framebuffer, tokens);
//     } else if(strcmp(command, "ls") == 0) {
//         _listFiles(framebuffer, tokens);
//     } else if (strcmp(command, "rm") == 0) {
//         _removeFile(framebuffer, tokens);
//     } else {
//         draw_string(framebuffer, "\n", start_x, &currentX, &currentY, textColor);
//         draw_string(framebuffer, prefix, start_x, &currentX, &currentY, textColor);
//         draw_string(framebuffer, "Command not found", start_x, &currentX, &currentY, 0xFF0000);
//     }
// }

char** parseCommand(struct limine_framebuffer* framebuffer, const char* input, size_t* count) {
    // Duplication sécurisée de l'entrée
    char* input_copy = strdup(input); // Duplique l'entrée (chaîne originale)
    if (input_copy == NULL) {
        draw_string(framebuffer, "\nMemory allocation failed", start_x, &currentX, &currentY, 0xFF0000);
        return NULL;
    }

    char** tokens = NULL;
    char* token;
    size_t num_tokens = 0;

    // Premier token
    token = strtok(input_copy, " ");
    while (token != NULL) {
        // Redimensionner le tableau de tokens
        char** new_tokens = realloc(tokens, sizeof(char*) * (num_tokens + 1));
        if (new_tokens == NULL) {
            // Gestion de l'échec de la réallocation mémoire
            draw_string(framebuffer, "\nMemory allocation failed", start_x, &currentX, &currentY, 0xFF0000);
            free(input_copy);
            for (size_t i = 0; i < num_tokens; i++) {
                free(tokens[i]); // Libérer les tokens alloués
            }
            free(tokens);
            return NULL;
        }
        tokens = new_tokens;

        // Copier chaque token dans une nouvelle mémoire séparée
        tokens[num_tokens] = strdup(token);
        if (tokens[num_tokens] == NULL) {
            // Gestion de l'échec de l'allocation mémoire
            draw_string(framebuffer, "\nToken memory allocation failed", start_x, &currentX, &currentY, 0xFF0000);
            free(input_copy);
            for (size_t i = 0; i < num_tokens; i++) {
                free(tokens[i]); // Libérer les tokens alloués
            }
            free(tokens);
            return NULL;
        }

        num_tokens++;
        token = strtok(NULL, " "); // Obtenir le prochain token
    }

    free(input_copy); // Libérer la copie de l'entrée d'origine

    *count = num_tokens; // Mettre à jour le nombre de tokens
    return tokens; // Retourner le tableau des tokens
}





