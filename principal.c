#include <stdio.h>
#include "converte.h"  /* inclui a declaração de converte */

int main(void)
{
    float t1, t2;

    printf("Entre com temperatura em Celsius: ");
    if (scanf("%f", &t1) != 1) {
        fprintf(stderr, "Entrada invalida\n");
        return 1;
    }

    t2 = converte(t1);

    printf("A temperatura em Fahrenheit vale: %f\n", t2);
    return 0;
}
