#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#define MAX_PASSOS 30000

// Estrutura para armazenar cada quadro da animação
typedef struct {
    int vetor[1000];
    int pivo_idx;
    int troca_i;
    int troca_j;
} PassoAnimacao;

PassoAnimacao *historico = NULL;
int total_passos = 0;

int comparacoes = 0;
int trocas = 0;
int passo = 0;

void registrar_passo(int values[], int N, int pivo_idx, int pos_i, int pos_j) {
    if (historico != NULL && total_passos < MAX_PASSOS) {
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

            // Troca os elementos de posição
            aux = values[i];
            values[i] = values[j];
            values[j] = aux;

            // GRAVA O PASSO DA ANIMAÇÃO
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
    int alturaDisponivel = alturaTela - 160;

    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    int barraHover = -1;

    // Detecta qual barra o mouse está apontando
    if (mouseY > 150 && mouseX >= 0 && mouseX < larguraTela) {
        barraHover = (int)(mouseX / larguraBarra);
        if (barraHover >= N) barraHover = N - 1;
    }

    for (int i = 0; i < N; i++) {
        // Escala proporcional até 10.000
        int alturaBarra = (int)((float)vetor[i] / 10000.0f * alturaDisponivel);
        if (alturaBarra < 2) alturaBarra = 2;

        float posX = i * larguraBarra;
        float posY = alturaTela - alturaBarra;

        Color corBarra = BLUE;

        if (i == pivo_idx) {
            corBarra = YELLOW;
        } else if (i == i_idx || i == j_idx) {
            corBarra = RED;
        } else if (i == barraHover) {
            corBarra = GREEN; // Destaque ao passar o mouse
        }

        DrawRectangle((int)posX, (int)posY, (int)(larguraBarra > 1.0f ? larguraBarra : 1.0f), alturaBarra, corBarra);
    }

    // Se o mouse estiver sobre uma barra, exibe a Tooltip com o valor exato
    if (barraHover != -1) {
        char txt[50];
        snprintf(txt, sizeof(txt), "Indice [%d]: %d", barraHover, vetor[barraHover]);
        int txtWidth = MeasureText(txt, 16);

        int posXTooltip = mouseX + 15;
        if (posXTooltip + txtWidth + 10 > larguraTela) posXTooltip = mouseX - txtWidth - 15;

        DrawRectangle(posXTooltip - 5, mouseY - 25, txtWidth + 10, 25, Fade(BLACK, 0.8f));
        DrawRectangleLines(posXTooltip - 5, mouseY - 25, txtWidth + 10, 25, GREEN);
        DrawText(txt, posXTooltip, mouseY - 20, 16, WHITE);
    }
}

int main() {
    clock_t t;
    int N;
    int i;
    
    srand(time(NULL));

    // Aloca a memória dinâmica para o histórico da animação
    historico = (PassoAnimacao *) malloc(MAX_PASSOS * sizeof(PassoAnimacao));
    if (historico == NULL) {
        printf("Erro de alocacao de memoria para o historico da animacao!\n");
        return 1;
    }

    // 1. GERAÇÃO DO ARQUIVO COM 1000 DADOS
    FILE *arq = fopen("Dados1000.txt", "w");
    if (arq == NULL) {
        printf("Erro ao criar o arquivo Dados1000.txt!\n");
        free(historico);
        return 1;
    }

    fprintf(arq, "1000\n");
    for (int a = 0; a < 1000; a++) {
        fprintf(arq, "%d ", rand() % 10000);
    }
    fclose(arq);
        
    // 2. LEITURA DOS DADOS
    arq = fopen("Dados1000.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo Dados1000.txt para leitura!\n");
        free(historico);
        return 1;
    }

    fscanf(arq, "%d", &N);

    int *vetor = (int *) malloc(N * sizeof(int));
    if (vetor == NULL) {
        printf("Erro de alocacao de memoria!\n");
        fclose(arq);
        free(historico);
        return 1;
    }

    for (i = 0; i < N; i++) {
        fscanf(arq, "%d", &vetor[i]);
    }
    fclose(arq);

    FILE *estatistica = fopen("Saida1000.txt", "w");
    if (estatistica == NULL) {
        printf("Erro ao criar o arquivo Saida1000.txt!\n");
        free(vetor);
        free(historico);
        return 1;
    }

    fprintf(estatistica, "Array antes da ordenacao: ");
    for (int k = 0; k < N; k++) {
        fprintf(estatistica, "%d ", vetor[k]);
    }
    fprintf(estatistica, "\n");

    // Registra o estado inicial
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

    // Relatório impresso no terminal
    printf("--- RELATORIO DE EXECUCAO (QUICK SORT) ---\n");
    printf("Total de elementos: %d\n", N);
    printf("Total de Comparacoes: %d\n", comparacoes);
    printf("Total de Trocas: %d\n", trocas);
    printf("Total de Passos/Particoes: %d\n", passo);
    printf("Quadros capturados para animacao: %d\n", total_passos);
    printf("==================================================\n");
    printf("Tempo de execucao: %.4lf milissegundos\n", ((double)t / CLOCKS_PER_SEC) * 1000.0);

    // 3. VISUALIZADOR RAYLIB
    InitWindow(1280, 720, "Visualizador Quicksort - N=1000");
    SetTargetFPS(60);

    int quadro_atual = 0;
    float tempo_acumulado = 0.0f;
    float velocidade = 0.001f; // Animação rápida por padrão para N=1000
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

        if (IsKeyPressed(KEY_UP) && velocidade > 0.0005f) {
            velocidade /= 2.0f;
        }

        if (IsKeyPressed(KEY_DOWN) && velocidade < 0.5f) {
            velocidade *= 2.0f;
        }

        // --- AVANÇO DO TEMPO ---
        if (!pausado) {
            tempo_acumulado += GetFrameTime();
            if (tempo_acumulado >= velocidade) {
                tempo_acumulado = 0.0f;
                if (quadro_atual < total_passos - 1) {
                    quadro_atual++;
                }
            }
        }

        // --- RENDERIZAÇÃO ---
        BeginDrawing();
            ClearBackground(RAYWHITE);

            PassoAnimacao p = historico[quadro_atual];

            desenharVetor(p.vetor, N, p.pivo_idx, p.troca_i, p.troca_j);

            // --- PAINEL ESQUERDO: STATUS DO PASSO ATUAL ---
            DrawRectangle(10, 10, 340, 120, Fade(LIGHTGRAY, 0.9f));
            DrawRectangleLines(10, 10, 340, 120, GRAY);

            DrawText(TextFormat("Quadro: %d / %d", quadro_atual + 1, total_passos), 20, 20, 18, BLACK);
            DrawText(TextFormat("Status: %s", pausado ? "PAUSADO" : "RODANDO"), 20, 42, 18, pausado ? RED : DARKGREEN);
            
            int valPivo = (p.pivo_idx != -1) ? p.vetor[p.pivo_idx] : -1;
            int valI = (p.troca_i != -1) ? p.vetor[p.troca_i] : -1;
            int valJ = (p.troca_j != -1) ? p.vetor[p.troca_j] : -1;

            DrawText(TextFormat("Pivo: Indice %d (Valor: %d)", p.pivo_idx, valPivo), 20, 65, 14, DARKBROWN);
            DrawText(TextFormat("Troca: [%d]:%d <-> [%d]:%d", p.troca_i, valI, p.troca_j, valJ), 20, 85, 14, RED);
            DrawText("Passe o mouse sobre as barras p/ ver o valor", 20, 105, 13, DARKGRAY);

            // --- PAINEL DIREITO: CONTROLES ---
            int larguraControles = 310;
            int posXControles = GetScreenWidth() - larguraControles - 10;
            int posYControles = 10;

            DrawRectangle(posXControles, posYControles, larguraControles, 125, Fade(LIGHTGRAY, 0.9f));
            DrawRectangleLines(posXControles, posYControles, larguraControles, 125, GRAY);

            DrawText("CONTROLES", posXControles + 10, posYControles + 8, 15, BLACK);
            DrawText("[ESPAÇO] Pausar / Retomar", posXControles + 10, posYControles + 28, 13, DARKGRAY);
            DrawText("[R] Reiniciar", posXControles + 10, posYControles + 45, 13, DARKGRAY);
            DrawText("[<- / ->] Avançar / Voltar Quadro", posXControles + 10, posYControles + 62, 13, DARKGRAY);
            DrawText("[CIMA / BAIXO] Acelerar / Desacelerar", posXControles + 10, posYControles + 79, 13, DARKGRAY);
            DrawText("Amarelo: Pivô | Vermelho: Troca | Verde: Mouse", posXControles + 10, posYControles + 100, 13, DARKBLUE);

        EndDrawing();
    }

    CloseWindow();
    free(vetor);
    free(historico);

    return 0;
}