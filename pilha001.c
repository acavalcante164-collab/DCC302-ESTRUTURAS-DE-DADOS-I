#include <stdio.h>
#include<stdlib.h>

#define MAX 10

typedef struct pilha {
    int topo;
    int Vet[MAX];
}Pilha;

void inicializa(Pilha* p){
    p->topo = 0;
}
int pilha_cheia(Pilha* p){
    return(p->topo == MAX);
}
int pilha_vazia(Pilha* p){
    return (p->topo == 0);
}
int empilhar(Pilha* p, int x){
    if (!pilha_cheia(p)){
        p->Vet[p->topo] = x;
        p->topo++;
    }
    return 0;
}
int desempilha(Pilha* p) {
    if (!pilha_vazia(p)) {
        p->topo--; // Primeiro decrementa para apontar para o último elemento
        return p->Vet[p->topo];
    }
    return '\0'; // Retorno de erro/vazio
}
void imprimir(Pilha* p){
    if(pilha_vazia(p)){
        printf("\nA Pilha estah vazia\n");
        return;
    }
    for(int i = p->topo - 1; i >= 0; i--){
        printf(" %d\n", p->Vet[i]);
    }

}

int main(){
    Pilha palito;
    

    inicializa(&palito);
    printf("Pilha inicializada");

    printf("\n EMPILHANDO: 10, 20, 30 \n");
    empilhar(&palito, 10);
    empilhar(&palito, 20);
    empilhar(&palito, 30);
    empilhar(&palito, 10);
    empilhar(&palito, 20);
    empilhar(&palito, 30);
    empilhar(&palito, 10);
    empilhar(&palito, 20);
    empilhar(&palito, 30);
    empilhar(&palito, 10);
    empilhar(&palito, 20);
    empilhar(&palito, 30);

    printf("Pilha atual\n");
    imprimir(&palito);    
    
    return 0;
}