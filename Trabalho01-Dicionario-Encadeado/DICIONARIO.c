#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ============================================================
// 1. DEFINIÇÃO DAS ESTRUTURAS (TADs)
// ============================================================

// Nó da Lista de Ocorrências (Linhas)
typedef struct NoOcorrencia {
    int linha;
    int qtd;
    struct NoOcorrencia *prox;
} NoOcorrencia;

// Nó da Lista do Dicionário (Palavras)
typedef struct NoPalavra {
    char *termo;                // String alocada dinamicamente
    NoOcorrencia *ocorrencias;  // Cabeça da lista de ocorrências
    struct NoPalavra *prox;     // Próxima palavra (ordem alfabética)
} NoPalavra;

// Estrutura Principal do Índice
typedef struct {
    NoPalavra *inicio;
} IndiceInvertido;

// ============================================================
// 2. FUNÇÕES AUXILIARES E DE MANIPULAÇÃO
// ============================================================

// Cria e inicializa o índice
IndiceInvertido* criar_indice() {
    IndiceInvertido *idx = (IndiceInvertido*) malloc(sizeof(IndiceInvertido));
    if (idx != NULL) idx->inicio = NULL;
    return idx;
}

// Normaliza string (minúsculas e sem pontuação nas pontas)
void normalizar_string(char *dest, const char *src) {
    int j = 0;
    for (int i = 0; src[i] != '\0'; i++) {
        if (isalnum(src[i])) { // Apenas letras e números
            dest[j++] = tolower(src[i]);
        }
    }
    dest[j] = '\0';
}

// Adiciona uma ocorrência (linha) a uma palavra existente
void adicionar_ocorrencia(NoPalavra *palavra, int linha) {
    NoOcorrencia *atual = palavra->ocorrencias;
    
    // Procura se a linha já existe na lista desta palavra
    while (atual != NULL) {
        if (atual->linha == linha) {
            atual->qtd++; // Já existe nesta linha, incrementa contador
            return;
        }
        if (atual->prox == NULL) break; // Para no último
        atual = atual->prox;
    }

    // Se não encontrou a linha, cria novo nó de ocorrência
    NoOcorrencia *novo = (NoOcorrencia*) malloc(sizeof(NoOcorrencia));
    novo->linha = linha;
    novo->qtd = 1;
    novo->prox = NULL;

    if (palavra->ocorrencias == NULL) {
        palavra->ocorrencias = novo;
    } else {
        atual->prox = novo; // Adiciona no final da lista de ocorrências
    }
}

// INSERÇÃO ORDENADA NO DICIONÁRIO
void processar_palavra(IndiceInvertido *idx, char *termo_bruto, int linha) {
    char termo[100];
    normalizar_string(termo, termo_bruto);
    if (strlen(termo) == 0) return;

    NoPalavra *atual = idx->inicio;
    NoPalavra *anterior = NULL;

    // 1. Procura a posição correta (Ordem Alfabética)
    while (atual != NULL && strcmp(atual->termo, termo) < 0) {
        anterior = atual;
        atual = atual->prox;
    }

    // 2. Cenário A: Palavra já existe (strcmp retornou 0)
    if (atual != NULL && strcmp(atual->termo, termo) == 0) {
        adicionar_ocorrencia(atual, linha);
    } 
    // 3. Cenário B: Palavra nova (insere entre 'anterior' e 'atual')
    else {
        NoPalavra *nova = (NoPalavra*) malloc(sizeof(NoPalavra));
        // Aloca memória estrita para a string
        nova->termo = strdup(termo); 
        nova->ocorrencias = NULL;
        nova->prox = atual; // Aponta para o próximo (que é maior alfabeticamente)

        adicionar_ocorrencia(nova, linha); // Adiciona a primeira ocorrência

        if (anterior == NULL) {
            idx->inicio = nova; // Insere no início da lista
        } else {
            anterior->prox = nova; // Insere no meio ou fim
        }
    }
}

// ============================================================
// 3. REQUISITOS
// ============================================================

// Ler arquivo e popular o índice
void carregar_arquivo(IndiceInvertido *idx, char *nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "r");
    if (!f) {
        printf("Erro ao abrir arquivo '%s'.\n", nome_arquivo);
        return;
    }

    char buffer[1024];
    int num_linha = 1;

    while (fgets(buffer, 1024, f) != NULL) {
        // Remove \n final
        buffer[strcspn(buffer, "\n")] = 0;
        
        char *token = strtok(buffer, " \t,.;:!?\"()[]{}");
        while (token != NULL) {
            processar_palavra(idx, token, num_linha);
            token = strtok(NULL, " \t,.;:!?\"()[]{}");
        }
        num_linha++;
    }
    fclose(f);
    printf("Arquivo indexado com sucesso!\n");
}

