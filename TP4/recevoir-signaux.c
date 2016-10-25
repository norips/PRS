/* 
 * File:   recevoir-sigaux.c
 * Author: rdruon
 *
 * Created on 18 octobre 2016, 10:49
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define _XOPEN_SOURCE 700
/*
 * 
 */
static void routine(int signo) {
    printf("Got %s\n", strsignal(signo));
}
int main(int argc, char** argv) {
    printf("PID = %d\n",getpid());
    struct sigaction s;
    s.sa_handler = routine;
    sigemptyset(&s.sa_mask);
    s.sa_flags = 0;
    for(int i = 0; i < NSIG; i++) {
        sigaction(i,&s,NULL);
    }
    while(1) {
        sleep(1);
    }
    
    return (EXIT_SUCCESS);
}

