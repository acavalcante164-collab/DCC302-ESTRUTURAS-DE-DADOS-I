#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Quantidades solicitadas no exercício
const int TAMANHOS[] = {100, 1000, 10000, 100000};
const int NUM_ARQUIVOS = 4;

// ============================================================
// 1. MÓDULO DE ARQUIVOS E UTILITÁRIOS
// ============================================================

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
            fclose(f);
            // AJUSTE AQUI: Mostra a quantidade exata solicitada
            printf("[OK] Arquivo: '%s' | Status: Gerado com Sucesso | Tamanho: %d numeros\n", nome, TAMANHOS[i]);
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
        fclose(f);
        // Feedback de salvamento
        // printf("    -> Salvo em '%s'\n", nome_final);
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
    printf("\n-----------------------------------------------------\n");
    printf("RELATORIO DE DESEMPENHO\n");
    printf("Arquivo Lido: %s\n", arquivo);
    printf("Tamanho do Arquivo: %d numeros\n", tam);
    printf("-----------------------------------------------------\n");
    
    int *dados_originais = carregar_arquivo(arquivo, tam);
    if (!dados_originais) {
        printf("Erro: Arquivo nao encontrado ou corrompido.\n");
        return;
    }

    int *vetor_teste = (int*) malloc(tam * sizeof(int));
    clock_t inicio, fim;
    double tempo;

    // --- TESTE 1: SELECTION SORT ---
    // AVISO: Limitamos Selection Sort para 100.000 pois demora MUITO. 
    if (tam <= 100000) { 
        copiar_vetor(vetor_teste, dados_originais, tam);
        
        printf("1. Algoritmo: Selection Sort\n");
        printf("   Status: Processando...\n");
        
        inicio = clock();
        selection_sort(vetor_teste, tam);
        fim = clock();
        
        tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("   Tempo de Execucao: %.6f segundos\n", tempo);
        salvar_ordenado(arquivo, "selection", vetor_teste, tam);
    } else {
        printf("1. Algoritmo: Selection Sort\n");
        printf("   Status: PULADO (Ineficiente para %d numeros)\n", tam);
    }

    // --- TESTE 2: QUICK SORT ---
    copiar_vetor(vetor_teste, dados_originais, tam);
    
    printf("\n2. Algoritmo: Quick Sort\n");
    printf("   Status: Processando...\n");

    inicio = clock();
    qsort(vetor_teste, tam, sizeof(int), comparar_ints);
    fim = clock();

    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("   Tempo de Execucao: %.6f segundos\n", tempo);
    salvar_ordenado(arquivo, "quick", vetor_teste, tam);

    free(dados_originais);
    free(vetor_teste);
}

// ============================================================
// 3. MÓDULO DE BUSCA
// ============================================================

// Busca Sequencial (O(N))
int busca_sequencial(int *vet, int tam, int chave, int *comparacoes) {
    for (int i = 0; i < tam; i++) {
        (*comparacoes)++;
        if (vet[i] == chave) return i;
    }
    return -1;
}

// Busca Binária (O(log N))
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
    // Exemplo com 10.000 números
    int TAM = 10000;
    char arq_bagun[] = "dados_10000.txt";
    char arq_orden[] = "ord_quick_dados_10000.txt";

    FILE *teste = fopen(arq_orden, "r");
    if (!teste) {
        printf("\n[AVISO] Arquivos ordenados nao encontrados.\n");
        printf("Por favor, execute a opcao 2 (Processar Ordenacao) primeiro.\n");
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

    // 1. Busca Sequencial
    comps = 0;
    inicio = clock();
    int idx1 = busca_sequencial(vet_bagun, TAM, valor, &comps);
    fim = clock();
    double t1 = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("\n[Busca Sequencial - Lista Aleatoria]\n");
    if(idx1 != -1) printf("Status: Encontrado (Indice %d)\n", idx1);
    else printf("Status: Nao encontrado\n");
    printf("Comparacoes: %d | Tempo: %.6f s\n", comps, t1);

    // 2. Busca Binária
    comps = 0;
    inicio = clock();
    int idx2 = busca_binaria(vet_orden, TAM, valor, &comps);
    fim = clock();
    double t2 = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("\n[Busca Binaria - Lista Ordenada]\n");
    if(idx2 != -1) printf("Status: Encontrado (Indice %d)\n", idx2);
    else printf("Status: Nao encontrado\n");
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
        printf("1. Gerar Arquivos (100, 1.000, 10.000, 100.000)\n");
        printf("2. Ler, Ordenar e Mostrar Benchmark\n");
        printf("3. Modulo de Busca (Sequencial vs Binaria)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                gerar_arquivos_aleatorios();
                break;
            case 2:
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