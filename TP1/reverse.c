#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h> // lseek
#include "tool/tools.h"

/**
* Ici on copie un fichier source dans un autre fichier en inversant l'odre de ses données
* usage: reverse fichier_source fichier_cible
*/

int main(int argc, char** argv) {
    checkParam(argc, 2);
    int fd1, fd2;
    fd1 = open(argv[1], O_RDONLY);
    verif((fd1 == -1), "Can't open input");
    fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    verif((fd2 == -1), "Can't open output");
    lseek(fd1, +1, SEEK_END);
    char buff;
    while (lseek(fd1, -2, SEEK_CUR) >= 0) {
        read(fd1, &buff, sizeof (char));
        verif((write(fd2, &buff, sizeof (char)) != sizeof (char)), "write");
    }
    return (EXIT_SUCCESS);
}
