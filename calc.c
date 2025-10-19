#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"

struct calc {
    char f[21]; /* formato para impressão */
    Pilha *p;   /* pilha de operandos */
};

Calc* calc_cria(char* formato) {
    Calc* c = (Calc*) malloc(sizeof(Calc));
    strcpy(c->f, formato);
    c->p = pilha_cria(); // Corrigido
    return c;
}

void calc_operando(Calc* c, float v) {
    pilha_push(c->p, v);
    printf("Operando empilhado: ");
    printf(c->f, v);
}

void calc_operador(Calc* c, char op) {
    float v1, v2, v;

    // A ordem é crucial: o primeiro pop é o segundo operando.
    if (pilha_vazia(c->p)) v2 = 0.0;
    else v2 = pilha_pop(c->p);

    if (pilha_vazia(c->p)) v1 = 0.0;
    else v1 = pilha_pop(c->p);

    switch (op) {
        case '+': v = v1 + v2; break;
        case '-': v = v1 - v2; break;
        case '*': v = v1 * v2; break;
        case '/': 
            if (v2 == 0) {
                printf("Erro: Divisao por zero!\n");
                exit(1);
            }
            v = v1 / v2; 
            break;
    }

    pilha_push(c->p, v);
    printf("Resultado parcial: ");
    printf(c->f, v);
}

float calc_resultado(Calc *c) {
    if (pilha_vazia(c->p)) {
        return 0.0;
    }
    return pilha_pop(c->p);
}

void calc_libera(Calc* c) {
    pilha_libera(c->p);
    free(c);
}