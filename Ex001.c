
/*
• Crie um vetor com5341 posições. Faça 2000 inserções nesse vetor com números aleatórios no intervalor de 1 a 106. As inserções devem ser feitas na posição (valor%5341). Conte quantas ezes houve colisões nesse vetor.
• Colisão é quando um número é sobrescrito no vetor.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5341

int main()
{
    int vet[TAM];
    int i, colisoes, valor;

    for (i = 0; i < TAM; i++)
        vet[i] = -1;

    colisoes = 0;
    srand((unsigned)time(NULL)); // Biblioteca stdlib.h  Define uma nova semente para a função rand

    for (i = 0; i < 2000; i++)
    {
        valor = rand() % 1000000 + 1; // Retorna um flutuante randômico entre 0 e 1
        if (vet[valor % TAM] != -1)
            colisoes++;
        vet[valor % TAM] = valor;
    }
    printf("Numero de colisoes: %d\n", colisoes);
    return 0;
}