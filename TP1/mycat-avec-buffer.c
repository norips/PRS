#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h> // lseek
#include "tool/tools.h"


int main(int argc, char** argv) {
    char buff;
    while (fread(&buff, 1, 1, stdin) > 0) {
        fwrite(&buff, 1, 1, stdout);
    }
    return (EXIT_SUCCESS);
}
