#include <stdio.h>
#include <stdlib.h>
struct lista {
 int info;
 struct lista* prox;
};
typedef struct lista Lista;

Lista* inicializa (void)
{
 return NULL;
}

Lista* cria (int v)
{
 Lista* p = (Lista*) malloc(sizeof(Lista));
 p->info = v;
 return p;
}

int vazia (Lista* l)
{
 return (l == NULL);
}

void libera (Lista* l)
{
 Lista* p = l;
 while (p != NULL) {
 Lista* t = p->prox; /* guarda referência para o próximo elemento
*/
 free(p); /* libera a memória apontada por p */
 p = t; /* faz p apontar para o próximo */
 }
}

/* função imprime: imprime valores dos elementos */
void imprime (Lista* l)
{
 Lista* p; /* variável auxiliar para percorrer a lista */
 for (p = l; p != NULL; p = p->prox)
 printf("info = %d\n", p->info);
}


// Função auxiliar para contar o número de elementos
int tamanho(Lista* l) {
    int n = 0;
    Lista* p = l;
    while (p != NULL) {
        n++;
        p = p->prox;
    }
    return n;
}
// Função auxiliar para inserir no FIM da lista (diferente de 'insere_ordenado')
// Usaremos esta no 'main' para criar nossas listas de teste.
Lista* insere_no_fim(Lista* l, int v) {
    Lista* novo = cria(v); // 'cria' já aloca e atribui 'v'
    novo->prox = NULL;

    // Se a lista está vazia, o novo nó é o primeiro
    if (vazia(l)) {
        return novo;
    }

    // Se a lista NÃO está vazia, percorre até o fim
    Lista* p = l;
    while (p->prox != NULL) {
        p = p->prox;
    }
    
    // 'p' agora é o último nó. Liga o novo nó a ele.
    p->prox = novo;
    return l; // Retorna o início da lista (que não mudou)
}

/*
 * Verifica se uma lista encadeada é um palíndromo.
 * Retorna 1 (verdadeiro) ou 0 (falso).
 */
int is_palindrome(Lista *L) {
    // 1. Lida com casos simples
    if (vazia(L) || L->prox == NULL) {
        // Uma lista vazia ou com um único elemento é um palíndromo
        return 1;
    }

    // 2. Descobre o tamanho da lista
    int n = tamanho(L);
    if (n == 0) return 1;

    // 3. Aloca um vetor auxiliar
    int* vetor_aux = (int*) malloc(sizeof(int) * n);
    if (vetor_aux == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return 0; // Falha (não é palíndromo)
    }

    // 4. Copia a lista para o vetor
    Lista* p = L;
    int i = 0;
    while (p != NULL) {
        vetor_aux[i] = p->info;
        p = p->prox;
        i++;
    }

    // 5. Verifica se o VETOR é um palíndromo
    int esquerda = 0;
    int direita = n - 1;
    int resultado = 1; // Assume que é verdadeiro

    while (esquerda < direita) {
        if (vetor_aux[esquerda] != vetor_aux[direita]) {
            resultado = 0; // É falso
            break;         // Pode parar de verificar
        }
        esquerda++;
        direita--;
    }

    // 6. Libera a memória auxiliar e retorna
    free(vetor_aux);
    return resultado;
}
int main (void) {
    // Teste 1: Lista que É um palíndromo (1 -> 2 -> 3 -> 2 -> 1)
    Lista* l1 = inicializa(); 
    l1 = insere_no_fim(l1, 1);
    l1 = insere_no_fim(l1, 2);
    l1 = insere_no_fim(l1, 3);
    l1 = insere_no_fim(l1, 2);
    l1 = insere_no_fim(l1, 1);
    
    printf("Lista 1:\n");
    imprime(l1);
    
    if (is_palindrome(l1)) {
        printf("Resultado: A Lista 1 E um palindromo.\n\n");
    } else {
        printf("Resultado: A Lista 1 NAO E um palindromo.\n\n");
    }
    
    // Teste 2: Lista que NÃO é um palíndromo (1 -> 2 -> 3 -> 4)
    Lista* l2 = inicializa();
    l2 = insere_no_fim(l2, 1);
    l2 = insere_no_fim(l2, 2);
    l2 = insere_no_fim(l2, 3);
    l2 = insere_no_fim(l2, 4);
    
    printf("Lista 2:\n");
    imprime(l2);

    if (is_palindrome(l2)) {
        printf("Resultado: A Lista 2 E um palindromo.\n\n");
    } else {
        printf("Resultado: A Lista 2 NAO E um palindromo.\n\n");
    }

    // Libera a memória
    libera(l1);
    libera(l2);
    
    return 0;
}