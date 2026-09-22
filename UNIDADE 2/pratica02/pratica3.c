#include <stdio.h>
#include <stdlib.h>     

typedef struct {
    char nome[50];
    float preco;
} Fruta;

void imprime (FILE*frutas, Fruta f){
    fprintf(frutas, "Nome: %s", f.nome);
    fprintf(frutas, "Preco: %.2f\n\n", f.preco); 
} 

int main () {
    FILE *frutas = fopen("frutas.txt", "w"); 
    if(frutas==NULL){ 
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    printf("O arquivo tipo txt esta sendo criado.\n\n");

    int quantidade = 0;  
    Fruta *lista = NULL; 
    char opcao; 

    do {
        quantidade++; 
        lista = (Fruta*) realloc(lista, quantidade * sizeof(Fruta)); 

        if (lista == NULL) { 
            printf("Erro ao alocar memoria.\n");
            return 1;
        }

    
        printf("Digite o nome da fruta %d: ", quantidade);
        fgets(lista[quantidade - 1].nome, sizeof(lista[quantidade - 1].nome), stdin); 

        printf("Digite o preco da fruta %d: ", quantidade);
        scanf(" %f", &lista[quantidade - 1].preco); 

        getchar();


        imprime(frutas, lista[quantidade - 1]); 

        printf("Deseja cadastrar outra fruta? (s/n): ");
        scanf(" %c", &opcao); 
        getchar(); 

    } while (opcao == 's' || opcao == 'S'); 

    free(lista); 
    fclose(frutas);

    printf ("\nDados gravados com sucesso no arquivo frutas.txt!\n");

    return 0;
}