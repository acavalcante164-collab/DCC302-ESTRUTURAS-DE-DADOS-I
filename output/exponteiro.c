#include <stdio.h>
#include <stdlib.h>

void troca1(int* a, int * b) {
    int *aux = *a;
    *a = *b;
    *b = *aux

}