#include <stdio.h>

// FUNCAO QUE CALCULA OPO FATORIAL DE UM NUMERO
long long fatorial(int n)
{
    long long fat = 1;
    for (int i = 2; i <= n; i++)
    {
        fat *= i;
    }
    return fat;
}

// FUNCAO QUE CALCULA O NUMERO DE EULER USANDO A SERIE
double calcular_e(int N)
{
    double e = 0.0;
    for (int i = 0; i <= N; i++)
    {
        e += 1.0 / fatorial(i);
    }
    return e;
}
int main()
{
    int termos;
    printf("DIGITE O NUMERO DE TERMOS DA SERIE PARA CALCULAR 'e': ");
    scanf("%d", &termos);

    double resultado = calcular_e(termos);
    printf("VALOR APROXIMADO DE E COM %d TERMOS: %.8lf\n", termos, resultado);

    return 0;
}