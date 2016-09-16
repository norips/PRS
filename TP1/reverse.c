#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h> // lseek
#include "tool/tools.h"

int main(int argc, char** argv) {
    checkParam(argc, 2);
    int fd1, fd2;
    fd1 = open(argv[1], O_RDONLY);
    verif((fd1 == -1), "Can't open input");
    fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    verif((fd2 == -1), "Can't open output");
    lseek(fd1, -1, SEEK_END);
    char buff;
    while (read(fd1, &buff, sizeof (char)) > 0) {
        verif((write(fd2, &buff, sizeof (char)) != sizeof (char)), "write");
        if (lseek(fd1, -2, SEEK_CUR) == -1) {
            return (EXIT_SUCCESS);
        }
    }
    return (EXIT_SUCCESS);
}
