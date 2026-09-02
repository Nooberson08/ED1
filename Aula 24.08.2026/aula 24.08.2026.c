#include <stdio.h>
#include <stdlib.h>

int main() {
    int quantidade = 0;
    
    
    char **nomes = NULL;
    float *precos = NULL;

    printf("Quantas frutas deseja cadastrar? ");
    scanf("%d", &quantidade);

    for (int i = 0; i < quantidade; i++) {
        
        nomes = (char **) realloc(nomes, (i + 1) * sizeof(char *));
        precos = (float *) realloc(precos, (i + 1) * sizeof(float));

        
        nomes[i] = (char *) malloc(50 * sizeof(char));

        printf("\n--- Fruta %d ---\n", i + 1);
        printf("Nome: ");
        scanf(" %49[^\n]", nomes[i]);

        printf("Preço (R$): ");
        scanf("%f", &precos[i]);
    }

    
    printf("\n=== FRUTAS CADASTRADAS ===\n");
    for (int i = 0; i < quantidade; i++) {
        printf("%d. %s - R$ %.2f\n", i + 1, nomes[i], precos[i]);
    }

    
    for (int i = 0; i < quantidade; i++) {
        free(nomes[i]); 
    }
    free(nomes); 
    free(precos); 

    return 0;
}
