#include <stdio.h>

void imprime(char *s)
{
    int i;
    for (i = 0; s[i] != '\0'; i++)
        printf("%c", s[i]);
    printf("\n");
}
int comprimento(char *s);
int main(void)
{
    int tam;
    char cidade[] = "Rio de Janeiro";
    tam = comprimento(cidade);
    printf("A string \"%s\" tem %d caracteres\n", cidade, tam);
    return 0;
}
int comprimento(char *s)
{
    int i;
    int n = 0;
    for (i = 0; s[i] != '\0'; i++)
        n++;
    return n;
}
