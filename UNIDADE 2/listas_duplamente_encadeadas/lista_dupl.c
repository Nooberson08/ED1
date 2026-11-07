#include <stdio.h>
#include <stdlib.h>

typedef struct No { //Representa cada "caixinha" (elemento) da lista
    int dado; //Armazena o valor inteiro que o nó guarda
    struct No *anterior; // aponta para o nó anterior na lista (permite voltar a lista)
    struct No *proximo; // aponta para o próximo nó na lista (faz a lista avançar)
} No; // A repetição do nome strcut dentro da strcukt acontece pois o typedef ainda não foi executado, então as variáveis são do tipo "strcut No" e não somente "No" ainda

typedef struct Lista { // controla a lista inteira, guardando apenas dois ponteiros principais
    No *inicio; // aponta para o primeiro elemento (head)
    No *fim; // aponta para o último elemento (tail)
} Lista;

void inicializar(Lista *lista) { // lista é criada, portanto, está vazia
    lista->inicio = NULL; // não há elementos no começo
    lista->fim = NULL; // não há elementos no final
}

void inserirInicio(Lista *lista, int valor) {  // 
    No *novo = (No *) malloc(sizeof(No)); // Aloca memória dinamicamente para o novo nó.
    if (novo == NULL) return; // verifica se a alocação deu certo

    novo->dado = valor; // Atribui o valor passado pelo usuário
    novo->anterior = NULL; // Como será o primeiro, não há nada antes dele.
    novo->proximo = lista->inicio; // O próximo do novo nó passa a ser o antigo primeiro nó.

    if (lista->inicio != NULL) { // Se a lista não estava vazia, o ponteiro anterior do antigo primeiro nó agora aponta para o novo nó. Se a lista estava vazia, o novo nó também passa a ser o fim da lista.
        lista->inicio->anterior = novo; // O início da lista é atualizado para o novo nó.
    } else {
        lista->fim = novo; //
    }
    lista->inicio = novo; //
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
    if (lista->inicio == NULL) return;

    No *temp = lista->inicio;
    lista->inicio = lista->inicio->proximo;

    if (lista->inicio != NULL) {
        lista->inicio->anterior = NULL;
    } else {
        lista->fim = NULL;
    }

    free(temp);
}

void removerFinal(Lista *lista) {
    if (lista->fim == NULL) return;

    No *temp = lista->fim;
    lista->fim = lista->fim->anterior;

    if (lista->fim != NULL) {
        lista->fim->proximo = NULL;
    } else {
        lista->inicio = NULL;
    }

    free(temp);
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
    printf("Lista inicializada.\n");

    inserirInicio(&lista, 20);
    inserirInicio(&lista, 10);
    inserirFinal(&lista, 30);

    printf("Ordem direta: ");
    imprimirDireto(&lista);

    printf("Ordem inversa: ");
    imprimirInverso(&lista);

    printf("Total de elementos: %d\n", contarElementos(&lista));

    liberarLista(&lista);
    printf("Lista liberada.\n");

    return 0;
}