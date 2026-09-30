#include <stdio.h>
#include "conversor.h"

int main (void){
   float metros;
   
    printf ("Informe o valor em metros para ser convertido: ");
    scanf ("%f", &metros);

    float cm = metroscentimetros (metros);
    float km = metrosquilometros (metros);
    float mm = metrosmilimetros  (metros);

   printf("\nResultados para %.2f metros:\n", metros);
    printf("- Centímetros: %.2f cm\n", cm);
    printf("- Quilómetros: %.6f km\n", km);
    printf("- Milímetros:  %.2f mm\n", mm);

    return 0;
}