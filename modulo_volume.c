/*
4) Escreva uma função que receba por parâmetro a altura e o raio de um cilindro circular
e retorne o volume desse cilindro. O volume de um cilindro circular é calculado por
meio da seguinte fórmula: em que π = 3.1415926.
*/

#include <stdio.h>

// Definindo o valor de π como constante
#define PI 3.1415926

// Função para calcular o volume do cilindro
float calcularVolumeCilindro(float raio, float altura)
{
    return PI * raio * raio * altura;
}

int main()
{
    float raio, altura;

    // Entrada de dados
    printf("Digite o raio do cilindro: ");
    scanf("%f", &raio);

    printf("Digite a altura do cilindro: ");
    scanf("%f", &altura);

    // Chamada da função e exibição do resultado
    float volume = calcularVolumeCilindro(raio, altura);
    printf("O volume do cilindro eh: %.4f\n", volume);

    return 0;
}
