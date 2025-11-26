#include <stdio.h>
#include <string.h>
int main (){

    char palavra1[50];
    char palavra2[50];

    printf("Digite a primeira palavra: ");
    scanf("%s", palavra1); //LE ATE O ESPACO

    printf("Digite a segunda palavra: ");
    scanf("%s", palavra2);

    if (strcmp(palavra1, palavra2) == 0) {
        printf("As palavras sao iguais.\n");
    } else {
        printf("As palavras sao diferentes.\n");
    }
    //concatenando
    strcat(palavra1, " "); //ADICIONA UM ESPACO
    strcat(palavra1, palavra2); //ADICIONA A SEGUNDA PALAVRA

    printf("Concatenado: %s\n", palavra1);
    printf("Tamanho total: %d letras\n", (int)strlen(palavra1));

    return 0;


}