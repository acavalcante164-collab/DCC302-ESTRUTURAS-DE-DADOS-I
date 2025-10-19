#include <stdio.h>

// Função para imprimir o triângulo lateral
void imprimeTriangulo(int n)
{
    // Parte crescente
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            printf("* ");
        }
        printf("\n");
    }

    // Parte decrescente
    for (int i = n - 1; i >= 1; i--)
    {
        for (int j = 1; j <= i; j++)
        {
            printf("* ");
        }
        printf("\n");
    }
}

int main()
{
    int n;
    printf("Digite o valor de n: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Por favor, digite um número maior que zero.\n");
        return 1;
    }

    imprimeTriangulo(n);

    return 0;
}