// Buscar palavra
void buscar_palavra(IndiceInvertido *idx) {
    char busca[100], termo[100];
    printf("Digite a palavra para buscar: ");
    scanf("%s", busca);
    normalizar_string(termo, busca);

    NoPalavra *atual = idx->inicio;
    while (atual != NULL) {
        if (strcmp(atual->termo, termo) == 0) {
            printf("Palavra: '%s' encontrada:\n", termo);
            NoOcorrencia *oc = atual->ocorrencias;
            while (oc != NULL) {
                printf(" -> Linha %d (%d vezes)\n", oc->linha, oc->qtd);
                oc = oc->prox;
            }
            return;
        }
        atual = atual->prox;
    }
    printf("Palavra '%s' nao encontrada no indice.\n", termo);
}

// Excluir palavra e liberar memória associada
void excluir_palavra(IndiceInvertido *idx) {
    char busca[100], termo[100];
    printf("Digite a palavra para excluir: ");
    scanf("%s", busca);
    normalizar_string(termo, busca);

    NoPalavra *atual = idx->inicio;
    NoPalavra *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->termo, termo) == 0) {
            // Achou! Vamos remover.
            
            // 1. Liberar a lista de ocorrências
            NoOcorrencia *oc = atual->ocorrencias;
            while (oc != NULL) {
                NoOcorrencia *tempOc = oc->prox;
                free(oc);
                oc = tempOc;
            }

            // 2. Arrumar ponteiros do dicionário
            if (anterior == NULL) {
                idx->inicio = atual->prox; // Era o primeiro
            } else {
                anterior->prox = atual->prox; // Era meio ou fim
            }

            // 3. Liberar a palavra e o nó
            free(atual->termo);
            free(atual);
            printf("Palavra '%s' removida com sucesso.\n", termo);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Palavra nao encontrada.\n");
}

// Palavra mais frequente
void exibir_mais_frequente(IndiceInvertido *idx) {
    if (idx->inicio == NULL) {
        printf("Indice vazio.\n");
        return;
    }

    NoPalavra *mais_freq_palavra = NULL;
    int max_total = -1;

    NoPalavra *atual = idx->inicio;
    while (atual != NULL) {
        int total_palavra = 0;
        NoOcorrencia *oc = atual->ocorrencias;
        
        // Soma todas as ocorrências de todas as linhas
        while (oc != NULL) {
            total_palavra += oc->qtd;
            oc = oc->prox;
        }

        if (total_palavra > max_total) {
            max_total = total_palavra;
            mais_freq_palavra = atual;
        }
        atual = atual->prox;
    }

    if (mais_freq_palavra) {
        printf("Palavra mais frequente: '%s' (Total: %d ocorrencias)\n", 
               mais_freq_palavra->termo, max_total);
    }
}

// Imprime todo o dicionário (Debug)
void imprimir_tudo(IndiceInvertido *idx) {
    NoPalavra *p = idx->inicio;
    if (!p) {
        printf("Dicionario Vazio.\n");
        return;
    }
    
    printf("\n--- INDICE INVERTIDO (Dicionario Ordenado) ---\n");
    while (p != NULL) {
        // Formatação para facilitar leitura
        printf("Termo: %-15s -> ", p->termo);
        
        NoOcorrencia *oc = p->ocorrencias;
        while (oc != NULL) {
            // Mostra [Linha: X (Y vezes)]
            printf("[Linha %d: %d vez%s] ", oc->linha, oc->qtd, (oc->qtd > 1 ? "es" : ""));
            oc = oc->prox;
        }
        printf("\n");
        p = p->prox;
    }
    printf("----------------------------------------------\n");
}

// Imprime o arquivo original com números de linha para conferência
void imprimir_arquivo_base(char *nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "r");
    if (!f) return;

    printf("\n=== CONTEUDO DO ARQUIVO '%s' ===\n", nome_arquivo);
    char buffer[1024];
    int linha = 1;
    while (fgets(buffer, 1024, f) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0; 
        printf("Linha %02d: \"%s\"\n", linha++, buffer);
    }
    printf("==========================================\n");
    fclose(f);
}

// ============================================================
// 4. MAIN (MODIFICADO CONFORME PEDIDO)
// ============================================================

int main() {
    IndiceInvertido *meuIndice = criar_indice();
    char arquivo[200];
    int op;

    printf("Digite o nome do arquivo de texto para indexar: ");
    scanf("%s", arquivo);

    carregar_arquivo(meuIndice, arquivo);

    do {
        printf("\n=== MOTOR DE BUSCA (INDICE INVERTIDO) ===\n");
        printf("1. Buscar Palavra\n");
        printf("2. Excluir Palavra\n");
        printf("3. Palavra Mais Frequente\n");
        printf("4. Imprimir Indice Completo (com Texto Original)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1: buscar_palavra(meuIndice); break;
            case 2: excluir_palavra(meuIndice); break;
            case 3: exibir_mais_frequente(meuIndice); break;
            case 4: 
                imprimir_arquivo_base(arquivo);
                imprimir_tudo(meuIndice); 
                break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (op != 0);

    return 0;
}
