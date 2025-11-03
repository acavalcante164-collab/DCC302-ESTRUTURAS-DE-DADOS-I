#include <stdio.h>
#include <stdlib.h> // MALLOC E FREE

//DEFINICAO DE ESTRUTURA DE NO DA LISTA
typedef struct nodo {
    int info;                 // VALOR ARMAZENADO
    struct nodo* anterior;    // CORRIGIDO: Ponteiro para o nó anterior
    struct nodo* proximo;     // CORRIGIDO: Ponteiro para o próximo nó
} Nodo;

typedef struct lista_dupla {
    Nodo* First; // Ponteiro para o primeiro nó
    Nodo* Last;  // Ponteiro para o último nó
    int tam;
} Lista_Dupla;

// FUNÇÃO PARA CRIAR E INICIALIZAR A LISTA (ESSENCIAL)
Lista_Dupla* cria_lista() {
    // Aloca memória para o "cabeçalho" da lista
    Lista_Dupla* l = (Lista_Dupla*) malloc(sizeof(Lista_Dupla));
    if (l != NULL) { // Verifica se a alocação funcionou
        l->First = NULL;
        l->Last = NULL;
        l->tam = 0;
    }
    return l;
}

// CORRIGIDO: A função agora é 'void'
void Insere_No_Comeco(Lista_Dupla* l, int valor) {
    // Se a lista não existe, não faz nada
    if (l == NULL) return; 

    Nodo* novo = (Nodo*) malloc(sizeof(Nodo)); //ALOCA ESPACO NA MEMORIA
    if (novo == NULL) return; // Verifica se a alocação do nó falhou

    novo->info = valor;
    novo->proximo = l->First;
    novo->anterior = NULL;
    
    l->tam++;

    if (l->First != NULL) // Se a lista não estava vazia
        l->First->anterior = novo;
    else // Se a lista estava vazIA
        l->Last = novo; // O novo nó é também o último

    l->First = novo; // O novo nó é sempre o primeiro
    // CORRIGIDO: Sem 'return'
}
void Insere_No_Fim(Lista_Dupla* l, int valor){
    if(l == NULL) return;

    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
    if(novo == NULL) return;

    novo->info = valor;
    novo->proximo = NULL;   // É o último, então aponta para NULL
    novo->anterior = l->Last; // O anterior dele é o "antigo último"

    l->tam++;

    if(l->Last  != NULL){
        l->Last->proximo = novo;
    } else {
        l->First = novo;
    }
    l->Last = novo;
}
//FUNCAO PARA IMPRIMIR A LISTA DO INCIO AO FIM
void imprime(Lista_Dupla* l) {
    if (l == NULL) return;

    // CORRIGIDO: O iterador 'p' deve ser do tipo Nodo*
    Nodo* p;
    printf("Lista: ");
    // CORRIGIDO: O loop começa em l->First e avança com p->proximo
    for (p = l->First; p != NULL; p = p->proximo) {
        printf("%d ", p->info); // CORRIGIDO: Imprime a info do nó
    }
    printf("\n");
}

//FUNCAO PARA LIMPAR A MEMORIA DA LISTA
void libera(Lista_Dupla* l) {
    if (l == NULL) return;

    // CORRIGIDO: O iterador 'p' deve ser do tipo Nodo*
    Nodo* p = l->First;
    while (p != NULL) {
        Nodo* temp = p->proximo; // CORRIGIDO: Guarda o proximo nó
        free(p);                 // Libera o nó atual
        p = temp;                // Avança para o próximo
    }
    // CORRIGIDO: Libera o "cabeçalho" da lista no final
    free(l);
}
Nodo* search(Lista_Dupla* L, int value) {
    if (L == NULL) return NULL;

    Nodo* p = L->First;
    while (p != NULL) {
        if (p->info == value) {
            return p; // Encontrou
        }
        p = p->proximo;
    }
    return NULL; // Não encontrou
}

