#include <stdio.h>
#include <stdlib.h> // Necessário para malloc() e free()

struct ponto {
    float x;
    float y;
};

int main(){
    struct ponto p; //CRIA A VARIAVEL 'P' NA MEMORIA
    struct ponto *pp; //CRIA  O PONTEIRO PP

    pp = &p;

    printf("Digite as cordenadas X e Y: ");
    scanf("%f %f", &pp->x, &pp->y);

    printf("O valor das Cordexas X e Y = %.2f %.2f", pp->x, pp->y);

    return 0;
}