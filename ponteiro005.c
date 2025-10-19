#include <stdio.h>
struct ponto{
    float x;
    float y;
};
void imprime (struct ponto* pp){
    printf("o ponto fornecido foi: %.2f %.2f", pp->x, pp->y);
}
void captura(struct ponto* pp){
    printf("Digite dois valores: ");
    scanf("%f %f", &pp->x, &pp->y);
}
int main(){
    struct ponto p;

    captura(&p);
    imprime(&p);

    return 0;

}