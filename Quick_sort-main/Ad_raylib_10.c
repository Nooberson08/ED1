#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

// Estrutura para armazenar cada quadro da animação
typedef struct {
    int vetor[100];
    int pivo_idx;
    int troca_i;
    int troca_j;
} PassoAnimacao;

PassoAnimacao historico[500];
int total_passos = 0;

int comparacoes = 0;
int trocas = 0;
int passo = 0;

void registrar_passo(int values[], int N, int pivo_idx, int pos_i, int pos_j) {
    for (int k = 0; k < N; k++) {
        historico[total_passos].vetor[k] = values[k];
    }
    historico[total_passos].pivo_idx = pivo_idx;
    historico[total_passos].troca_i = pos_i;
    historico[total_passos].troca_j = pos_j;
    total_passos++;
}

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

            // Realiza a troca
            aux = values[i];
            values[i] = values[j];
            values[j] = aux;

            // SALVA O "RETRATO" APÓS A TROCA
            registrar_passo(values, total_N, pivo_index, i, j);

            trocas++;
            i++;
            j--;
        }
    }
    
    if (begin < j) quicksort(values, begin, j + 1, total_N, estatistica);
    if (i < end) quicksort(values, i, end, total_N, estatistica);
}

void desenharVetor(int vetor[], int N, int pivo_idx, int i_idx, int j_idx) {
    int larguraTela = GetScreenWidth();
    int alturaTela = GetScreenHeight();
    int larguraBarra = larguraTela / N;

    for (int i = 0; i < N; i++) {
        int alturaBarra = vetor[i] * 3; 
        int posX = i * larguraBarra;
        int posY = alturaTela - alturaBarra;

        // Cor padrão: Azul
        Color corBarra = BLUE;

        // Destaque visual
        if (i == pivo_idx) corBarra = YELLOW;      // Amarelo para o pivô
        else if (i == i_idx || i == j_idx) corBarra = RED; // Vermelho para os elementos trocados

        DrawRectangle(posX, posY, larguraBarra - 2, alturaBarra, corBarra);
        DrawText(TextFormat("%d", vetor[i]), posX + (larguraBarra / 4), posY - 20, 15, BLACK);
    }
}

int main() {
    int N;
    srand(time(NULL));

    // Gerar e ler arquivo
    FILE *arq = fopen("Dados10.txt", "w");
    if (!arq) return 1;
    fprintf(arq, "10\n");
    for (int a = 0; a < 10; a++) fprintf(arq, "%d ", rand() % 100);
    fclose(arq);

    arq = fopen("Dados10.txt", "r");
    if (!arq) return 1;
    fscanf(arq, "%d", &N);
    int *vetor = (int *) malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) fscanf(arq, "%d", &vetor[i]);
    fclose(arq);

    FILE *estatistica = fopen("Saida10.txt", "w");

    // 1. GRAVA O ESTADO INICIAL
    registrar_passo(vetor, N, -1, -1, -1);

    // 2. EXECUTA O QUICKSORT E GUARDA OS PASSOS
    quicksort(vetor, 0, N, N, estatistica);

    fclose(estatistica);

    // 3. INTERFACE GRÁFICA INTERATIVA
    InitWindow(900, 500, "Visualizador de Quicksort - Projeto Final");
    SetTargetFPS(60);

    int quadro_atual = 0;
    float tempo_acumulado = 0.0f;
    float velocidade = 0.5f; // Tempo em segundos por passo (0.5s)
    bool pausado = false;

    while (!WindowShouldClose()) {
        // --- CONTROLES DE TECLADO ---
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

        if (IsKeyPressed(KEY_UP) && velocidade > 0.05f) {
            velocidade -= 0.05f;
        }

        if (IsKeyPressed(KEY_DOWN) && velocidade < 2.0f) {
            velocidade += 0.05f;
        }

        // --- AVANÇO AUTOMÁTICO DO TEMPO ---
        if (!pausado) {
            tempo_acumulado += GetFrameTime();
            if (tempo_acumulado >= velocidade) {
                tempo_acumulado = 0.0f;
                if (quadro_atual < total_passos - 1) {
                    quadro_atual++;
                }
            }
        }

        // --- DESENHO NA TELA ---
        BeginDrawing();
            ClearBackground(RAYWHITE);

            PassoAnimacao p = historico[quadro_atual];

            // Desenha as barras do vetor
            desenharVetor(p.vetor, N, p.pivo_idx, p.troca_i, p.troca_j);

            // --- PAINEL ESQUERDO: STATUS DO ALGORITMO ---
            DrawRectangle(10, 10, 260, 95, Fade(LIGHTGRAY, 0.85f));
            DrawRectangleLines(10, 10, 260, 95, GRAY);

            DrawText(TextFormat("Passo: %d / %d", quadro_atual + 1, total_passos), 20, 20, 20, BLACK);
            DrawText(TextFormat("Status: %s", pausado ? "PAUSADO" : "RODANDO"), 20, 45, 18, pausado ? RED : DARKGREEN);
            DrawText(TextFormat("Intervalo: %.2fs/passo", velocidade), 20, 70, 16, DARKGRAY);

            // --- PAINEL DIREITO: CONTROLES E LEGENDA (Canto Superior Direito) ---
            int larguraControles = 290;
            int posXControles = GetScreenWidth() - larguraControles - 10; // Calcula a posição inicial no lado direito
            int posYControles = 10;

            DrawRectangle(posXControles, posYControles, larguraControles, 125, Fade(LIGHTGRAY, 0.85f));
            DrawRectangleLines(posXControles, posYControles, larguraControles, 125, GRAY);

            DrawText("CONTROLES", posXControles + 10, posYControles + 8, 15, BLACK);
            DrawText("[ESPAÇO] Pausar / Retomar", posXControles + 10, posYControles + 28, 13, DARKGRAY);
            DrawText("[R] Reiniciar", posXControles + 10, posYControles + 45, 13, DARKGRAY);
            DrawText("[<- / ->] Avançar / Voltar Passo", posXControles + 10, posYControles + 62, 13, DARKGRAY);
            DrawText("[CIMA / BAIXO] Alterar Velocidade", posXControles + 10, posYControles + 79, 13, DARKGRAY);
            DrawText("Amarelo: Pivô | Vermelho: Troca", posXControles + 10, posYControles + 100, 13, DARKBLUE);

        EndDrawing();
    }

    CloseWindow();
    free(vetor);
    return 0;
}