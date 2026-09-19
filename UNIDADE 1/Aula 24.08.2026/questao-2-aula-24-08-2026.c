#include <stdio.h>
#include <stdlib.h>

int main() {
    int linhas = 3;
    int colunas = 3;
    int i, j;

    
    int **matriz = (int **) malloc(linhas * sizeof(int *));
    if (matriz == NULL) {
        printf("Erro ao alocar memória para as linhas!\n");
        return 1;
    }


    for (i = 0; i < linhas; i++) {
        matriz[i] = (int *) malloc(colunas * sizeof(int));
        if (matriz[i] == NULL) {
            printf("Erro ao alocar memória para as colunas!\n");
            return 1;
        }
    }

    
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            matriz[i][j] = i * 3 + j;
        }
    }

    
    printf("Matriz 3x3 preenchida:\n");
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }

    
    for (i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}
