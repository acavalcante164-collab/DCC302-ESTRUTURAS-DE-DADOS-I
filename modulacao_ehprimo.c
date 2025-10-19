#include <stdio.h>
#include <stdlib.h>

// Função para verificar se um numero eh primo
int ehPrimo(int n) {
    if (n < 2) return 0;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

// Função para ler numeros e verificar se sao primos
void lerNumeros() {
    int num;
    printf("Digite um numero inteiro positivo (0 para sair): ");
    scanf("%d", &num);

    while (num != 0) {
        if (ehPrimo(num))
            printf("%d eh primo!\n", num);
        else
            printf("%d NÃO eh primo!\n", num);

        printf("\nDigite outro numero (0 para sair): ");
        scanf("%d", &num);
    }
}

// Função principal
int main() {
    lerNumeros();
    return 0;
}
