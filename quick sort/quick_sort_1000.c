//PEGUEI O ARQUIVO BASE DO QUICK SORT E ADICIONEI UM FILE PARA LER OS DADOS NO ARQUIVO TXT.
//CODIGO PARA GERAR 1000 INDICES

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

    int comparacoes=0;
    int trocas=0;
    int passo=0;

// Função Quicksort adaptada
void quicksort(int values[], int begin, int end, int total_N, FILE *estatistica) {
    // Caso base: se a sublista tiver 0 ou 1 elemento, já está ordenada
    if (begin >= end - 1) return;
    
    int i = begin;
    int j = end - 1;
    
    // Escolha do pivô (elemento central)
    int pivo = values[begin + (end - begin) / 2];//pega o indice do primeiro elemento + (tamanho do vetor - indice do primeiro elemento)/2

    passo++;
    fprintf(estatistica, "\n==================================================\n");
    fprintf(estatistica, "PASSO %d: Subvetor de indices [%d a %d]\n", passo, begin, end - 1);//mostra quem será o pivô e quem ficará a esquerda e a direita dele
    fprintf(estatistica, "Pivo Escolhido: %d\n", pivo);//mostra quem será o pivô e quem ficará a esquerda e a direita dele
    fprintf(estatistica, "--------------------------------------------------\n");

    int aux;
    
    while (i <= j) {
        while (i < end && values[i] < pivo){
            comparacoes ++;// Conta as comparações verdadeiras
            i++;
        } 
        comparacoes ++;// Conta a última comparação (que deu FALSO e parou o while)

        while (j >= begin && values[j] > pivo){
            comparacoes ++;// Conta as comparações verdadeiras
            j--;
        } 
        comparacoes ++;// Conta a última comparação (que deu FALSO e parou o while)

        
        if (i <= j) {

            fprintf(estatistica, " [Troca]: %d (pos %d) <->  %d (pos %d)\n", values[i], i, values[j], j);

            // Troca os elementos de posição
            aux = values[i];
            values[i] = values[j];
            values[j] = aux;

            trocas++;
            i++;
            j--;
            
        }
    }
    
    fprintf(estatistica, "--------------------------------------------------\n");
    fprintf(estatistica, "Estado do vetor apos o PASSO %d: ", passo);
    for (int k = 0; k < total_N; k++) {
        fprintf(estatistica,"%d ", values[k]);
    }
    
    fprintf(estatistica,"\n==================================================\n");

    // Chamadas recursivas para as duas metades
    if (begin < j) quicksort(values, begin, j + 1, total_N, estatistica);
    if (i < end) quicksort(values, i, end, total_N, estatistica);
}

int main() {


    int N;
    int i;
    
    srand(time(NULL));

    
    FILE *arq = fopen("Dados1000.txt", "w");
    if (arq == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return 1;
        }

        // Grava o tamanho N (1000) primeiro no topo do arquivo
        fprintf(arq, "1000\n");
        
        // Grava os 1000 números aleatórios
        for (int a = 0; a < 1000; a++) {
            fprintf(arq, "%d ", rand() % 10000);
        }
        fclose(arq);
        
        // abre o arquivo recém-criado para leitura
    arq = fopen("Dados1000.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo para leitura!\n");
        return 1;
        }

    // Lê o tamanho N do vetor
    fscanf(arq, "%d", &N);

    // Aloca a memória dinamicamente
    int *vetor = (int *) malloc(N * sizeof(int));
    if (vetor == NULL) {
        printf("Erro de alocacao de memoria!\n");
        fclose(arq);
        return 1;
    }

    for (i = 0; i < N; i++) {
        fscanf(arq, "%d", &vetor[i]);
    }
    fclose(arq);

    FILE *estatistica = fopen("Saida1000.txt", "w");
    if (estatistica==NULL){
        printf ("Erro ao criar o arquivo Saida.txt!\n");
        free(vetor);
        return 1;
    }

    
    // Salva o array antes da ordenação no arquivo
    fprintf(estatistica, "Array antes da ordenacao: ");
    for (int k = 0; k < N; k++) {
        fprintf(estatistica, "%d ", vetor[k]);
    }
    fprintf(estatistica, "\n");

    // Executa a ordenação Quick Sort (passando o arquivo de estatística)
    quicksort(vetor, 0, N, N, estatistica);

    // Salva o array após a ordenação no arquivo
    fprintf(estatistica, "\nArray ordenado: ");
    for (int k = 0; k < N; k++) {
        fprintf(estatistica, "%d ", vetor[k]);
    }
    fprintf(estatistica, "\n");

    fprintf(estatistica, "\n--- RELATORIO DE EXECUCAO (QUICK SORT) ---\n");
    fprintf(estatistica, "Total de elementos: %d\n", N);
    fprintf(estatistica, "Total de Comparacoes: %d\n", comparacoes);
    fprintf(estatistica, "Total de Trocas: %d\n", trocas);
    fprintf(estatistica, "Total de Passos/Particoes: %d\n", passo);
    fprintf(estatistica, "==================================================\n");


    fclose(estatistica);

    // ==========================================
    // EXIBE APENAS O RELATÓRIO E OS ARRAYS NO TERMINAL
    // ==========================================
    printf("Array antes da ordenacao: ");
    // Precisamos recriar/reler ou guardar uma cópia se quisermos printar exatamente o original. 
    // Como o vetor original foi alterado, vamos ler do arquivo Saida.txt ou apenas mostrar o final.
    // Vamos ler o arquivo Saida.txt para exibir as partes desejadas no terminal de forma limpa:
    
    FILE *ler_saida = fopen("Saida1000.txt", "r");
    if (ler_saida != NULL) {
        char linha[1000];
        // Lê a primeira linha (Array antes)
        if (fgets(linha, sizeof(linha), ler_saida) != NULL) {
            printf("%s", linha);
        }
        
        fclose(ler_saida);
    }

    // Exibe o array ordenado no terminal também
    printf("Array ordenado: ");
    for (int k = 0; k < N; k++) {
        printf("%d ", vetor[k]);
    }
    printf("\n");

    printf("\n--- RELATORIO DE EXECUCAO (QUICK SORT) ---\n");
    printf("Total de elementos: %d\n", N);
    printf("Total de Comparacoes: %d\n", comparacoes);
    printf("Total de Trocas: %d\n", trocas);
    printf("Total de Passos/Particoes: %d\n", passo);
    printf("==================================================\n");
    
    // Libera a memória alocada
    free(vetor);

    return 0;
}