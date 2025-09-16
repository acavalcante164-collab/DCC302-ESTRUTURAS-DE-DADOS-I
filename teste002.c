#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5341
int main (){
    int vet[TAM];
    int i, colisoes, valor;
    for (i = 0; i < TAM; i++)
        vet[i] = -1;
    colisoes = 0;
    srand((unsigned)time(NULL));
    for (i = 0; i < 2000; i++){
        valor = rand()%1000000 + 1;
        if(vet[valor%TAM] != -1)
            colisoes++;
        vet[valor%TAM] = valor;
    }
    printf("Numero de colisoes: %d\n", colisoes);
}
