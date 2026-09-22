#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char matricula[20];
    char nome[50];
    float nota_final;

} Aluno;

void imprime (FILE*alunos, Aluno a){
    fprintf(alunos, "Matricula: %s", a.matricula);
    fprintf(alunos, "Nome: %s", a.nome);
    fprintf(alunos, "Nota Final: %.2f\n\n", a.nota_final); // o "." indica que está acessando o campo nota da estrutura a do tipo Aluno. O "\n\n" adiciona duas quebras de linha após a nota para separar visualmente os registros no arquivo.
} //usada para gravar os dados do aluno no arquivo de texto

int main (){
    FILE *alunos = fopen("alunos.txt", "w");
    if(alunos==NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    else{
        printf("Arquivo aberto com sucesso.\n");
    }   
    
    Aluno *qtde_alunos = (Aluno*) malloc(5 * sizeof(Aluno));
    if (qtde_alunos == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

   for (int i = 0; i < 5; i++){
        printf ("\nDigite os seguintes dados do aluno %d:\n", i + 1);
        
        printf ("Matricula:\n ");
        scanf (" %[^\n]", qtde_alunos[i].matricula); 
        
        printf ("Nome:\n ");
        scanf (" %[^\n]", qtde_alunos[i].nome);     
        
        printf ("Nota Final:\n ");
        scanf ("%f", &qtde_alunos[i].nota_final);

        imprime(alunos, qtde_alunos[i]); 
    }
   
    free(qtde_alunos);       
    fclose(alunos);

    printf ("\nDados gravados com sucesso no arquivo alunos.txt!\n");
    return 0;
}