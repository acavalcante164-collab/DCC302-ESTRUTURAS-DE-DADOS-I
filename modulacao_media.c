#include <stdio.h>

//FUNCAO QUE REALIZA SOMA
int media(int x, int y) {
    return (x + y) / 2;
}

int main() {
    int a, b;
    printf("Digite dois numeros: ");
    scanf("%d%d", &a, &b);
    printf("A MEDIA eh: %d\n", media(a,b));

    return 0;
}