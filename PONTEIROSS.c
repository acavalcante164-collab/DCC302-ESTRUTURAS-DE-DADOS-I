#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5341

int main()
{
    int a;
    int *p;

    a = 10;
    p = &a;

    *p = 5;

    printf("%d", a);
}
//Mudou o A atráves de P

