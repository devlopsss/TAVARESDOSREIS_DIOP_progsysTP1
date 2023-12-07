//
// Created by ensea on 05/12/23.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#include <iostream>
#include <cstring>

#include <iostream>
#include <cstring>

#include <iostream>
#include <cstring>
#include <unistd.h>

int main() {
    char input[100];

    write(STDOUT_FILENO, "Bienvenue dans le programme shell simplifié. Tapez 'exit' pour quitter.\n", 72);

    while (true) {
        // Demander à l'utilisateur d'entrer une commande
        write(STDOUT_FILENO, "$ ", 2);
        ssize_t bytesRead = read(STDIN_FILENO, input, sizeof(input));

        // Quitter si Ctrl+D est pressé (EOF)
        if (bytesRead == 0) {
            write(STDOUT_FILENO, "Bye bye...\n", 10);
            break;
        }

        // Supprimer le saut de ligne à la fin de la commande
        input[strcspn(input, "\n")] = '\0';

        // Vérifier si l'utilisateur a saisi "exit"
        if (std::strcmp(input, "exit") == 0) {
            write(STDOUT_FILENO, "Bye bye...\n", 10);
            break;
        }

        // Exécuter la commande (dans cet exemple, simplement l'afficher)
        write(STDOUT_FILENO, "Commande non reconnue : ", 24);
        write(STDOUT_FILENO, input, bytesRead);
        write(STDOUT_FILENO, "\n", 1);
    }

    return 0;
}

