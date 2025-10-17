#include <stdio.h>

#define MAX 10

typedef struct pilha {
    int topo;
    int Vet[MAX];
}Pilha;

int empilhar(Pilha* p, int x){
    if (!pilha_cheia(p)){
        p->Vet[p->topo] = x;
        p->topo++;
    }
    return 0;
}