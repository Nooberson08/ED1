#include <stdio.h>
#include <stdlib.h>
int main(void) { 
    int numero; 
    int*ponteiro= NULL;
    printf("DIGITE UM VALOR"); 
    scanf("%d", &numero);
    ponteiro=&numero;
printf("numero=%d \n ponteiro = %p");
return 0;
}