#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PALAVRAS 1000
#define TAM_PALAVRA 50
#define NOME_ARQUIVO "frases_repetidas.txt"

// 1. ALTERAÇÃO NA STRUCT: Adicionamos 'frequencia'
typedef struct No {
    int doc_id;
    int frequencia; // Quantas vezes a palavra apareceu nesta linha
    struct No *prox;
} No;

typedef struct {
    char palavra[TAM_PALAVRA];
    No *inicio_lista;
} EntradaIndice;

EntradaIndice indice[MAX_PALAVRAS];
int total_palavras = 0;

// --- FUNÇÕES AUXILIARES ---

// 2. ALTERAÇÃO NA INSERÇÃO: Incrementa se já existe
void adicionar_ocorrencia(EntradaIndice *entrada, int doc_id) {
    No *temp = entrada->inicio_lista;
    
    // Procura se este Doc ID já existe na lista
    while (temp != NULL) {
        if (temp->doc_id == doc_id) {
            // SE JÁ EXISTE: Apenas aumenta o contador e sai
            temp->frequencia++; 
            return; 
        }
        temp = temp->prox;
    }

    // SE NÃO EXISTE: Cria novo nó
    No *novo = (No*) malloc(sizeof(No));
    novo->doc_id = doc_id;
    novo->frequencia = 1; // Começa com 1 ocorrência
    novo->prox = entrada->inicio_lista;
    entrada->inicio_lista = novo;
}

int buscar_indice_palavra(char *palavra) {
    for (int i = 0; i < total_palavras; i++) {
        if (strcmp(indice[i].palavra, palavra) == 0) return i;
    }
    return -1;
}

void normalizar(char *dst, char *src) {
    int j = 0;
    for (int i = 0; src[i] != '\0'; i++) {
        if (isalnum(src[i])) {
            dst[j++] = tolower(src[i]);
        }
    }
    dst[j] = '\0';
}

// --- PROCESSAMENTO ---

void processar_linha(int doc_id, char *linha) {
    char *token = strtok(linha, " \n\t.,;!?");
    
    while (token != NULL) {
        char palavra_limpa[TAM_PALAVRA];
        normalizar(palavra_limpa, token);

        if (strlen(palavra_limpa) > 0) {
            int idx = buscar_indice_palavra(palavra_limpa);

            if (idx != -1) {
                adicionar_ocorrencia(&indice[idx], doc_id);
            } else {
                if (total_palavras < MAX_PALAVRAS) {
                    strcpy(indice[total_palavras].palavra, palavra_limpa);
                    indice[total_palavras].inicio_lista = NULL;
                    adicionar_ocorrencia(&indice[total_palavras], doc_id);
                    total_palavras++;
                }
            }
        }
        token = strtok(NULL, " \n\t.,;!?");
    }
}

void carregar_base_de_dados(char *nome_arq) {
    FILE *file = fopen(nome_arq, "r");
    char buffer[1024]; 
    int linha_atual = 1;

    if (file) {
        printf("--- Indexando arquivo '%s' ---\n", nome_arq);
        while (fgets(buffer, 1024, file) != NULL) {
            buffer[strcspn(buffer, "\n")] = 0;
            printf("Lendo Linha %d: \"%s\"\n", linha_atual, buffer);
            processar_linha(linha_atual, buffer);
            linha_atual++;
        }
        fclose(file);
        printf("--- Indexacao Concluida! ---\n");
    } else {
        printf("Erro ao abrir o arquivo.\n");
    }
}

// Cria um arquivo com palavras repetidas para testar
void criar_arquivo_teste() {
    FILE *f = fopen(NOME_ARQUIVO, "w");
    if (f) {
        fprintf(f, "O rato roeu a roupa do rei de Roma.\n"); // Linha 1 (rato 1x)
        fprintf(f, "rato rato rato.\n");                     // Linha 2 (rato 3x)
        fprintf(f, "O rei gostava do rato e do gato.\n");    // Linha 3 (rato 1x)
        fclose(f);
        printf("Arquivo de teste '%s' criado.\n", NOME_ARQUIVO);
    }
}

void menu_busca() {
    char termo[TAM_PALAVRA];
    while (1) {
        printf("\nDigite uma palavra para buscar (ou 'sair'): ");
        scanf("%s", termo);
        
        if (strcmp(termo, "sair") == 0) break;
        
        char termo_limpo[TAM_PALAVRA];
        normalizar(termo_limpo, termo);

        int idx = buscar_indice_palavra(termo_limpo);
        if (idx != -1) {
            printf("A palavra '%s' aparece em:\n", termo_limpo);
            No *atual = indice[idx].inicio_lista;
            
            // 3. ALTERAÇÃO NA IMPRESSÃO: Mostra a frequência
            while (atual != NULL) {
                printf(" -> Linha %d (%d vezes)\n", atual->doc_id, atual->frequencia);
                atual = atual->prox;
            }
        } else {
            printf("Palavra nao encontrada.\n");
        }
    }
}

int main() {
    criar_arquivo_teste();
    carregar_base_de_dados(NOME_ARQUIVO);
    menu_busca();
    return 0;
}
