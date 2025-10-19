#include <stdio.h>

typedef struct{
    float x;
    float y;
} Ponto; //DEFINE A struct e ja cria o apelido "Ponto"

int main(){
    Ponto p1;
    p1.x = 10.0;
    p1.y = 20.0;

    printf("VALORES DE X e Y = %.2f %.2f", p1.x, p1.y);
    return 0;
} 