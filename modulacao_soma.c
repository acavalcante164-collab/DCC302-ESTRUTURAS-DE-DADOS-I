#include <stdio.h>

//FUNCAO QUE REALIZA SOMA
int soma(int x, int y) {
    return x + y;
}

int main() {
    int a, b;
    printf("Digite dois numeros: ");
    scanf("%d%d", &a, &b);
    printf("A soma eh: %d\n", soma(a,b));

    return 0;
}