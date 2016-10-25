#include <signal.h>
#include <unistd.h>
#include <setjmp.h>

#include "executer-avant-delai.h"

jmp_buf buf;
void routine(int signo) {
    siglongjmp(buf,1);
}
int executer_avant_delai( void (*fun)(void *), void *parametre, int delai_en_seconde){
    if(sigsetjmp(buf,1) != 1) {
        alarm(delai_en_seconde);
        struct sigaction s;
        s.sa_handler = routine;
        s.sa_flags = 0;
        sigemptyset(&s.sa_mask);
        //Receive SIGALRM
        sigaction(SIGALRM,&s,NULL);
        fun(parametre);
        return 1;
    } else {
        return 0;
    }
    
}
