#include <stdio.h>

// DEFINICAO DE PI
#define PI 3.1414592

// FUNCAO PARA CONVERTER GRAUS PARA RADIANOS
float GrausParaRadianos(float graus)
{
    return graus * (PI / 180.0);
}

// FUNCAO PARA CALCULAR O FATORIAL DE UM NUMERO INTEIRO
long long fatorial(int num)
{
    long long fat = 1;
    for (int i = 2; i <= num; i++)
    {
        fat *= i;
    }
    return fat;
}

// FUNCAO PARA CALCULAR O SENO USANDO A SERIE DE TAYLOR
float SenoTaylor(float graus)
{
    float x = GrausParaRadianos(graus);
    float seno = 0.0;

    for (int n = 0; n <= 5; n++)
    {
        float termo = ((n % 2 == 0 ? 1 : -1) * (pow(x, 2*n + 1))) / fatorial(2 * n + 1);
        seno += termo;
    }
    return seno;
}

int main()
{
    float angulo;
    printf("Digite o angulo em graus: ");
    scanf("%f", &angulo);

    float seno = SenoTaylor(angulo);
    printf("O seno aproximado de %.2f graus eh : %.6f\n", angulo, seno);

    return 0;
}