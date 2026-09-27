#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char texto[1000];
} Texto;

int main() {
    
    FILE *arquivo = fopen("texto.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    printf("Digite o texto (pressione Enter em uma linha vazia para finalizar):\n");
    Texto t;    
    
    
    while (1) {
        if (fgets(t.texto, sizeof(t.texto), stdin) == NULL) {
            break;
        }
        
        
        if (t.texto[0] == '\n' || t.texto[0] == '\r') {
            break;
        }

        // Escreve a linha no arquivo
        fprintf(arquivo, "%s", t.texto);
    }

    
    fclose(arquivo);


    
    FILE *fp;
    int c; 

    int caracteres = 0;
    int palavras = 0;
    int linhas = 0;
    int letrasA = 0;

    int dentroPalavra = 0;

    fp = fopen("texto.txt", "r");

    if (fp == NULL) {
        printf("Erro na abertura do arquivo para leitura!\n");
        return 1;
    }

    // 3. Leitura caractere por caractere
    while (1) {
        c = fgetc(fp);

        if (c == EOF) {
            break;
        }

        caracteres++;

        if (c == '\n') {
            linhas++;
        }

        if (c == 'a' || c == 'A') {
            letrasA++;
        }

        if (c == ' ' || c == '\n' || c == '\r' || c == '\t') {
            dentroPalavra = 0;
        } 
        else {
            if (dentroPalavra == 0) {
                palavras++;
                dentroPalavra = 1;
            }
        }
    }

    if (caracteres > 0 && linhas == 0) {
        linhas = 1;
    }

    fclose(fp);

    printf("\n--- Resultados ---\n");
    printf("Quantidade de caracteres: %d\n", caracteres);
    printf("Quantidade de palavras: %d\n", palavras);
    printf("Quantidade de linhas: %d\n", linhas);
    printf("Quantidade de letras A: %d\n", letrasA);

    return 0; 
}