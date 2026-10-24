# Quick sort

Trabalho da unidade 2 da disciplina de ALGORITMOS E ESTRUTURA DE DADOS I .

Implementação do código base antes de fazer a parte gráfica e visual com o raylib.

## Sobre o Projeto

Este repositório contém a implementação prática, testes de desempenho e análise do algoritmo de ordenação **Quicksort** desenvolvido na linguagem C.

## Funcionalidades Principais

1. **Geração de Dados Aleatórios (rand e srand)**:
   A massa de dados utilizada para os testes (como conjuntos de 1.000 e 10.000 elementos) é gerada dinamicamente utilizando as funções rand e srand da biblioteca padrão, garantindo variabilidade de dados a cada execução.

2. **Estratégia de Escolha do Pivô**:
   O algoritmo seleciona o pivô utilizando o cálculo do elemento central do subvetor atual.

   * **Exemplo Prático**: Imagine que estamos analisando um subvetor que vai do índice begin = 4 até end = 10 (ou seja, os elementos nas posições 4, 5, 6, 7, 8 e 9):

     * `end - begin = 10 - 4 = 6` elementos.

     * `(end - begin) / 2 = 6 / 2 = 3` posições a partir do início.

     * `begin + 3 = 4 + 3 = 7` (o elemento na posição 7 é escolhido como pivô).

3. **Cronometragem de Desempenho (time.h)**:
   O tempo de execução de cada ordenação é monitorado utilizando recursos da biblioteca `<time.h>` e a função `clock()`, permitindo avaliar o custo computacional de forma rigorosa.

## Como compilar e executar

1. Certifique-se de ter um compilador C instalado (como o GCC).

2. Abra o terminal na pasta do projeto e compile o código modificando o número após `quick_sort` (10, 100, 1000 ou 10000) para executar o `quick_sort` que deseja:

   ```
   gcc quick_sort10.c -o aula
   
   ```

   Execute:

   ```
   ./aula.exe
   
   ```

3. O código vai gerar um FILE "dados10.txt" onde vai criar, de forma aleatória, 10 elementos para que o `quick_sort` possa ser executado.

4. Após a leitura desse FILE criado anteriormente, será gerado um novo FILE "saida10.txt", onde será impressa a saída do código com o processo executado: comparações, passo a passo, tempo executado, quantidade de elementos.



# Raylib — Instalação no Windows e Linux

Este guia apresenta como instalar e compilar projetos usando a biblioteca **Raylib** para desenvolvimento de jogos em **C** nos sistemas operacionais **Windows** e **Linux**.

A Raylib é uma biblioteca simples e multiplataforma para desenvolvimento de jogos e aplicações gráficas em C/C++.

---

## 📋 Pré-requisitos

Você precisará de:

* Compilador C (`gcc`)
* Git
* CMake
* Raylib

---

# 🪟 Windows

## Opção 1 — MSYS2

A maneira recomendada para trabalhar com C no Windows é utilizar o **MSYS2**.

### 1. Instalar o MSYS2

Baixe o MSYS2 em: [https://www.msys2.org/](https://www.msys2.org/)

Após a instalação, abra o terminal **MSYS2 UCRT64** e atualize os pacotes:

```bash
pacman -Syu
```

Se o terminal solicitar o fechamento, feche-o, abra novamente o **MSYS2 UCRT64** e execute:

```bash
pacman -Su
```

### 2. Instalar o compilador

No terminal **MSYS2 UCRT64**:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
```

Verifique a instalação:

```bash
gcc --version
```

### 3. Instalar a Raylib

Execute:

```bash
pacman -S mingw-w64-ucrt-x86_64-raylib
```

Verifique:

```bash
pkg-config --modversion raylib
```

---

## # Como rodar o codigo no windowns

Para compilar o seu código em C com a Raylib diretamente pelo terminal no Windows (linkando as bibliotecas do sistema como OpenGL, GDI e Multimedia), utilize:

```bash
gcc NomedoArquivo.c -o exe.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

Para executar o programa gerado:

```bash
./exe.exe
```

---

# 🐧 Linux

Os comandos abaixo são voltados principalmente para distribuições baseadas em Debian/Ubuntu.

## 1. Atualizar o sistema e instalar dependências

```bash
sudo apt update
sudo apt install build-essential git cmake pkg-config
```

Instale as dependências gráficas e de áudio:

```bash
sudo apt install \
libasound2-dev \
libx11-dev \
libxrandr-dev \
libxi-dev \
libxcursor-dev \
libxinerama-dev \
libgl1-mesa-dev \
libglu1-mesa-dev
```

---

## 2. Instalar a Raylib

Clone e compile a biblioteca:

```bash
git clone https://github.com/raysan5/raylib.git
cd raylib
mkdir build && cd build
cmake ..
make
sudo make install
sudo ldconfig
```

---

## # Como rodar o codigo no linux

Para compilar o seu arquivo em C no Linux linkando manualmente todas as dependências gráficas, de sistema e threads:

```bash
gcc NomedoArquivo.c -o exe -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

Para executar o programa gerado:

```bash
./exe
```

---

# 🧪 Exemplo Básico (`main.c`)

Crie um arquivo chamado `main.c` com o conteúdo abaixo para testar sua instalação:

```c
#include "raylib.h"

int main(void)
{
    InitWindow(800, 450, "Meu primeiro jogo");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(
            "Raylib funcionando!",
            250,
            200,
            30,
            BLACK
        );

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
```

---

# 📁 Estrutura recomendada do projeto

```text
meu-jogo/
│
├── src/
│   └── main.c
│
├── assets/
│   ├── images/
│   ├── sounds/
│   └── fonts/
│
├── include/
├── build/
└── README.md
```

---

## 📚 Documentação e Recursos

* Documentação Oficial: [raylib.com](https://www.raylib.com/)
* Repositório no GitHub: [github.com/raysan5/raylib](https://github.com/raysan5/raylib)
* Exemplos Práticos: [raylib.com/examples.html](https://www.raylib.com/examples.html)
