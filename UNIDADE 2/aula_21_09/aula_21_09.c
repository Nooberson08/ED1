#include <stdio.h>
#include <stdlib.h>

//Função abrir arquivo
int main (void){
    FILE * arq;
    //int c;
    char linha[100];
    arq = fopen("arquivo.txt", "r");
        if(arq == NULL){
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }
        else{
            printf("Arquivo aberto com sucesso.\n");
        }
        //fputc('A', arq);- só podem ser usadas com a função 'w' ou 'a'
        //fputs("Hello, World!\n", arq);- só podem ser usadas com a função 'w' ou 'a'
        //fprintf(arq, "Hello, World!\n"); - só podem ser usadas com a função 'w' ou 'a'
        //fread(&buffer, sizeof(buffer), 1, arq);- só podem ser usadas com a função 'w' ou 'a'

        //c = fgetc(arq);
        //printf("O caractere lido foi: %c\n", c);
        //fgets(linha, 100, arq);
        //feof(arq); - serve para ler todos os dados do arquivo
        //fscanf(arq, "%[^\n]", linha);
        //printf("A linha lida foi: %s", linha);

            while (!feof(arq)){ // Estrutura de repetição para ler todas as linhas do arquivo
            fscanf(arq, "%[^\n]\n", linha); // Lê uma linha
            //fscanf(arq, "%s", linha); - Lê uma palavra
            printf("A linha lida foi: %s", linha);
        }

    fclose(arq);
    return 0;
}