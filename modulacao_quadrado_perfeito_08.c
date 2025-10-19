/*
8) Elabore uma função para verificar se um número é um quadrado perfeito. Um quadrado
perfeito é um número inteiro não negativo que pode ser expresso como o quadrado de
outro número inteiro. Exemplos: 1, 4, 9.
*/
#include <stdio.h>
#include <math.h> //PARA USAR O SQRT()

// FUNCAO QUE VERIFICA SE UM NUMERO EH QUADRADO PERFEITO
int EhQuadradoPerfeito(int n)
{
    if (n < 0)
        return 0; // NUMEROS NEGATIVOS NAO PODEM SER QUADRADOS PERFEITO

    int raiz = sqrt(n);
    return (raiz * raiz == n);
}

int main()
{
    int numero;

    printf("Digite um numero inteiro: ");
    scanf("%d", &numero);

    if (EhQuadradoPerfeito(numero))
    {
        printf("%d Eh um quadrado perfeito.\n", numero);
    }
    else
    {
        printf("%d NAO EH UM QUADRADO PERFEITO.\n", numero);
    }
    return 0;
}