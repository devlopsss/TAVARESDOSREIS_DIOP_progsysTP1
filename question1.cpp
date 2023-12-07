//
// Created by ensea on 07/12/23.
//

#include <unistd.h>
#include <string.h>

int main() {
    // le  message d'accueil
    const char welcomeMessage[] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
    write(STDOUT_FILENO, welcomeMessage, sizeof(welcomeMessage) - 1);

    // je crée une boucle pour le prompt
    while (1) {
        // Prompt
        const char prompt[] = "enseash % ";
        write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);

        // Déclaration d'un tableau de caractères pour stocker la commande de l'utilisateur
        char commande[100];

        // Lire la commande de l'utilisateur
        read(STDIN_FILENO, commande, sizeof(commande));

        // Supprimer le saut de ligne (\n) à la fin de la commande
        commande[strcspn(commande, "\n")] = '\0';

        // Vérifier si l'utilisateur a saisi "exit" pour quitter
        if (strcmp(commande, "exit") == 0) {
            // Sortir de la boucle si l'utilisateur veut quitter
            break;
        }

        // Traitement de la commande (ici, on peut ajouter du code pour exécuter la commande)

    }

    return 0;
}


