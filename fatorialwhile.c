/* FATORIAL */
#include <stdio.h>

int main (void)
{
    int i , n, f = 1;

    printf("Digite um numero inteiro nao negativo: ");
    scanf("%d", &n);

    // Calcula fatorial
    i = 1;

    while (i <= n){
        f *= i;
        i++;
    }
    printf(" Fatorial = %d \n", f);
    return 0;
}