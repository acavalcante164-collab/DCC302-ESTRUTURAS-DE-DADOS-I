#include <stdio.h>
#include <stdlib.h>

//FUNCAO QUE CONVERTE HORAS, MINUTOS  E SEGUNDO EM SEGUNDOS TOTAIS
int converterParaSegundos(int h, int m, int s) {
    return (h * 3600) + (m * 60) + s;
}

int main () {
    int horas, minutos, segundos;

    //ENTRADA DO USUARIO
    printf("DIGITE AS HORAS, MINUTOS E SEGUNDOS (NESSA ORDEM!):  ");
    scanf("%d %d %d", &horas, &minutos, &segundos);

    //CHAMADA DA FUNCAO
    int totalSegundos = converterParaSegundos(horas, minutos, segundos);

    //SAIDA
    printf(" A CONVERSAO DESSE HORARIO EM SEGUNDO EH: %d\n", totalSegundos);

    return 0;
}