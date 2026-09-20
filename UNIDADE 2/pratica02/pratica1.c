#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[50];
    char id[20];
    float salario;
} Funcionario;

void imprime (FILE*funcionarios, Funcionario f){
    fprintf(funcionarios, "Nome: %s", f.nome);
    fprintf(funcionarios, "ID: %s\n", f.id);
    fprintf(funcionarios, "Salario: %.2f\n", f.salario);
} //usada para gravar os dados do funcionario no arquivo de texto



int main() {

Funcionario f;    //declaração da variável f do tipo Funcionario

FILE* funcionarios; // criação do ponteiro para o arquivo de texto
funcionarios = fopen("entrada.txt", "w"); // Abre (ou cria, se não existir) um arquivo de texto chamado entrada.txt no modo de escrita ("w" de write). O ponteiro funcionarios passa a representar esse arquivo.
if(funcionarios==NULL){ // Verifica se o arquivo foi aberto corretamente. Se fopen retornar NULL, significa que houve um erro ao abrir o arquivo.
    printf("Erro ao abrir o arquivo.\n");
    return 1;
}

    printf("O arquivo tipo txt esta sendo criado.\n");

    printf("Digite o ID do funcionario: "); // Solicita ao usuário que digite o ID do funcionário e armazena o valor na variável f.id usando scanf. O %s indica que será lida uma string.
    scanf("%s", f.id); // o "f.id" indica que o valor digitado será armazenado no campo id da estrutura f do tipo Funcionario.

    
    getchar(); //Limpa o "Enter" (\n) que sobra no buffer do teclado após o scanf anterior, evitando que ele atrapalhe a próxima leitura de texto.

    printf("Digite o nome do funcionario: ");
    fgets(f.nome, sizeof(f.nome), stdin); // Pedem o nome do funcionário e usam a função fgets para ler a string digitada (permitindo até que o nome tenha espaços) e guardá-la em f.nome

    printf("Digite o salario do funcionario: ");
    scanf("%f", &f.salario);



imprime (funcionarios, f);

fclose(funcionarios); // Fecha o arquivo de forma correta e segura, garantindo que todas as alterações sejam salvas definitivamente no disco do computador.




    return 0;
}