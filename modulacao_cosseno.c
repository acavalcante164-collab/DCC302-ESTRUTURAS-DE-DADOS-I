#include <stdio.h>
#include <math.h> // para pow()

#define PI 3.1414592

// Converte graus para radianos
float grausParaRadianos(float graus)
{
    return graus * (PI / 180.0);
}

// Calcula o fatorial
long long fatorial(int n)
{
    long long fat = 1;
    for (int i = 2; i <= n; i++)
    {
        fat *= i;
    }
    return fat;
}

// Função para calcular o cosseno usando a série de Taylor
float cossenoTaylor(float graus)
{
    float x = grausParaRadianos(graus);
    float cosseno = 0.0;

    for (int n = 0; n <= 5; n++)
    {
        float termo = (pow(-1, n) * pow(x, 2 * n)) / fatorial(2 * n);
        cosseno += termo;
    }

    return cosseno;
}

int main()
{
    float angulo;
    printf("Digite o ângulo em graus: ");
    scanf("%f", &angulo);

    float resultado = cossenoTaylor(angulo);
    printf("O cosseno aproximado de %.2f graus é: %.6f\n", angulo, resultado);

    return 0;
}
