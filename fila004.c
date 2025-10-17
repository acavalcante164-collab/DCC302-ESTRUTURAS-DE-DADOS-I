#include <stdio.h>
#include <stdlib.h>

//ERRO NÃO AVERIGUAR MUITO
struct lista {
    int info;
    struct lista* prox; //PONTEIRO AUTO REFERENCIADO CAPAZ DE APONTAR AO STRUCT LIST
};
typedef struct lista Lista;

typedef struct nodo{
    int info;
    struct nodo* prox;
} Nodo;

typedef struct lista{
	Nodo *prim;
	int tam;
//pilha endereço somente do topo 
}
//NODO informação e ponteiro para o proxino
/* função de inicialização: retorna uma lista vazia e volta aonde parou aponta para null temos uma lista vazia  */
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

//prova questao FAZER NA MARRA BRUTAO
/* função imprime: imprime valores dos elementos

|L | | | |   ->  |P | | | |   ->  != NULL
*/
void imprime (Lista* L)   //void pois nao retorna nada
{
 Lista* p; /* variável auxiliar para percorrer a lista */
 for (p = L; p != NULL; p = p->prox)
    printf("info = %d\n", p->info);
}
Nodo *retira
int main(){
    Nodo* L = cria_lista();
    L = insere (L,10);
    L = insere (L,20);
    
    
    imprime(L);
    

    return 0;
}
/*
void imprimee(Nodo* p){
    for(Nodo* p = p; p != NULL; p = p->prox)
        printf("%d\n", p->info);

}
*/
