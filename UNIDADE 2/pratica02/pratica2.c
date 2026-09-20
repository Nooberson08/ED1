#include <stdio.h>
#include <stdlib.h>     

typedef struct {
    char nome[50];
    float nota;
} Aluno;

void imprime (FILE*alunos, Aluno a){
    fprintf(alunos, "Nome: %s", a.nome);
    fprintf(alunos, "Nota: %.2f\n\n", a.nota); // o "." indica que está acessando o campo nota da estrutura a do tipo Aluno. O "\n\n" adiciona duas quebras de linha após a nota para separar visualmente os registros no arquivo.
} //usada para gravar os dados do aluno no arquivo de texto

int main () {
    FILE *alunos = fopen("alunos.txt", "w"); // Abre (ou cria, se não existir) um arquivo de texto chamado entrada.txt no modo de escrita ("w" de write). O ponteiro alunos passa a representar esse arquivo.
    if(alunos==NULL){ // Verifica se o arquivo foi aberto corretamente. Se fopen retornar NULL, significa que houve um erro ao abrir o arquivo.
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    printf("O arquivo tipo txt esta sendo criado.\n\n");

    int quantidade = 0;  //declaração da variável N do tipo inteiro para armazenar a quantidade de alunos que o usuário deseja cadastrar
    Aluno *lista = NULL; //declaração do ponteiro lista do tipo Aluno, que será usado para armazenar dinamicamente os dados dos alunos
    char opcao; //declaração da variável opcao do tipo char, que será usada para armazenar a escolha do usuário sobre continuar cadastrando alunos ou não

    do {
        quantidade++; //incrementa a quantidade de alunos cadastrados
        lista = (Aluno*) realloc(lista, quantidade * sizeof(Aluno)); //realoca a memória para armazenar os dados do novo aluno

        if (lista == NULL) { // Verifica se a realocação de memória foi bem-sucedida. Se realloc retornar NULL, significa que houve um erro na alocação de memória.
            printf("Erro ao alocar memoria.\n");
            return 1;
        }

    
        printf("Digite o nome do aluno %d: ", quantidade);
        fgets(lista[quantidade - 1].nome, sizeof(lista[quantidade - 1].nome), stdin); // Pedem o nome do aluno e usam a função fgets para ler a string digitada (permitindo até que o nome tenha espaços) e guardá-la em lista[quantidade - 1].nome

        printf("Digite a nota do aluno %d: ", quantidade);
        scanf(" %f", &lista[quantidade - 1].nota); // Solicita ao usuário que digite a nota do aluno e armazena o valor na variável lista[quantidade - 1].nota usando scanf. O %f indica que será lido um número de ponto flutuante.

        getchar(); //Limpa o "Enter" (\n) que sobra no buffer do teclado após o scanf anterior, evitando que ele atrapalhe a próxima leitura de texto.


        imprime(alunos, lista[quantidade - 1]); // Chama a função imprime para gravar os dados do aluno no arquivo de texto

        printf("Deseja cadastrar outro aluno? (s/n): ");
        scanf(" %c", &opcao); // Lê a escolha do usuário sobre continuar cadastrando alunos ou não. O espaço antes de %f é usado para ignorar qualquer caractere de nova linha que possa estar no buffer.
        getchar(); //Limpa o "Enter" (\n) que sobra no buffer do teclado após o scanf anterior, evitando que ele atrapalhe a próxima leitura de texto.

    } while (opcao == 's' || opcao == 'S'); // Continua o loop enquanto o usuário quiser cadastrar mais alunos

    free(lista); // Libera a memória alocada dinamicamente para a lista de alunos, evitando vazamentos de memória.
    fclose(alunos); // Fecha o arquivo de forma correta e segura, garantindo que todas as alterações sejam salvas definitivamente no disco do computador.

    printf ("\nDados gravados com sucesso no arquivo alunos.txt!\n");

    return 0;
}