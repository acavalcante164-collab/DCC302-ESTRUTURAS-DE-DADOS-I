#include<stdio.h>
int main(void)
{
float v[10]; //CRIA UM VETOR DE PONTO FLUTUANTE DE 10 POSICOES
float med, var; //DECLARA VARIAVEL PARA MEDIA E VARIACAO
int i; //INDICE PARA O LOOP

//FAZ A LEITURA DE TODOS OS VALORES DE V[i]
for(i=0; i < 10; i++)
    scanf("%f", &v[i]);

//CALCULA A MEDIA
med = 0.0;                      // MEDIA INICIA NULL ZERADA
for (i = 0; i < 10; i++)        //PERCORRE TODOS OS VALORES LIDO
    med = med + v[i];           //PEGA O ZERO E SOMA TODOS OS VALORES LIDOS
med = med / 10;                 //PEGA OS VALORES LIDOS E DIVIDE POR 10

//VARIACAO COMECA EM ZERO
var = 0.0;
for (i = 0; i < 10; i++) //PERCORRE TODOS OS VALORES LIDO
    var = var + (v[i] - med) * (v[i] - med); //ACUMULA O QUADRADO DA DIFERENCA PEGA O ZERO(VALORES PERCORRIDO - A MEDIA) MULTIPLICADO (VALORES PERCORRIDO - A MEDIA)
var = var / 10; //PEGA OS VALORES LIDOS E DIVIDE POR 10

printf("VARIACAO = %.2f\nMEDIA = %.2f", var, med);
    return 0;
}