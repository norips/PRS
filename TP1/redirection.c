/* 
 * File:   redirection.c
 * Author: rdruon
 *
 * Created on 27 septembre 2016, 10:00
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "tool/tools.h"
/*
 * 
 */
void print() {
    printf("Test 1 \n");
    printf("Test 2 \n");
    printf("Test 3 \n");
    printf("Test 4 \n");
}

void rediriger_vers(void (*f) (void), char* file) {
    int back = dup(1); //On sauvegarde la sortie standard
    int fd = open(file,O_CREAT | O_WRONLY | O_TRUNC,0666); //On ouvre/créer un fichier en ecriture
    verif((fd == -1), "open file"); //On verifie l'ouverture
    verif(dup2(fd,1) == -1,"dup2"); //On verifie la duplication de fd dans 1, quand on écrira dans la sortie standard(1) cela ecrira sur le fichier(fd)
    f(); //On appel la fonction passé en paramètre
    verif(dup2(back,1) == -1,"dup2"); //On restaure la sortie standard sauvegardé
    close(fd);
}
int main(int argc, char** argv) {
    printf("Sortie standard 1\n");
    rediriger_vers(print,"test.log");
    printf("Sortie standard 2\n");
    return (EXIT_SUCCESS);
}

