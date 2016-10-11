/* 
 * File:   vrai-pipe.c
 * Author: rdruon
 *
 * Created on 4 octobre 2016, 08:48
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../TP1/tool/tools.h"
/*
 * 
 */
int main(int argc, char** argv) {
    checkParam(argc,2);
    int fd[2];
    pipe(fd);
    int statl=0;
    int statr=0;
    if(fork() == 0) {
        close(fd[1]);
        dup2(fd[0],0);
        execvp(argv[2],(argv+2));
        perror("right");
    } else {
        if(fork()) {
            close(fd[0]);
            dup2(fd[1],1);
            execlp(argv[1],argv[1],NULL);
            perror("left");
        } else {
            wait(&statr);
        }
        wait(&statl);
    }
    return WEXITSTATUS(statl) == 0 ? WEXITSTATUS(statr) : WEXITSTATUS(statl);
}