/**
 * @brief Remove o primeiro nó que contém o 'value' especificado.
 */
void remove_valor(Lista_Dupla* L, int value) {
    if (L == NULL) return;

    // 1. Encontrar o nó a ser removido
    Nodo *p = search(L, value);

    // 2. Se o nó não for encontrado (p == NULL), não faz nada
    if (p == NULL) {
        return; 
    }

    // 3. O nó foi encontrado. Agora, vamos re-conectar a lista.

    // --- Ajusta o ponteiro 'proximo' do nó ANTERIOR ---
    if (p->anterior == NULL) {
        // Caso 1: O nó a ser removido (p) é o PRIMEIRO da lista
        // O novo 'First' será o nó seguinte a 'p'
        L->First = p->proximo;
    } else {
        // Caso 2: O nó (p) está no meio ou no fim
        // O nó anterior a 'p' deve "pular" 'p' e apontar para o próximo
        p->anterior->proximo = p->proximo;
    }

    // --- Ajusta o ponteiro 'anterior' do nó POSTERIOR ---
    if (p->proximo == NULL) {
        // Caso 3: O nó a ser removido (p) é o ÚLTIMO da lista
        // O novo 'Last' será o nó anterior a 'p'
        L->Last = p->anterior;
    } else {
        // Caso 4: O nó (p) está no início ou no meio
        // O nó posterior a 'p' deve "pular" 'p' e apontar para o anterior
        p->proximo->anterior = p->anterior;
    }

    // 4. Agora que 'p' está isolado da lista, liberar sua memória
    free(p);
    
    // 5. Atualizar o tamanho
    L->tam--;
}
int getPosicaoDoInicio(Nodo* elemento_alvo) {
    if (elemento_alvo == NULL) return -1; // Posição inválida

    int pos = 1;
    Nodo* p = elemento_alvo;

    // "Caminha" para trás até o início
    while (p->anterior != NULL) {
        p = p->anterior;
        pos++;
    }
    
    return pos;
}

/**
 * @brief Calcula a posição de um nó em relação ao FIM.
 * Assume que a posição 1 é a última.
 */
int getPosicaoDoFim(Nodo* elemento_alvo) {
    if (elemento_alvo == NULL) return -1; // Posição inválida

    int pos = 1;
    Nodo* p = elemento_alvo;

    // "Caminha" para frente até o fim
    while (p->proximo != NULL) {
        p = p->proximo;
        pos++;
    }
    
    return pos;
}
int main() {
    Lista_Dupla* lista = cria_lista(); 
    
    // 1. Vamos criar a lista exata da imagem: 10, 6, 17, 40, 50
    Insere_No_Fim(lista, 10);
    Insere_No_Fim(lista, 6);
    Insere_No_Fim(lista, 17);
    Insere_No_Fim(lista, 40);
    Insere_No_Fim(lista, 50);

    printf("Lista criada (igual a da imagem):\n");
    imprime(lista); // Saída: Lista: 10 6 17 40 50 (Tam: 5)
    
    printf("\n--- Testando o elemento 40 ---\n");

    // 2. Pegar a referência (ponteiro) para o nó '40'
    Nodo* no_40 = search(lista, 40);

    if (no_40 != NULL) {
        // 3. Calcular as posições a partir APENAS do ponteiro 'no_40'
        int pos_inicio = getPosicaoDoInicio(no_40);
        int pos_fim = getPosicaoDoFim(no_40);
        
        // 4. Imprimir o resultado
        printf("O elemento %d ocupa a %dª posicao (em relacao ao inicio)\n", no_40->info, pos_inicio);
        printf("O elemento %d ocupa a %dª posicao (em relacao ao fim)\n", no_40->info, pos_fim);
    } else {
        printf("Nao foi possivel encontrar o elemento 40.\n");
    }

    libera(lista);

    return 0;
    return 0;
}

