#include "geometria.h"
#include <stdio.h>

int main (void){
    float R;

    float Bt, Ht;
    
    float Br, Hr;
     

    printf ("Informe o valor para calcular a area do seu circulo: ");
    scanf ("%f", &R);
    printf ("A area do circulo e: %.2f\n\n", Acirculo(R));

    printf ("Informe a base e a altura para calcular a area do triangulo: ");
    scanf ("%f %f", &Bt, &Ht);
    printf("A area do triangulo e: %.2f\n\n", Atriangulo(Bt, Ht));

    printf ("Informe a base e a altura para calcular a area do retangulo: ");
    scanf ("%f %f", &Br, &Hr);
    printf("A area do retangulo e: %.2f\n\n", Aretangulo(Br, Hr));

return 0;
}