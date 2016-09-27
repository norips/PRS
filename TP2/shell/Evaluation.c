#include "Shell.h"
#include "Evaluation.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <bits/fcntl-linux.h>

void
verifier(int cond, char *s) {
    if (!cond) {
        perror(s);
        exit(1);
    }
}

int
evaluer_expr(Expression *e) {
    if (e == NULL) return -1;
    int pid,stat;
    switch (e->type) {

        case VIDE:
            break;

        case SIMPLE:
            pid = fork();
            if(pid == 0) {
                execvp(e->arguments[0],e->arguments);
                perror("exec");
            }
            wait(&stat);
            break;

        case REDIRECTION_I:
            {
            int fd = open(e->arguments[0],O_RDONLY);
            int back = dup(0);
            verifier((fd != -1),"open");
            verifier((dup2(fd,0) != -1),"dup2");
            evaluer_expr(e->droite);
            evaluer_expr(e->gauche);
            verifier((dup2(back,0) != -1),"dup2");
            close(fd);
            break;
            }
        case REDIRECTION_O:
            {
            int fd = open(e->arguments[0],O_CREAT | O_WRONLY | O_TRUNC, 0666);
            int back = dup(1);
            verifier((fd != -1),"open");
            verifier((dup2(fd,1) != -1),"dup2");
            evaluer_expr(e->droite);
            evaluer_expr(e->gauche);
            verifier((dup2(back,1) != -1),"dup2");
            close(fd);
            break;
            }
                    
        case REDIRECTION_A:
            {
            int fd = open(e->arguments[0],O_CREAT | O_WRONLY | O_APPEND, 0666);
            int back = dup(1);
            verifier((fd != -1),"open");
            verifier((dup2(fd,1) != -1),"dup2");
            evaluer_expr(e->droite);
            evaluer_expr(e->gauche);
            verifier((dup2(back,1) != -1),"dup2");
            close(fd);
            break;
            }
        case REDIRECTION_E:
            {
            int fd = open(e->arguments[0],O_CREAT | O_WRONLY | O_TRUNC, 0666);
            int back = dup(2);
            verifier((fd != -1),"open");
            verifier((dup2(fd,2) != -1),"dup2");
            evaluer_expr(e->droite);
            evaluer_expr(e->gauche);
            verifier((dup2(back,2) != -1),"dup2");
            close(fd);
            break;
            }
        case REDIRECTION_EO:
            {
            int fd = open(e->arguments[0],O_CREAT | O_WRONLY | O_APPEND, 0666);
            int back = dup(1);
            int backerr = dup(2);
            verifier((fd != -1),"open");
            verifier((dup2(fd,1) != -1),"dup2");
            verifier((dup2(fd,2) != -1),"dup2");
            evaluer_expr(e->droite);
            evaluer_expr(e->gauche);
            verifier((dup2(back,1) != -1),"dup2");
            verifier((dup2(backerr,2) != -1),"dup2");
            close(fd);
            break;
            }
        case BG:
            {
            pid = fork();
            if(pid == 0) {
                evaluer_expr(e->gauche);
                exit(EXIT_SUCCESS);
            }
            break;
            }
        case PIPE:
            {
                int pfd[2];
                pipe(pfd);
                int stdi = dup(0);
                int stdo = dup(1);
                int pid = fork();
                if(pid == 0){
                    dup2(pfd[0], 0); /* connect the read side with stdin */
                    evaluer_expr(e->droite);
                    exit(EXIT_SUCCESS);
                } else if (pid > 0) {
                    dup2(pfd[1], 1); /* connect the write side with stdin */
                    evaluer_expr(e->gauche);
                    int stat;
                    wait(&stat); // Block here
                }
                dup2(stdi,0);
                dup2(stdo,1);
                printf("test\n");
                break;
            }
        default:
            break;
    }
    return 1;
}
