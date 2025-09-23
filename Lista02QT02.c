/*
 DCC302 - ESTRUTURAS DE DADOS I - T01 (2025.2)
NOME: ALONSO FERNANDES CAVALANTE
MATRICULA: 2024005534

EXERCICIO DA AULA 02  17/09/2025 A 24/09/2025
*/

/*

DESCRIÇÃO:
2 - Um ponteiro pode ser usado para dizer a uma função onde ela deve depositar o resultado de seus cálculos.
Escreva uma função hm que converta minutos em horas-e-minutos. A função recebe um inteiro mnts e os endereços de duas variáveis inteiras,
digamos h e m, e atribui valores a essas variáveis de modo que m seja menor que 60 e que 60*h + m seja igual a mnts.
Escreva também uma função main que use a função hm.

*/
#include <stdio.h>
#include <stdlib.h>
//FUNCAO QUE CONVERTE MINUTOS EM HORAS
void hm(int mnts,int* h, int* m){

*h = mnts / 60; //CALCULA AS HORAS E GUARDA NO ENDERECO DE h
*m = mnts % 60; //CALCULO OS MINUTOS RESTANTES E GUARDA NO ENDERECO DE m

}

int main(){
int horas, minutos, min;

printf("Digite os Minutos: ");
scanf("%d", &minutos);

//CHAMANDO A FUNCAO E PASSANDO OS ENDERECOS DE HORAS E MIN
hm(minutos, &horas, &min);

printf("%dmin eh a mesma coisa que %dhoras e %dmin.\n", minutos, horas, min);

return 0;

}

