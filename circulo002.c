#include <stdio.h>
#include <math.h>

/*
CRIE UMA FUNCAO QUE VERIFICA SE UM DADO PONTO ESTA NO INTERIOR DE UM CIRCULO
*/

// Definições de tipos abstratos
typedef struct ponto {
    float x;
    float y;
} Ponto;

typedef struct circulo {
    Ponto centro;
    float raio;
} Circulo;

// Função que calcula a distância entre dois pontos
float distancia(Ponto p1, Ponto p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// Função que verifica se o ponto está dentro ou na borda do círculo
int pontoDentroCirculo(Ponto p, Circulo c) {
    float d = distancia(p, c.centro);
    return d <= c.raio; // 1 (verdadeiro) se dentro ou na borda, 0 (falso) se fora
}

int main() {
    Ponto p = {2.0, 3.0};
    Circulo c = {{0.0, 0.0}, 5.0}; // centro (0,0), raio = 5

    if (pontoDentroCirculo(p, c)) {
        printf("O ponto (%.2f, %.2f) esta dentro do circulo.\n", p.x, p.y);
    } else {
        printf("O ponto (%.2f, %.2f) esta fora do circulo.\n", p.x, p.y);
    }

    return 0;
}
