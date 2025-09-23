#include <stdio.h>

int main()
{
    int var = 15;
    int *ptr;

    ptr = &var;
    printf("Conteudo de var: %d\n", var);
    printf("Endereco de var: %p\n", var); //%p vai mostrar onde está a declaração na memoria
    printf("Conteudo apontado por ptr: %d\n", *ptr);
    printf("Endereco apontado por ptr: %p\n", ptr);
    printf("Endereco do ptr                = %p\n", &ptr);

    *ptr = 73;
    printf("\n\n");
    printf("Conteudo de var: %d\n", var);
    printf("Endereco de var: %p\n", var);
    printf("Conteudo apontado por ptr: %d\n", *ptr);
    printf("Endereco apontado por ptr: %p\n", ptr);
    printf("Endereco do ptr                = %p\n", &ptr);
    return 0;
}
/*
PONTEIRO É UM APONTADOR PARA ENDEREÇO DE MEMÓRIA (UMA VARIÁVEL QUE PODE CONTER
ENDEREÇOS DE MEMÓRIA), COM ISSO PODEMOS ATUALIZAR OS CONTEUDOS DESSES ENDEREÇOS DE FORMA INDIRETA 

%p vai mostrar onde está a declaração na memoria
para declarar ponteiro em C usasse *
podemos utilizar para apontar o endereço dessa variável ,
para isso atribua o ponteiro ao endereço da variavel



o conteúdo de ptr é o endereço da variável var

//PONTEIROS
*ptr : o apontado por, conteúdo do endereço da variável que ptr aponta
ptr : o endereço da variável
&ptr : o endereço do ponteiro



*/