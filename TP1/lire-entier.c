#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h> // lseek
#include "tool/tools.h"


int main(int argc, char** argv) {
    checkParam(argc, 2);
    int fd = open(argv[1], O_RDONLY);
    verif((fd == -1), "Open entier.txt");

    int pos = atoi(argv[2]);
    verif((lseek(fd, pos, SEEK_SET) == -1), "lseek");

    unsigned int i = 0;
    verif((read(fd, &i, sizeof (unsigned int)) == -1), "Can't read file");

    close(fd);
    printf("%u", i);
    return (EXIT_SUCCESS);
}
