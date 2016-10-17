/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   afficher_bin.c
 * Author: norips
 *
 * Created on 17 octobre 2016, 16:12
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*
 * 
 */
int main(int argc, char** argv) {
    double d;
    while(read(0,&d,sizeof(double))) {
        printf("%lf\n",d);
    }
    return (EXIT_SUCCESS);
}

