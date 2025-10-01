#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5   // Tamanho máximo da fila de peças

// Estrutura que representa uma peça do Tetris Stack
typedef struct {
    char nome;  // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;     // Identificador único (usado apenas internamente)
} Peca;

// Estrutura que representa a fila circular
typedef struct {
    Peca itens[MAX];  // Vetor de peças
    int inicio;       // Índice da primeira peça
    int fim;          // Índice onde a próxima peça será inserida
    int total;        // Quantidade atual de peças na fila
} Fila;

// Prototipação de funções
void inicializarFila(Fila *f);
int filaCheia(Fila *f);
int filaVazia(Fila *f);
void inserir(Fila *f, Peca p);
Peca remover(Fila *f);
void exibirFila(Fila *f);
Peca gerarPeca();

// Variável global para gerar IDs únicos
int contadorID = 0;

// Função principal
int main() {
    Fila fila;
    inicializarFila(&fila);
    int opcao;

    // Inicializar com 5 peças
    for (int i = 0; i < MAX; i++) {
        inserir(&fila, gerarPeca());
    }

    do {
        printf("\n--- Estado Atual da Fila ---\n");
        exibirFila(&fila);

        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                if (!filaVazia(&fila)) {
                    Peca jogada = remover(&fila);
                    printf("\nPeça jogada: [%c]\n", jogada.nome);
                } else {
                    printf("\nFila vazia! Nenhuma peça para jogar.\n");
                }
                break;
            }
            case 2: {
                if (!filaCheia(&fila)) {
                    Peca nova = gerarPeca();
                    inserir(&fila, nova);
                    printf("\nPeça inserida: [%c]\n", nova.nome);
                } else {
                    printf("\nFila cheia! Não é possível inserir nova peça.\n");
                }
                break;
            }
            case 0:
                printf("\nEncerrando o jogo...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// Função para inicializar a fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
    srand(time(NULL)); // Inicializa gerador aleatório
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->total == MAX;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Insere uma peça no final da fila
void inserir(Fila *f, Peca p) {
    if (filaCheia(f)) return;
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX; // Circular
    f->total++;
}

// Remove uma peça da frente da fila
Peca remover(Fila *f) {
    Peca removida = {'-', -1};
    if (filaVazia(f)) return removida;
    removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX; // Circular
    f->total--;
    return removida;
}

// Exibe a fila atual (apenas tipo da peça)
void exibirFila(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia.\n");
        return;
    }
    printf("Fila de peças:\n");
    int i = f->inicio;
    for (int c = 0; c < f->total; c++) {
        printf("[%c] ", f->itens[i].nome);
        i = (i + 1) % MAX;
    }
    printf("\n");
}

// Gera uma nova peça automaticamente
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];  // Escolhe um tipo aleatório
    nova.id = contadorID++;         // ID ainda existe, mas só interno
    return nova;
}
