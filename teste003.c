#include <stdio.h>
#include <stdlib.h>
/* função busca: busca um elemento na lista */
Lista2* busca (Lista2* l, int v)
{
 Lista2* p;
 for (p=l; p!=NULL; p=p->prox)
 if (p->info == v)
 return p;
 return NULL; /* não achou o elemento */
}
Lista2* insere(Lista2* l, int v) {
    Lista2* novo = (Lista2*) malloc(sizeof(Lista2)); // cria novo nó
    novo->info = v;   // guarda o valor
    novo->prox = l;   // próximo do novo é o antigo primeiro
    novo->ant  = NULL; // como é o primeiro, não tem anterior

    // se a lista não era vazia, o antigo primeiro deve apontar para o novo
    if (l != NULL)
        l->ant = novo;

    return novo; // o novo é o início da lista
}
