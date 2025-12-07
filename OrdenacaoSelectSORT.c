#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 10

//FUNCAO AUXILIAR PARA TROCAR DOIS VALORES DE LUGAR (PONTEIROS)
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//EM VEZ DE BUSCAR UM VALOR ESPECIFICO (X), ELA BUSCA ONDE ESTA O MENOR VALOR
// RETORNA O INDICE DO MENOR VALOR NO INTERVALO [INICIO FIM]
int buscaSequencialMenor(int vetor [], int inicio, int tamanho){
    int indiceMenor = inicio; //ASSUME QUE O PRIMEIRO EH O MENOR

    //PERCORRE SEQUENCIALMENTE O RESTO PARA VER SE ACHA ALGUEM MENOR
    for (int i = inicio + 1; i < tamanho; i++){
        if (vetor[i] < vetor[indiceMenor]){
            indiceMenor = i; //ATUALIZA O INDICE DO MENOR ENCONTRADO
        }
    }
    return indiceMenor;
}

//ALGORITMO DE ORDENACAO (SELECTSORT)
void ordenar(int vetor[], int tamanho) {
    //PARA CADA POSICAO DO VETOR(DA PRIMEIRA ATE A PENULTIMA)
    for(int i = 0; i < tamanho - 1; i++){
        //1. USA A BUSCA SEQUENCIAL PARA ACHAR O MENOR
        //NO PEDECO DESORDENADO DO VETOR
        int indiceDoMenor = buscaSequencialMenor(vetor, i , tamanho);

        //TROCA O ELEMENTO ATAUL COM O MENOR ENCONTRADO
        if (indiceDoMenor != i){
            trocar(&vetor[i], &vetor[indiceDoMenor]);
        }
        //VISUALIZACAO PASSO A PASSO
        printf("Passo %d (Menor achado: %d): ", i+1, vetor[i]);
        for(int k=0; k<tamanho; k++) printf("%d ", vetor[k]);
        printf("\n");
    }
}
int main(){
    int vetor[TAM] = {64,25,12,22,11,90,1,5,8,33};

    printf("--- VETOR ORIGINAL ---\n");
    for(int i = 0; i<TAM; i++) printf("%d ", vetor[i]);
    printf("\n\n");

    ordenar(vetor, TAM);

    printf("\n--- VETOR ORDENADO ---\n");
    for(int i = 0; i < TAM; i++) printf("%d ", vetor[i]);
    printf("\n");

    return 0;
}