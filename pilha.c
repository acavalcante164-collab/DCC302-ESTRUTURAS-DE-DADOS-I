#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

#define MAX_SIZE 50

struct pilha {
    int topo;
    float vet[MAX_SIZE];
};

Pilha* pilha_cria(void) {
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    if (p != NULL) {
        p->topo = 0;
    }
    return p;
}

void pilha_push(Pilha* p, float v) {
    if (p->topo < MAX_SIZE) {
        p->vet[p->topo++] = v;
    } else {
        printf("Erro: Pilha cheia!\n");
        exit(1); // Termina o programa em caso de erro grave
    }
}

float pilha_pop(Pilha* p) {
    if (!pilha_vazia(p)) {
        return p->vet[--p->topo];
    } else {
        printf("Erro: Pilha vazia!\n");
        return 0.0; // Retorno de segurança
    }
}

int pilha_vazia(Pilha* p) {
    return (p->topo == 0);
}

void pilha_libera(Pilha* p) {
    free(p);
}