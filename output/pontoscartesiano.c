/* Captura e imprime as coordenadas de um ponto qualquer */
#include <stdio.h>

struct ponto
{
    float x;
    float y;
};

int main (void)
{
    struct ponto p;
    struct ponto *pp;

    printf("Digite as coordenadas do ponto (x y):  ");
    scanf("%f %f", &p.x, &p.y);
    printf("O ponto fornecido foi: (%.2f, %.2f)\n", p.x, p.y);

    return 0;
    
}
void imprime (struct ponto* pp)
{
    printf("O ponto fornecido foi: (%.2f, %.2f)\n", pp->x, pp->y );
}