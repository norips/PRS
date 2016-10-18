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

/*
 * 
 */
static void routine(int signo) {
    printf("Got %s\n", strsignal(signo));
}
int main(int argc, char** argv) {
    printf("PID = %d\n",getpid());
    for(int i = 0; i < NSIG; i++) {
        signal(i,routine);
    }
    while(1) {
        sleep(1);
    }
    
    return (EXIT_SUCCESS);
}

