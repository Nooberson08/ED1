#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int matricula;
    char nome[64];
    char curso[64];
    float media;
} Aluno;


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


void salvarArquivo(Aluno* lista, int n) {
    FILE* f = fopen("alunos.dat", "wb");
    if (f != NULL) {
        fwrite(lista, sizeof(Aluno), n, f);
        fclose(f);
    }
}

int cadastrarAluno(Aluno** lista, int* n, int* capacidade) {
    if (*n >= *capacidade) {
        *capacidade = (*capacidade == 0) ? 2 : (*capacidade * 2);
        Aluno* temp = (Aluno*)realloc(*lista, (*capacidade) * sizeof(Aluno));
        if (temp == NULL) return 0;
        *lista = temp;
    }

    printf("\n--- Cadastro de Aluno ---\n");
    printf("Matricula: ");
    scanf("%d", &(*lista)[*n].matricula);

    // Limpar o buffer do teclado após o scanf
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Nome: ");
    fgets((*lista)[*n].nome, 64, stdin);
    limparNewline((*lista)[*n].nome);

    printf("Curso: ");
    fgets((*lista)[*n].curso, 64, stdin);
    limparNewline((*lista)[*n].curso);

    printf("Media: ");
    scanf("%f", &(*lista)[*n].media);

    (*n)++;
    salvarArquivo(*lista, *n);
    printf("Aluno cadastrado com sucesso!\n");
    return 1;
}

int listarAlunos(Aluno* lista, int n) {
    if (n == 0) {
        printf("\nNenhum aluno cadastrado.\n");
        return 0;
    }

    printf("\n--- Lista de Alunos ---\n");
    for (int i = 0; i < n; i++) {
        printf("Matricula: %d\n", lista[i].matricula);
        printf("Nome: %s\n", lista[i].nome);
        printf("Curso: %s\n", lista[i].curso);
        printf("Media: %.2f\n", lista[i].media);
        printf("-------------------------\n");
    }
    return 1;
}

int buscarAluno(Aluno* lista, int n, int matricula) {
    for (int i = 0; i < n; i++) {
        if (lista[i].matricula == matricula) {
            return i; 
        }
    }
    return -1; 
}

int alterarMedia(Aluno** lista, int n, int matricula) {
    int idx = buscarAluno(*lista, n, matricula);
    if (idx == -1) {
        printf("\nAluno com matricula %d nao encontrado.\n", matricula);
        return 0;
    }

    printf("\nAluno encontrado: %s\n", (*lista)[idx].nome);
    printf("Nova media: ");
    scanf("%f", &(*lista)[idx].media);

    salvarArquivo(*lista, n);
    printf("Media alterada com sucesso!\n");
    return 1;
}

int main() {
    int quantidade_alunos = 0;
    int capacidade = 0;
    Aluno* alunos = NULL;

   
    FILE* alunos_fd = fopen("alunos.dat", "wb");
    if (alunos_fd == NULL) return 1;
    fclose(alunos_fd);

    int opcao;
    do {
        printf("\n=== MENU ===\n");
        printf("1. Cadastrar Aluno\n");
        printf("2. Listar Alunos\n");
        printf("3. Buscar Aluno\n");
        printf("4. Alterar Media\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao:\n>> ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            cadastrarAluno(&alunos, &quantidade_alunos, &capacidade);
        } else if (opcao == 2) {
            listarAlunos(alunos, quantidade_alunos);
        } else if (opcao == 3) {
            int cod;
            printf("Informe o codigo para busca: ");
            scanf("%d", &cod);
            int idx = buscarAluno(alunos, quantidade_alunos, cod);
            if (idx != -1) {
                printf("\nEncontrado: %s | Curso: %s | Media: %.2f\n", 
                       alunos[idx].nome, alunos[idx].curso, alunos[idx].media);
            } else {
                printf("\nAluno nao encontrado.\n");
            }
        } else if (opcao == 4) {
            int mat;
            printf("Informe a matricula do aluno para alterar a media: ");
            scanf("%d", &mat);
            alterarMedia(&alunos, quantidade_alunos, mat);
        }
    } while (opcao != 0);

    free(alunos);
    return 0;
}