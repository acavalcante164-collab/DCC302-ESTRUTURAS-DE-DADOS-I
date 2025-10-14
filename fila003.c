#include <stdio.h>
#include <stdlib.h>

struct lista {
    int info;
    struct lista* prox; //PONTEIRO AUTO REFERENCIADO CAPAZ DE APONTAR AO STRUCT LIST
};
typedef struct lista Lista;

typedef struct nodo{
    int info;
    struct nodo* prox;
} Nodo;

/* função de inicialização: retorna uma lista vazia */
Nodo* cria_lista(){
    return NULL;
}

Nodo* insere(Nodo* Prim, int v){
    Nodo* new = (Nodo*) malloc(sizeof(Nodo));
    new->prox = Prim;
    Prim = new;
    new->info = v;
    return Prim;
}

/* função imprime: imprime valores dos elementos */
void imprime (Lista* L)   //void pois nao retorna nada
{
 Lista* p; /* variável auxiliar para percorrer a lista */
 for (p = L; p != NULL; p = p->prox)
    printf("info = %d\n", p->info);
}
int main(){
    Nodo* L = cria_lista();
    L = insere(L,20);
    L = insere(L,50);
    L = insere (L,10);

    imprime(L);
    imprimee(L);

    return 0;
}
/*
void imprimee(Nodo* p){
    for(Nodo* p = p; p != NULL; p = p->prox)
        printf("%d\n", p->info);

}
*/
