#include <stdio.h>

int comprimento (char* str);

void copia (char* dest, char* orig);


int main (void) {

 char str[101], str1[51], str2[51];

 printf("Entre com uma seqüência de caracteres: ");
 scanf(" %50[^\n]", str1);

 printf("Entre com outra seqüência de caracteres: ");
 scanf(" %50[^\n]", str2);

 copia(str, str1);

 printf("Comprimento da concatenação: %d\n",comprimento(str));

 return 0;
}