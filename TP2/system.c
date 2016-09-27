/* 
 * File:   system.c
 * Author: rdruon
 *
 * Created on 21 septembre 2016, 14:44
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // lseek
#include <sys/wait.h> //wait
#include "../TP1/tool/tools.h"

/*
 * 
 */
int System(char* command) {
    int pid = fork();
    if(pid == 0) {
        execl("/bin/sh","/bin/sh","-c",command,NULL);
    }
    int stat;
    wait(&stat);
    return stat;
}
int main(int argc, char** argv) {
    checkParam(argc, 1);
    verif((System(argv[1]) == -1), "system");
    return (EXIT_SUCCESS);
}

