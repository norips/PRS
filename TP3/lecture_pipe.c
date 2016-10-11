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
    //close(fd[1]);
    char c;
    if(write(fd[1],"c",sizeof(char)) == -1) {
        perror("write");
    }
    
    
    
    
    
    
    
    
    
    
    
    return (EXIT_SUCCESS);
}

