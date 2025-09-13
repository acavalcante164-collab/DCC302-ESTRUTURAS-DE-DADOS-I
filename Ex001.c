/*
PESQUISA SOBRE PONTEIROS
*/
#include <stdio.h>
#include <conio.h>

int main (void)
{
    //Valor eh a variavel que
    //sera apontada pelo ponteiro
    int valor = 27;

    //declaracao de variavel ponteiro
    int *ptr;

    //atribuindo o endereco da variaveel valor ao ponteiro
    ptr = &valor;

    printf("Utilizando ponteiro\n\n");
    printf("Conteudo da variavel valor: %d\n", valor);
    printf("Endereco da variavel valor: %x \n", &valor);
    printf("Conteudo da variavel ponteiro ptr: %x ", ptr);

    getch();
    return (0);
}
