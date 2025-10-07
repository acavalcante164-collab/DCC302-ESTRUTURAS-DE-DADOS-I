#include <stdio.h>

//FUNCAO RECURSIVA VAI CHAMAR A SE MESMA PARA MONTAR O FATORIAL
int fatorial (int n){
    if (n == 0 || n == 1){ //CASO BASE QUE JA SABEMOS OS RESULTADOS
        return 1;          //CASO BASE 0! == 1 || 1! == 1
    } else {
        return n * fatorial (n - 1);    //CHAMADA RECURSIVA ATE CHEGAR NO CASO BASE QUE JA SABEMOS
    }
}

int main (){
    int num;
    printf("Digite um numero >= 0: ");
    scanf("%d", &num);

    printf("O fatoria de %d eh = %d \n", num, fatorial(num));

    return 0;
}