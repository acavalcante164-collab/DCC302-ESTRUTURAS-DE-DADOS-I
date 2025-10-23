#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da lista
typedef struct nodo {
    int valor;
    struct nodo* prox;
} Nodo;

// Estrutura da Fila
typedef struct fila {
    Nodo* ini;
    Nodo* Fim;
    int Tam;
} Fila;

// --- Protótipos das Funções ---
Fila* criafila();
int inserir(Fila* f, int v);
void imprimir(Fila* f);
int esta_vazia(Fila* f);
void destroi_fila(Fila* f);
// (Faltou a implementação de remover, mas vamos focar no que você escreveu)


// --- Função Principal ---
int main() {
    Fila* minhaFila = criafila();

    if (minhaFila == NULL) {
        printf("Erro: Falha ao alocar memoria para a fila.\n");
        return 1;
    }

    printf("Inserindo elementos 10, 20, 30...\n");
    inserir(minhaFila, 10);
    inserir(minhaFila, 20);
    inserir(minhaFila, 30);

    imprimir(minhaFila);

    printf("Tamanho da fila: %d\n", minhaFila->Tam);

    // Lembre-se sempre de liberar a memória alocada
    destroi_fila(minhaFila);

    return 0;
}


// --- Implementação das Funções ---

Fila* criafila() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    if (f != NULL) {
        f->ini = NULL;
        f->Fim = NULL;
        f->Tam = 0;
    }
    return f;
}

int esta_vazia(Fila* f) {
    // Se 'f' for nulo ou 'ini' for nulo, a fila está vazia.
    if (f == NULL || f->ini == NULL) {
        return 1;
    }
    return 0;
}

int inserir(Fila* f, int v) {
    if (f == NULL) return 0; // Boa prática: verificar se a fila existe

    Nodo* novo = (Nodo*) malloc(sizeof(Nodo));
    if (novo == NULL) return 0; // Falha ao alocar memória para o novo nó

    novo->valor = v;
    novo->prox = NULL; // CORREÇÃO: Usar '=' para atribuição

    if (esta_vazia(f)) {
        // Se a fila está vazia, o novo nó é tanto o início quanto o fim
        f->ini = novo;
    } else {
        // Se não, o último elemento antigo aponta para o novo
        f->Fim->prox = novo;
    }

    // O novo nó é sempre o novo fim da fila
    f->Fim = novo;
    f->Tam++;
    return 1;
}

void imprimir(Fila* f) {
    if (esta_vazia(f)) {
        printf("Fila esta vazia!\n");
        return;
    }

    // CORREÇÃO: Criar um ponteiro de NODO para percorrer a lista
    Nodo* p = f->ini;

    printf("Fila: [ ");
    while (p != NULL) {
        printf("%d ", p->valor);
        p = p->prox; // Avança para o próximo nó
    }
    printf("]\n");
}

void destroi_fila(Fila* f) {
    if (f == NULL) return;

    Nodo* p = f->ini;
    while (p != NULL) {
        Nodo* temp = p;
        p = p->prox;
        free(temp);
    }
    free(f); // Não se esqueça de liberar a própria estrutura da fila
}