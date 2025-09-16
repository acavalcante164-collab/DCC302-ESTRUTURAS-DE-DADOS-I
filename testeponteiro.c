#include <stdio.h>

//Atualizacao indireta
void display(int var, int *ptr);
void update(int *p);

int main()
{
    int var = 15;
    int *ptr;

    ptr = &var;

    display(var, ptr);
    
    update(&var);

    printf("\n\n");
    display(var, ptr);

    return 0;
}
void display(int var, int *ptr)
{
    printf("Conteudo de var =  %d\n", var);
    printf("Endereco de var =  %p\n", var);
    printf("Conteudo apontado por ptr =  %d\n", *ptr);
    printf("Endereco apontado por ptr = %p\n", ptr);
    printf("Endereco do ptr           =  %p\n", &ptr);
}
void update(int *p)
{
    //VAI ATUALIZAR MINHA VARIAVEL, O APONTADO
    *p = *p + 1;
}
