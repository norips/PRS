/* 
 * File:   taille_buffer_pipe.c
 * Author: rdruon
 *
 * Created on 4 octobre 2016, 09:04
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
 * 
 */
int main(int argc, char** argv) {
    int fd[2];
    pipe(fd);//max 65535
    long nbOctet = atol(argv[1]);
    for(long i = 0 ; i < nbOctet;i++) {
        if(write(fd[1],"c",sizeof(char)) == -1) {
            perror("write");
        }
        printf("%ld\n",i);
    }
    close(fd[1]);
    char c;
    int n=0;
    int i;
    while((i = read(fd[0],&c,sizeof(char)))>0) {
        n+=i;
    }
    printf("Read %d byte on %ld write\n",n,nbOctet);
    return (EXIT_SUCCESS);
}

