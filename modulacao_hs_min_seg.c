/*
7) Elabore uma função que receba três números inteiros como parâmetro, representando
horas, minutos e segundos. A função deve retornar esse horário convertido em
segundos.

*/
#include <stdio.h>
#include <stdlib.h>

int main () {
    int horas, minutos, segundos;

    printf(" Digite as horas, minutos e segundos (Nessa mesma sequencia): ");
    scanf("%d %d %d", &horas, &minutos, &segundos);

    int h = horas * 3600;
    int m = minutos * 60;
    int s = h + m + segundos ;

    printf ("A conversao dessas horas e minutos em segundo eh: %d", s);
    return 0;
}
