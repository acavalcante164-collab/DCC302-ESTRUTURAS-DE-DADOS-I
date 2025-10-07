/*
 DCC302 - ESTRUTURAS DE DADOS I - T01 (2025.2)
NOME: ALONSO FERNANDES CAVALANTE
MATRICULA: 2024005534

LISTA 03 - EXERCICIO DA AULA 04  24/09/2025 A 06/10/2025
*/

/*

DESCRIÇÃO:

Faça uma estrutura que usa um struct ponto e uma funcao para ler e outra para imprimir as coordenadas de um ponto. Obs.: perceba que no caso da leitura precisamos obrigatoriamente passar o ponteiroda estrutura,caso contrário não seria possível passar para o programa principal os dados lidos

*/
#include <stdio.h>

struct ponto {
    float x;
    float y;
};

//FUNCAO PARA MOSTRAR OS VALORES CONTIDOS
void imprime (struct ponto* pp){
    printf("O PONTO FORNECIDO FOI: (%.2f, %.2f)\n", pp->x, pp->y);
}
//FUNCAO PARA OBTER OS VALORES
void captura (struct ponto *pp){
    printf("DIGITE AS COORDENADAS DO PONTO (x,y): ");
    scanf("%f %f", &pp->x, &pp->y);
}
//FUNCAO PRINCIPAL
int main(){
    struct ponto p;

    captura(&p);
    imprime(&p);

    return 0;
}