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

typedef int (*fptr)(void); // pointeur de fonction
fptr g[N];

int fonc() {
    double d;
    int res = nombre_suivant(&d);
    d = d * 0.68 + d * 0.458;
    write(STDOUT_FILENO, &d, sizeof (double));
    return res;
}

int main(int argc, char** argv) {
    checkParam(argc, 2);
    int f = open("./genNb", O_RDONLY);
    for (int i = 0; i < N; i++) {
        g[i] = &fonc;
    }
    int pip[2];
    int stdout = dup(1);
    pipe(pip);
    dup2(f,0);
    if(fork() == 0){
        close(pip[1]);
        dup2(pip[0],0);
        close(pip[0]);
        int pip2[2];
        pipe(pip2);
        close(pip2[0]);
        dup2(pip2[1],1);
        if(fork() == 0){
            close(pip2[1]);
            dup2(pip2[0],0);
            close(pip2[0]);
            int pip3[2];
            pipe(pip3);
            close(pip3[0]);
            dup2(pip3[1],1);
            close(pip3[1]);
            if(fork() == 0){
                close(pip3[1]);
                dup2(pip3[0],0);
                close(pip3[0]);
                while(!g[2]()){}
            }
            while(!g[1]()){}
        }
    }
    while(!g[0]()){}
    wait(NULL);
    return (EXIT_SUCCESS);
}

