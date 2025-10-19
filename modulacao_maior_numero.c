#include <stdio.h>

// FUNCAO QUE RECEBE DOIS INTEIRO E RETORNA O MAIOR
int maior (int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

int main () {
    int num1, num2, resultado;

    printf("Digite dois numeros inteiros:\n");
    scanf("%d %d", &num1, &num2);

    resultado = maior(num1, num2);

    printf("O maior numero eh: %d\n", resultado);

    return 0;
}