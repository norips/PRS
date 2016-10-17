/* 
 * File:   calculer.c
 * Author: rdruon
 *
 * Created on 11 octobre 2016, 10:26
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../TP1/tool/tools.h"
/*
 * 
 */
#define N 3

int nombre_suivant(double *d) {
    if (read(STDIN_FILENO, d, sizeof (double)) <= 0)
        return -1;
    return 0;
}

typedef double (*funtab_t)(double);
double ajouter_un_dizieme(double d){return d+0.1;}
double ajouter_un_centieme(double d){return d+0.01;}
double ajouter_un_millieme(double d){return d+0.001;}

funtab_t funtab[]={ajouter_un_millieme,ajouter_un_centieme,ajouter_un_dizieme,ajouter_un_millieme};
void closeP(int pipe[][2],int n) {
    for(int i = 0;i < n; i++) {
        close(pipe[i][0]);
        close(pipe[i][1]);
    }
}
int main(int argc, char** argv) {
    int pip[N][2];
    int stdout = dup(1);
    for(int i = 0; i < N; i++) {
        pipe(pip[i]);
    }
    
    for (int i = 0; i < N; i++) {
        if(fork() == 0){
            if(i!=0) {
                dup2(pip[i][0],0);
            }
            if(i != N-1) {
                dup2(pip[i+1][1],1);
            }
            closeP(pip,N);
            double d;
            while(nombre_suivant(&d) != -1){
                d = funtab[i](d);
                //fprintf(stderr,"funtab %d = %lf",i,d);
                write(STDOUT_FILENO,&d,sizeof(double));
            }
            wait(NULL);
            exit(EXIT_SUCCESS);
        }
    }
    wait(NULL);
    return (EXIT_SUCCESS);
}

