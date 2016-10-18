/* 
 * File:   emettre-signaux.c
 * Author: rdruon
 *
 * Created on 18 octobre 2016, 11:19
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "../TP1/tool/tools.h"
/*
 * 
 */
int main(int argc, char** argv) {
    checkParam(argc,3);
    int pid = atoi(argv[1]);
    int k = atoi(argv[2]);
    for(int i = 0; i < k; i++) {
        for(int j = 0; (j+3) < argc; j++) {
            int sig = atoi(argv[3+j]);
            verif(sig == 0,"atoi sig");
            kill(pid,sig);
            usleep(100);
        }
    }
    return (EXIT_SUCCESS);
}

