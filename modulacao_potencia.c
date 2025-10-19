#include <stdio.h>

// FUNCAO PARA CALCULAR A POTENCIA X ELEVADO A Y
int potencia(int x, int y)
{
    int resultado = 1;
    for (int i = 0; i < y; i++)
    {
        resultado *= x;
    }
    return resultado;
}

int main()
{
    int base, expoente;

    printf("Digite o valor da base (x): ");
    scanf("%d", &base);

    printf("Digite o valor do expoente (y): ");
    scanf("%d", &expoente);

    int resultado = potencia(base, expoente);

    printf("Resultado: %d elevado a %d = %d\n", base, expoente, resultado);

    return 0;
}