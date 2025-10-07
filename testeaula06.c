#include <stdio.h>
#include <string.h> // Para usar strlen() e strcmp()
#include <ctype.h>  // Para usar tolower() (opcional, para ignorar maiúsculas/minúsculas)

// A capacidade máxima da nossa pilha (e da palavra)
#define MAX 50 // Aumentei o limite para palavras maiores

// 1. A ESTRUTURA DA PILHA (modificada para usar char)
typedef struct pilha {
    int topo;
    char VET[MAX]; // Alterado de int para char
} Pilha;

// ---- FUNÇÕES DE CONTROLE DA PILHA ----

// Função para inicializar a pilha
void inicializa_pilha(Pilha* p) {
    p->topo = 0;
}

// Função que verifica se a pilha está cheia (seu código original)
int pilha_cheia(Pilha* p) {
    return (p->topo == MAX);
}

// Função que verifica se a pilha está vazia
int pilha_vazia(Pilha* p) {
    return (p->topo == 0);
}

// 2. FUNÇÃO EMPILHA (modificada para char e com retorno melhorado)
// Retorna 1 em caso de sucesso, 0 em caso de falha (pilha cheia)
int empilha(Pilha* p, char c) {
    if (!pilha_cheia(p)) {
        p->VET[p->topo] = c;
        p->topo++;
        return 1; // Sucesso
    }
    return 0; // Falha
}

// 3. FUNÇÃO DESEMPILHA
// Retorna o caractere do topo ou '\0' (nulo) se a pilha estiver vazia
char desempilha(Pilha* p) {
    if (!pilha_vazia(p)) {
        p->topo--; // Primeiro decrementa para apontar para o último elemento
        return p->VET[p->topo];
    }
    return '\0'; // Retorno de erro/vazio
}


// ---- FUNÇÃO PRINCIPAL (MAIN) ----

int main() {
    Pilha minha_pilha;
    char palavra_original[MAX];
    char palavra_invertida[MAX];
    int i;
    int tamanho_palavra;

    // Inicializa a pilha antes de usar!
    inicializa_pilha(&minha_pilha);

    // 4. LER A PALAVRA DO USUÁRIO
    printf("Digite uma palavra para verificar se eh um palindromo: ");
    scanf("%s", palavra_original);

    tamanho_palavra = strlen(palavra_original);

    // Verifica se a palavra cabe na pilha
    if (tamanho_palavra >= MAX) {
        printf("Erro: A palavra eh muito grande para a pilha (max: %d caracteres).\n", MAX - 1);
        return 1; // Termina o programa com erro
    }

    // 5. EMPILHAR CADA CARACTERE DA PALAVRA
    printf("\nEmpilhando os caracteres: %s\n", palavra_original);
    for (i = 0; i < tamanho_palavra; i++) {
        // Opcional: converte para minúscula para ignorar diferenças
        // char caractere = tolower(palavra_original[i]);
        // empilha(&minha_pilha, caractere);
        empilha(&minha_pilha, palavra_original[i]);
    }

    // 6. DESEMPILHAR PARA FORMAR A PALAVRA INVERTIDA
    printf("Desempilhando para inverter...\n");
    for (i = 0; i < tamanho_palavra; i++) {
        palavra_invertida[i] = desempilha(&minha_pilha);
    }
    palavra_invertida[i] = '\0'; // Adiciona o terminador de string no final!

    printf("Palavra original: %s\n", palavra_original);
    printf("Palavra invertida: %s\n", palavra_invertida);

    // 7. COMPARAR AS STRINGS E DAR O RESULTADO
    // strcmp retorna 0 se as strings forem iguais
    if (strcmp(palavra_original, palavra_invertida) == 0) {
        printf("\nResultado: A palavra '%s' EH um palindromo!\n", palavra_original);
    } else {
        printf("\nResultado: A palavra '%s' NAO EH um palindromo.\n", palavra_original);
    }

    return 0;
}