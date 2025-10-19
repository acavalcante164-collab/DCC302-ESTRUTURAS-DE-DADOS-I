#include <stdio.h>
#define PI 3.14159

// Função que calcula o volume de uma esfera
float calcularVolumeEsfera(float raio) {
    return (4.0 / 3.0) * PI * raio * raio * raio;
}

int main() {
    float r;

    // Entrada do raio
    printf("Digite o raio da esfera: ");
    scanf("%f", &r);

    // Cálculo e saída
    float volume = calcularVolumeEsfera(r);
    printf("O volume da esfera eh: %.4f\n", volume);

    return 0;
}
