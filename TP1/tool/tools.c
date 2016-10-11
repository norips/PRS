#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tools.h"

/*
* Vérifie la condition cond. Si elle est vérifiée, le message msg est affiché sur la sortie d'erreur standard et le programme se termine.
* En C, les booléens (vrai/faux) n'existent pas, on use à la place de simple entiers. faux = 0 et vrai correspond à toutes les valeurs autres que 0.
*/ 
void verif(int cond, const char* msg) {
    if (!cond)
        return;
    perror(msg); // Appel système indiquant qu'on affiche le message msg dans la sortie d'erreur
    exit(EXIT_FAILURE); // Qutte le programme avec le code de sortie EXIT_FAILURE
}

/**
* Vérifie que le nombre argc est supérieur à n. Si non, on affiche le message 'Need x parameters' et on quitte.
* Est utilisé pour tester si le nombre de paramètres passés à la commande compilée est suffisant.
*/
void checkParam(const int argc, int n) {
    if (argc > n)
        return;
    fprintf(stderr, "Need %d parameters\n", n);
    exit(EXIT_FAILURE);
}
