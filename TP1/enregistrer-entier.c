#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h> // lseek
#include "tool/tools.h"

/**
* Ecrit un entier dans le fichier à la position précisée
* usage: enregistrer-entier fichier_à_modifier position_à_laquelle_écrire valeur_à_ecrire
*/


int main(int argc, char** argv) {
    checkParam(argc, 3);
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666); // On ouvre le fichier
    verif((fd == -1), "Open entier.txt");

    int pos = atoi(argv[2]); // pos contient la position à laquelle on va écrire dans le fichier
    unsigned int i = atoi(argv[3]); // i contient la valeur que l'on va écrire dans le fichier
    if (lseek(fd, pos , SEEK_SET) == -1) { // On positionne le "curseur" d'écriture à la position pos, et on vérifie si tout s'est bien passé.
        perror("lseek");
        return (EXIT_FAILURE); //Si probleme, on affiche lseek dans la sortie d'erreur et on quitte le programme
    }
    verif((write(fd, &i, sizeof (unsigned int)) == -1), "write"); // On écrit i dans le fichier tout en vérifiant si tout s'est bien passé (voir tool/tool.c)

    close(fd); // on ferme le fichier 
    return (EXIT_SUCCESS);
}
