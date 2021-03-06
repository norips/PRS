#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX 16

typedef bool echiquier[MAX][MAX];


static bool ok(int n, int ligne, int colonne, echiquier e);

void
nreines(int n, int ligne, echiquier e, int *cpt) {
    for (int col = 0; col < n; col++)
        if (ok(n, ligne, col, e)) {
            if (ligne == n - 1)
                (*cpt)++;
            else {
                bool present = false;
                if (e[ligne][col]) {
                    present = true;
                }
                e[ligne][col] = true;
                nreines(n, ligne + 1, e, cpt);
                if (!present)
                    e[ligne][col] = false;
            }
        }
}

static bool
ok(int n, int ligne, int colonne, echiquier e) {
    int l, c;
    for (l = 0; l < ligne; l++)
        if (e[l][colonne])
            return false;

    for (l = ligne - 1, c = colonne - 1; l >= 0 && c >= 0; l--, c--)
        if (e[l][c])
            return false;

    for (l = ligne - 1, c = colonne + 1; l >= 0 && c <= n; l--, c++)
        if (e[l][c])
            return false;
    return true;
}

void
usage(char *s) {
    fprintf(stderr, "%s entier entier", s);
    exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[]) {
    echiquier e;
    int cpt = 0;
    char *endptr;

    if (argc < 3)
        usage(argv[0]);

    int n = strtoul(argv[1], &endptr, 10);
    if (*endptr != 0)
        usage(argv[1]);

    int start = strtol(argv[2], &endptr, 10);
    if (*endptr != 0)
        usage(argv[1]);

    memset(e, 0, sizeof (e));
    e[0][start % 16] = true;
    nreines(n, 0, e, &cpt);
    printf("res : %d\n", cpt);
    int file = open("/tmp/nreine", O_WRONLY | O_CREAT, 0666);
    lseek(file, start * sizeof (int), SEEK_SET);
    write(file, &cpt, sizeof (int));

    return EXIT_SUCCESS;
}


