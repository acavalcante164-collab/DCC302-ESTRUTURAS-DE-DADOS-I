#include <stdlib.h> /* malloc, free, exit */
#include <stdio.h> /* printf */
#include <math.h> /* sqrt */
#include "ponto.h"

struct ponto {
 float x;
 float y;
};

Ponto* cria (float x, float y) {
 Ponto* p = (Ponto*) malloc(sizeof(Ponto));
 if (p == NULL) {
 printf("Memória insuficiente!\n");
 exit(1);
 }
 p->x = x;
 p->y = y;
 return p;
}
void libera (Ponto* p) {
 free(p);
}
void acessa (Ponto* p, float* x, float* y) {
 *x = p->x;
 *y = p->y;
}
void atribui (Ponto* p, float x, float y) {
 p->x = x;
 p->y = y;
}
