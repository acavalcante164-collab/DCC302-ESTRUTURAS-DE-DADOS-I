#include <stdio.h>
#include "indice.h"

int main() {
    Palavra* dicionario = criar_dicionario();
    char nome_arquivo[100];
    int opcao;
    char termo[100];

    printf("Nome do arquivo (ex: entrada.txt): ");
    scanf("%s", nome_arquivo);

    dicionario = processar_arquivo(dicionario, nome_arquivo);

    do {
        printf("\n1. Imprimir | 2. Buscar | 3. Remover | 4. Frequencia | 0. Sair\nOpcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: imprimir_indice(dicionario); break;
            case 2: 
                printf("Termo: "); scanf("%s", termo);
                buscar_palavra(dicionario, termo); break;
            case 3:
                printf("Remover: "); scanf("%s", termo);
                dicionario = remover_palavra(dicionario, termo); break;
            case 4: exibir_mais_frequente(dicionario); break;
            case 0: liberar_memoria(dicionario); break;
            default: printf("Invalido.\n");
        }
    } while (opcao != 0);

    return 0;
}