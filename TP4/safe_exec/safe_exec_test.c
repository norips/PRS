/* 
 * File:   safe_exec_test.c
 * Author: rdruon
 *
 * Created on 8 novembre 2016, 10:04
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "safe_exec.h"
/*
 * 
 */
void g() {
    volatile int *a = NULL;
    char x = *a;
}
void f() {
    int r;
    r = essayer(g,SIGSEGV);
    if(r) {
        printf("Erreur durant l'execution.\n");
    } else {
        printf("L'execution de f s'est bien déroulé.\n");
    }
}
int main(int argc, char** argv) {
    int r;
    r = essayer(f,SIGSEGV);
    if(r) {
        printf("Erreur durant l'execution.\n");
    } else {
        printf("L'execution de f s'est bien déroulé.\n");
    }
    return (EXIT_SUCCESS);
}

