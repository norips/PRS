/* 
 * File:   hello-goodbye.c
 * Author: rdruon
 *
 * Created on 8 novembre 2016, 11:07
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../TP1/tool/tools.h"

void *HelloGoodbye(void *p) {
    printf("%p: bonjour\n", pthread_self());
    sleep(1);
    printf("%p: a bientot\n", pthread_self());

    return NULL;
}

int main(int argc, char *argv[]) {
    checkParam(argc,1);
    int k = atoi(argv[1]);
    pthread_t tab_thread[k];
    for(int i = 0; i < k; i++){
        pthread_create(&tab_thread[i],NULL,HelloGoodbye,NULL);
    }
    
    for(int i = 0; i < k; i++){
        pthread_join(tab_thread[i],NULL);
    }

    return EXIT_SUCCESS;
}