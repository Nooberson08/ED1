typedef struct Fila Fila;

Fila* criarFila(void);
void liberarFila(Fila *f);

int filaVazia(Fila *f);
int tamanhoFila(Fila *f);

int enqueue(Fila *f, int valor);
int dequeue(Fila *f, int *valorRemovido);
int front(Fila *f, int *valor);
int back(Fila *f, int *valor);
void imprimirFila(Fila *f);
