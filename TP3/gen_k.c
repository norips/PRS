/* 
 * File:   gen_k.c
 * Author: rdruon
 *
 * Created on 11 octobre 2016, 10:12
 */

#include <stdio.h>
#include <stdlib.h>
#include "../TP1/tool/tools.h"
/*
 * 
 */
int main(int argc, char** argv) {
    checkParam(argc,1);
    int k = atoi(argv[1]);
    srand((unsigned)time(NULL));
    FILE *f = fopen("./genNb","wb");
    for(int i = 0; i < k; i++) {
        double X=((double)rand()/(double)RAND_MAX);
        fwrite(&X,sizeof(double),1,f);
    }
    fflush(f);
    fclose(f);
    
    return (EXIT_SUCCESS);
}

