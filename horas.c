#include<stdio.h>

void hm(int mnts, int* h, int* m){
    *h = mnts / 60; //CALCULA AS HORAS E GUA
    *m = mnts % 60;
}
int main(){
    int horas, minutos, min;

    printf("DIGITE OS MINUTOS: ");
    scanf("%d", &minutos);

    hm(minutos, &horas, &min);

    printf("%d minutos corresponde ah %d horas e %d minutos", minutos, horas, min);

    return 0;
}