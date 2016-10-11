/* 
 * File:   log.c
 * Author: rdruon
 *
 * Created on 11 octobre 2016, 09:46
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
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
    char buf[256];
    int n = 0;
    close(pip[1]);
    int file = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0666);
    while ((n = read(pip[0], buf, 255 * sizeof (char))) > 0) {
        buf[n] = '\0';
        write(file, buf, n);
        printf("%s", buf);
    }
    close(pip[0]);
    return (EXIT_SUCCESS);
}

