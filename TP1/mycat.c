#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h> // lseek
#include "tool/tools.h"

#define SIZE 2 // SIZE détermine par tranche de combien d'octets on doit lire le buffer d'entrée
/**
* Ici on lit tout ce qui se trouve dans l'entrée standard et on le sort sur la sortie standard.
*/
int main(int argc,char** argv) { //main est le point d'entré d'un programme C (et dans beaucoup d'autres langages aussi). C'est là que le programme débute. argc contient le nombre d'arguments passés en paramètre. argv est un tableau contenant les paramètres sous forme de tableau de caractère.
    int i, j = 0;
    char buff[SIZE];
    while ((i = read(0, buff, SIZE-1)) > 0) { // read lit un buffer (première param. 0 étant l'entrée standard) sur SIZE-1(Le dernier emplacement du tableau contiendra OEF voire plus loin) octets (param 3), stocke la valeur lue dans le param 2 et renvoie le nombre d'octets effectivement lus
        j += i; // j va contenir le nombre total d'octets lus
        buff[i] = '\0'; // on ajoute un caractère OEF à la fin du buffer contenant les données lues. 
        write(1, buff, i); // on écrit dans la sortie standard (1, premier param) la valeur de buff (param 2) sur i (i étant le nombre effectif d'octets lus) octets (param 3)
    }
    printf("\n %d octets lus\n", j); // On affiche le nombre total d'octets lus (renseigne toi sur printf)
    return (EXIT_SUCCESS); // on termine le programme en retournant une valeur disant que tout s'est bien passé
}
