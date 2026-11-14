#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

int main() {
    Pilha pilha;

    inicializar(&pilha);

    int opcao, valor;

    do {
        printf("Menu\n"
               "0 - Sair\n"
               "1 - Esta Vazia?\n"
               "2 - Push\n"
               "3 - Pop\n"
               "4 - Peek\n"
               "5 - Imprimir Pilha\n"
               "6 - Contar Elementos\n");

        scanf("%d", &opcao);

        printf("\n");

        switch(opcao) {
            case 0:
                break;
            case 1:
                estaVazia(&pilha);
                break;
            case 2:
                printf("Informe o valor a ser inserido: ");
                scanf("%d", &valor);
                push(&pilha, valor);
                break;
            case 3:
                valor = pop(&pilha);
                break;
            case 4:
                peek(&pilha, &valor);
                break;
            case 5:
                imprimirPilha(&pilha);
                break;
            case 6:
                contarElementos(&pilha);
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    liberarPilha(&pilha);

    return 0;
}