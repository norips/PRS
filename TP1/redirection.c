/* 
 * File:   redirection.c
 * Author: rdruon
 *
 * Created on 27 septembre 2016, 10:00
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "tool/tools.h"
/*
 * 
 */
void print() {
    printf("Test 1 \n");
    printf("Test 2 \n");
    printf("Test 3 \n");
    printf("Test 4 \n");
}
void rediriger_vers(void (*f) (void), char* file) {
    int back = dup(1);
    int fd = open(file,O_CREAT | O_WRONLY | O_TRUNC,0666);
    verif((fd == -1), "open file");
    verif(dup2(fd,1) == -1,"dup2");
    f();
    verif(dup2(back,1) == -1,"dup2");
    
}
int main(int argc, char** argv) {
    printf("Sortie standard 1\n");
    rediriger_vers(print,"test.log");
    printf("Sortie standard 2\n");
    return (EXIT_SUCCESS);
}

