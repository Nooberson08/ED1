#include <stdio.h> //printf
#include <stdlib.h>//malloc, free, exit
#include "ContaBancaria.h"

struct conta {
    char titular [200];
    int numero;
    float saldo;
};

ContaBancaria* criar_conta(char titular [200], int numero, float saldo_inicial){
    ContaBancaria *c = (ContaBancaria*) malloc (sizeof(ContaBancaria));
    if (c != NULL){
        int i = 0;

    while (titular[i] != '\0' && i < 199) {
    c->titular[i] = titular[i];
    i++;
}

    c->titular[i] = '\0';
        c->numero = numero;
        c->saldo = saldo_inicial;
    }
    return c;
}
void liberar_conta(ContaBancaria* c) {
    printf ("Conta liberada");
    free (c);
}

void depositar(ContaBancaria* c, float valor) {
    if (c != NULL && valor > 0) {
        c->saldo += valor;
    }
}

int sacar(ContaBancaria* c, float valor) {
    if (c != NULL && valor > 0 && c->saldo >= valor) {
        c->saldo -= valor;
        return 1; // Sucesso
    }
    return 0; // Falha (saldo insuficiente)
}

int transferir(ContaBancaria* origem, ContaBancaria* destino, float valor) {
               
    if (origem == NULL || destino == NULL) {
        return 0;
    }

    if (valor <= 0 || origem->saldo < valor) {
        return 0;
    }

    origem->saldo -= valor;
    destino->saldo += valor;

    return 1;
}
    
float consultar_saldo (ContaBancaria* c){
    if (c == NULL){
        printf ("Saldo zerado");
        return 0.0f;
    }
    return c ->saldo;
}

