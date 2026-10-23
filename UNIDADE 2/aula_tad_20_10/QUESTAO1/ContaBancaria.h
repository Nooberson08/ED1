typedef struct conta ContaBancaria;

ContaBancaria* criar_conta(char titular [200], int numero, float saldo_inicial);
void liberar_conta(ContaBancaria* c);
void depositar (ContaBancaria* c, float valor);
int sacar (ContaBancaria* c, float valor);
int transferir (ContaBancaria* origem, ContaBancaria* destino, float valor);
float consultar_saldo (ContaBancaria* c);

