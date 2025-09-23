/* PROGRAMA QUE LE UM NUMERO E IMPRIME SEU FATORIAL*/
#include <stdio.h>
void fat(int n);

// FUNCAO PRINCIPAL
int main()
{
    int n;
    printf("Digite um numero positivo: \n");
    scanf("%d", &n);
    fat(n);
    return 0;
}
/* FUNCAO PARA IMPRIMIR O VALOR DO FATORIAL*/
void fat(int n)
{
    int i;
    int f = 1;
    for (i = 1; i <= n; i++)
        f *= i;
    printf("FATORIAL = %d\n", f);
}

