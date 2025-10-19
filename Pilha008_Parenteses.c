#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PILHA 100 // Define um tamanho máximo para a nossa pilha

// --- IMPLEMENTAÇÃO DA PILHA DE CARACTERES ---

typedef struct {
    char VET[MAX_PILHA];
    int topo;
} Pilha;

// Função para criar e inicializar uma nova pilha
Pilha* cria_pilha() {
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    if (p != NULL) {
        p->topo = 0; // A pilha começa vazia
    }
    return p;
}

// Função para verificar se a pilha está vazia
int pilha_vazia(Pilha* p) {
    return (p->topo == 0);
}

// Função para verificar se a pilha está cheia
int pilha_cheia(Pilha* p) {
    return (p->topo == MAX_PILHA);
}

// Função para empilhar um caractere
void empilha(Pilha* p, char c) {
    if (!pilha_cheia(p)) {
        p->VET[p->topo] = c;
        p->topo++;
    } else {
        printf("Erro: Pilha cheia!\n");
    }
}

// Função para desempilhar um caractere
char desempilha(Pilha* p) {
    if (!pilha_vazia(p)) {
        p->topo--;
        return p->VET[p->topo];
    } else {
        // Retorna um caractere nulo para indicar erro/pilha vazia
        return '\0';
    }
}

// --- FUNÇÃO PRINCIPAL DE VERIFICAÇÃO ---

int verifica_balanceamento(const char* expressao) {
    int i;
    int tamanho = strlen(expressao);
    Pilha* minha_pilha = cria_pilha();

    // Se não conseguir criar a pilha, retorna erro.
    if (minha_pilha == NULL) {
        return 0; // Indica falha
    }

    printf("Verificando expressao: \"%s\"\n", expressao);

    // 1. Percorre cada caractere da expressão
    for (i = 0; i < tamanho; i++) {
        char caractere_atual = expressao[i];

        // 2. Se encontrou um '(', empilha
        if (caractere_atual == '(') {
            printf("  Encontrou '(', empilhando...\n");
            empilha(minha_pilha, caractere_atual);
        }
        // 3. Se encontrou um ')', trata o fechamento
        else if (caractere_atual == ')') {
            printf("  Encontrou ')', tentando desempilhar...\n");
            // Se a pilha estiver vazia, há um ')' a mais. Inválido!
            if (pilha_vazia(minha_pilha)) {
                printf("  ERRO: Encontrou ')' mas a pilha esta vazia. Expressao invalida!\n");
                free(minha_pilha); // Libera a memória antes de sair
                return 0; // 0 significa "inválido"
            }
            // Se não está vazia, desempilha para "casar" o parêntese
            else {
                desempilha(minha_pilha);
                printf("  Sucesso! Um par foi fechado.\n");
            }
        }
    }

    // 4. Ao final, verifica se a pilha ficou vazia
    if (pilha_vazia(minha_pilha)) {
        printf("Fim da expressao. A pilha esta vazia. Expressao valida!\n\n");
        free(minha_pilha);
        return 1; // 1 significa "válido"
    } else {
        printf("ERRO: Fim da expressao, mas a pilha nao esta vazia. Ha '(' a mais. Expressao invalida!\n\n");
        free(minha_pilha);
        return 0; // 0 significa "inválido"
    }
}


int main() {
    // --- TESTES ---

    if (verifica_balanceamento("a + (b * (c - d))")) {
        // Sucesso
    }
    
    if (verifica_balanceamento("((a+b)) * c")) {
        // Sucesso
    }

    if (verifica_balanceamento("(a+b(")) {
        // Falha
    }
    
    if (verifica_balanceamento(")a+b(")) {
        // Falha
    }

    if (verifica_balanceamento("(a * b) )")) {
        // Falha
    }

    return 0;
}