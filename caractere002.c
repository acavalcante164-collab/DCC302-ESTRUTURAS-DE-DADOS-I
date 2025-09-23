#include <stdio.h>
#include <stdlib.h>



void copia (char* dest, char* orig){
    int i;
    for(i = 0; orig[i] != '0'; i++)
        dest[i] = orig[i];
    /*FECHA A CADEIA COPIADA*/
    dest[i] = '\0';
}

/*
Cópia de cadeia de caracteres.
Vamos agora considerar a implementação de uma função para copiar os elementos de uma
cadeia de caracteres para outra. Assumimos que a cadeia que receberá a cópia tem espaço
suficiente para que a operação seja realizada. O protótipo desta função pode ser dado por:
*/