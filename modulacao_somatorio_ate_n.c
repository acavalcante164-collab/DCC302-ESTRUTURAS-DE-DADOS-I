#include <stdio.h>

// FUNCAO QUE CALCULA O SOMATORIO DE 1 ATE N
int somatorio(int n)
{
    int soma = 0;
    for (int i = 1; i <= n; i++)
    {
        soma += i;
    }
    return soma;
}

int main()
{
    int numero;

    printf("Digite um numero inteiro positivo: ");
    scanf("%d", &numero);

    if (numero <= 0)
    {
        printf("Digite um numero positivo.\n");
        return 1;
    }

    int resultado = somatorio(numero);
    printf("O somatorio de 1 ate %d eh: %d\n", numero, resultado);

    return 0;
}