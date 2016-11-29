#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#define MAX 16

typedef bool echiquier[MAX][MAX];


static bool ok(int n, int ligne, int colonne, echiquier e);

typedef struct struct_param {
    int n;
    echiquier e;
    int *cpt;
    int current;
} struct_param;

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

void* threadFunc(void *n) {
    struct_param *param = (struct_param*) n;
    nreines(param->n, 0, param->e, param->cpt);
    return NULL;
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
    fprintf(stderr, "%s entier", s);
    exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[]) {
    int cpt = 0;
    char *endptr;

    if (argc < 2)
        usage(argv[0]);

    int n = strtoul(argv[1], &endptr, 10);

    if (*endptr != 0)
        usage(argv[1]);
    pthread_t tab_thread[n];
    struct_param tab_param[n];
    for (int i = 0; i < n; i++) {
        tab_param[i].cpt = malloc(sizeof (int));
        *tab_param[i].cpt = 0;
        tab_param[i].n = n;
        tab_param[i].current = i;
        memset(tab_param[i].e, 0, sizeof (tab_param[i].e));
        tab_param[i].e[0][i % 16] = true;
    }
    for (int i = 0; i < n; i++) {
        pthread_create(tab_thread + i, NULL, threadFunc, tab_param + i);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(tab_thread[i], NULL);
    }
    for (int i = 0; i < n; i++) {
        cpt+=*tab_param[i].cpt;
    }
    printf("%d\n", cpt);

    return EXIT_SUCCESS;
}

