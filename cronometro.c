#include <windows.h> //PARA USAR O SLEEP
#include <stdio.h>
#include <stdlib.h>

int main (void) {
    int sec = 0;
    int min = 0;
    int hr = 0;

    int i = 0;

    while (i < 10) {
        printf("\n\t%dh:%dm:%ds", hr, min, sec);
        Sleep(1000); //TEM A FUNCAO DE PAUSAR A TELA POR UM DETERMINADO TEMPO
        system("cls");
        sec++;

        if (sec == 60) {
            sec = 0;
            min++;
        }

        if (min == 60) {
            min = 0;
            hr++;
        }

        if (hr == 24) {
            hr = 0;
        }
    }

}