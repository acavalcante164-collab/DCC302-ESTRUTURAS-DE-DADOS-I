/* Fatorial versão 2*/
#include <stdio.h>
int main(void){
int i;
int n;
int f =1;

printf("digite um numero inteiro nao negativo: ");
scanf("%d", &n);

//Fatorial
for (i = 1; i <= n; i++){
    f *= i;
}
printf(" Fatorial = %d \n", f);
return 0;
}