#include <stdlib.h>
#include <stdio.h>
#define MAX 10
typedef struct pilha{
   int topo;
   int VETOR[MAX];
}Pilha;
/* ---------------- CRIAÇÃO DA PILHA ---------------- */
Pilha* CriaPilha(){
    Pilha* p = (Pilha*)malloc(sizeof(Pilha)); //ALOCA ESPACO PARA A STACK
    if (p == NULL){
        printf("Erro ");
        exit(1);
    }
    p->topo = 0;
    return p;
}
int EstahCheia(Pilha* p){
    return p->topo == MAX;
}
int EstahVazia(Pilha* p){
    return p->topo == 0;
}
int Empilha(Pilha* p, int x){
    if(!EstahCheia(p)){
        p->VETOR[p->topo] = x;
        p->topo++;
        return 1;
    } else{
        printf("pilha Cheia");
        return 0;
    }
}
int DesEmpilha(Pilha* p){
    if (!EstahVazia(p)){
        p->topo--;
        return p->VETOR[p->topo];
    } else{
        printf("Erro");
        return -1;
    }
}
int Topo(Pilha* p){
    if(!EstahVazia(p)){
        return p->VETOR[p->topo - 1];
    } else {
        printf("A pilha esta vazia");
        return -1;
    }
}
/* ---------------- IMPRIMIR ---------------- */
void ImprimePilha(Pilha* p) {
    if (EstahVazia(p)) {
        printf("Pilha vazia!\n");
        return;
    }

    printf("\n--- PILHA ---\n");
    for (int i = p->topo - 1; i >= 0; i--) {
        printf(" %d\n", p->VETOR[i]);
    }
}

/* ---------------- LIBERAR ---------------- */
void LiberaPilha(Pilha* p) {
    free(p);
}

/* ---------------- MAIN ---------------- */
int main() {
    Pilha* prato = CriaPilha(); // agora com malloc
    printf("Pilha criada com sucesso!\n");

    Empilha(prato, 10);
    Empilha(prato, 20);
    Empilha(prato, 30);

    printf("Topo atual: %d\n", Topo(prato));

    printf("\nDesempilhando: %d\n", DesEmpilha(prato));
    printf("Topo atual: %d\n", Topo(prato));

    printf("\n--- PILHA ATUAL ---\n");
    ImprimePilha(prato);

    LiberaPilha(prato);
    return 0;
}