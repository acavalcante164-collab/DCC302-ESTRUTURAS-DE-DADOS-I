#include <stdio.h>
#include <math.h>
/*
 DCC302 - ESTRUTURAS DE DADOS I - T01 (2025.2)
NOME: ALONSO FERNANDES CAVALANTE
MATRICULA: 2024005534

LISTA 03 - EXERCICIO DA AULA 04  24/09/2025 A 06/10/2025
*/

/*

DESCRIÇÃO:

Considerando os slides anteriores, crie uma função que verifica se um dado Ponto está no interior de um círculo.

*/
struct Ponto{
    float x;
    float y;
};

struct Circulo{
    struct Ponto centro; //CENTRO DO CIRCULO TBM EH UM PONTO
    float raio;    //RAIO DO CIRCULO
};

//FUNCAO PARA CALCULAR A DISTANCIA ENTRE DOIS PONTOS
float distancia(struct Ponto *p1, struct Ponto *p2){

    float d = sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2));
    return d;
}

//VERIFICAO SE UM PONTO ESTA NO INTERIO OU NA BORDA
//1 PARA VERDADEIRO
int interior (struct Circulo *c, struct Ponto *p){
    //DISTANCIA
    float d = distancia(&c->centro, p);
    if (d <= c->raio){
        return 1; /*O PONTO ESTA NO INTERIOR DO CIRCULO*/
    } else    
        return 0;
}

int main(){
    //CIRCULO TESTE
    struct Circulo testeCirculo;
    testeCirculo.centro.x = 0.0;
    testeCirculo.centro.y = 0.0;
    testeCirculo.raio = 5.0;

    //PONTO DENTRO DO CIRCULO
    struct Ponto pontoA;
    pontoA.x = 3.0;
    pontoA.y = 3.0;

    //FORA DO CIRCULO
    struct Ponto pontoB;
    pontoB.x = 5.0;
    pontoB.y = 5.0;

    //VERIFICA O PONTO A
    if (interior(&testeCirculo, &pontoA)){
        printf("O PONTO A (%.1f, %.1f) ESTA DENTRO DO CIRCULO.\n", pontoA.x, pontoA.y);
    } else {
        printf("O PONTO A (%.1f, %.1f) ESTA FORA DO CIRCULO.\n", pontoA.x, pontoA.y);
    }

    //VERIFICA PONTO B
    if (interior(&testeCirculo, &pontoB)){
        printf("O PONTO B (%.1f, %.1f) ESTA DENTRO DO CIRCULO.\n", pontoB.x, pontoB.y);
    } else {
        printf("O PONTO B (%.1f, %.1f) ESTA FORA DO CIRCULO.\n", pontoB.x, pontoB.y);
    }  

    return 0;
}
