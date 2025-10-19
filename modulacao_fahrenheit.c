#include <stdio.h>
#include <stdlib.h>

//Funcao que converte FAHRENHEIT EM CELSIUS
float fahrenheitParaCelsius(float f) {
    return (f - 32.0) * (5.0 / 9.0);
}

//FUNCAO PARA LER A TEMPERATURA EM FAHRENHEIT
float lerFahrenheit(){
    float temp;
    printf("Digite a temperatura em FAHRENHEIT: ");
    scanf("%f", &temp);
    return temp;
}

//FUNCAO PARA EXIBIR OS RESULTADOS
void exibirResultados(float f, float c) {
    printf("A temperatura %.2f (F) em Celsius eh: %.3f (C)\n", f, c);
}

//FUNCAO PRINCIPAL
int main() {
    float fahrenheit = lerFahrenheit();
    float celsius = fahrenheitParaCelsius(fahrenheit);
    exibirResultados(fahrenheit, celsius);
    
    return 0;
}