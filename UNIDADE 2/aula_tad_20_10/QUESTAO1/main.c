
#include <stdio.h>
#include <stdlib.h>
#include "ContaBancaria.h"

int main() {
    char titular[200];
    int numero;
    float saldo_inicial;
    float valor;
    int resultado;

    // Criar a primeira conta
    printf("Digite o nome do titular: ");
    scanf(" %199[^\n]", titular);

    printf("Digite o numero da conta: ");
    scanf("%d", &numero);

    printf("Digite o saldo inicial: ");
    scanf("%f", &saldo_inicial);

    ContaBancaria* conta1 = criar_conta(titular, numero, saldo_inicial);

    if (conta1 == NULL) {
        printf("Erro ao criar a conta!\n");
        return 1;
    }

    // Consultar saldo
    printf("\nSaldo atual: R$ %.2f\n", consultar_saldo(conta1));

    // Depositar
    printf("\nDigite o valor do deposito: R$ ");
    scanf("%f", &valor);

    depositar(conta1, valor);

    printf("Saldo apos o deposito: R$ %.2f\n",
           consultar_saldo(conta1));

    // Sacar
    printf("\nDigite o valor do saque: R$ ");
    scanf("%f", &valor);

    resultado = sacar(conta1, valor);

    if (resultado == 1) {
        printf("Saque realizado com sucesso!\n");
    } else {
        printf("Saque nao realizado!\n");
    }

    printf("Saldo atual: R$ %.2f\n", consultar_saldo(conta1));

    // Criar a segunda conta para testar a transferencia
    printf("\nDigite o nome do segundo titular: ");
    scanf(" %199[^\n]", titular);

    printf("Digite o numero da segunda conta: ");
    scanf("%d", &numero);

    printf("Digite o saldo inicial da segunda conta: R$ ");
    scanf("%f", &saldo_inicial);

    ContaBancaria* conta2 = criar_conta(titular, numero, saldo_inicial);

    if (conta2 == NULL) {
        printf("Erro ao criar a segunda conta!\n");
        liberar_conta(conta1);
        return 1;
    }

    // Transferir entre as contas
    printf("\nDigite o valor da transferencia: R$ ");
    scanf("%f", &valor);

    resultado = transferir(conta1, conta2, valor);

    if (resultado == 1) {
        printf("Transferencia realizada com sucesso!\n");
    } else {
        printf("Transferencia nao realizada!\n");
    }

    printf("\nSaldo da primeira conta: R$ %.2f\n",
           consultar_saldo(conta1));

    printf("Saldo da segunda conta: R$ %.2f\n",
           consultar_saldo(conta2));

    // Liberar memoria
    liberar_conta(conta1);
    liberar_conta(conta2);

    return 0;
}
