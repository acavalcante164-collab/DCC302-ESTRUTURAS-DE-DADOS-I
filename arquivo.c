#include <stdio.h>
#include <stdlib.h>
int main()
{
    char str[20];
    char *result;
    FILE *arq;
    arq = fopen("C:\\Users\\alons\\Dropbox\\Alonso\\UFRR\\DCC205 - PROGRAMAÇÃO ESTRUTURADA\arquivos_em_c\\texto.txt", "r");
    if (arq == NULL)
    {
        printf("Problema\n");
        exit(1);
    }
    result = fgets(str, 13, arq);
    if (result == NULL)
        printf("ERRO\n");
    else
        printf("%s", str);

    fclose(arq);

    return 0;
}