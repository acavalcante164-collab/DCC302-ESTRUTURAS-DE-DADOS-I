#include <stdio.h>
#include <stdlib.h> //NECESSARIO PARA MALLOC E FREE

struct ponto{
    float x;
    float y;
};
int main(){
    struct ponto *pp;

    //ALOCA MEMORIA DO TAMANHO DE "STRUCT PONTO" E GUARDA O ENDERECO EM PP
    pp = (struct ponto*)malloc(sizeof (struct ponto));

    //SEMPRE VERIFICA SE A ALOCACAO DEU CERTO
    if (pp == NULL){
        printf("Erro na alocacao");
        return 1; //codigo de erro
    }
    printf("Digite as cordenadas de X e Y: ");
    scanf("%f %f", &pp->x, &pp->y);

    printf("o valor das Coordenadas X e Y = %.2f %.2f\n", pp->x, pp->y);
    //SEMPRE QUE USAR MALLOC, DEVE LIBERAR A MEMORIA NO FINAL
    free(pp);
    return 0;
}