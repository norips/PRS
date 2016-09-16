#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h> // lseek
#include "tool/tools.h"


int main(int argc, char** argv) {
    checkParam(argc, 3);
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    verif((fd == -1), "Open entier.txt");

    int pos = atoi(argv[2]);
    unsigned int i = atoi(argv[3]);
    if (lseek(fd, pos , SEEK_SET) == -1) {
        perror("lseek");
        return (EXIT_FAILURE);
    }
    verif((write(fd, &i, sizeof (unsigned int)) == -1), "write");

    close(fd);
    return (EXIT_SUCCESS);
}
