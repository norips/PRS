/* 
 * File:   lecture_pipe.c
 * Author: rdruon
 *
 * Created on 4 octobre 2016, 09:20
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * 
 */
int main(int argc, char** argv) {
    int fd[2];
    pipe(fd);
    close(fd[1]);
    char c[256];
    if(read(fd[0],&c,256*sizeof(char)) == -1) {
        perror("read");
    }
    c[255] = '\0';
    printf("%s",c);
    
    return (EXIT_SUCCESS);
}

