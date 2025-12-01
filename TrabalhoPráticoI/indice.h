#ifndef INDICE_H
#define INDICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para ocorrências (nó da lista encadeada interna)
typedef struct Ocorrencia {
    int num_linha;
    int qtd;
    struct Ocorrencia* prox;
} Ocorrencia;

// Estrutura para palavras (nó da lista encadeada principal)
typedef struct Palavra {
    char* termo;
    Ocorrencia* lista_ocorrencias;
    struct Palavra* prox;
} Palavra;

// Funções Principais
Palavra* criar_dicionario();
Palavra* processar_arquivo(Palavra* dic, const char* nome_arquivo);
void imprimir_indice(Palavra* dic);

// Extras Obrigatórios
void buscar_palavra(Palavra* dic, char* termo);
Palavra* remover_palavra(Palavra* dic, char* termo);
void exibir_mais_frequente(Palavra* dic);

// Utilitários
void liberar_memoria(Palavra* dic);

#endif