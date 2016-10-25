/* 
 * File:   longjmp.c
 * Author: rdruon
 *
 * Created on 25 octobre 2016, 11:12
 */

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

/*
 * 
 */
jmp_buf buf;
void f() {
    longjmp(buf,1);
}

void g() { // Not working inside a function if the function exited
    setjmp(buf);
}
int main(int argc, char** argv) {
    volatile int i;
    setjmp(buf);
        printf("%d\n",i);
        i++;
        if(i < 10){
            f();
        }
    return (EXIT_SUCCESS);
}

