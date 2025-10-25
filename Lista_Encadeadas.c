#include <stdio.h>
#include <stdlib.h>

// --- Definição das Estruturas ---

typedef struct nodo{
    int valor;
    struct  nodo* prox;
} Nodo;

typedef struct fila{
    Nodo* ini;
    Nodo* Fim;
    int Tam;
} Fila;

// --- Funções Auxiliares (Definidas Antes de Serem Usadas) ---

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
    // Uma fila está vazia se seu início for NULO (ou Tam == 0).
    return (f->ini == NULL);
}

// --- Funções Principais da Fila ---

int inserir (Fila* f, int v){
    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
    if(novo != NULL){
        novo->prox = NULL;
        novo-> valor = v;
        
        // Agora 'esta_vazia' é conhecida pelo compilador
        if (!esta_vazia(f)) 
            f->Fim->prox = novo; // O antigo Fim aponta para o novo
        else
            f->ini = novo;       // Se estava vazia, o início é o novo
        
        f->Fim = novo;           // O Fim é sempre o novo nodo
        f->Tam++;
        return 1;
    }
    return 0; // Falha no malloc
}

/* * CORREÇÃO 1: A assinatura mudou de 'int v' para 'int* v'.
 * Agora 'v' é um ponteiro para onde devemos guardar o valor removido.
 */
int remover (Fila* f, int* v){ 
    if(!esta_vazia(f)){
        f->Tam--;
        
        // CORREÇÃO 2: Atribui o valor ao endereço para onde 'v' aponta
        *v = f->ini->valor; 
        
        Nodo* p = f->ini;      // Guarda o nodo a ser removido
        f->ini = f->ini->prox; // Avança o início da fila
        
        /* * CORREÇÃO 3 (Bug Lógico): 
         * Se f->ini se tornou NULL, a fila está vazia.
         * Precisamos atualizar f->Fim para NULL também.
         */
        if(f->ini == NULL) {
            f->Fim = NULL;
        }
        
        free(p); // Libera o nodo antigo
        return 1; // Sucesso
    }
    return 0; // Falha (fila estava vazia)
}

/* * CORREÇÃO 4: Implementação da função 'tamanho' que estava faltando.
 */
int tamanho(Fila* f) {
    if (f == NULL) {
        return 0;
    }
    // Retornar f->Tam é O(1), muito eficiente!
    return f->Tam; 
}

void imprimir(Fila* f){
    Nodo* p = f->ini;

    if (esta_vazia(f)) {
        printf("Fila vazia!\n");
        return;
    }

    printf("Fila: [ ");
    while (p != NULL) {
        printf("%d ", p->valor); 
        p = p->prox;             
    }
    printf("] (Tamanho: %d)\n", tamanho(f)); // Usando a nova função
}

void destroi_fila(Fila* f) {
    Nodo* p = f->ini;
    while (p != NULL) {
        Nodo* temp = p; // Guarda o nodo atual
        p = p->prox;    // Avança para o próximo
        free(temp);     // Libera o nodo anterior
    }
    free(f); // Libera a estrutura da fila
}

// --- Função Principal (main) ---

int main(){
    Fila* FF = criafila();
    if (FF == NULL) {
        printf("Erro ao alocar memoria para a fila!\n");
        return 1; 
    }

    // Inserindo elementos
    inserir(FF, 23);
    inserir(FF, 10);
    inserir(FF, 7);

    // Imprimindo a fila
    imprimir(FF); // Saída esperada: Fila: [ 23 10 7 ] (Tamanho: 3)

    // Exemplo de como usar a função 'remover' corrigida
    int valor_removido;
    
    if (remover(FF, &valor_removido)) {
        printf("Valor removido: %d\n", valor_removido); // Saída: 23
    }
    imprimir(FF); // Saída esperada: Fila: [ 10 7 ] (Tamanho: 2)
    
    if (remover(FF, &valor_removido)) {
        printf("Valor removido: %d\n", valor_removido); // Saída: 10
    }
    if (remover(FF, &valor_removido)) {
        printf("Valor removido: %d\n", valor_removido); // Saída: 7
    }
    
    // A fila agora está vazia
    imprimir(FF); // Saída esperada: Fila vazia!

    // Tentando remover de fila vazia
    if (!remover(FF, &valor_removido)) {
        printf("Nao foi possivel remover (fila vazia).\n");
    }

    // Libere a memória no final
    destroi_fila(FF);

    return 0;
}