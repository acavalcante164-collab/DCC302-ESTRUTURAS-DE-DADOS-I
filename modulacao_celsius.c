/*
3) Escreva uma função que receba por parâmetro uma temperatura em graus Fahrenheit
e a retorne convertida em graus Celsius. A fórmula de conversão é: C = (F – 32.0) *
(5.0/9.0), sendo F a temperatura em Fahrenheit e C a temperatura em Celsius.
*/
#include <stdio.h>
#include <stdlib.h>

//FUNCAO FAHRENHEIT CELSIUS
float fahrenheit (float f) {
    return (f - 32.0) * (5.0 / 9.0);
}
int main () {
    float x;
    printf("Digite a temperatura em FAHRENHEIT: ");
    scanf("%f", &x);

    printf("A temprerantura %.2f (F) em Celsius eh: %.2f", x, fahrenheit(x));

    return 0;
}