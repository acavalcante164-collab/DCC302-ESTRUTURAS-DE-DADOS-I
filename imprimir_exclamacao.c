#include <stdio.h>

// FUNCAO PARA IMPRIMIR O PADRAO DE EXCLAMACAO
void ImprimirExclamacao(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            printf("! ");
        }
        printf("\n");
    }
}

int main()
{
    int n;
    printf("Digite um numero inteiro positivo: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("insira um numero maior que zero.\n");
        return 1;
    }

    ImprimirExclamacao(n);

    return 0;
}