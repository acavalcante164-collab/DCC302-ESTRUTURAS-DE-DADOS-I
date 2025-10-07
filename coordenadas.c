#include <stdio.h>

/* Captura e imprime as coordenadas de um ponto qualquer */
typedef struct ponto {

    float x;
    float y;
}Ponto;

void ler(Ponto *p){
    scanf("%f %f", &p->x, &p->y);

}
void imprimir(){
    printf("Ponto fornecido: (%.2f %.2f)\n", p.x, p.y);
    
}
}
int main(){

    /*Desta forma, a estrutura ponto passa a ser um tipo e podemos então declarar variáveis deste tipo
    
    Esta linha de código declara p como sendo uma variável do tipo struct ponto. Os
    elementos de uma estrutura podem ser acessados através do operador de acesso
    “ponto” (.). Assim, é válido escrever: 

    */
    struct ponto p;

    printf("Cordenadas (X e Y): ");
    
    
    return 0;
}

