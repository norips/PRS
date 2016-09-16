#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tools.h"
void verif(int cond, const char* msg) {
    if (!cond)
        return;
    perror(msg);
    exit(EXIT_FAILURE);
}

void checkParam(int argc, int n) {
    if (argc > n)
        return;
    fprintf(stderr, "Need %d parameters\n", n);
    exit(EXIT_FAILURE);
}
