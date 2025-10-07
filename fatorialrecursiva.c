#include <stdio.h>

int fatorial (int n) {
    if (n == 0 || n == 1) {
        return 1; 
                          //CASO BATE 0! = 1 E 1! =1
    } else {
        return n * fatorial(n-1);   //chamada recursiva
    }    
}

int main (){
    int num;

    printf("Digite um numero: ");
    scanf("%d", &num);

    if (num < 0) {
        printf("Fatorial nao exite para numeros negativos.\n");
    } else {
        printf("o fatorial de %d eh %d\n", num, fatorial(num));
    }
    return 0;
}

/*
Você quer saber 5! → você pede: "me diz 4! e eu multiplico por 5".

Para saber 4!, você pede: "me diz 3! e eu multiplico por 4".

Para saber 3!, você pede: "me diz 2! e eu multiplico por 3".

Para saber 2!, você pede: "me diz 1! e eu multiplico por 2".

Quando chega no 1!, você já sabe a resposta (1) → é o caso base.

Depois, as respostas voltam empilhadas:

Se n for 0 ou 1, a função já devolve 1 e para.

Senão, ela faz n * fatorial(n-1), ou seja, pede para a função calcular o fatorial do número menor.

Como o computador faz fatorial(5) na prática:

fatorial(5) → precisa de fatorial(4)

fatorial(4) → precisa de fatorial(3)

fatorial(3) → precisa de fatorial(2)

fatorial(2) → precisa de fatorial(1)

fatorial(1) → caso base → retorna 1
*/