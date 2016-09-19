#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h> // lseek
#include "tool/tools.h"


/**
* Ici on lit tout ce qui se trouve dans l'entrée standard et on le sort sur la sortie standard.
*/
int n = 1; // n détermine par tranche de combien d'octets on doit lire le buffer d'entrée
int main(int argc,char** argv) { //main est le point d'entré d'un programme C (et dans beaucoup d'autres langages aussi). C'est là que le programme débute. argc contient le nombre d'arguments passés en paramètre. argv est un tableau contenant les paramètres sous forme de tableau de caractère.
    int i, j = 0;
    char *buff;
    buff = malloc(sizeof (char)*(n + 1)); // Alors ça c'est un truc de barbu et pas justifié ici m'enfin (Enfin si un peu pour une histoire de valeur n variable mais une const preproco aurait suffit), c'est une allocation mémoire. Pas nécessaire de t'embrouiller avec ça maintenant.
    while ((i = read(0, buff, n)) > 0) { // read lit un buffer (première param. 0 étant l'entrée standard) sur n octets (param 3), stocke la valeur lue dans le param 2 et renvoie le nombre d'octets effectivement lus
        j += i; // j va contenir le nombre total d'octets lus
        buff[n] = '\0'; // on ajoute un caractère OEF à la fin du buffer contenant les données lues. 
        write(1, buff, n); // on écrit dans la sortie standard (1, premier param) la valeur de buff (param 2) sur n octets (param 3)
    }
    printf("\n %d octets lus\n", j); // On affiche le nombre total d'octets lus (renseigne toi sur printf)
    free(buff); // On désalloue buff, je maintiens que c'est un gros truc de barbu :P
    return (EXIT_SUCCESS); // on termine le programme en retournant une valeur disant que tout s'est bien passé
}
