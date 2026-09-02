#include "raylib.h"
#include <stdlib.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA 600

typedef struct {
    Vector2 pos;
    Vector2 vel;
    float raio;
    Color cor;
} Bola;


//Cria o vetor inicial de bolas
Bola *criarBolas(int quantidade)
{
    Bola *bolas = (Bola *)malloc(quantidade * sizeof(Bola));

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

        //Evita bola parada
        if (b->vel.x == 0)
            b->vel.x = 2;

        if (b->vel.y == 0)
            b->vel.y = 2;

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


//Atualiza a posição da bola
void atualizarBola(Bola *b)
{
    b->pos.x += b->vel.x;
    b->pos.y += b->vel.y;

    //Colisão com as laterais
    if (b->pos.x - b->raio < 0 ||
        b->pos.x + b->raio > LARGURA_JANELA) {

        b->vel.x *= -1;
    }

    //Colisão com o topo e o fundo
    if (b->pos.y - b->raio < 0 ||
        b->pos.y + b->raio > ALTURA_JANELA) {

        b->vel.y *= -1;
    }
}


//Adiciona uma nova bola usando realloc
void adicionarBola(Bola **bolas, int *quantidadeBolas)
{
    int novaQuantidade = *quantidadeBolas + 1;

    Bola *temp = realloc(
        *bolas,
        novaQuantidade * sizeof(Bola)
    );

    if (temp == NULL) {
        return;
    }

    *bolas = temp;
    *quantidadeBolas = novaQuantidade;

    // A nova bola será a última
    Bola *b = *bolas + (novaQuantidade - 1);

    b->pos = (Vector2){
        GetRandomValue(50, LARGURA_JANELA - 50),
        GetRandomValue(50, ALTURA_JANELA - 50)
    };

    b->vel = (Vector2){
        GetRandomValue(-3, 3),
        GetRandomValue(-3, 3)
    };

    if (b->vel.x == 0)
        b->vel.x = 2;

    if (b->vel.y == 0)
        b->vel.y = 2;

    b->raio = 10;

    b->cor = (Color){
        GetRandomValue(50, 255),
        GetRandomValue(50, 255),
        GetRandomValue(50, 255),
        255
    };
}


//Remove a última bola usando realloc
void removerBola(Bola **bolas, int *quantidadeBolas)
{
    /* Não deixa a quantidade ficar negativa */
    if (*quantidadeBolas <= 0) {
        return;
    }

    int novaQuantidade = *quantidadeBolas - 1;

    //Se não houver mais bolas, libera a memória
    if (novaQuantidade == 0) {

        free(*bolas);

        *bolas = NULL;
        *quantidadeBolas = 0;

        return;
    }

    Bola *temp = realloc(
        *bolas,
        novaQuantidade * sizeof(Bola)
    );

    if (temp == NULL) {
        return;
    }

    *bolas = temp;
    *quantidadeBolas = novaQuantidade;
}


int main(void)
{
    //Inicializa a janela
    InitWindow(
        LARGURA_JANELA,
        ALTURA_JANELA,
        "Exercicio 1 - Alocacao Dinamica"
    );

    SetTargetFPS(60);


    //Quantidade inicial definida no exercício
    int quantidadeBolas = 12;

    /* Cria as bolas */
    Bola *bolas = criarBolas(quantidadeBolas);

    if (bolas == NULL) {
        CloseWindow();
        return 1;
    }


    //Loop principal
    while (!WindowShouldClose()) {


        if (IsKeyPressed(KEY_SPACE)) {

            adicionarBola(
                &bolas,
                &quantidadeBolas
            );
        }


        
        if (IsKeyPressed(KEY_BACKSPACE)) {

            removerBola(
                &bolas,
                &quantidadeBolas
            );
        }


       
        for (int i = 0; i < quantidadeBolas; i++) {

            
            atualizarBola(bolas + i);
        }


        //Desenho
        BeginDrawing();

        ClearBackground(RAYWHITE);


        //Desenha todas as bolas
        for (int i = 0; i < quantidadeBolas; i++) {

            DrawCircleV(
                bolas[i].pos,
                bolas[i].raio,
                bolas[i].cor
            );
        }


        //Mostra a quantidade de bolas
        DrawText(
            TextFormat(
                "Quantidade de bolas: %d",
                quantidadeBolas
            ),
            20,
            20,
            25,
            BLACK
        );


        //Instruções
        DrawText(
            "ESPACO = adicionar bola",
            20,
            55,
            20,
            DARKGRAY
        );

        DrawText(
            "BACKSPACE = remover bola",
            20,
            80,
            20,
            DARKGRAY
        );


        EndDrawing();
    }


    //Libera a memória
    free(bolas);

    //Fecha a janela
    CloseWindow();

    return 0;
}