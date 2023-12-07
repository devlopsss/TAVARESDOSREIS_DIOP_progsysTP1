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

        // On lit la commande
        ssize_t input_length = read(STDIN_FILENO, command, MAX_COMMAND_LENGTH);

        // On verifie si on doit arreter le processus (si l'entrée est "exit")
        if (strncmp(command, "exit", 4) == 0) {
            write(STDOUT_FILENO, "Au revoir!\n", 11);
            break;
        }

        // On enlève la ligne precedente
        command[input_length - 1] = '\0';

        // Execution de la comande
        pid_t pid = fork();

        if (pid == 0) {
            // Child 
            execlp(command, command, NULL);

            // If exec fails
            perror("Error");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            // Fork failed
            perror("Error");
        } else {
            // Parent 
            wait(NULL);
        }
    }

    return 0;
}
