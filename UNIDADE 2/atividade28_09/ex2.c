#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int codigo;
    char nome[64];
    float preco;
    float estoque;
} Mercadoria;

void limparNewline(char* str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }
}


void salvarArquivo(Mercadoria* lista, int n) {
    FILE* f = fopen("mercadorias.dat", "wb");
    if (f != NULL) {
        fwrite(lista, sizeof(Mercadoria), n, f);
        fclose(f);
    }
}

int cadastrarMercadoria(Mercadoria** lista, int* n, int* capacidade) {
    if (*n >= *capacidade) {
        *capacidade = (*capacidade == 0) ? 2 : (*capacidade * 2);
        Mercadoria* temp = (Mercadoria*)realloc(*lista, (*capacidade) * sizeof(Mercadoria));
        if (temp == NULL) return 0;
        *lista = temp;
    }

    printf("\n--- Cadastro de Mercadoria ---\n");
    printf("Codigo: ");
    scanf("%d", &(*lista)[*n].codigo);

    // Limpar o buffer do teclado após o scanf
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Nome: ");
    fgets((*lista)[*n].nome, 64, stdin);
    limparNewline((*lista)[*n].nome);

    printf("Preco: ");
    scanf("%f", &(*lista)[*n].preco);

    printf("Estoque: ");
    scanf("%f", &(*lista)[*n].estoque);

    (*n)++;
    salvarArquivo(*lista, *n);
    printf("Mercadoria cadastrada com sucesso!\n");
    return 1;
}

int listarMercadorias(Mercadoria* lista, int n) {
    if (n == 0) {
        printf("\nNenhuma mercadoria cadastrada.\n");
        return 0;
    }

    printf("\n--- Lista de Mercadorias ---\n");
    for (int i = 0; i < n; i++) {
        printf("Codigo: %d\n", lista[i].codigo);
        printf("Nome: %s\n", lista[i].nome);
        printf("Preco: %.2f\n", lista[i].preco);
        printf("Estoque: %.2f\n", lista[i].estoque);
        printf("-------------------------\n");
    }
    return 1;
}

int buscarMercadoria(Mercadoria* lista, int n, int codigo) {
    for (int i = 0; i < n; i++) {
        if (lista[i].codigo == codigo) {
            return i; 
        }
    }
    return -1; 
}

int alterarPreco(Mercadoria** lista, int n, int codigo) {
    int idx = buscarMercadoria(*lista, n, codigo);
    if (idx == -1) {
        printf("\nMercadoria com codigo %d nao encontrada.\n", codigo);
        return 0;
    }

    printf("\nMercadoria encontrada: %s\n", (*lista)[idx].nome);
    printf("Novo preco: ");
    scanf("%f", &(*lista)[idx].preco);

    salvarArquivo(*lista, n);
    printf("Preco alterado com sucesso!\n");
    return 1;
}

int main() {
    int quantidade_mercadorias = 0;
    int capacidade = 0;
    Mercadoria* mercadorias = NULL;

   
    FILE* mercadorias_fd = fopen("mercadorias.dat", "wb");
    if (mercadorias_fd == NULL) return 1;
    fclose(mercadorias_fd);

    int opcao;
    do {
        printf("\n=== MENU ===\n");
        printf("1. Cadastrar Mercadoria\n");
        printf("2. Listar Mercadorias\n");
        printf("3. Buscar Mercadoria\n");
        printf("4. Alterar Preco\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao:\n>> ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            cadastrarMercadoria(&mercadorias, &quantidade_mercadorias, &capacidade);
        } else if (opcao == 2) {
            listarMercadorias(mercadorias, quantidade_mercadorias);
        } else if (opcao == 3) {
            int codigo;
            printf("Informe o codigo para busca: ");
            scanf("%d", &codigo);
            int idx = buscarMercadoria(mercadorias, quantidade_mercadorias, codigo);
            if (idx != -1) {
                printf("\nEncontrado: %s | Preco: %.2f | Estoque: %.2f\n",
                       mercadorias[idx].nome, mercadorias[idx].preco, mercadorias[idx].estoque);
            } else {
                printf("\nMercadoria nao encontrada.\n");
            }
        } else if (opcao == 4) {
            int codigo;
            printf("Informe o codigo da mercadoria para alterar o preco: ");
            scanf("%d", &codigo);
            alterarPreco(&mercadorias, quantidade_mercadorias, codigo);
        }
    } while (opcao != 0);

    free(mercadorias);
    return 0;
}