#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

// Estrutura para armazenar cada quadro da animação
typedef struct {
    int vetor[500];
    int pivo_idx;
    int troca_i;
    int troca_j;
} PassoAnimacao;

PassoAnimacao historico[5000];
int total_passos = 0;

int comparacoes = 0;
int trocas = 0;
int passo = 0;

void registrar_passo(int values[], int N, int pivo_idx, int pos_i, int pos_j) {
    if (total_passos < 5000) {
        for (int k = 0; k < N; k++) {
            historico[total_passos].vetor[k] = values[k];
        }
        historico[total_passos].pivo_idx = pivo_idx;
        historico[total_passos].troca_i = pos_i;
        historico[total_passos].troca_j = pos_j;
        total_passos++;
    }
}

// Função Quicksort adaptada com gravação de quadros
void quicksort(int values[], int begin, int end, int total_N, FILE *estatistica) {
    if (begin >= end - 1) return;
    
    int i = begin;
    int j = end - 1;
    int pivo_index = begin + (end - begin) / 2;
    int pivo = values[pivo_index];

    passo++;
    fprintf(estatistica, "\n==================================================\n");
    fprintf(estatistica, "PASSO %d: Subvetor de indices [%d a %d]\n", passo, begin, end - 1);
    fprintf(estatistica, "Pivo Escolhido: %d\n", pivo);
    fprintf(estatistica, "--------------------------------------------------\n");

    int aux;
    
    while (i <= j) {
        while (i < end && values[i] < pivo) {
            comparacoes++;
            i++;
        } 
        comparacoes++;

        while (j >= begin && values[j] > pivo) {
            comparacoes++;
            j--;
        } 
        comparacoes++;

        if (i <= j) {
            fprintf(estatistica, " [Troca]: %d (pos %d) <->  %d (pos %d)\n", values[i], i, values[j], j);

            aux = values[i];
            values[i] = values[j];
            values[j] = aux;

            registrar_passo(values, total_N, pivo_index, i, j);

            trocas++;
            i++;
            j--;
        }
    }
    
    fprintf(estatistica, "--------------------------------------------------\n");
    fprintf(estatistica, "Estado do vetor apos o PASSO %d: ", passo);
    for (int k = 0; k < total_N; k++) {
        fprintf(estatistica, "%d ", values[k]);
    }
    fprintf(estatistica, "\n==================================================\n");

    if (begin < j) quicksort(values, begin, j + 1, total_N, estatistica);
    if (i < end) quicksort(values, i, end, total_N, estatistica);
}

void desenharVetor(int vetor[], int N, int pivo_idx, int i_idx, int j_idx) {
    int larguraTela = GetScreenWidth();
    int alturaTela = GetScreenHeight();
    
    float larguraBarra = (float)larguraTela / N;
    
    // Reserva espaço na parte superior para a HUD e para os números em pé
    int alturaDisponivel = alturaTela - 200;

    for (int i = 0; i < N; i++) {
        int alturaBarra = (int)((float)vetor[i] / 1000.0f * alturaDisponivel);
        if (alturaBarra < 2) alturaBarra = 2;

        float posX = i * larguraBarra;
        float posY = alturaTela - alturaBarra;

        Color corBarra = BLUE;

        if (i == pivo_idx) {
            corBarra = YELLOW;
        } else if (i == i_idx || i == j_idx) {
            corBarra = RED;
        }

        float larguraReal = (larguraBarra > 3.0f) ? larguraBarra - 1.0f : larguraBarra;
        DrawRectangle((int)posX, (int)posY, (int)larguraReal, alturaBarra, corBarra);

        // --- EXIBIÇÃO DOS NÚMEROS NA VERTICAL ---
        // Desenha o texto rotacionado em -90 graus para caber na largura de 10px da barra
        Vector2 posTexto = { posX + (larguraBarra / 2.0f) - 3.0f, posY - 5.0f };
        Vector2 origem = { 0, 0 };
        
        // Cor do texto muda para vermelho/amarelo quando a barra estiver em destaque
        Color corTexto = BLACK;
        if (i == pivo_idx) corTexto = DARKBROWN;
        else if (i == i_idx || i == j_idx) corTexto = RED;

        DrawTextPro(GetFontDefault(), TextFormat("%d", vetor[i]), posTexto, origem, -90.0f, 10.0f, 1.0f, corTexto);
    }
}

