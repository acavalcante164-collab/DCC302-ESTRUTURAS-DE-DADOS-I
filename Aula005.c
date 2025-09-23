/*
 DCC302 - ESTRUTURAS DE DADOS I - T01 (2025.2)
NOME: ALONSO FERNANDES CAVALANTE
MATRICULA: 2024005534

EXERCICIO DA AULA 01  10/09/2025 A 17/09/2025
*/

/*

DESCRIÇÃO:
Função de busca
A função de busca recebe a informação referente ao elemento que queremos buscar e
tem como valor de retorno o ponteiro do nó da lista que representa o elemento. Caso o
elemento não seja encontrado na lista, o valor retornado é NULL.

*/
#include <stdio.h>
#include <stdlib.h>

/*DEFININDO A ESTRUTURA DA LISTA DUPLAMENTE ENCADEADA*/
typedef struct lista2 {
    int info;
    struct lista2* ant;
    struct lista2* prox;
} Lista2;
/*FUNCAO DE INSERCAO NO INICIO*/
Lista2* insere(Lista2* l, int v){
    Lista2* novo = (Lista2*) malloc(sizeof(Lista2));
    novo->info =v; //GUARDA O VALOR
    novo->prox = l; //PROXIMO DO NOVO EJ O ANTIGO PRIMEIRO
    novo->ant = NULL; //COMO EH O PRIMEIRO, NAO TEM ANTERIOR

    if(l != NULL)
        l->ant = novo; //AJUSTA O ANTERIOR DO ANTIGO PRIMEIRO
    return novo; //NOVO EH O INICIO DA LISTA
}
/*FUNCAO PARA IMPRIMIR TODOS OS ELEMENTOS*/
void imprime(Lista2* l) {
    Lista2* p;
    for (p = l; p != NULL; p = p->prox){
        printf("%d ", p->info);
    }
    printf("\n");
}
/*FUNCAO DE BUSCA*/
Lista2* busca(Lista2* l, int v) {
    Lista2* p;
    for(p = l; p != NULL; p = p->prox) {
        if (p->info == v)
            return p; //ACHOU
    }
    return NULL; //NAO ACHOU
}
/*FUNCAO DE REMOCAO*/
Lista2* retira(Lista2* l, int v){
    Lista2* p = busca(l, v);

    if(p == NULL)
        return 1; //NAO ACHOU
    
    //SE FOR O PRIMEIRO ELEMENTO
    if (l == p)
            l = p->prox;
    else
        p->ant->prox = p->prox;

    //SE NAO FOR ULTIMO ELEMENTO
    if (p->prox != NULL)
        p->prox->ant = p->ant;

    free(p); //LIBERA MEMORIA
    return l;
}
/*LIBERA TODA A LISTA DA MEMORIA*/
void libera(Lista2* l) {
    Lista2* p = l;
    while (p != NULL) {
        Lista2* t = p->prox;
        free(p);
        p =  t;
    }
}
/*FUNCAO PRINCIPAL*/
int main(){
    Lista2* lista = NULL;

    //INSERE VALORES
    lista = insere(lista, 10);
    lista = insere(lista, 20);
    lista = insere(lista, 30);

    printf("Lista original:\n");
    imprime(lista);

    //REMOVE O VALOR 20
    lista = retira(lista, 20);
    printf("\nDepois de remover 20:\n");
    imprime(lista);

    //REMOVE O PRIMEIRO (30)
    lista = retira(lista, 30);
    printf("\nDepois de Remover 30:\n");
    imprime(lista);

    //REMOVE O ULTIMO (10)
    lista = retira(lista, 10);
    printf("\nDepois de remover 10 (LISTA VAZIA):\n");
    imprime(lista);
    
    libera(lista); //LIBERA MEMORIA
    return 0;
}
