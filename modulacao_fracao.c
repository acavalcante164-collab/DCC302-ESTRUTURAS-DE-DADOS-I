#include <stdio.h>

// FUNCAO QUE CALCULA A SERIE S
float CalcularSerie(int N)
{
    float S = 0.0;
    for (int i = 2; i <= N; i++)
    {
        float numerador = (i * i) + 1;
        float denominador = i + 3;
        S += numerador / denominador;
    }
    return S;
}
int main()
{
    int N;
    printf("Digite um numero inteiro positivo N: ");
    scanf("%d", &N);

    if (N < 2)
    {
        printf("O numero deve ser maior ou igual a 2.\n");
        return 1;
    }

    float resultado = CalcularSerie(N);
    printf("O resultado da serie S eh: %.2f\n", resultado);

    return 0;
}