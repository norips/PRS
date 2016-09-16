#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h> // lseek
#include "tool/tools.h"


int main(int argc, char** argv) {
    checkParam(argc, 1);
    int n = atoi(argv[1]);
    fprintf(stderr, "%d", n);
    int fd = open("./entier.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    verif((fd == -1), "Open entier.txt");

    for (unsigned int i = 0; i < n; i++) {
        write(fd, &i, sizeof (unsigned int));
    }
    close(fd);
    return (EXIT_SUCCESS);
}
