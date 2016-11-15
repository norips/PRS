#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>

#include "safe_exec.h"

sigjmp_buf *current;

void routine(int signo) {
    siglongjmp(*current,1);
}
int essayer(void (*fun)(void),int sig){
    sigjmp_buf new, *old;
    old = current;
    current = &new;
    if(sigsetjmp(current,1)==0) {
        struct sigaction s;
        s.sa_handler = routine;
        sigemptyset(&s.sa_mask);
        s.sa_flags=0;
        sigaction(sig,&s,NULL);
        fun();
        current = old;
        return 0;
    } else {
        current = old;
        return -1;
    }
}
