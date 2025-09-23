#include <stdio.h>
#include <stdlib.h>

/*
Comprimento da cadeia de caracteres.
Consideremos a implementação de uma função que recebe como parâmetro de entrada uma
cadeia de caracteres e fornece como retorno o número de caracteres existentes na cadeia. O
protótipo da função pode ser dado por:
*/


// Função que imprime uma string caractere por caractere
int comprimento(char* s){
    int i;
    int n = 0; /* contador */ 
    for(i = 0; s[i] != '\0'; i++)
        n++;
    return n;    
}

int main(void){
    int tam;
    char cidade[] = "Rio de janeiro";
    tam = comprimento(cidade);
    printf("A String \"%s\" tem %d caractere\n", cidade, tam);

    return 0;
}
