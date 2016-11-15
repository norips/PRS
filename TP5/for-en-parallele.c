/* 
 * File:   for-en-parallele.c
 * Author: rdruon
 *
 * Created on 15 novembre 2016, 11:42
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
/*
 * 
 */
unsigned long k=0;
static pthread_mutex_t mutex_stock = PTHREAD_MUTEX_INITIALIZER;
#define MAX 1000
void* Calculate(void *n){
    pthread_mutex_lock(&mutex_stock);
    for(unsigned long i = 0; i < MAX; i++)
        k++;
    pthread_mutex_unlock(&mutex_stock);
}
int main(int argc, char** argv) {
    int nb_threads = atoi(argv[1]);

    pthread_t **tab_thread = malloc(nb_threads * sizeof (pthread_t*));
    
    for (int i = 0; i < nb_threads; i++) {
        tab_thread[i] = malloc(sizeof (pthread_t));
        pthread_create(tab_thread[i], NULL, Calculate, NULL);
    }
    
    for (int i = 0; i < nb_threads; i++) {
        pthread_join(*tab_thread[i], NULL);
    }
    printf("%ld",k);
    return (EXIT_SUCCESS);
}

