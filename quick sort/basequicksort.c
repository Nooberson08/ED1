//CÓDIGO ADAPTADOR DE: https://pt.wikipedia.org/wiki/Quicksort#C++
//CODIGO USADO PARA REALIZAR UMA ORDENAÇÃO EM QUICK SORT, QUE CONSISTE EM
//ORDENAR UM CONJUNTO DE ELEMENTOS, ELEGENDO UM DESSES ELEMENTOS COMO PIVÔ,
//E A PARTIR DESSE PIVÔ, VERIFICAR QUAIS ELEMENTOS SÃO MAIORES OU MENORES E ASSIM ORDENALOS DA SEGUINTE FORMA:
//ELEMENTOS MENORES QUE O PIVÔ FICAM A ESQUERDA E OS MAIORES A DIREITA. 



#include <stdio.h>
#include <stdlib.h>

// Função Quicksort adaptada
void quicksort(int values[], int begin, int end) { 
    // Caso base: se a sublista tiver 0 ou 1 elemento, já está ordenada 
    if (begin >= end - 1) return; 
    
    int i = begin; 
    int j = end - 1; 
    
    // Escolha do pivô (elemento central) 
    int pivo = values[begin + (end - begin) / 2]; 
    int aux; 
    
    while (i <= j) { 
        while (i < end && values[i] < pivo) i++; 
        while (j >= begin && values[j] > pivo) j--; 
        
        if (i <= j) { 
            // Troca os elementos de posição 
            aux = values[i]; 
            values[i] = values[j]; 
            values[j] = aux; 
            i++; 
            j--; 
        } 
    } 
    
    // Chamadas recursivas para as duas metades 
    if (begin < j) quicksort(values, begin, j + 1); 
    if (i < end) quicksort(values, i, end); 
} 

int main() { 
    // Vetor de teste estático (fixo no código) 
    // Correção: alterado de array[2] para array[10] pois há 10 elementos
    int array[10] = {5, 8, 1, 2, 7, 3, 6, 9, 4, 10}; 
    
    printf("Array antes da ordenacao: "); 
    for (int i = 0; i < 10; i++) { 
        printf("%d ", array[i]); 
    } 
    printf("\n"); 
    
    // Executa a ordenacao 
    quicksort(array, 0, 10); 
    
    printf("Array ordenado: "); 
    for (int i = 0; i < 10; i++) { 
        printf("%d ", array[i]); 
    } 
    printf("\n"); 
    
    return 0; 
}