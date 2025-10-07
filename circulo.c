#include <stdio.h>
#include <math.h>
/*
CRIE UMA FUNCAO QUE VERIFICA SE UM DADO PONTO ESTA NO INTERIOR DE UM CIRCULO
*/

typedef struct ponto{
    float x;
    float y;
}Ponto;

typedef struct circulo{
    Ponto centro;
    float raio;
}Circulo;

float distancia(Ponto p1, Ponto p2){
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y,2));
}
int pontoDentroCirculo(Ponto p, Circulo c){
    float d = distancia(p, c.centro);
    return d<= c.raio;
}
int main(){
    Ponto p = {2.0, 3.0};
    Circulo c  = {{0.0,0.0},5.0}; // centro (0,0), raio = 5

    if

}