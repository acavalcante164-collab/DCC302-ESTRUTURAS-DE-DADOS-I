#include <stdio.h>
#include <windows.h>  // Para Sleep() e Beep()
#include <stdlib.h>

int main() {
    int minutos, segundos, total_segundos;

    // Entrada do usuário
    printf("Digite o tempo do temporizador:\n");
    printf("Minutos: ");
    scanf("%d", &minutos);
    printf("Segundos: ");
    scanf("%d", &segundos);

    // Convertendo tudo para segundos
    total_segundos = minutos * 60 + segundos;

    printf("\nTemporizador iniciado por %d minuto(s) e %d segundo(s)...\n\n", minutos, segundos);

    // Contagem regressiva
    while (total_segundos > 0) {
        int m = total_segundos / 60;
        int s = total_segundos % 60;

        printf("\rTempo restante: %02d:%02d", m, s);
        fflush(stdout);      // Garante atualização da linha
        Sleep(1000);         // Espera 1 segundo
        total_segundos--;
    }

    // Alerta sonoro (opcional)
    printf("\r⏰ Tempo esgotado!                  \n");
    Beep(750, 500);  // Som opcional (frequência, duração)
    
    return 0;
}
