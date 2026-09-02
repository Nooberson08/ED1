#include "raylib.h"
#include <stdlib.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA 600

#define TAM_CELULA 40

#define LINHAS (ALTURA_JANELA / TAM_CELULA)
#define COLUNAS (LARGURA_JANELA / TAM_CELULA)

typedef struct {
    Vector2 pos;
    Vector2 vel;
    float raio;
    Color cor;
} Bola;


//CRIA A MATRIZ DINÂMICA
   

int **criarMatriz(int linhas, int colunas)
{
    int **matriz = (int **)malloc(linhas * sizeof(int *));

    if (matriz == NULL) {
        return NULL;
    }

    for (int i = 0; i < linhas; i++) {

        matriz[i] = (int *)malloc(colunas * sizeof(int));

        if (matriz[i] == NULL) {

            for (int j = 0; j < i; j++) {
                free(matriz[j]);
            }

            free(matriz);
            return NULL;
        }

        //Começamos todas as células com 0.
         
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = 0;
        }
    }

    return matriz;
}


//LIBERA A MATRIZ

void liberarMatriz(int **matriz, int linhas)
{
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }

    free(matriz);
}


// CRIA AS BOLAS
  

Bola *criarBolas(int quantidade)
{
    Bola *bolas = (Bola *)malloc(
        quantidade * sizeof(Bola)
    );

    if (bolas == NULL) {
        return NULL;
    }

    for (int i = 0; i < quantidade; i++) {

        Bola *b = bolas + i;

        b->pos = (Vector2){
            GetRandomValue(50, LARGURA_JANELA - 50),
            GetRandomValue(50, ALTURA_JANELA - 50)
        };

        b->vel = (Vector2){
            GetRandomValue(-3, 3),
            GetRandomValue(-3, 3)
        };

        //Evita que a bola fique parada.

        if (b->vel.x == 0) {
            b->vel.x = 2;
        }

        if (b->vel.y == 0) {
            b->vel.y = 2;
        }

        b->raio = 10;

        b->cor = (Color){
            GetRandomValue(50, 255),
            GetRandomValue(50, 255),
            GetRandomValue(50, 255),
            255
        };
    }

    return bolas;
}


//ATUALIZA A BOLA

void atualizarBola(Bola *b)
{
    b->pos.x += b->vel.x;
    b->pos.y += b->vel.y;

    //Colisão com as laterais.
     

    if (b->pos.x - b->raio < 0 ||
        b->pos.x + b->raio > LARGURA_JANELA) {

        b->vel.x *= -1;
    }

    //Colisão com o topo e o fundo.
    if (b->pos.y - b->raio < 0 ||
        b->pos.y + b->raio > ALTURA_JANELA) {

        b->vel.y *= -1;
    }
}


    //DESENHA A MATRIZ
  

void desenharMatriz(
    int **matriz,
    int linhas,
    int colunas
)
{
    for (int i = 0; i < linhas; i++) {

        for (int j = 0; j < colunas; j++) {

            int x = j * TAM_CELULA;
            int y = i * TAM_CELULA;

            
            
            //Se a célula foi visitada, usamos uma cor diferente.

            if (matriz[i][j] == 1) {

                DrawRectangle(
                    x,
                    y,
                    TAM_CELULA,
                    TAM_CELULA,
                    LIGHTGRAY
                );

            } else {

                DrawRectangle(
                    x,
                    y,
                    TAM_CELULA,
                    TAM_CELULA,
                    DARKGRAY
                );
            }

            //Desenha as linhas da grade.

            DrawRectangleLines(
                x,
                y,
                TAM_CELULA,
                TAM_CELULA,
                GRAY
            );
        }
    }
}


//MARCA A CÉLULA VISITADA


void marcarCelulaVisitada(
    int **matriz,
    int linhas,
    int colunas,
    Bola *b
)
{

    int coluna = (int)(
        b->pos.x / TAM_CELULA
    );

    int linha = (int)(
        b->pos.y / TAM_CELULA
    );



    if (linha >= 0 && linha < linhas &&
        coluna >= 0 && coluna < colunas) {


        matriz[linha][coluna] = 1;
    }
}


//CONTA AS CÉLULAS VISITADAS

int contarCelulasVisitadas(
    int **matriz,
    int linhas,
    int colunas
)
{
    int contador = 0;

    for (int i = 0; i < linhas; i++) {

        for (int j = 0; j < colunas; j++) {

            if (matriz[i][j] == 1) {
                contador++;
            }
        }
    }

    return contador;
}


//FUNÇÃO PRINCIPAL

int main(void)
{


    InitWindow(
        LARGURA_JANELA,
        ALTURA_JANELA,
        "Exercicio 2 - Matriz como Mapa de Calor"
    );

    SetTargetFPS(60);


    //CRIA A MATRIZ

    int linhas = LINHAS;
    int colunas = COLUNAS;

    int **matriz = criarMatriz(
        linhas,
        colunas
    );

    if (matriz == NULL) {

        CloseWindow();

        return 1;
    }


    //CRIA AS BOLAS

    int quantidadeBolas = 12;

    Bola *bolas = criarBolas(
        quantidadeBolas
    );

    if (bolas == NULL) {

        liberarMatriz(
            matriz,
            linhas
        );

        CloseWindow();

        return 1;
    }


    //LOOP PRINCIPAL

    while (!WindowShouldClose()) {


        //ATUALIZA AS BOLAS

        for (int i = 0; i < quantidadeBolas; i++) {

            /*
             * bolas + i é equivalente a &bolas[i].
             */

            atualizarBola(
                bolas + i
            );


            //MARCA A CÉLULA VISITADA

            marcarCelulaVisitada(
                matriz,
                linhas,
                colunas,
                bolas + i
            );
        }


        //CONTA AS CÉLULAS VISITADAS

        int visitadas = contarCelulasVisitadas(
            matriz,
            linhas,
            colunas
        );


        //DESENHA

        BeginDrawing();

        ClearBackground(RAYWHITE);



        desenharMatriz(
            matriz,
            linhas,
            colunas
        );



        for (int i = 0; i < quantidadeBolas; i++) {

            DrawCircleV(
                bolas[i].pos,
                bolas[i].raio,
                bolas[i].cor
            );
        }


        //MOSTRA O CONTADOR

        DrawRectangle(
            0,
            0,
            300,
            45,
            Fade(BLACK, 0.75f)
        );

        DrawText(
            TextFormat(
                "Celulas visitadas: %d",
                visitadas
            ),
            10,
            10,
            20,
            WHITE
        );


        EndDrawing();
    }


    //LIBERA A MEMÓRIA

    free(bolas);

    liberarMatriz(
        matriz,
        linhas
    );


    //FECHA A JANELA

    CloseWindow();

    return 0;
}