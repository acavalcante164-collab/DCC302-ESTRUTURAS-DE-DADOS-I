#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct pilha{
    int topo;
    int VETOR[MAX];
}Pilha;

void CriaPilha (Pilha* p){
    p->topo = 0;
}
int EstahVazia(Pilha* p){
    return p->topo == 0;
}
int EstaCheia(Pilha* p){
    return p->topo == MAX;
}
void LiberaPilha(Pilha* p){
    free(p);
}
int Empilha(Pilha* p, int x){
    if(!EstaCheia(p)){
        p->VETOR[p->topo] = x;
        p->topo++;
    }
    return 0;
}
int DesEmpilha(Pilha* p){
    if(!EstaCheia(p)){
        p->topo--;
        return p->VETOR[p->topo];
    }
    return 0;
}
void ImprimePilha( Pilha* p){
    if(EstaCheia(p)){
        printf("Estah Cheia!\n");
        return;
    }
    if(EstahVazia(p)){
        printf("Estah Cheia!\n");
        return;
    }
    for (int i = p->topo - 1; i >= 0; i--){
        printf(" %d\n", p->VETOR[i]);
    }
}

int main(){
    Pilha prato;

    CriaPilha(&prato);
    printf("\nLoad.... Pilha Inicializada\n");

    printf("\nEmpilhando...");
    Empilha(&prato, 10);
    Empilha(&prato, 20);
    Empilha(&prato, 30);

    printf("\n--- PILHA ATUAL ---\n");
    ImprimePilha(&prato);

    return 0;
}
