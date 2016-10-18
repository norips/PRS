/* 
 * File:   strsignal.c
 * Author: rdruon
 *
 * Created on 18 octobre 2016, 10:23
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strsignal();
#include <signal.h>

/*
 * 
 */
int main(int argc, char** argv) {
    for(int i = 0; i < NSIG; i++) {
        printf("%2d : %s\n",i,strsignal(i));
    }
    return (EXIT_SUCCESS);
}

