#include <stdio.h>

// Função que calcula o IMC
float calcularIMC(float peso, float altura) {
    return peso / (altura * altura);
}

int main() {
    float peso, altura, imc;

    // Entrada de dados
    printf("Digite o peso (kg): ");
    scanf("%f", &peso);

    printf("Digite a altura (m): ");
    scanf("%f", &altura);

    // Cálculo do IMC
    imc = calcularIMC(peso, altura);

    // Exibição do resultado
    printf("O IMC calculado eh: %.2f\n", imc);

    return 0;
}
