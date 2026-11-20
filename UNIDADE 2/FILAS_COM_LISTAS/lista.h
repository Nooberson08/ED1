typedef struct Lista Lista;

Lista* criarLista(void);
void liberarLista(Lista *l);

int listaVazia(Lista *l);
int tamanhoLista(Lista *l);

int inserirFimLista(Lista *l, int valor);
int removerInicioLista(Lista *l, int *valorRemovido);
int consultarInicioLista(Lista *l, int *valor);
int consultarFimLista(Lista *l, int *valor);
void imprimirLista(Lista *l);
