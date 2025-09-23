/*
Concatenação de cadeias de caracteres.
Vamos considerar uma extensão do exemplo anterior e discutir a implementação de uma
função para concatenar uma cadeia de caracteres com outra já existente. Isto é, os
caracteres de uma cadeia são copiados no final da outra cadeia. Assim, se uma cadeia
representa inicialmente a cadeia PUC e concatenarmos a ela a cadeia Rio, teremos como
resultado a cadeia PUCRio. Vamos mais uma vez considerar que existe espaço reservado
que permite fazer a cópia dos caracteres. O protótipo da função pode ser dado por: 
*/
#include <stdio.h>
void concatena(char*dest, char*orig){
    int i = 0; //INDICE USADO NA CADEIA DESTINO, INICIALIZADO COM ZERO
    int j; //INDICE USADO NA CADEIA ORIGEM
    //ACHA O FINAL DA CADEIA DESTINO
    i = 0;
    while (s[i] != '\0')
        i++;
    //COPIA ELEMENTOS DA ORIGEM PARA O FINAL DO DESTINO
    for (j = 0; orig[i] != '\0'; j++){
        dest[i] = orig[j];
        i++;
    }
    //FECHA A CADEIA DO DESTINO
    dest[i] = '\0';

}