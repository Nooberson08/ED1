typedef struct No {
    int dado;
    struct No* proximo;
} No;

typedef struct Pilha {
    No* topo;
} Pilha;

void inicializar(Pilha *pilha);
int estaVazia(Pilha *pilha);
void push(Pilha *pilha, int valor);
int pop(Pilha *pilha);
int peek(Pilha *pilha, int *valor);
void imprimirPilha(Pilha *pilha);
int contarElementos(Pilha *pilha);
void liberarPilha(Pilha *pilha);