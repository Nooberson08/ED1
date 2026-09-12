#include <stdio.h>
#define MAX 3

typedef struct funcionario {

    char nome[50];
    float salario;
    int identificador;
    char cargo[50];

} funcionario;

// A) Preenche os dados
void recebe(funcionario *f) {

    printf("Nome: ");
    scanf(" %[^\n]", f->nome);

    printf("Salario: ");
    scanf("%f", &f->salario);

    printf("Identificador: ");
    scanf("%d", &f->identificador);

    printf("Cargo: ");
    scanf(" %[^\n]", f->cargo);
}


// B) Imprime os dados
void imprime(funcionario *f) {

    printf("\nNome: %s\n", f->nome);
    printf("Salario: R$ %.2f\n", f->salario);
    printf("Identificador: %d\n", f->identificador);
    printf("Cargo: %s\n", f->cargo);
}


// C) Altera o salario
void alteraSalario(funcionario *f) {

    printf("\nDigite o novo salario: ");
    scanf("%f", &f->salario);
}


// D) Encontra o funcionario com maior e menor salario
void maiorMenor(funcionario v[], int tamanho) {

    int maior = 0;
    int menor = 0;

    for (int i = 1; i < tamanho; i++) {

        if (v[i].salario > v[maior].salario) {
            maior = i;
        }

        if (v[i].salario < v[menor].salario) {
            menor = i;
        }
    }

    printf("\n===== MAIOR SALARIO =====\n");
    printf("Cargo: %s\n", v[maior].cargo);
    printf("Salario: R$ %.2f\n", v[maior].salario);

    printf("\n===== MENOR SALARIO =====\n");
    printf("Cargo: %s\n", v[menor].cargo);
    printf("Salario: R$ %.2f\n", v[menor].salario);
}


int main(void) {

    funcionario f[MAX];

    // Preenchendo o vetor
    for (int i = 0; i < MAX; i++) {

        printf("\n===== FUNCIONARIO %d =====\n", i + 1);

        recebe(&f[i]);
    }


    // Imprimindo os funcionários
    printf("\n\n===== FUNCIONARIOS CADASTRADOS =====\n");

    for (int i = 0; i < MAX; i++) {

        imprime(&f[i]);
    }


    // Alterando o salario do primeiro funcionário
    printf("\n===== ALTERAR SALARIO =====\n");

    alteraSalario(&f[0]);


    // Mostrando maior e menor salario
    maiorMenor(f, MAX);


    return 0;
}