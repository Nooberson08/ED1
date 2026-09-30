#include "calculadora.h"
#include <stdio.h>

int soma (int a, int b) {
    return a+b;
}

int subtracao (int a, int b){
    return a-b;
}

int multiplicacao (int a, int b) {
    return a*b;
}

float divisao (int a, int b){
   if (b==0){
    printf ("Divisor não pode ser 0");
   }
   else{
    return (float) a/b;
   }
        
    }
