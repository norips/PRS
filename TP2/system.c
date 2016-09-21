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
int main(int argc, char** argv) {
    checkParam(argc,1);
    verif((system(argv[1]) == -1),"system");
    return (EXIT_SUCCESS);
}

