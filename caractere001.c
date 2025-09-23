#include <stdio.h>
#include <stdlib.h>

// Função que imprime uma string caractere por caractere
void imprime(char* s){
    int i;
    for (i = 0; s[i] != '\0'; i++) // enquanto não achar o '\0'
        printf("%c", s[i]);  // imprime o caractere
    printf("\n"); // pula linha no final
}
int main(){
    char palavra1[] = "Ola, mundo!";
    char palavra2[] = "Programacao em C";

    printf("imprimindo palavra1:\n");
    imprime(palavra1);

    printf("imprimindo palavra2:\n");
    imprime(palavra2);

    return 0;
}
