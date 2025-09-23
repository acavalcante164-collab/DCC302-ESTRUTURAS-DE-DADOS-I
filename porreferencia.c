#include <stdio.h>
void dobrar(int *x)
{
    *x = *x * 2;
}
int main()
{
    int a = 5;
    dobrar(&a); // atribuicao do endereco de a
    printf("Fora da funcao: %d\n", a);
    return 0;
}
