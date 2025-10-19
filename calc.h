#ifndef CALC_H
#define CALC_H

#include "pilha.h" // A calculadora DEPENDE da pilha

typedef struct calc Calc;

Calc* calc_cria(char* formato);
void calc_operando(Calc* c, float v);
void calc_operador(Calc* c, char op);
void calc_libera(Calc* c);
float calc_resultado(Calc *c); // Função nova para pegar o resultado final

#endif // CALC_H