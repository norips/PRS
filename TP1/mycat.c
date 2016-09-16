#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h> // lseek
#include "tool/tools.h"
int n = 1;
int main(int argc,char** argv) {
    int i, j = 0;
    char *buff;
    buff = malloc(sizeof (char)*(n + 1));
    while ((i = read(0, buff, n)) > 0) {
        j += i;
        buff[n] = '\0';
        write(1, buff, n);
    }
    printf("\n %d octets lus\n", j);
    free(buff);
    return (EXIT_SUCCESS);
}
