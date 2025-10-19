#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5341

int main()
{
    int A, B, S;
    int *ptA;
    int *ptB;
    int *ptS;

    A = 2;
    B = 3;
    ptA = &A;
    ptB = &B;
    ptS = &S;

    *ptS = *ptA + *ptB;
    printf("Resultado = %d", S);
}