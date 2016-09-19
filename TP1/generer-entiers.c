#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h> // lseek
#include "tool/tools.h"

/**
* Génère une suite d'entiers et la stocke dans le fichier entier.txt
* usage: generer-entiers nb_entier_à_generer
*/

int main(int argc, char** argv) {
    checkParam(argc, 1); // on check si l'user a bien passé suffisament de paramètres (va voir dans tool/tools.c)
    int n = atoi(argv[1]); // atoi convertit une tableau de char en entier. n va contenir le nombre d'entiers à générer.
    fprintf(stderr, "%d", n);
    int fd = open("./entier.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666); // On ouvre le fichier entier.txt, avec les modes "ecrire uniquement, créer si existe pas, ajouter à la fin"
    verif((fd == -1), "Open entier.txt"); // on vérifie si l'ouverture s'est bien passée

    for (unsigned int i = 0; i < n; i++) {
        write(fd, &i, sizeof (unsigned int)); // On écrit i dans le fichier fd
    }
    close(fd); // on ferme le fichier fd
    return (EXIT_SUCCESS);
}
