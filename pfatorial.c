/*Programa que le um numero e imprime seu fatorial */
#include <stdio.h>

int fat(int n); /*Prototipo da funcao*/
/*Funcao principal*/
int main (void)
{
    int n;
    scanf("%d", &n);
    printf("Fatorial = %d\n", fat(n));
    return 0;
}