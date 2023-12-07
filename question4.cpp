#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char input[100];
    int status;

    write(STDOUT_FILENO, "Bienvenue dans le programme shell simplifié.\n Tapez 'exit' pour quitter.\n", 73);

    while (true) {
        // recuperation de commande
        write(STDOUT_FILENO, "$ ", 2);
        ssize_t bytesRead = read(STDIN_FILENO, input, sizeof(input));


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

        // Exécution de la commande
        pid_t pid = fork();

        if (pid == 0) {
            //  child
            execlp(input, input, nullptr);


            perror("Error");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            // Échec du fork
            perror("Error");
        } else {
            // parent
            waitpid(pid, &status, 0);
        }

        // Affichage du code de retour ou le signal dans le prompt
        if (WIFEXITED(status)) {
            write(STDOUT_FILENO, " [exit:", 7);
            char exitCodeChar = WEXITSTATUS(status) + '0';
            write(STDOUT_FILENO, &exitCodeChar, 1);
            write(STDOUT_FILENO, "]\n", 2);
        } else if (WIFSIGNALED(status)) {
            write(STDOUT_FILENO, " [sign:", 8);
            char signalCodeChar = WTERMSIG(status) + '0';
            write(STDOUT_FILENO, &signalCodeChar, 1);
            write(STDOUT_FILENO, "]\n", 2);
        }
    }

    return 0;
}
