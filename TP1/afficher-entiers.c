#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h> // lseek
#include "tool/tools.h"



int main(int argc, char** argv) {
    int fd;
    if(argc < 2) {
	fd = open("entier.txt", O_RDONLY);
    } else {
    	fd = open(argv[1], O_RDONLY);
    }    
    verif((fd == -1), "Open entier.txt");
    unsigned int i = 0;
    while (read(fd, &i, sizeof (unsigned int)) > 0) {
        printf("%u\n", i);
    }
    close(fd);
    return (EXIT_SUCCESS);
}
