#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>

#include "safe_exec.h"

sigjmp_buf buf;

void routine(int signo) {
    siglongjmp(buf,1);
}
int essayer(void (*fun)(void),int sig){
    if(sigsetjmp(buf,1)==0) {
        struct sigaction s;
        s.sa_handler = routine;
        sigemptyset(&s.sa_mask);
        s.sa_flags=0;
        sigaction(sig,&s,NULL);
        fun();
        return 0;
    } else {
        return -1;
    }
}
