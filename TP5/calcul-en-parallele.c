#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX  10000000
double resultat[MAX];
int nb_threads;

void *Calculate(void *p) {
    int n = *((int*)p);
    for(int i = n*MAX/nb_threads; i < (n+1)*MAX/nb_threads-1;i++){
        resultat[i] = acos(cos((double) i));
    }
    return NULL;
}
int main(int argc, char *argv[]) {
    nb_threads = atoi(argv[1]);

    pthread_t tab_thread[nb_threads];
    
    for (int i = 0; i < nb_threads; i++) {
        int *n = malloc(sizeof(int));
        *n = i;
        pthread_create(tab_thread + i, NULL, Calculate, n);
    }

    for (int i = 0; i < nb_threads; i++) {
        pthread_join(tab_thread[i], NULL);
    }

    return EXIT_SUCCESS;
}
