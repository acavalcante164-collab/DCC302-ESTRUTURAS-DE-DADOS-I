#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição do nome do arquivo (constante)
#define ARQUIVO_DADOS "agenda.bin"
#define TAM_NOME 50

// 1. Definição da Struct (O "Molde" do nosso contato)
typedef struct {
    char nome[TAM_NOME];
    int dia;
    int mes;
    int ano;
} Contato;

// Função auxiliar para limpar o buffer do teclado
// Resolve o problema de "pular" leituras após um scanf
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para remover o \n que o fgets captura
void remover_nova_linha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// ---------------------------------------------------------
// FUNÇÃO DE CADASTRO (Gravar)
// Usa "ab" (Append Binary) para adicionar ao fim sem apagar
// ---------------------------------------------------------
void cadastrar_contato() {
    FILE *file = fopen(ARQUIVO_DADOS, "ab");
    
    // Tratamento de Erro: Falha ao abrir
    if (file == NULL) {
        printf("\n[ERRO CRITICO] Nao foi possivel abrir o arquivo para escrita!\n");
        printf("Verifique as permissoes da pasta.\n");
        return;
    }

    Contato novo;

    printf("\n--- Novo Cadastro ---\n");
    
    // Leitura segura de String
    printf("Nome: ");
    limpar_buffer(); // Garante que não há lixo antes de ler o nome
    if (fgets(novo.nome, TAM_NOME, stdin) == NULL) {
        printf("[ERRO] Falha ao ler o nome.\n");
        fclose(file);
        return;
    }
    remover_nova_linha(novo.nome);

    // Leitura dos números
    printf("Data de Nascimento (Dia Mes Ano): ");
    // Verifica se o usuário digitou 3 números corretamente
    if (scanf("%d %d %d", &novo.dia, &novo.mes, &novo.ano) != 3) {
        printf("[ERRO] Formato de data invalido!\n");
        fclose(file);
        return;
    }

    // Gravação segura da struct inteira
    // Retorna a quantidade de itens gravados (deve ser 1)
    if (fwrite(&novo, sizeof(Contato), 1, file) != 1) {
        printf("[ERRO] Falha na escrita do disco (HD cheio ou corrompido).\n");
    } else {
        printf(">>> Contato salvo com sucesso!\n");
    }

    fclose(file);
}

// ---------------------------------------------------------
// FUNÇÃO DE LEITURA (Carregar)
// Usa "rb" (Read Binary) para ler os dados
// ---------------------------------------------------------
void listar_contatos() {
    FILE *file = fopen(ARQUIVO_DADOS, "rb");

    // Tratamento de Erro: Arquivo não existe (primeira execução)
    if (file == NULL) {
        printf("\n[AVISO] Nenhuma agenda encontrada. Cadastre o primeiro contato!\n");
        return;
    }

    Contato temp;
    int contador = 0;

    printf("\n--- Lista de Aniversarios ---\n");
    printf("%-30s | %s\n", "NOME", "DATA"); // Cabeçalho formatado
    printf("-----------------------------------------------\n");

    // Loop de Leitura:
    // fread retorna a quantidade de itens lidos com sucesso.
    // Enquanto conseguir ler 1 struct inteira, continua o loop.
    while (fread(&temp, sizeof(Contato), 1, file) == 1) {
        printf("%-30s | %02d/%02d/%04d\n", temp.nome, temp.dia, temp.mes, temp.ano);
        contador++;
    }

    if (contador == 0) {
        printf("A agenda esta vazia.\n");
    } else {
        printf("-----------------------------------------------\n");
        printf("Total: %d contatos listados.\n", contador);
    }

    // Verifica se parou por erro ou fim de arquivo
    if (!feof(file)) {
        printf("\n[ALERTA] Ocorreu um erro durante a leitura do arquivo.\n");
    }

    fclose(file);
}

// ---------------------------------------------------------
// MENU PRINCIPAL
// ---------------------------------------------------------
int main() {
    int opcao;

    do {
        printf("\n=== AGENDA DE ANIVERSARIOS ===\n");
        printf("1. Cadastrar Contato\n");
        printf("2. Listar Todos\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_contato();
                break;
            case 2:
                listar_contatos();
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

