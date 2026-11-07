#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *anterior;
    struct No *proximo;
} No;

typedef struct Lista {
    No *inicio;
    No *fim;
} Lista;

void inicializar(Lista *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

void inserirInicio(Lista *lista, int valor) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) return;

    novo->dado = valor;
    novo->anterior = NULL;
    novo->proximo = lista->inicio;

    if (lista->inicio != NULL) {
        lista->inicio->anterior = novo;
    } else {
        lista->fim = novo;
    }
    lista->inicio = novo;
}

void inserirFinal(Lista *lista, int valor) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) return;

    novo->dado = valor;
    novo->proximo = NULL;
    novo->anterior = lista->fim;

    if (lista->fim != NULL) {
        lista->fim->proximo = novo;
    } else {
        lista->inicio = novo;
    }
    lista->fim = novo;
}

void inserirPosicao(Lista *lista, int valor, int posicao) {
    if (posicao <= 1) {
        inserirInicio(lista, valor);
        return;
    }

    No *atual = lista->inicio;
    int contador = 1;

    while (atual != NULL && contador < posicao) {
        atual = atual->proximo;
        contador++;
    }

    if (atual == NULL) {
        inserirFinal(lista, valor);
    } else {
        No *novo = (No *) malloc(sizeof(No));
        if (novo == NULL) return;

        novo->dado = valor;
        novo->proximo = atual;
        novo->anterior = atual->anterior;

        if (atual->anterior != NULL) {
            atual->anterior->proximo = novo;
        }
        atual->anterior = novo;
    }
}

void removerInicio(Lista *lista) {
    if (lista->inicio == NULL) {
        printf("A lista esta vazia!\n");
        return;
    }

    No *temp = lista->inicio;
    lista->inicio = lista->inicio->proximo;

    if (lista->inicio != NULL) {
        lista->inicio->anterior = NULL;
    } else {
        lista->fim = NULL;
    }

    free(temp);
    printf("Elemento removido do inicio.\n");
}

void removerFinal(Lista *lista) {
    if (lista->fim == NULL) {
        printf("A lista esta vazia!\n");
        return;
    }

    No *temp = lista->fim;
    lista->fim = lista->fim->anterior;

    if (lista->fim != NULL) {
        lista->fim->proximo = NULL;
    } else {
        lista->inicio = NULL;
    }

    free(temp);
    printf("Elemento removido do final.\n");
}

void removerValor(Lista *lista, int valor) {
    No *atual = lista->inicio;

    while (atual != NULL && atual->dado != valor) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Valor %d nao encontrado na lista.\n", valor);
        return;
    }

    if (atual == lista->inicio) {
        removerInicio(lista);
    } else if (atual == lista->fim) {
        removerFinal(lista);
    } else {
        atual->anterior->proximo = atual->proximo;
        atual->proximo->anterior = atual->anterior;
        free(atual);
        printf("Valor %d removido com sucesso.\n", valor);
    }
}

No* buscar(Lista *lista, int valor) {
    No *atual = lista->inicio;

    while (atual != NULL) {
        if (atual->dado == valor) return atual;
        atual = atual->proximo;
    }

    return NULL;
}

void imprimirDireto(Lista *lista) {
    No *atual = lista->inicio;

    printf("NULL <-> ");
    while (atual != NULL) {
        printf("%d <-> ", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

void imprimirInverso(Lista *lista) {
    No *atual = lista->fim;

    printf("NULL <-> ");
    while (atual != NULL) {
        printf("%d <-> ", atual->dado);
        atual = atual->anterior;
    }
    printf("NULL\n");
}

int contarElementos(Lista *lista) {
    int contador = 0;
    No *atual = lista->inicio;
    while (atual != NULL) {
        contador++;
        atual = atual->proximo;
    }
    return contador;
}

void liberarLista(Lista *lista) {
    No *atual = lista->inicio;

    while (atual != NULL) {
        No *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    lista->inicio = NULL;
    lista->fim = NULL;
}

int main() {
    Lista lista;
    inicializar(&lista);

    int opcao, valor, posicao;
    No *resultado;

    do {
        printf("\n--- MENU LISTA DUPLAMENTE ENCADEADA ---\n");
        printf("1. Inserir no inicio\n");
        printf("2. Inserir no final\n");
        printf("3. Inserir em posicao especifica\n");
        printf("4. Remover do inicio\n");
        printf("5. Remover do final\n");
        printf("6. Remover um valor\n");
        printf("7. Buscar elemento\n");
        printf("8. Imprimir (Direto)\n");
        printf("9. Imprimir (Inverso)\n");
        printf("10. Contar elementos\n");
        printf("11. Liberar lista\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                inserirInicio(&lista, valor);
                break;
            case 2:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                inserirFinal(&lista, valor);
                break;
            case 3:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                printf("Digite a posicao desejada: ");
                scanf("%d", &posicao);
                inserirPosicao(&lista, valor, posicao);
                break;
            case 4:
                removerInicio(&lista);
                break;
            case 5:
                removerFinal(&lista);
                break;
            case 6:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                removerValor(&lista, valor);
                break;
            case 7:
                printf("Digite o valor que deseja buscar: ");
                scanf("%d", &valor);
                resultado = buscar(&lista, valor);
                if (resultado != NULL) {
                    printf("Elemento %d encontrado na lista!\n", resultado->dado);
                } else {
                    printf("Elemento %d nao encontrado.\n", valor);
                }
                break;
            case 8:
                printf("Lista (Direto): ");
                imprimirDireto(&lista);
                break;
            case 9:
                printf("Lista (Inverso): ");
                imprimirInverso(&lista);
                break;
            case 10:
                printf("Total de elementos: %d\n", contarElementos(&lista));
                break;
            case 11:
                liberarLista(&lista);
                printf("Lista liberada com sucesso.\n");
                break;
            case 0:
                liberarLista(&lista);
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}