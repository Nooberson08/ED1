
//TIPO EXPORTADO
typedef struct ponto Ponto;

//FUNÇOES EXPORTADAS
Ponto * pto_cria (float x, float y);
void pto_libera (Ponto* p);
void pto_acessa (Ponto* p, float* x, float* y);
void pto_atribui (Ponto* p, float x, float y);
float pto_distancia (Ponto* p1, Ponto* p2);
