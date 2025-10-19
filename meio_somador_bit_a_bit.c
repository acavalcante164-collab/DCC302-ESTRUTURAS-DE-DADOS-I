#include <stdio.h>

// FUNCAO MEIO SOMADOR

void meioSomador(int a, int b, int *Soma, int *Carry)
{
    *Soma = a ^ b;  // SOMA USANDO XOR
    *Carry = a & b; // CARRY USANDO AND
}

int main()
{
    int a, b, S, C;

    printf("Digite o primeiro bit (0 ou 1): ");
    scanf("%d", &a);

    printf("Digite o segundo bit (0 ou 1): ");
    scanf("%d", &b);

    meioSomador(a, b, &S, &C);

    printf("Resultado: Soma = %d\n Carry = %d\n", S, C);

    return 0;
}