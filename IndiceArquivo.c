#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PALAVRAS 1000 // Aumentamos o limite do dicionário
#define TAM_PALAVRA 50
#define NOME_ARQUIVO "frases.txt"

// --- ESTRUTURAS DE DADOS (Iguais ao anterior) ---

typedef struct No {
    int doc_id;
    struct No *prox;
} No;

typedef struct {
    char palavra[TAM_PALAVRA];
    No *inicio_lista;
} EntradaIndice;

EntradaIndice indice[MAX_PALAVRAS];
int total_palavras = 0;

// --- FUNÇÕES AUXILIARES ---

// Adiciona ID na lista (evita duplicatas do mesmo ID na mesma palavra)
void adicionar_ocorrencia(EntradaIndice *entrada, int doc_id) {
    No *temp = entrada->inicio_lista;
    while (temp != NULL) {
        if (temp->doc_id == doc_id) return; // Já indexou esta palavra neste documento
        temp = temp->prox;
    }
    No *novo = (No*) malloc(sizeof(No));
    novo->doc_id = doc_id;
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
        // isalnum mantém letras e números. Ignora pontuação.
        if (isalnum(src[i])) {
            dst[j++] = tolower(src[i]);
        }
    }
    dst[j] = '\0';
}

// --- CORE: PROCESSAMENTO DE TEXTO ---

// Recebe uma linha inteira e o número dessa linha (ID)
void processar_linha(int doc_id, char *linha) {
    // Delimitadores: Espaço, Quebra de linha, Tabulação, Pontuação comum
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

// --- FUNÇÃO NOVA: LEITURA DE ARQUIVO ---
void carregar_base_de_dados(char *nome_arq) {
    FILE *file = fopen(nome_arq, "r");
    char buffer[1024]; // Buffer grande para ler a linha
    int linha_atual = 1; // Este será o nosso Doc ID

    if (file) {
        printf("--- Indexando arquivo '%s' ---\n", nome_arq);
        
        // Lê o arquivo linha por linha
        while (fgets(buffer, 1024, file) != NULL) {
            // Remove o \n final para ficar bonito no print (opcional)
            buffer[strcspn(buffer, "\n")] = 0;
            
            printf("Lendo Doc ID %d: \"%s\"\n", linha_atual, buffer);
            
            // Manda indexar esta linha específica
            processar_linha(linha_atual, buffer);
            
            linha_atual++;
        }
        fclose(file);
        printf("--- Indexacao Concluida! ---\n");
    } else {
        printf("Erro ao abrir o arquivo.\n");
    }
}

// Função para criar um arquivo de teste automaticamente
void criar_arquivo_teste() {
    FILE *f = fopen(NOME_ARQUIVO, "w");
    if (f) {
        fprintf(f, "O rato roeu a roupa do rei de Roma.\n");
        fprintf(f, "O rei de Roma ficou com raiva.\n");
        fprintf(f, "A roupa do rei era de veludo.\n");
        fprintf(f, "O rato correu para o buraco.\n");
        fclose(f);
        printf("Arquivo de teste '%s' criado.\n", NOME_ARQUIVO);
    }
}

// Função de Busca interativa
void menu_busca() {
    char termo[TAM_PALAVRA];
    while (1) {
        printf("\nDigite uma palavra para buscar (ou 'sair'): ");
        // scanf é seguro aqui pois queremos apenas uma palavra única
        scanf("%s", termo);
        
        if (strcmp(termo, "sair") == 0) break;
        
        char termo_limpo[TAM_PALAVRA];
        normalizar(termo_limpo, termo);

        int idx = buscar_indice_palavra(termo_limpo);
        if (idx != -1) {
            printf("A palavra '%s' aparece nas linhas: ", termo_limpo);
            No *atual = indice[idx].inicio_lista;
            while (atual != NULL) {
                printf("[%d] ", atual->doc_id);
                atual = atual->prox;
            }
            printf("\n");
        } else {
            printf("Palavra nao encontrada no indice.\n");
        }
    }
}

int main() {
    // 1. Desativei a criação automática para não apagar meu arquivo!
    // criar_arquivo_teste(); 

    // 2. Agora ele vai ler o arquivo que EU editei
    carregar_base_de_dados(NOME_ARQUIVO);

    // 3. Permite ao usuário buscar
    menu_busca();

    return 0;
}