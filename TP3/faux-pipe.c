#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h> // lseek
#include <sys/wait.h> //wait
#include "../TP1/tool/tools.h"

int main(int argc, char** argv) {
    checkParam(argc, 2);
    if (fork() == 0) {
        int temp = open("./temp", O_CREAT | O_TRUNC | O_WRONLY, 0666);
        dup2(temp, 1);
        execlp(argv[1], argv[1], NULL);
        perror("right");
    } else {
        wait(NULL);
        if (fork() == 0) {
            int temp = open("./temp", O_RDONLY);
            dup2(temp, 0);
            execvp(argv[2], (argv + 2));
            perror("left");
        } else {
            wait(NULL);
        }
    }
    return (EXIT_SUCCESS); // on termine le programme en retournant une valeur disant que tout s'est bien passé
}

