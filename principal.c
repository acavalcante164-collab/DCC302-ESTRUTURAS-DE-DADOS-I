/*Programa para conversao de temperatura */
#include <stdio.h>

float converte (float c);

int main (void)
{
    float t1, t2;

    /* mostra mensagem para usuario */
    printf("Entre com temperatura em Celsius: ");
    
    /*Captura valor entrado via teclado */
    scanf("%f", &t1);

    /* faz a conversao */
    t2 = converte(t1);

    /* exibe resultado */

    printf("A temperatura em Fahrenheit vale: %f\n", t2);

    return 0;
}