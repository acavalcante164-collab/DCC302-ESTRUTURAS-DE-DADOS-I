#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void CriaPilha(Pilha* p){    
    p-> topo = 0;    
}
void LiberaPilha(Pilha* p){
    free(p);
}
int EstahVazia (Pilha* p){
    return (p->topo == 0);
}
int EstahCheia(Pilha* p){
    return (p->topo == MAX);
}
int empilha(Pilha* p, int v){
    if(!EstahCheia(p)){
        /* INSERE UM ELEMENTO NA PROXIMA POSICAO LIVRE */
        p->vetor[p->topo] = v;
        p->topo++;
    }
    return 0;    
}
int desempilha(Pilha* p) {
    if (!EstahCheia(p)) {
        p->topo--; // Primeiro decrementa para apontar para o último elemento
        return p->vetor[p->topo];
    }
    return '\0'; // Retorno de erro/vazio
}
void imprimir(Pilha* p){
    if(EstahVazia(p)){
        printf("\nA Pilha estah VAZIA\n");
        return;
    }
    if (EstahCheia(p)) {
        printf("\nA Pilha estah CHEIA\n");
        return;
    }
    for(int i = p->topo - 1; i >= 0; i--){
        printf(" %d\n", p->vetor[i]);
    }

}