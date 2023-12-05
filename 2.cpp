//
// Created by ensea on 05/12/23.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main() {
    char command[MAX_COMMAND_LENGTH];
    char welcome_message[] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
    char prompt[] = "enseash % ";

    write(STDOUT_FILENO, welcome_message, strlen(welcome_message));

    while (1) {
        write(STDOUT_FILENO, prompt, strlen(prompt));

        // Read user input
        ssize_t input_length = read(STDIN_FILENO, command, MAX_COMMAND_LENGTH);

        // Check for the exit command
        if (strncmp(command, "exit", 4) == 0) {
            write(STDOUT_FILENO, "Au revoir!\n", 11);
            break;
        }

        // Remove the newline character at the end
        command[input_length - 1] = '\0';

        // Execute the command
        pid_t pid = fork();

        if (pid == 0) {
            // Child process
            execlp(command, command, NULL);

            // If exec fails
            perror("Error");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            // Fork failed
            perror("Error");
        } else {
            // Parent process
            wait(NULL);
        }
    }

    return 0;
}
