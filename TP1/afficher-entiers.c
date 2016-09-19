#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h> // lseek
#include "tool/tools.h"

/**
* Ici on affiche les entiers générées avec generer-entier et on les affiche sur la sortie standard
* usage: afficher-entiers (fichier à lire, optionnel)
*/

int main(int argc, char** argv) {
    int fd;
    if(argc < 2) {
	fd = open("entier.txt", O_RDONLY); // on ouvre entier.txt si aucun fichier n'est précisé en argument de la commande
    } else {
    	fd = open(argv[1], O_RDONLY); // Si argument il y a, on ouvre le fichier passé en paramètre
    }    
    verif((fd == -1), "Open entier.txt"); 
    unsigned int i = 0;
    while (read(fd, &i, sizeof (unsigned int)) > 0) { // on lit toutes les valeurs dans le fichier
        printf("%u\n", i); // on les affiche
    }
    close(fd); // on ferme le fichier
    return (EXIT_SUCCESS);
}
