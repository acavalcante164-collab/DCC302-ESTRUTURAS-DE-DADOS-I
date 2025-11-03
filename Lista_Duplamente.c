#include <stdio.h>
#include <stdlib.h>  // MALLOC E FREE

//DEFINICAO DE ESTRUTURA DE NO DA LISTA
typedef struct nodo {
    int info;               //VALOR ARMAZENADO
    struct nodo* anterior;     //PONTEIRO PARA O NO ANTERIOR
    struct nodo* proximo;    // PONTEIRO PARA O PRIXIMO NO
} Nodo;

typedef struct lista_dupla{
    Nodo* First;    // Ponteiro para o primeiro nó
    Nodo* Last;     // Ponteiro para o último nó
    int tam;
} Lista_Dupla;

Lista_Dupla* cria_lista(){
    Lista_Dupla* l = (Lista_Dupla*) malloc(sizeof(Lista_Dupla));
    if (l != NULL){
        l->First = NULL;
        l->Last = NULL;
        l->tam = 0;
    }
}

//(funcao insere no comeco e insere no final)
void Insere_No_Comeco(Lista_Dupla* l, int valor){

    Nodo* novo = (Nodo*) malloc(sizeof(Nodo)); //ALOCA ESPACO NA MEMORIA

    novo->info = valor;
    novo->proximo = l->First;
    novo->anterior = NULL;

    l->tam++;

    if (l->First != NULL)
        l->First->anterior = novo;
    else
        l->Last = novo;
    l->First = novo;
    return l;
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

int main() {
    // CORRIGIDO: Chama a função para criar e alocar a lista
    Lista_Dupla* lista = cria_lista(); 
    
    // Verifica se a lista foi criada com sucesso
    if (lista == NULL) {
        printf("Erro ao alocar memoria para a lista!\n");
        return 1;
    }

    // CORRIGIDO: As funções 'Insere_No_Comeco' são 'void'
    Insere_No_Comeco(lista, 10);
    Insere_No_Comeco(lista, 5);
    Insere_No_Comeco(lista, 20);

    //IMPRIME A LISTA
    // Saída esperada: Lista: 20 5 10
    imprime(lista);

    //LIBERA A MEMORIA
    libera(lista);

    return 0;
}