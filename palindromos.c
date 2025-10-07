#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 16


typedef struct pilha{
    int topo;
    char VET[MAX];
} Pilha;
void inicio(Pilha* p){
    p->topo = 0;
}
int empilha(Pilha* p, char c){
    if(!pilha_cheia(p)){
        p->VET[p->topo] = c;
        p->topo++;
        return 1;
    }
    return 0; //falha
}
int pilha_cheia(Pilha* p){
    return(p->topo == MAX);
}
int vazia(Pilha* p){
    return (p->topo == 0);
}
char desempilha(Pilha* p){
    if(!pilha_vazia(p)){
        p->topo--;
        return p-> VET[p->topo];
    }
    return '\0';
}
int main (){
    Pilha minha_pilha;
    char original[MAX];
    char invertido[MAX];
    int i;
    int tamanho_palavra;

    inicializa(&minha_pilha);

    printf("Digite uma palavra: ");
    scanf(" %s", &original);

    tamanho_palavra = strlen(original);

    if(tamanho_palavra >= MAX){
        printf("ERRO");
        return 1;
    }
    printf("\nEmpilha %s\n", original);
    for (i = 0; i < tamanho_palavra; i++){
        empilha(&minha_pilha, original[i]);
    }
    printf("Desempilha\n");
    for(i = 0; i < tamanho_palavra; i++){
        invertido[i] = desempilha(&minha_pilha);
    }
    invertido[i] = '\0';

    printf("Palavra ORIGINAL: %s\n", original);
    printf("Palavra invertida: %s\n", invertido);

    return 0;
}