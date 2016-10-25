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
    printf("Child receive %d\n", signo);
}

int main(int argc, char** argv) {
    checkParam(argc,3);
    if ((child_pid = fork()) == 0) {
        struct sigaction s;
        s.sa_handler = routine2;
        s.sa_flags = 0;
        sigemptyset(&s.sa_mask);
        //Receive SIGUSR1
        sigaction(SIGUSR1,&s,NULL);
        //Fill mask
        sigset_t mask, old_mask;
        
        sigemptyset(&mask);
        sigaddset(&mask,SIGUSR1);
        //Block SIGUSR1
        sigprocmask(SIG_BLOCK,&mask,&old_mask);
        //Get ppid
        int ppid = getppid();
        
        //Get k
        int k = atoi(argv[1]);
        for(int i = 0; i < k; i++) {
            for(int j = 0; (j+2) < argc; j++) {
                //Get signo
                int sig = atoi(argv[2 + j]);
                verif(sig == 0,"atoi sig");
                //Send to parent
                kill(ppid,sig);
                //Wait for parent
                sigsuspend(&old_mask);
            }
        }
        kill(ppid,SIGKILL);
    } else {
        struct sigaction s;
        s.sa_handler = routine;
        sigemptyset(&s.sa_mask);
        s.sa_flags = 0;
        for(int i = 0; i < NSIG; i++) {
            sigaction(i,&s,NULL);
        }
        while (1) {
        }
    }
    return (EXIT_SUCCESS);
}

