#include <signal.h>
#include <unistd.h>
#include <setjmp.h>

#include "executer-avant-delai.h"

sigjmp_buf buf;
void routine(int signo) {
    siglongjmp(buf,1);
}
int executer_avant_delai( void (*fun)(void *), void *parametre, int delai_en_seconde){
    if(sigsetjmp(buf,1)==0) {
        struct sigaction s;
        s.sa_handler = routine;
        s.sa_flags = 0;
        sigemptyset(&s.sa_mask);
        //Receive SIGALRM
        sigaction(SIGALRM,&s,NULL);
        alarm(delai_en_seconde);
        fun(parametre);
        return 1;
    } else {
        return 0;
    }
    
}
