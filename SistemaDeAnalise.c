#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Quantidades solicitadas
const int TAMANHOS[] = {100, 1000, 10000, 100000};
const int NUM_ARQUIVOS = 4;

// ============================================================
// 1. MÓDULO DE ARQUIVOS E UTILITÁRIOS
// ============================================================

// Retorna o tamanho do arquivo em Bytes
long obter_tamanho_arquivo(char *nome) {
    FILE *f = fopen(nome, "rb");
    if (!f) return -1;
    fseek(f, 0, SEEK_END);
    long tam = ftell(f);
    fclose(f);
    return tam;
}

// Gera arquivos com números aleatórios
void gerar_arquivos_aleatorios() {
    printf("\n>>> GERANDO ARQUIVOS DE DADOS...\n");
    srand((unsigned)time(NULL));

    for (int i = 0; i < NUM_ARQUIVOS; i++) {
        char nome[50];
        sprintf(nome, "dados_%d.txt", TAMANHOS[i]);
        
        FILE *f = fopen(nome, "w");
        if (f) {
            for (int j = 0; j < TAMANHOS[i]; j++) {
                fprintf(f, "%d\n", rand() % 1000000); // Números 0-999999
            }
            long bytes = ftell(f);
            fclose(f);
            printf("[OK] '%s' gerado com sucesso. (Tamanho: %ld bytes)\n", nome, bytes);
        } else {
            printf("[ERRO] Falha ao criar '%s'.\n", nome);
        }
    }
}

// Lê o arquivo para um vetor na memória
int* carregar_arquivo(char *nome, int tam) {
    FILE *f = fopen(nome, "r");
    if (!f) return NULL;

    int *vetor = (int*) malloc(tam * sizeof(int));
    if (vetor) {
        for (int i = 0; i < tam; i++) {
            fscanf(f, "%d", &vetor[i]);
        }
    }
    fclose(f);
    return vetor;
}

// Salva vetor ordenado em arquivo
void salvar_ordenado(char *nome_origem, char *algoritmo, int *vetor, int tam) {
    char nome_final[100];
    sprintf(nome_final, "ord_%s_%s", algoritmo, nome_origem);

    FILE *f = fopen(nome_final, "w");
    if (f) {
        for (int i = 0; i < tam; i++) {
            fprintf(f, "%d\n", vetor[i]);
        }
        long bytes = ftell(f);
        fclose(f);
        printf("    -> Salvo em '%s' (%ld bytes)\n", nome_final, bytes);
    }
}

// Copia vetores para não ordenar o original (preservar para outros testes)
void copiar_vetor(int *dest, int *orig, int tam) {
    for(int i=0; i<tam; i++) dest[i] = orig[i];
}

// ============================================================
// 2. MÓDULO DE ORDENAÇÃO
// ============================================================

// Selection Sort (O(N^2))
void selection_sort(int *vet, int tam) {
    for (int i = 0; i < tam - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < tam; j++) {
            if (vet[j] < vet[menor]) menor = j;
        }
        int temp = vet[i];
        vet[i] = vet[menor];
        vet[menor] = temp;
    }
}

