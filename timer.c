#include <stdio.h>
#include <windows.h> // Sleep
#include <stdlib.h>

int main() {
    int tempo;

    // Solicita ao usuário o tempo em segundos
    printf("Digite o tempo do temporizador (em segundos): ");
    scanf("%d", &tempo);

    printf("\nTemporizador iniciado por %d segundos...\n", tempo);

    // Contagem regressiva
    while (tempo > 0) {
        printf("Faltam %d segundo(s)...\n", tempo);
        Sleep(1000);  // Espera 1 segundo (1000 milissegundos)
        tempo--;
    }

    printf("\n⏰ Tempo esgotado!\n");
    return 0;
}
