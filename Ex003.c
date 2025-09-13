#include<stdio.h>

int main(void)
{
int a, b;
printf("Digite dois valores inteiro: ");
scanf("%d %d", &a, &b);
if ((a%2 == 0) &&  (b%2 ==0 ))
    printf("\nVoce digitou dois numeros pares");
return 0;
}