#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // Para tolower()
#include <locale.h> // Para acentos

#define ARQUIVO_DADOS "agenda.bin"
#define ARQUIVO_CSV "agenda_export.csv" // Para resolver o problema de leitura externa
#define TAM_NOME 50

typedef struct {
    char nome[TAM_NOME];
    int dia, mes, ano;
} Contato;

// =============================================================
// MÓDULO DE UTILITÁRIOS (HELPER FUNCTIONS)
// =============================================================

// 1. SOLUÇÃO DO BUFFER E SCANF
// Lê uma linha inteira, remove o \n e limpa qualquer sujeira.
void ler_texto(char *buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        } else {
            // Se não achou \n, o usuário digitou mais que o permitido.
            // Limpa o resto do buffer.
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

// Lê um número de forma segura (lê texto e converte)
int ler_inteiro() {
    char buffer[20];
    ler_texto(buffer, sizeof(buffer));
    return atoi(buffer); // Retorna 0 se não for número, ou o valor convertido
}

// 2. SOLUÇÃO DA BUSCA (CASE INSENSITIVE)
// Retorna 1 se strings forem iguais (ignorando maiúsculas), 0 caso contrário
int comparar_nomes(const char *a, const char *b) {
    char tempA[TAM_NOME], tempB[TAM_NOME];
    // Copia para temporários para não alterar os originais
    strcpy(tempA, a);
    strcpy(tempB, b);
    
    for(int i = 0; tempA[i]; i++) tempA[i] = tolower(tempA[i]);
    for(int i = 0; tempB[i]; i++) tempB[i] = tolower(tempB[i]);
    
    return strcmp(tempA, tempB) == 0;
}

// 3. SOLUÇÃO DE VALIDAÇÃO DE DATA
int data_valida(int d, int m, int a) {
    if (a < 1900 || a > 2100) return 0;
    if (m < 1 || m > 12) return 0;
    
    int dias_mes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Ano bissexto: div por 4 E (não div por 100 OU div por 400)
    if (m == 2 && (a % 4 == 0 && (a % 100 != 0 || a % 400 == 0))) {
        dias_mes[2] = 29;
    }
    
    if (d < 1 || d > dias_mes[m]) return 0;
    
    return 1;
}

// =============================================================
// FUNÇÕES PRINCIPAIS
// =============================================================

void cadastrar_contato() {
    FILE *file = fopen(ARQUIVO_DADOS, "ab");
    if (!file) {
        perror("Erro ao abrir arquivo"); // Imprime o erro exato do sistema
        return;
    }

    Contato novo;
    printf("\n--- Novo Cadastro ---\n");
    
    // Leitura segura sem scanf
    do {
        printf("Nome (min 3 chars): ");
        ler_texto(novo.nome, TAM_NOME);
    } while (strlen(novo.nome) < 3);

    do {
        printf("Data de Nascimento (Dia Mes Ano separados por espaco): ");
        char buffer[50];
        ler_texto(buffer, 50);
        // Tenta extrair 3 inteiros da string lida
        if (sscanf(buffer, "%d %d %d", &novo.dia, &novo.mes, &novo.ano) == 3) {
            if (data_valida(novo.dia, novo.mes, novo.ano)) {
                break; // Data válida, sai do loop
            } else {
                printf("[ERRO] Data invalida (ex: 30 de fevereiro nao existe).\n");
            }
        } else {
            printf("[ERRO] Formato incorreto. Digite algo como: 15 05 1990\n");
        }
    } while (1);

    // 4. VERIFICAÇÃO DE ESCRITA
    if (fwrite(&novo, sizeof(Contato), 1, file) != 1) {
        printf("[ERRO CRITICO] Falha ao gravar no disco!\n");
    } else {
        printf(">>> Sucesso!\n");
    }
    fclose(file);
}

void alterar_contato() {
    FILE *file = fopen(ARQUIVO_DADOS, "rb+");
    if (!file) {
        printf("Arquivo nao encontrado ou bloqueado.\n");
        return;
    }

    char busca[TAM_NOME];
    printf("Digite o nome para alterar: ");
    ler_texto(busca, TAM_NOME);

    Contato temp;
    int achou = 0;

    while (fread(&temp, sizeof(Contato), 1, file) == 1) {
        // Usa a comparação inteligente
        if (comparar_nomes(temp.nome, busca)) {
            achou = 1;
            printf("Encontrado: %s (%02d/%02d/%04d)\n", temp.nome, temp.dia, temp.mes, temp.ano);
            
            printf("Novo Nome [Enter mantem '%s']: ", temp.nome);
            char buffer_nome[TAM_NOME];
            ler_texto(buffer_nome, TAM_NOME);
            if (strlen(buffer_nome) > 0) {
                strcpy(temp.nome, buffer_nome);
            }

            printf("Nova Data [Digite 0 0 0 para manter]: ");
            int d, m, a;
            char buffer_data[50];
            ler_texto(buffer_data, 50);
            if (sscanf(buffer_data, "%d %d %d", &d, &m, &a) == 3) {
                if (d != 0 && data_valida(d, m, a)) {
                    temp.dia = d; temp.mes = m; temp.ano = a;
                }
            }

            fseek(file, -sizeof(Contato), SEEK_CUR);
            if (fwrite(&temp, sizeof(Contato), 1, file) != 1) {
                printf("[ERRO] Falha ao atualizar registro.\n");
            } else {
                printf(">>> Atualizado!\n");
            }
            break;
        }
    }

    // 5. VERIFICAÇÃO DE LEITURA
    if (ferror(file)) {
        printf("[ALERTA] Erro fisico de leitura no arquivo.\n");
    }

    if (!achou) printf("Contato nao encontrado.\n");
    fclose(file);
}

// 6. RESOLVENDO "ARQUIVO ILEGÍVEL" (Exportar para CSV)
// Permite abrir no Excel depois
void exportar_csv() {
    FILE *bin = fopen(ARQUIVO_DADOS, "rb");
    FILE *csv = fopen(ARQUIVO_CSV, "w");
    
    if (!bin || !csv) {
        printf("Erro ao abrir arquivos para exportacao.\n");
        if(bin) fclose(bin);
        return;
    }

    Contato temp;
    fprintf(csv, "Nome;Dia;Mes;Ano\n"); // Cabeçalho do CSV
    
    while (fread(&temp, sizeof(Contato), 1, bin) == 1) {
        fprintf(csv, "%s;%d;%d;%d\n", temp.nome, temp.dia, temp.mes, temp.ano);
    }
    
    printf("Dados exportados para '%s'. Abra no Excel!\n", ARQUIVO_CSV);
    fclose(bin);
    fclose(csv);
}

void listar_contatos() {
    FILE *file = fopen(ARQUIVO_DADOS, "rb");
    if (!file) return;

    Contato temp;
    printf("\n%-30s | DATA\n", "NOME");
    printf("----------------------------------------\n");
    while (fread(&temp, sizeof(Contato), 1, file) == 1) {
        printf("%-30s | %02d/%02d/%04d\n", temp.nome, temp.dia, temp.mes, temp.ano);
    }
    fclose(file);
}

int main() {
    setlocale(LC_ALL, "Portuguese"); // 7. Tenta ajustar acentuação
    int opcao;

    do {
        printf("\n1. Cadastrar\n2. Listar\n3. Alterar\n4. Exportar CSV (Excel)\n0. Sair\nOpcao: ");
        opcao = ler_inteiro(); // Leitura segura de int

        switch(opcao) {
            case 1: cadastrar_contato(); break;
            case 2: listar_contatos(); break;
            case 3: alterar_contato(); break;
            case 4: exportar_csv(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while(opcao != 0);

    return 0;
}