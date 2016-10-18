/* 
 * File:   calculer_offset.c
 * Author: rdruon
 *
 * Created on 18 octobre 2016, 09:37
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../TP1/tool/tools.h"

#define P 3
/*
 * 
 */
typedef double (*funtab_t)(double);
double ajouter_un_dizieme(double d){return d+0.1;}
double ajouter_un_centieme(double d){return d+0.01;}
double ajouter_un_millieme(double d){return d+0.001;}

funtab_t funtab[]={ajouter_un_millieme,ajouter_un_centieme,ajouter_un_dizieme,ajouter_un_millieme};

int main(int argc, char** argv) {
    checkParam(argc,2);
    int f_in = open(argv[1],O_RDONLY);
    int f_out = open(argv[2],O_CREAT | O_TRUNC | O_WRONLY,0666);
    int end = lseek(f_in,0,SEEK_END);
    lseek(f_in,0,SEEK_SET);
    int nb_of_elem = end / sizeof(double);
    int nb_elem_per_proc = nb_of_elem / P;
    for(int i = 0; i < P; i++) {
        if(fork() == 0) {
            int f_intmp = open(argv[1],O_RDONLY);
            int f_outtmp = open(argv[2],O_CREAT | O_WRONLY,0666);
            verif(lseek(f_intmp,i*nb_elem_per_proc*sizeof(double),SEEK_SET) == -1,"lseek in");
            verif(lseek(f_outtmp,i*nb_elem_per_proc*sizeof(double),SEEK_SET) == -1,"lseek out");
            for(int j = 0; j < nb_elem_per_proc; j++) {
                double d;
                verif(read(f_intmp,&d,sizeof(double)) < 0, "read");
                d = funtab[i](d);
                verif(write(f_outtmp,&d,sizeof(double)) == -1, "write");
            }
            exit(EXIT_SUCCESS);
                
        }
    }
    lseek(f_in,P*nb_elem_per_proc*sizeof(double),SEEK_SET);
    lseek(f_out,P*nb_elem_per_proc*sizeof(double),SEEK_SET);
    for(int i = 0; i < nb_of_elem % P;i++) {
        double d;
        verif(read(f_in,&d,sizeof(double)) < 0, "read");
        d = funtab[i](d);
        verif(write(f_out,&d,sizeof(double)) == -1, "write");
    }
    for(int i = 0; i < P; i++) {
        wait(NULL);
    }
            
    return (EXIT_SUCCESS);
}

