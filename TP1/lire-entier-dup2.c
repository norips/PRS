#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h> // lseek
#include "tool/tools.h"


/**
* Ici on affiche l'entier situé à la position demandée dans un fichier
* usage: lire-entier fichier_à_lire position_à_laquelle_lire

*/
int main(int argc, char** argv) {
    checkParam(argc, 2);
    int fd = open(argv[1], O_RDONLY);
    int log = open("ERREURS-LIRE.log", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    verif((dup2(log,2) == -1), "dup2");
    verif((fd == -1), "Open entier.txt");

    int pos = atoi(argv[2]);
    verif((lseek(fd, pos, SEEK_SET) == -1), "lseek");

    unsigned int i = 0;
    verif((read(fd, &i, sizeof (unsigned int)) == -1), "Can't read file");

    close(fd);
    printf("%u", i);
    return (EXIT_SUCCESS);
}
