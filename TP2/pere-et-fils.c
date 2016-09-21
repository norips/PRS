#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h> // lseek
#include "../TP1/tool/tools.h"


int main(int argc,char** argv) { 
    int pid = 0;
    int father_pid = getpid();
    pid = fork();
    if(pid == 0) {
        int son_pid = getpid();
        printf("je m'appelle %d et je suis le fils de %d\n",son_pid,father_pid);
    } else {
        printf("je m'appelle %d et je suis le pere de %d\n",father_pid,pid);
    }
    return (EXIT_SUCCESS); // on termine le programme en retournant une valeur disant que tout s'est bien passé
}
