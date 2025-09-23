#include <stdio.h>
int main(){
    int A, B, S;
    int *ptA, *ptB, *ptS;

    A = 2;
    B = 3;

    ptA = &A; //ptA recebe o endereco de A
    ptB = &B; //ptB recebe o endereco de B
    ptS = &S; //ptS recebe o endereco de S
    
    *ptS = *ptA + *ptB; //ptS está em um endero que nao foi declarado nada entao esta vazio = que vai receber o conteudo apontado das variaveis A e B
    
    printf("Resultado = %d", S);



    return 0;
}