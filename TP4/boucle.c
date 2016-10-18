/* 
 * File:   boucle.c
 * Author: rdruon
 *
 * Created on 18 octobre 2016, 10:42
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "../TP1/tool/tools.h"

static void routine(int signo) {
    //Ignore interrupt
    printf("you can't stop me !\n");
}
/*
 * 
 */
int main(int argc, char** argv) {
    verif(signal(SIGINT,routine) == SIG_ERR,"signal");
    while(1) {
        sleep(1);
    }
    return (EXIT_SUCCESS);
}

