#include <stdio.h>
#include <stdlib.h>

/*
--- FILA CIRCULAR ---
DEFININDO UMA FILA (REPRESENTADO)
O QUE PODEMOS FAZER COM UMA FILA ?
-CRIAR E INICIALIZAR UMA FILA
-ENFILEIRAR (INSERIR) UM ELEMENTO
-DESENFILEIRAR (RETIRAR) UM ELEMENTO
-DESTRUIR UMA FILA(LIBERAR A MEMORIA OCUPADA)
-SABER SE A FILA ESTA VAZIA
-SABER SE A FILA ESTA CHEIA
-IMPRIMIR
*/
#define MAX 10

typedef struct fila {
    int comeco;
    int final;
    int quantidade;
    int VETOR[MAX];
} Fila;

// Função para criar a fila
/*
-Aloca memoria para a estrutura fisica;
-Inicializa os controles de inicio e o fim da fila;
-Retorna um ponteiro para a estrutura criada;
*/
Fila* cria_fila() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
        if (f != NULL) {
            f->comeco = 0;
            f->final = 0;
            f->quantidade = 0; // INICIA COM 0 ELEMENTOS
        }
        return f;
}
// FUNCAO PARA VERIFICAR ESTADO
/*
O QUE CARACTERIZA UMA FILA CHEIA?
O FIM DA FILA ESTA NA ULTIMA POSICAO;
*/
int esta_cheia(Fila* f) {
    return (f->quantidade == MAX);
}
/*
O QUE CARACTERIZA UMA FILA VAZIA?
O INICIO E O FIM DA FILA ESTA NA MESMA POSICAO
*/
int esta_vazia(Fila* f) {
    return (f->quantidade == 0);
}
// Função de INSERIR 
/*
-Recebe um ponteiro para uma estrutura do tipo fila e um valor a ser enfileirado;
-Verifica se a fila já não está cheia;
-Se não está, então ... 
Coloca o elemento na posição indicada pelo fim
Incrementa o valor do fim;
-A função inserir() retorna 1 (um) se o valor foi enfileirado ou então -retorna 0 (zero) se não foi possível enfileirar;
*/
int inserir(Fila* f, int v) {
    if (esta_cheia(f)) {
        return 0;                                   // Falha, fila cheia
    }

    f->VETOR[f->final] = v;                         // INSERE O VALOR NA POSICAO 'FIM'
    f->final = (f->final + 1) % MAX;                // AVANCA O 'FIM' DE FORMA CIRCULAR
    f->quantidade++;                                // INCREMENTA A QUANTIDADE DE ELEMENTOS

    return 1;                                       // Sucesso
}
// Função de RETIRAR 
/*
-Recebe um ponteiro para uma estrutura do tipo fila e um ponteiro para uma variável inteira;
-Verifica se a fila já não está vazia;
-Se não está, então ... 
Retira o elemento da posição indicada pelo início;
Incrementa o valor do início;
-A função retirar() retorna 1 (um) seovalorfoi
retirado da fila ou então retorna0(zero) senão
*/
int retirar(Fila* f, int* v) {                      // 'v' é um ponteiro para "devolver" o valor
    if (esta_vazia(f)) {
        return 0;                                   // Falha, fila vazia
    }
    *v = f->VETOR[f->comeco];                       // Pega o valor do comeco e coloca no endereço apontado por 'v'
    f->comeco = (f->comeco + 1) % MAX;              // Avança o 'início' de forma circular
    f->quantidade--;                                // Decrementa a quantidade de elementos

 return 1; // Sucesso
}
/*
Recebe um ponteiro para uma estruturadotipofila e libera a memória ocupadapor ela;
*/
void liberaFila(Fila* f){
    free(f);
}
// Função para imprimir os elementos da fila
void imprimir_fila(Fila* f) {
    if (esta_vazia(f)) {
        printf("Fila Vazia!\n");
        return;
    }

    printf("Fila: [ ");
    
    // Inicia um índice 'i' no começo da fila
    int i = f->comeco;
    int count;

    // Percorre a quantidade exata de elementos na fila
    for (count = 0; count < f->quantidade; count++) {
        printf("%d ", f->VETOR[i]);
        // Avança o índice de forma circular para o próximo elemento
        i = (i + 1) % MAX;
    }

    printf("]\n");
}

int main() {
    // 1. Cria a Fila
    Fila* minha_fila = cria_fila();
    int valor_removido;

    printf("--- Teste de Fila Circular ---\n");
    printf("Fila acabou de ser criada.\n");
    imprimir_fila(minha_fila); // Deve mostrar "Fila Vazia!"

    printf("\n--- Inserindo 5 elementos ---\n");
    inserir(minha_fila, 10);
    inserir(minha_fila, 20);
    inserir(minha_fila, 30);
    inserir(minha_fila, 40);
    inserir(minha_fila, 50);
    imprimir_fila(minha_fila); // Deve mostrar: [ 10 20 30 40 50 ]

    printf("\n--- Removendo 2 elementos ---\n");
    if (retirar(minha_fila, &valor_removido)) {
        printf("Valor removido: %d\n", valor_removido); // Deve ser 10
    }
    if (retirar(minha_fila, &valor_removido)) {
        printf("Valor removido: %d\n", valor_removido); // Deve ser 20
    }
    imprimir_fila(minha_fila); // Deve mostrar: [ 30 40 50 ]

    printf("\n--- Preenchendo a fila para testar circularidade ---\n");
    // MAX é 10, já temos 3 elementos. Vamos inserir mais 7.
    inserir(minha_fila, 60);
    inserir(minha_fila, 70);
    inserir(minha_fila, 80);
    inserir(minha_fila, 90);
    inserir(minha_fila, 100);
    inserir(minha_fila, 110);
    inserir(minha_fila, 120);
    
    imprimir_fila(minha_fila); // Deve mostrar a fila cheia

    printf("\nTentando inserir com a fila cheia...\n");
    if (!inserir(minha_fila, 999)) {
        printf("Nao foi possivel inserir. Fila esta cheia, como esperado.\n");
    }

    printf("\n--- Removendo mais 3 elementos ---\n");
    if (retirar(minha_fila, &valor_removido)) {
        printf("Valor removido: %d\n", valor_removido); // Deve ser 30
    }
     if (retirar(minha_fila, &valor_removido)) {
        printf("Valor removido: %d\n", valor_removido); // Deve ser 40
    }
     if (retirar(minha_fila, &valor_removido)) {
        printf("Valor removido: %d\n", valor_removido); // Deve ser 50
    }
    imprimir_fila(minha_fila);

    printf("\n--- Inserindo mais 2 elementos (demonstrando circularidade) ---\n");
    // Agora o 'final' da fila vai para o início do vetor
    inserir(minha_fila, 130);
    inserir(minha_fila, 140);
    imprimir_fila(minha_fila);

    // 2. Libera a memória
    printf("\n--- Liberando a memoria da fila ---\n");
    liberaFila(minha_fila);
    printf("Fila liberada com sucesso.\n");

    return 0;
}
