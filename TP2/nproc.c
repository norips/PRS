#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h> // lseek
#include <sys/wait.h> //wait
#include "../TP1/tool/tools.h"


int main(int argc,char** argv) { 
    checkParam(argc,1);
    int n = atoi(argv[1]);
    int pid = 0;
    for(int i = 0 ; i < n ; i++) {
        pid = fork();
        if(pid == 0) {
            int son_pid = getpid();
            printf("je m'appelle %d et je suis le numero %d\n",son_pid,i);
            return(EXIT_SUCCESS);
        } else {
            int stat;
            wait(&stat);
        }
    }
    return (EXIT_SUCCESS); // on termine le programme en retournant une valeur disant que tout s'est bien passé
}
