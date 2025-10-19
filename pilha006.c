#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct pilha{
    int topo;
    int VETOR[MAX];
}Pilha;

/*
Pilha* CriaPilha(){
pilha* p = (Pilha*)malloc(sizeof(pilha));
p->topo =0;
return p;
}
*/


void CriaPilha(Pilha* p){
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
    if(!EstahVazia(p)){
        p->topo--;
        return p->VETOR[p->topo];
    }
    return 0;
}
/*int topo (Pilha* p){
    return p->VETOR[p->topo-1];
}*/
void ImprimePilha( Pilha* p){
    if(EstaCheia(p)){
        printf("Estah Cheia!\n");
        return;
    }
    if(EstahVazia(p)){
        printf("Estah Vazia!\n");
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

    DesEmpilha(&prato);
    DesEmpilha(&prato);
    DesEmpilha(&prato);

    printf("\n--- PILHA ATUAL ---\n");
    ImprimePilha(&prato);

    LiberaPilha(&prato);
    return 0;
}
