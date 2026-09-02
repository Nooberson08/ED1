#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int i, tamanho = 10;
    int *vetor = (int*) malloc(tamanho*sizeof(int));
    if(vetor==NULL){
        printf("ERRO NA ALOCAÇÃO!");
        exit(1);
    }
    else{
        printf("vetor alocado!\n");
    }
    for(i=0; i<tamanho; i++){
        vetor[i] = i;
        printf("%d \t", vetor[i]);
    }
    return 0;
}