int main() {
    clock_t t;
    int N;
    int i;
    
    srand(time(NULL));

    FILE *arq = fopen("Dados100.txt", "w");
    if (arq == NULL) {
        printf("Erro ao criar o arquivo Dados100.txt!\n");
        return 1;
    }

    fprintf(arq, "100\n");
    for (int a = 0; a < 100; a++) {
        fprintf(arq, "%d ", rand() % 1000);
    }
    fclose(arq);
        
    arq = fopen("Dados100.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo Dados100.txt para leitura!\n");
        return 1;
    }

    fscanf(arq, "%d", &N);

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

    FILE *estatistica = fopen("Saida100.txt", "w");
    if (estatistica == NULL) {
        printf("Erro ao criar o arquivo Saida100.txt!\n");
        free(vetor);
        return 1;
    }

    fprintf(estatistica, "Array antes da ordenacao: ");
    for (int k = 0; k < N; k++) {
        fprintf(estatistica, "%d ", vetor[k]);
    }
    fprintf(estatistica, "\n");

    registrar_passo(vetor, N, -1, -1, -1);

    t = clock();
    quicksort(vetor, 0, N, N, estatistica);
    t = clock() - t;

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
    fprintf(estatistica, "Tempo de execucao: %.4lf milissegundos\n", ((double)t / CLOCKS_PER_SEC) * 1000.0);

    fclose(estatistica);

    printf("--- RELATORIO DE EXECUCAO (QUICK SORT) ---\n");
    printf("Total de elementos: %d\n", N);
    printf("Total de Comparacoes: %d\n", comparacoes);
    printf("Total de Trocas: %d\n", trocas);
    printf("Total de Passos/Particoes: %d\n", passo);
    printf("Quadros capturados para animacao: %d\n", total_passos);
    printf("==================================================\n");
    printf("Tempo de execucao: %.4lf milissegundos\n", ((double)t / CLOCKS_PER_SEC) * 1000.0);

    // Inicialização da Janela com tamanho estendido para abrigar o texto vertical
    InitWindow(1100, 650, "Visualizador Quicksort - N=100");
    SetTargetFPS(60);

    int quadro_atual = 0;
    float tempo_acumulado = 0.0f;
    float velocidade = 0.05f;
    bool pausado = false;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) pausado = !pausado;

        if (IsKeyPressed(KEY_R)) {
            quadro_atual = 0;
            pausado = false;
        }

        if (IsKeyPressed(KEY_RIGHT) && quadro_atual < total_passos - 1) {
            quadro_atual++;
        }

        if (IsKeyPressed(KEY_LEFT) && quadro_atual > 0) {
            quadro_atual--;
        }

        if (IsKeyPressed(KEY_UP) && velocidade > 0.005f) {
            velocidade -= 0.005f;
        }

        if (IsKeyPressed(KEY_DOWN) && velocidade < 0.5f) {
            velocidade += 0.01f;
        }

        if (!pausado) {
            tempo_acumulado += GetFrameTime();
            if (tempo_acumulado >= velocidade) {
                tempo_acumulado = 0.0f;
                if (quadro_atual < total_passos - 1) {
                    quadro_atual++;
                }
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            PassoAnimacao p = historico[quadro_atual];

            desenharVetor(p.vetor, N, p.pivo_idx, p.troca_i, p.troca_j);

            // Painel Esquerdo: Status
            DrawRectangle(10, 10, 270, 100, Fade(LIGHTGRAY, 0.9f));
            DrawRectangleLines(10, 10, 270, 100, GRAY);

            DrawText(TextFormat("Quadro: %d / %d", quadro_atual + 1, total_passos), 20, 20, 18, BLACK);
            DrawText(TextFormat("Status: %s", pausado ? "PAUSADO" : "RODANDO"), 20, 45, 18, pausado ? RED : DARKGREEN);
            DrawText(TextFormat("Intervalo: %.3fs/passo", velocidade), 20, 70, 15, DARKGRAY);

            // Painel Direito: Controles
            int larguraControles = 290;
            int posXControles = GetScreenWidth() - larguraControles - 10;
            int posYControles = 10;

            DrawRectangle(posXControles, posYControles, larguraControles, 125, Fade(LIGHTGRAY, 0.9f));
            DrawRectangleLines(posXControles, posYControles, larguraControles, 125, GRAY);

            DrawText("CONTROLES", posXControles + 10, posYControles + 8, 15, BLACK);
            DrawText("[ESPAÇO] Pausar / Retomar", posXControles + 10, posYControles + 28, 13, DARKGRAY);
            DrawText("[R] Reiniciar", posXControles + 10, posYControles + 45, 13, DARKGRAY);
            DrawText("[<- / ->] Avançar / Voltar Quadro", posXControles + 10, posYControles + 62, 13, DARKGRAY);
            DrawText("[CIMA / BAIXO] Alterar Velocidade", posXControles + 10, posYControles + 79, 13, DARKGRAY);
            DrawText("Amarelo: Pivô | Vermelho: Troca", posXControles + 10, posYControles + 100, 13, DARKBLUE);

        EndDrawing();
    }

    CloseWindow();
    free(vetor);

    return 0;
}