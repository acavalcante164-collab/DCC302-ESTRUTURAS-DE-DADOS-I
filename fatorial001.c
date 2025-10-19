#include <stdio.h>

int fatorial (int n){
    if (n == 0 || n == 1){  //caso base para encerrar o loop
        return 1;
    } else {
        return n * fatorial (n - 1);    //caso recursiovo
    }
}
int main(){
    int num;

    printf("Digite um valor > 0: ");
    scanf("%d", &num);

    if (num < 0 ){
        printf("Coloca um valor positivo!");
    } else{
        printf("%d",fatorial(num));
    }
    
    return 0;
}