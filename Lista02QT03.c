/*
 DCC302 - ESTRUTURAS DE DADOS I - T01 (2025.2)
NOME: ALONSO FERNANDES CAVALANTE
MATRICULA: 2024005534

EXERCICIO DA AULA 02  17/09/2025 A 24/09/2025
*/

/*

DESCRIÇÃO:
3.Escreva uma função mm que receba um vetor inteiro v[0..n-1] e os endereços de duas variáveis inteiras,
digamos min e max, e deposite nessas variáveis o valor de um elemento mínimo e o valor de um elemento máximo do vetor.
Escreva também uma função main que use a função mm.

*/
#include <stdio.h>

void mm(int* min, int *max, int tam, int* vet){
    *max = vet[0]; //INICIALIZA O VETOR MAX NA PRIMEIRA POSICAO
    *min = vet[0]; //INICIALIZA O VETOR MIN NA PRIMEIRA POSICAO

    //PERCORRE O VETOR A PARTIR DO SEGUNDO ELEMENTO
    for(int i = 1; i < tam; i++){
        if (vet[i] > *max){
            *max = vet[i]; //ATUALIZA O VALOR DE MAX
        }
        if (vet[i] < *min){
            *min = vet[i]; //ATUALIZA O VETOR DE MIN
        }
    }    
}
int main (){
    int meuVetor[] = {87, 32, 97, 13, 24}; 
    //RETORNA A QUANTIDADE DE BYTES DA VARIAVEL / TAMANHO DE UM ELEMENTO
    int tamanho = sizeof(meuVetor) / sizeof(meuVetor[0]); //QUANTIDADE DE ELEMENTOS DO VETOR
    int valorMax, valorMin;

    mm(&valorMin, &valorMax, tamanho, meuVetor); //CHAMADA DA FUNCAO

    printf("Valor Maximo = %d\n", valorMax);
    printf("Valo Minimo = %d\n", valorMin);
    
    return 0;
}
