#include <stdio.h>
#define MAX 3

typedef struct Pessoa {

    char nome[50];
    char documento[30];
    int idade;

} Pessoa;

//a) Preenche os dados]
void recebe(Pessoa *p) {

    printf("Nome: ");
    scanf(" %[^\n]", p->nome);

    printf("Documento: ");
    scanf(" %[^\n]", p->documento);

    printf("Idade: ");
    scanf("%d", &p->idade);
}

//b) Imprime os dados
void imprime(Pessoa *p) {
    
    printf("\nNome: %s\n", p->nome);
    printf("Documento: %s\n", p->documento);
    printf("Idade: %d\n", p->idade);
}

//c) Altera a idade
void alteraIdade(Pessoa *p) {
    
    printf("\nDigite a nova idade: ");
    scanf("%d", &p->idade);
}

//d) Encontra a pessoa com maior e menor idade
void maiorMenor(Pessoa v[], int tamanho) {

    int maior = 0;
    int menor = 0;

    for (int i = 1; i < tamanho; i++) {

        if (v[i].idade > v[maior].idade) {
            maior = i;
        }

        if (v[i].idade < v[menor].idade) {
            menor = i;
        }
    }

    printf("\n====== RESULTADO ======\n");

    printf("\nPessoa com maior idade:\n");
    imprime(&v[maior]);

    printf("\nPessoa com menor idade:\n");
    imprime(&v[menor]);
}

int main() {

    Pessoa pessoas[MAX];

    for (int i = 0; i < MAX; i++) {
        printf("\n=== PESSOA %d ===\n", i + 1);
        recebe(&pessoas[i]);
    }

    printf("\n=== DADOS DAS PESSOAS ===\n");
    for (int i = 0; i < MAX; i++) {
        imprime(&pessoas[i]);
    }

    printf("\n=== ALTERANDO IDADE DA PESSOA 1 ===\n");
    alteraIdade(&pessoas[0]);

    printf("\n=== PESSOAS COM MAIOR E MENOR IDADE ===\n");
    maiorMenor(pessoas, MAX);


    return 0;
}
