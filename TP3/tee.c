/* 
 * File:   tee.c
 * Author: rdruon
 *
 * Created on 11 octobre 2016, 09:59
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
    checkParam(argc,1);
    int file = open(argv[1],O_CREAT | O_TRUNC | O_WRONLY,0666);
    int n;
    char buf[256];
    while((n = read(STDIN_FILENO,buf,255*sizeof(char))) > 0) {
        write(file,buf,n);
        buf[n] = '\0';
        printf("%s",buf);
    }
    close(file);
    return (EXIT_SUCCESS);
}

