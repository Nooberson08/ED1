#include <stdio.h>

typedef union desempenho{
    float IRA;
    float IEA;
    float MC;
} desempenho;

typedef struct pessoa{
    char nome [50];
    char cpf[20];
    char rg[20];
    char telefone[20];
    int idade;
    int tipo;
    desempenho Desempenho;
} pessoa;

void recebe (pessoa*a){
    printf ("Digite seu nome: ");
    scanf(" %[^\n]", a->nome);

    printf ("idade: ");
    scanf ("%d", &a->idade);

    printf ("cpf: ");
    scanf ("%s", &a->cpf);

    printf ("rg: ");
    scanf ("%s", &a->rg);

    printf ("telefone: ");
    scanf (" %[^\n]", &a->telefone);

    printf ("Digite o tipo de desempenho (1-IRA, 2-IEA, 3-MC): ");
    scanf ("%d", &a->tipo);
    if (a->tipo == 1){
        printf ("Digite o IRA: ");
        scanf ("%f", &a->Desempenho.IRA);
    } else if (a->tipo == 2){
        printf ("Digite o IEA: ");
        scanf ("%f", &a->Desempenho.IEA);
    } else if (a->tipo == 3){
        printf ("Digite o MC: ");
        scanf ("%f", &a->Desempenho.MC);
    }

}
void imprime (pessoa a){
    printf("\n Nome: %s | idade: %d\n | cpf: %s\n | rg: %s\n | telefone: %s \n", a.nome, a.idade, a.cpf, a.rg, a.telefone);

    if (a.tipo == 1){
        printf ("IRA: %.2f\n", a.Desempenho.IRA);
    } else if (a.tipo == 2){
        printf ("IEA: %.2f\n", a.Desempenho.IEA);
    } else if (a.tipo == 3){
        printf ("MC: %.2f\n", a.Desempenho.MC);
    }
}
int main (void){
    pessoa p;
    recebe (&p);
    imprime (p);
    return 0;
}