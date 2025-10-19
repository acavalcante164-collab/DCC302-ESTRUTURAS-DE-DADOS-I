#ifndef PILHA_H
#define PILHA_H

// Estrutura da Pilha
typedef struct pilha Pilha;

// Interface das funções da Pilha
Pilha* pilha_cria(void);
void pilha_push(Pilha* p, float v); // Empilha um float
float pilha_pop(Pilha* p);          // Desempilha um float
int pilha_vazia(Pilha* p);
void pilha_libera(Pilha* p);

#endif // PILHA_H