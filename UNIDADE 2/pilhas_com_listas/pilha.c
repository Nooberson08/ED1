#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

void inicializar(Pilha *pilha) {
    pilha->topo = NULL;
    printf("A pilha foi inicializada\n\n");
}

int estaVazia(Pilha *pilha) {
    printf("A pilha %s vazia\n\n", (pilha->topo) == NULL ? "esta" : "nao esta");
    return pilha->topo == NULL;
}

void push(Pilha *pilha, int valor) {
    No *novo = (No*) malloc(sizeof(No));
    novo->dado = valor;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
}

int pop(Pilha *pilha) {
    No* novo = pilha->topo;

    if (pilha->topo == NULL) {  
        printf("A pilha esta vazia\n\n");
        return 0;
    }
    
    int valor = pilha->topo->dado;
    pilha->topo = pilha->topo->proximo;
    free(novo);

    return valor;
}

int peek(Pilha *pilha, int *valor) {
    if (pilha->topo == NULL) {
        printf("A pilha esta vazia\n\n");
        return 0;
    }
    
    *valor = pilha->topo->dado;
    printf("Topo: %d\n\n", pilha->topo->dado);

    return pilha->topo->dado;
}

void imprimirPilha(Pilha *pilha) {
    No* atual = pilha->topo;

    printf("\n\nTopo\n");
    
    while (atual != NULL) {
        printf("%d\n", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL\n\n");
}

int contarElementos(Pilha *pilha) {
    No* atual = pilha->topo;
    int contador = 0;

    while (atual != NULL) {
        contador++;
        atual = atual->proximo;
    }

    printf("A pilha tem %d elementos\n\n", contador);

    return contador;
}

void liberarPilha(Pilha *pilha) {
    No* atual = pilha->topo;

    while (atual != NULL) {
        No *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    printf("A pilha foi liberada\n\n");
}