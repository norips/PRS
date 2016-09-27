/* 
 * File:   execute.c
 * Author: rdruon
 *
 * Created on 27 septembre 2016, 09:34
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
    checkParam(argc, 1);
    printf("*** Execution \n");
    int pid = fork();
    if(pid == 0) {
        int res = execvp(argv[1], (argv + 1));
        verif(res != -1, "execvp");
    }
    int status;
    wait(&status);
    printf("code retour %d\n",WEXITSTATUS(status));
    return (EXIT_SUCCESS);
}

