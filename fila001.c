#include <stdio.h>

#define MAX 100 //DEFINE UM TAMANHO MAXIMO PARA O VETOR DA FILA

//CRIA UMA FUNCAO "fila" E APELIDA ELA DE "Fila" 
typedef struct fila{
    int inicio, fim, tam;
    int VET[MAX];
} Fila;

Fila* cria_fila(){
    Fila* f = (Fila*) malloc(sizeof(Fila));
    return f;
}

//FUNCAO INSERIR FILA
int inserir (Fila* f, int v){
    if(!estah_cheia(f)){
        f->VET[f->fim++] = v;
        if (f->fim == MAX)
            f->fim=0;
        return 1;
    }
    return 0;
}