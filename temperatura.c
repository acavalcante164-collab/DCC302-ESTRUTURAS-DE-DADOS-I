//Programa para conversão de temperatura
#include <stdio.h>

float converte (float c)
{
    float f;
    f = 1.8 * c + 32;
    return f;
}

int main (void)
{
    float t1;
    float t2;

    /* mostra mensagem para usuario*/
    printf("Digite a temperatura em Celcius: ");

    /* Captura valor entrado via teclado */
    scanf("%f", &t1);

    /* faz a conversao */
    t2 = converte(t1);

    /* exibe resultado */
    printf("A temperatura em Fahrenheit eh: %.2f\n", t2);

    return 0;
}
