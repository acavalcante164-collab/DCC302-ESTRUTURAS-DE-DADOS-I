#ifndef STACK_H
#define STACK_H

#define MAX 100
typedef struct pilha{
    int topo;
    int vetor[MAX];
} Pilha;

void CriaPilha(Pilha* p);
void LiberaPilha(Pilha* p);
int EstahVazia (Pilha* p);
int EstahCheia(Pilha* p);
int empilha(Pilha* p, int v); 
int desempilha(Pilha* p);
void imprimir(Pilha* p);

#endif // STACK_H