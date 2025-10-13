#include <stdio.h>
#include <stdlib.h>

#define MAX 5 //DEFINE O TAMANHO MAXIMO DA FILA

//ESTRUTURA DA FILA
typedef struct fila{
    int inicio;
    int fim;
    int qtd; //QUANTIDADE DE ELEMENTOS DA FILA
    int vet[MAX];
} Fila;

Fila* cria_fila();
int esta_vazia(Fila* f);
int esta_cheia(Fila* f);
int inserir(Fila* f, int v);
int remover(Fila* f); //FUNCAO PARA REMOVER E TESTAR
void imprimir(Fila* f); //FUNCAO PARA VISUALIZAR A FILA

int main(){

}
Fila* cria_fila(){
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
    return f;
}
int esta_vazia(Fila* f){
    return (f->qtd == 0);
}
int esta_cheia(Fila* f){
    return (f->qtd == MAX);
}
//INSERIR
int inserir(Fila* f, int v){
    if (esta_cheia(f)){
        printf("Erro; Fila cheia!\n");
        return 0; //ERRO
    }
    f->vet[f->fim] = v;
    f->fim = (f->fim + 1) % MAX;
    f->qtd++;
    return 1; //SUCESSO
}