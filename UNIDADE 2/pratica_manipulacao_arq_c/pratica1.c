#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char matricula[20];
    char nome[50];
    float nota_final;
} Aluno;

int main (){
    
    FILE *arquivo = fopen("alunos.txt", "w");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    Aluno alunos[5];

    for (int i = 0; i < 5; i++){
        printf ("\nDigite os dados do aluno %d:\n", i + 1);
        printf ("Matricula: ");
        scanf (" %[^\n]", alunos[i].matricula);
        printf ("Nome: ");
        scanf (" %[^\n]", alunos[i].nome);
        printf ("Nota Final: ");
        scanf ("%f", &alunos[i].nota_final);


        fprintf(arquivo, "%s %s %.2f\n", alunos[i].matricula, alunos[i].nome, alunos[i].nota_final);
    }

    
    fclose(arquivo);
    printf("\nGravacao concluida. Fechando o arquivo...\n");

    
    printf("\n--- REABRINDO E LENDO DO ARQUIVO (alunos.txt) ---\n");
    
    arquivo = fopen("alunos.txt", "r");
    if(arquivo == NULL){
        printf("Erro ao reabrir o arquivo para leitura.\n");
        return 1;
    }

    Aluno lido;
    
    while (!feof(arquivo)){
        fscanf(arquivo, "%s %s %f", lido.matricula, lido.nome, &lido.nota_final);
        printf("Matricula: %s | Nome: %s | Nota Final: %.2f\n", lido.matricula, lido.nome, lido.nota_final);
    }

    fclose(arquivo);
    return 0;
}