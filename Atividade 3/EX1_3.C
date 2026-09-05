/*
 * Exercício 1 - Union + Enum + Struct + Alocação Dinâmica com raylib
 * Adição do item ITEM_ESCUDO e do atributo de armadura no Jogador.
 */

#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA  600
#define RAIO_JOGADOR   20.0f
#define TOTAL_ITENS    10

typedef enum {
    ITEM_ARMA,
    ITEM_POCAO,
    ITEM_ESCUDO // Novo tipo de item adicionado
} TipoItem;

typedef struct {
    float dano;
    int   alcance;
} DadosArma;

typedef struct {
    int cura;
} DadosPocao;

/* Nova struct específica para os dados do escudo */
typedef struct {
    int absorcao;
} DadosEscudo;

/* Union expandida para acomodar o novo DadosEscudo */
typedef union {
    DadosArma   arma;
    DadosPocao  pocao;
    DadosEscudo escudo;
} DadosItem;

typedef struct {
    Vector2   pos;
    float     raio;
    TipoItem  tipo;
    DadosItem dados;
    bool      coletado;
} Item;

typedef struct {
    Vector2 pos;
    float   raio;
    int     vida;
    float   dano;
    int     armadura; // Novo campo adicionado na struct do jogador
} Jogador;

Item *criarItens(int quantidade) {
    Item *itens = (Item *)malloc(quantidade * sizeof(Item));
    if (itens == NULL) return NULL;

    for (int i = 0; i < quantidade; i++) {
        Item *it = (itens + i);
        it->pos      = (Vector2){ GetRandomValue(30, LARGURA_JANELA - 30),
                                  GetRandomValue(30, ALTURA_JANELA - 30) };
        it->raio     = 12.0f;
        it->coletado = false;
        
        // Sorteia entre 0, 1 e 2 (ITEM_ARMA, ITEM_POCAO, ITEM_ESCUDO)
        it->tipo     = (TipoItem)GetRandomValue(ITEM_ARMA, ITEM_ESCUDO);

        if (it->tipo == ITEM_ARMA) {
            it->dados.arma.dano    = (float)GetRandomValue(2, 8);
            it->dados.arma.alcance = GetRandomValue(1, 3);
        } else if (it->tipo == ITEM_POCAO) {
            it->dados.pocao.cura = GetRandomValue(10, 30);
        } else {
            // Preenche os dados específicos do escudo sorteado
            it->dados.escudo.absorcao = GetRandomValue(5, 15);
        }
    }
    return itens;
}

void aplicarItem(Jogador *j, Item *item) {
    switch (item->tipo) {
        case ITEM_ARMA:
            j->dano += item->dados.arma.dano;
            break;
        case ITEM_POCAO:
            j->vida += item->dados.pocao.cura;
            break;
        case ITEM_ESCUDO: // Trata o efeito do novo item de escudo
            j->armadura += item->dados.escudo.absorcao;
            break;
    }
    item->coletado = true;
}

bool colidiu(Vector2 a, float raioA, Vector2 b, float raioB) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float distancia2 = dx * dx + dy * dy;
    float somaRaios2 = (raioA + raioB) * (raioA + raioB);
    return distancia2 <= somaRaios2;
}

void desenharItem(Item *item) {
    if (item->coletado) return;
    
    Color cor = RED;
    if (item->tipo == ITEM_ARMA) {
        cor = RED;
    } else if (item->tipo == ITEM_POCAO) {
        cor = GREEN;
    } else if (item->tipo == ITEM_ESCUDO) {
        cor = SKYBLUE; // Escudo representado pela cor azul claro
    }

    DrawCircleV(item->pos, item->raio, cor);
}

int main(void) {
    srand((unsigned int)time(NULL));

    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Exercicio 1 - Escudo");
    SetTargetFPS(60);

    Jogador jogador = { { LARGURA_JANELA / 2.0f, ALTURA_JANELA / 2.0f }, RAIO_JOGADOR, 100, 5.0f, 0 };
    Item *itens = criarItens(TOTAL_ITENS);

    while (!WindowShouldClose()) {
        float vel = 250.0f * GetFrameTime();
        if (IsKeyDown(KEY_RIGHT)) jogador.pos.x += vel;
        if (IsKeyDown(KEY_LEFT))  jogador.pos.x -= vel;
        if (IsKeyDown(KEY_UP))    jogador.pos.y -= vel;
        if (IsKeyDown(KEY_DOWN))  jogador.pos.y += vel;

        for (int i = 0; i < TOTAL_ITENS; i++) {
            Item *it = (itens + i);
            if (!it->coletado && colidiu(jogador.pos, jogador.raio, it->pos, it->raio)) {
                aplicarItem(&jogador, it);
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            for (int i = 0; i < TOTAL_ITENS; i++) {
                desenharItem(itens + i);
            }

            DrawCircleV(jogador.pos, jogador.raio, BLUE);

            DrawText(TextFormat("Vida: %d   Dano: %.1f   Armadura: %d", jogador.vida, jogador.dano, jogador.armadura), 10, 10, 20, DARKGRAY);
            DrawText("Vermelho = Arma | Verde = Pocao | Azul = Escudo", 10, 34, 16, GRAY);
            DrawText("Setas movem o jogador | ESC sai", 10, ALTURA_JANELA - 25, 16, GRAY);

        EndDrawing();
    }

    free(itens);
    CloseWindow();
    return 0;
}