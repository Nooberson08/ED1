// EXERCÍCIO DE PRÁTICA DAS FUNÇÕES MALLOC, REALLOC E STRUCT



#include <stdio.h>
#include <stdlib.h>

typedef struct item { // DEFININDO A STRUCT E MUDANDO SEU NOME PARA ITEM COM O TYPEDEF
    char nome [50];
    int quantidade;
} item; 

int main (){ 
    int capacidade = 2; // DEFININDO A CAPACIDADE INICIAL DO VETOR
    item *inventario = (item*) malloc(capacidade * sizeof(item)); // ALOCANDO MEMÓRIA PARA O VETOR DE ITENS

    if (inventario == NULL) { // VERIFICANDO SE A ALOCAÇÃO DE MEMÓRIA FOI BEM-SUCEDIDA
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    printf("Digite o nome do item: ");
    scanf(" %49[^\n]", inventario[0].nome); // LENDO O NOME DO ITEM

    printf("Digite a quantidade do item: ");
    scanf("%d", &inventario[0].quantidade); // LENDO A QUANTIDADE DO ITEM

    printf("Digite o nome do item 2: ");
    scanf(" %49[^\n]", inventario[1].nome); // LENDO O NOME DO ITEM 2

    printf("Digite a quantidade do item 2 ");
    scanf("%d", &inventario[1].quantidade); // LENDO A QUANTIDADE DO ITEM 2

    capacidade = 4; // AUMENTANDO A CAPACIDADE DO VETOR PARA 4

    item *temp = (item *) realloc(inventario, capacidade * sizeof(item)); // REALOCANDO MEMÓRIA PARA O VETOR DE ITENS

    if (temp == NULL) { // VERIFICANDO SE A REALOCAÇÃO DE MEMÓRIA FOI BEM-SUCEDIDA
        printf("Erro ao realocar memória.\n");
        free(inventario); // LIBERANDO A MEMÓRIA ALOCADA ANTERIORMENTE
        return 1;
    }
    inventario = temp;

    printf("Digite o nome do item 3: ");
    scanf(" %49[^\n]", inventario[2].nome); // LENDO O NOME DO ITEM 3   

    printf("Digite a quantidade do item 3: ");
    scanf("%d", &inventario[2].quantidade); // LENDO A QUANTIDADE DO ITEM 3

    printf("Digite o nome do item 4: ");
    scanf(" %49[^\n]", inventario[3].nome); // LENDO O NOME DO ITEM 4

    printf("Digite a quantidade do item 4: ");
    scanf("%d", &inventario[3].quantidade); // LENDO A QUANTIDADE DO ITEM 4
    
    return 0;
}