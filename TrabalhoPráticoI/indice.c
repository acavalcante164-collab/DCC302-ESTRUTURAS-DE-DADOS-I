#include "indice.h"

// Função auxiliar interna
void adicionar_ocorrencia(Palavra* p, int linha) {
    Ocorrencia* atual = p->lista_ocorrencias;
    Ocorrencia* ant = NULL;

    while (atual != NULL) {
        if (atual->num_linha == linha) {
            atual->qtd++; // [cite: 17]
            return;
        }
        ant = atual;
        atual = atual->prox;
    }

    Ocorrencia* nova = (Ocorrencia*) malloc(sizeof(Ocorrencia));
    nova->num_linha = linha;
    nova->qtd = 1;
    nova->prox = NULL;

    if (ant == NULL) p->lista_ocorrencias = nova;
    else ant->prox = nova;
}

Palavra* inserir_palavra(Palavra* dic, char* termo, int linha) {
    Palavra* atual = dic;
    Palavra* ant = NULL;

    // Busca posição alfabética
    while (atual != NULL && strcmp(atual->termo, termo) < 0) {
        ant = atual;
        atual = atual->prox;
    }

    // Palavra existe
    if (atual != NULL && strcmp(atual->termo, termo) == 0) {
        adicionar_ocorrencia(atual, linha);
        return dic;
    }

    // Palavra nova
    Palavra* nova = (Palavra*) malloc(sizeof(Palavra));
    nova->termo = (char*) malloc(strlen(termo) + 1);
    strcpy(nova->termo, termo);
    nova->lista_ocorrencias = NULL;
    nova->prox = atual;

    adicionar_ocorrencia(nova, linha);

    if (ant == NULL) return nova;
    ant->prox = nova;
    return dic;
}

Palavra* criar_dicionario() {
    return NULL;
}

Palavra* processar_arquivo(Palavra* dic, const char* nome_arquivo) {
    FILE* arq = fopen(nome_arquivo, "r");
    if (!arq) {
        printf("Erro ao abrir arquivo.\n");
        return dic;
    }

    char linha_texto[2048];
    int num_linha = 1;

    while (fgets(linha_texto, sizeof(linha_texto), arq)) {
        // Tokenização
        char* token = strtok(linha_texto, " \t\n\r.,;:!?\"()[]{}"); 
        while (token != NULL) {
            dic = inserir_palavra(dic, token, num_linha);
            token = strtok(NULL, " \t\n\r.,;:!?\"()[]{}");
        }
        num_linha++;
    }
    fclose(arq);
    return dic;
}

void imprimir_indice(Palavra* dic) {
    Palavra* p = dic;
    while (p != NULL) {
        printf("%s: ", p->termo);
        Ocorrencia* o = p->lista_ocorrencias;
        while (o != NULL) {
            printf("(%d,%d)", o->num_linha, o->qtd);
            if (o->prox) printf(", ");
            o = o->prox;
        }
        printf("\n");
        p = p->prox;
    }
}

void buscar_palavra(Palavra* dic, char* termo) {
    Palavra* p = dic;
    while (p != NULL) {
        if (strcmp(p->termo, termo) == 0) {
            printf("Encontrada: %s\n", p->termo);
            Ocorrencia* o = p->lista_ocorrencias;
            while (o != NULL) {
                printf("  Linha %d: %d vezes\n", o->num_linha, o->qtd);
                o = o->prox;
            }
            return;
        }
        p = p->prox;
    }
    printf("Palavra '%s' nao encontrada.\n", termo);
}

Palavra* remover_palavra(Palavra* dic, char* termo) {
    Palavra* atual = dic;
    Palavra* ant = NULL;

    while (atual != NULL && strcmp(atual->termo, termo) != 0) {
        ant = atual;
        atual = atual->prox;
    }

    if (atual == NULL) return dic;

    if (ant == NULL) dic = atual->prox;
    else ant->prox = atual->prox;

    // Liberação de memória das ocorrências
    Ocorrencia* o = atual->lista_ocorrencias;
    while (o != NULL) {
        Ocorrencia* temp = o;
        o = o->prox;
        free(temp);
    }
    free(atual->termo);
    free(atual);
    
    printf("Removido com sucesso.\n");
    return dic;
}

void exibir_mais_frequente(Palavra* dic) {
    Palavra* p = dic;
    char* termo_max = NULL;
    int max_freq = -1;

    while (p != NULL) {
        int soma = 0;
        Ocorrencia* o = p->lista_ocorrencias;
        while (o != NULL) {
            soma += o->qtd;
            o = o->prox;
        }
        if (soma > max_freq) {
            max_freq = soma;
            termo_max = p->termo;
        }
        p = p->prox;
    }

    if (termo_max) printf("Mais frequente: '%s' (%d ocorrencias)\n", termo_max, max_freq);
}

void liberar_memoria(Palavra* dic) {
    while (dic != NULL) {
        Ocorrencia* o = dic->lista_ocorrencias;
        while (o != NULL) {
            Ocorrencia* to = o;
            o = o->prox;
            free(to);
        }
        Palavra* tp = dic;
        dic = dic->prox;
        free(tp->termo);
        free(tp);
    }
}