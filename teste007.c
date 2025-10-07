#include <stdio.h>

struct ponto {
    float x;
    float y
};

int main(){
    struct ponto *pp;

    printf("Digite as cordenadas X e Y: ");
    scanf("%f %f", &pp->x, &pp->y);

    printf("O valor das Cordexas X e Y = %.2f %.2f", pp->x, pp->y);

    return 0;
}