// Função de comparação para o Quick Sort
int comparar_ints(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Executa e mede o tempo
void benchmark_ordenacao(char *arquivo, int tam) {
    printf("\nAnalise do arquivo: %s (%d numeros)\n", arquivo, tam);
    
    int *dados_originais = carregar_arquivo(arquivo, tam);
    if (!dados_originais) {
        printf("Erro ao ler arquivo.\n");
        return;
    }

    int *vetor_teste = (int*) malloc(tam * sizeof(int));
    clock_t inicio, fim;
    double tempo;

    // --- TESTE 1: SELECTION SORT ---
    // AVISO: Limitamos Selection Sort para 100.000 pois demora MUITO. 
    // Em PCs normais, 100k no selection sort pode levar minutos.
    if (tam <= 100000) { 
        copiar_vetor(vetor_teste, dados_originais, tam);
        
        printf("  > Executando Selection Sort... ");
        fflush(stdout); // Força print antes de travar processando
        
        inicio = clock();
        selection_sort(vetor_teste, tam);
        fim = clock();
        
        tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("Tempo: %.6f seg.\n", tempo);
        salvar_ordenado(arquivo, "selection", vetor_teste, tam);
    } else {
        printf("  > Selection Sort pulado (muito lento para esse tamanho).\n");
    }

    // --- TESTE 2: QUICK SORT ---
    copiar_vetor(vetor_teste, dados_originais, tam);
    
    printf("  > Executando Quick Sort...     ");
    fflush(stdout);

    inicio = clock();
    qsort(vetor_teste, tam, sizeof(int), comparar_ints);
    fim = clock();

    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo: %.6f seg.\n", tempo);
    salvar_ordenado(arquivo, "quick", vetor_teste, tam);

    free(dados_originais);
    free(vetor_teste);
}

// ============================================================
// 3. MÓDULO DE BUSCA
// ============================================================

// Busca Sequencial (O(N)) - Funciona em qualquer lista
int busca_sequencial(int *vet, int tam, int chave, int *comparacoes) {
    for (int i = 0; i < tam; i++) {
        (*comparacoes)++;
        if (vet[i] == chave) return i;
    }
    return -1;
}

// Busca Binária (O(log N)) - SÓ funciona em lista ordenada
int busca_binaria(int *vet, int tam, int chave, int *comparacoes) {
    int inicio = 0, fim = tam - 1;
    while (inicio <= fim) {
        (*comparacoes)++;
        int meio = (inicio + fim) / 2;
        if (vet[meio] == chave) return meio;
        if (vet[meio] < chave) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

void menu_busca() {
    // Para buscar, vamos usar o arquivo de 10.000 como exemplo (equilibrado)
    int TAM = 10000;
    char arq_bagun[] = "dados_10000.txt";
    char arq_orden[] = "ord_quick_dados_10000.txt";

    // Verifica se os arquivos existem
    FILE *teste = fopen(arq_orden, "r");
    if (!teste) {
        printf("\n[AVISO] Arquivos ordenados nao encontrados.\n");
        printf("Execute a opcao 2 (Processar Ordenacao) primeiro!\n");
        return;
    }
    fclose(teste);

    int *vet_bagun = carregar_arquivo(arq_bagun, TAM);
    int *vet_orden = carregar_arquivo(arq_orden, TAM);
    
    int valor, comps;
    clock_t inicio, fim;

    printf("\n--- MODULO DE BUSCA (Base de dados: 10.000 numeros) ---\n");
    printf("Digite um valor para buscar: ");
    scanf("%d", &valor);

    // 1. Busca Sequencial (Vetor Desordenado)
    comps = 0;
    inicio = clock();
    int idx1 = busca_sequencial(vet_bagun, TAM, valor, &comps);
    fim = clock();
    double t1 = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("\n[Busca Sequencial - Lista Aleatoria]\n");
    if(idx1 != -1) printf("Encontrado no indice: %d\n", idx1);
    else printf("Nao encontrado.\n");
    printf("Comparacoes: %d | Tempo: %.6f s\n", comps, t1);

    // 2. Busca Binária (Vetor Ordenado)
    comps = 0;
    inicio = clock();
    int idx2 = busca_binaria(vet_orden, TAM, valor, &comps);
    fim = clock();
    double t2 = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("\n[Busca Binaria - Lista Ordenada]\n");
    if(idx2 != -1) printf("Encontrado no indice: %d\n", idx2);
    else printf("Nao encontrado.\n");
    printf("Comparacoes: %d | Tempo: %.6f s\n", comps, t2);

    free(vet_bagun);
    free(vet_orden);
}

// ============================================================
// 4. MENU PRINCIPAL
// ============================================================

int main() {
    int opcao;

    do {
        printf("\n=========================================\n");
        printf("   SISTEMA DE ANALISE DE ALGORITMOS\n");
        printf("=========================================\n");
        printf("1. Gerar Arquivos Aleatorios\n");
        printf("2. Ler, Ordenar e Benchmark (Selection vs Quick)\n");
        printf("3. Modulo de Busca (Sequencial vs Binaria)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                gerar_arquivos_aleatorios();
                break;
            case 2:
                // Verifica se o primeiro arquivo existe antes de tentar
                if (fopen("dados_100.txt", "r") == NULL) {
                    printf("\n[ERRO] Gere os arquivos primeiro (Opcao 1)!\n");
                } else {
                    for (int i = 0; i < NUM_ARQUIVOS; i++) {
                        char nome[50];
                        sprintf(nome, "dados_%d.txt", TAMANHOS[i]);
                        benchmark_ordenacao(nome, TAMANHOS[i]);
                    }
                }
                break;
            case 3:
                menu_busca();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}