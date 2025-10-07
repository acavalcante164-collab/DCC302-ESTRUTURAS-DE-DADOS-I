#include <stdio.h>
int comprimento (char* s)
{
 int i;
 int n = 0; /* contador */
 for (i=0; s[i] != '\0'; i++)
 n++;
 return n;
}

void copia (char* dest, char* orig)
{
 int i;
 for (i=0; orig[i] != '\0'; i++)
 dest[i] = orig[i];
 /* fecha a cadeia copiada */
 dest[i] = '\0';
} 

