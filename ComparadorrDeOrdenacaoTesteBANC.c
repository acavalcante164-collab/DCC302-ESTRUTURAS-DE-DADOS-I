#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- ALGORITMO 1: SELECTION SORT (LENTO: O(N^2)) ---
void selection_sort(int vetor[], int tam) {
    for (int i = 0; i < tam - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < tam; j++) {
            if (vetor[j] < vetor[menor]) {
                menor = j;
            }
        }
        int temp = vetor[i];
        vetor[i] = vetor[menor];
        vetor[menor] = temp;
    }
}

// --- FUNÇÃO AUXILIAR PARA O QUICK SORT (NATIVO DO C) ---
int comparar_ints(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// --- UTILITÁRIOS ---

// Carrega o arquivo para a memória
int* carregar_arquivo(char *nome_arquivo, int tamanho) {
    FILE *f = fopen(nome_arquivo, "r");
    if (!f) {
        printf("Erro: Nao achei o arquivo '%s'. Gere-o primeiro!\n", nome_arquivo);
        exit(1);
    }

    // Alocação Dinâmica (malloc) é necessária para vetores grandes!
    // Se usar int vet[100000], a memória da stack estoura.
    int *vetor = (int*) malloc(tamanho * sizeof(int));
    
    for (int i = 0; i < tamanho; i++) {
        fscanf(f, "%d", &vetor[i]);
    }
    fclose(f);
    return vetor;
}

// Cria uma cópia do vetor para o teste ser justo
int* copiar_vetor(int *origem, int tamanho) {
    int *destino = (int*) malloc(tamanho * sizeof(int));
    for(int i=0; i<tamanho; i++) {
        destino[i] = origem[i];
    }
    return destino;
}

int main() {
    // Vamos testar com 10.000 ou 100.000 números
    // AVISO: Selection Sort com 100.000 pode demorar minutos!
    int QTD = 100000; 
    char *arquivo = "numeros_100000.txt"; 

    printf("--- CARREGANDO %d NUMEROS ---\n", QTD);
    int *dados_originais = carregar_arquivo(arquivo, QTD);
    
    // Preparando as cópias para a batalha
    int *vetor1 = copiar_vetor(dados_originais, QTD);
    int *vetor2 = copiar_vetor(dados_originais, QTD);

    clock_t inicio, fim;
    double tempo_cpu;

    // ---------------------------------------------------------
    // ROUND 1: SELECTION SORT (Sua implementação baseada em busca)
    // ---------------------------------------------------------
    printf("\nIniciando Selection Sort (Lento)... aguarde...\n");
    
    inicio = clock(); // LIGA O CRONÔMETRO
    selection_sort(vetor1, QTD);
    fim = clock();    // PARA O CRONÔMETRO

    tempo_cpu = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
    printf(">> Tempo Selection Sort: %f segundos\n", tempo_cpu);


    // ---------------------------------------------------------
    // ROUND 2: QUICK SORT (Algoritmo Otimizado)
    // ---------------------------------------------------------
    printf("\nIniciando Quick Sort (Rapido)...\n");

    inicio = clock(); // LIGA O CRONÔMETRO
    // qsort é uma função nativa do C que implementa QuickSort
    qsort(vetor2, QTD, sizeof(int), comparar_ints);
    fim = clock();    // PARA O CRONÔMETRO

    tempo_cpu = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
    printf(">> Tempo Quick Sort:     %f segundos\n", tempo_cpu);

    // Limpeza de memória
    free(dados_originais);
    free(vetor1);
    free(vetor2);

    return 0;
}