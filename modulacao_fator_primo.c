#include <stdio.h>

// FUNCAO PARA ENCONTRAR O MAIOR FATOR PRIMO
int maiorFatorPrimo(int n)
{
    int maior = -1;

    // REMOVE FATORES DE 2
    while (n % 2 == 0)
    {
        maior = 2;
        n /= 2;
    }

    // VERIFICA FATORES IMPARES
    for (int i = 3; i * i <= n; i += 2)
    {
        while (n % i == 0)
        {
            maior = i;
            n /= i;
        }
    }

    // SE O NUMERO RESTANTE FOR MAIOR QUE 2, ELE EH PRIMO
    if (n > 2)
    {
        maior = n;
    }

    return maior;
}

int main()
{
    int numero;

    printf("Digite um numero inteiro positivo: ");
    scanf("%d", &numero);

    if (numero <= 0)
    {
        printf("Numero invalido. Digite um numero inteiro positivo.\n");
        return 1;
    }

    int maiorPrimo = maiorFatorPrimo(numero);
    printf("O maior fator primo de %d eh:   %d\n", numero, maiorPrimo);

    return 0;
}