#include <stdio.h>
#include <stdlib.h>

// 1. Definição da estrutura do Nó
struct NO {
    int info;
    struct NO *esq;
    struct NO *dir;
};

// Definição do tipo ArvBin (ponteiro para nó)
typedef struct NO* ArvBin;

// Protótipo da função
int insere_ArvBin(ArvBin* raiz, int valor);

int main() {
    // Criando uma árvore vazia
    ArvBin raiz = NULL;

    // Inserindo valores
    if (insere_ArvBin(&raiz, 10)) printf("Inserido 10 com sucesso!\n");
    if (insere_ArvBin(&raiz, 5))  printf("Inserido 5 com sucesso!\n");
    if (insere_ArvBin(&raiz, 20)) printf("Inserido 20 com sucesso!\n");
    
    return 0;
}

// --- IMPLEMENTAÇÃO DA FUNÇÃO DE INSERÇÃO ---
int insere_ArvBin(ArvBin* raiz, int valor){
    // Validação básica
    if(raiz == NULL)
        return 0;

    // 1. Criação do novo nó (O que você já tinha feito)
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    
    if(novo == NULL)
        return 0; // Falha na alocação de memória

    novo->info = valor;
    novo->dir = NULL;
    novo->esq = NULL;

    // 2. Inserção na Árvore
    
    // CASO A: A árvore está vazia? O novo nó vira a raiz.
    if (*raiz == NULL) {
        *raiz = novo;
    } 
    // CASO B: A árvore não está vazia. Precisamos procurar onde inserir.
    else {
        struct NO* atual = *raiz;
        struct NO* anterior = NULL;

        // Navega até encontrar uma posição NULL (folha)
        while(atual != NULL){
            anterior = atual;
            
            if(valor == atual->info){
                free(novo); // Elemento já existe, libera memória e sai
                return 0; 
            }

            if(valor > atual->info)
                atual = atual->dir; // Vai para a direita
            else
                atual = atual->esq; // Vai para a esquerda
        }
        
        // Agora 'anterior' é o pai do novo nó. Decidimos se vai na esq ou dir.
        if(valor > anterior->info)
            anterior->dir = novo;
        else
            anterior->esq = novo;
    }

    return 1; // Sucesso
}