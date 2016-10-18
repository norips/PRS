/* 
 * File:   signayx-pere-fils.c
 * Author: rdruon
 *
 * Created on 18 octobre 2016, 11:29
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "../TP1/tool/tools.h"
/*
 * 
 */

int child_pid;
static void routine(int signo) {
    printf("Receive sig nb : %d\n",signo);
    kill(child_pid,SIGUSR1);
}

static void routine2(int signo) {
}
int main(int argc, char** argv) {
    checkParam(argc,3);
    if ((child_pid = fork()) == 0) {
        sigset_t mask;
        sigfillset(&mask);
        sigdelset(&mask,SIGUSR1);
        int pid = getppid();
        int k = atoi(argv[1]);
        signal(SIGUSR1,routine2);
        for(int i = 0; i < k; i++) {
            for(int j = 0; (j+2) < argc; j++) {
                int sig = atoi(argv[2+j]);
                verif(sig == 0,"atoi sig");
                kill(pid,sig);
                sigsuspend(&mask);
                printf("Continue\n");
            }
        }
        kill(pid,SIGKILL);
    } else {
        for (int i = 0; i < NSIG; i++) {
            signal(i, routine);
        }
        while (1) {
        }
    }
    return (EXIT_SUCCESS);
}

