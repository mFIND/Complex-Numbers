#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "2.11.spis.h"
#define pi 3.141592653589793

/* funkcja pokazujaca w ktorym miejscu jest blad */
void blad(int n){
    int i;
    printf("Blad! ->  ");
    for(i=0;i<n;i++){printf(" ");}
    printf("^\n");
    return;
}
/*
Wylicza A i B do wzoru Aexp(Bjpi) majac dane a i b ze wzoru a+bj
*/
void postac_wykl(double *s_a, double *s_b){
    double z;
    /** printf("To jest test, suma_a i suma_b: %f %f\n", *a, *b); */
    if(*s_a== 0 && *s_b == 0) return;
    z=sqrt((*s_a)*(*s_a)+(*s_b)*(*s_b));
    if(*s_a>0){
        *s_b=asin((*s_b)/z)/pi;
        *s_a=z;
        return;
    }
    if(*s_b>0){
        *s_b=acos((*s_a)/z)/pi;
        *s_a=z;
        return;
    }
    *s_b=-acos((*s_a)/z)/pi;
    *s_a=z;
}
