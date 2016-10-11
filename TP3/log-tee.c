/* 
 * File:   log-tee.c
 * Author: rdruon
 *
 * Created on 11 octobre 2016, 10:04
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../TP1/tool/tools.h"
/*
 * 
 */
int main(int argc, char** argv) {
    checkParam(argc, 2);
    int pip[2];
    pipe(pip);
    int pid = fork();
    if (pid == 0) {
        close(pip[0]);
        dup2(pip[1], STDOUT_FILENO);
        close(pip[1]);
        execvp(argv[2], (argv + 2));
        perror("fils");
    }
    close(pip[1]);
    dup2(pip[0],STDIN_FILENO);
    close(pip[0]);
    execl("/net/cremi/rdruon/prs/PRS/TP3/bin/tee","tee",argv[1]);
    return (EXIT_SUCCESS);
}

