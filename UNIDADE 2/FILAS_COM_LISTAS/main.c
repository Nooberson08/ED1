#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

void exibirMenu(void) {
    printf("\n==========================================\n");
    printf("      SISTEMA DE ATENDIMENTO (FILA)\n");
    printf("==========================================\n");
    printf("1. Adicionar pessoa a fila (senha)\n");
    printf("2. Chamar proxima pessoa (remover inicio)\n");
    printf("3. Consultar quem sera atendido em seguida\n");
    printf("4. Exibir todas as pessoas aguardando\n");
    printf("5. Informar quantidade de pessoas na fila\n");
    printf("6. Consultar ultima senha da fila\n");
    printf("0. Liberar memoria e sair\n");
    printf("Escolha uma opcao: ");
}

int main(void) {
    Fila *fila = criarFila();
    if (fila == NULL) {
        printf("Erro critico: falha ao alocar memoria para a fila.\n");
        return 1;
    }

    int opcao, senha;

    do {
        exibirMenu();
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                printf("Digite a senha / identificacao da pessoa: ");
                if (scanf("%d", &senha) == 1) {
                    if (enqueue(fila, senha)) {
                        printf("Senha %d adicionada ao final da fila.\n", senha);
                    } else {
                        printf("Erro: nao foi possivel alocar memoria.\n");
                    }
                } else {
                    while (getchar() != '\n');
                    printf("Entrada invalida! Digite um numero inteiro.\n");
                }
                break;

            case 2:
                if (dequeue(fila, &senha)) {
                    printf("Chamando senha %d para atendimento! (Removida do inicio)\n", senha);
                } else {
                    printf("Aviso: nao ha pessoas aguardando na fila.\n");
                }
                break;

            case 3:
                if (front(fila, &senha)) {
                    printf("Proxima pessoa a ser atendida: senha %d\n", senha);
                } else {
                    printf("Aviso: a fila esta vazia.\n");
                }
                break;

            case 4:
                printf("Pessoas aguardando atendimento:");
                imprimirFila(fila);
                break;

            case 5:
                printf("Quantidade de pessoas na fila: %d\n", tamanhoFila(fila));
                break;

            case 6:
                if (back(fila, &senha)) {
                    printf("Ultima senha na fila: %d\n", senha);
                } else {
                    printf("Aviso: a fila esta vazia.\n");
                }
                break;

            case 0:
                printf("Liberando memoria e encerrando sistema...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    liberarFila(fila);
    return 0;
}