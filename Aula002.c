/*
 DCC302 - ESTRUTURAS DE DADOS I - T01 (2025.2)
NOME: ALONSO FERNANDES CAVALANTE
MATRICULA: 2024005534

EXERCICIO DA AULA 01  10/09/2025 A 17/09/2025
*/

/*

DESCRIÇÃO:
Lista duplamente encadeada

*/
#include <stdio.h>
#include <stdlib.h>

// DEFINICAO DA ESTRUTURA DA LISTA DUPLAMENTE ENCADEADA
struct lista2
{
    int info;
    struct lista *ant;
    struct lista *prox;
};
typedef struct lista2 Lista2;

// FUNCAO QUE INDERE UM NOVO ELEMENTO NO INICIO
Lista2 *insere(Lista2 *l, int v)
{
    Lista2 *novo = (Lista2 *)malloc(sizeof(Lista2)); // CRIA NOVO NO
    novo->info = v;                                  // GUARDA O VALOR
    novo->prox = l;                                  // PROXIMO DO NOVO EH O ANTIGO PRIMEIRO
    novo->ant = NULL;                                // COMO EH O PRIMEIRO, NAO TEM ANTERIOR

    // SE A LISTA NAO ERA VAZIA, O ANTIGO PRIMEIRO DEVE APONTAR PARA O NOVO
    if (l != NULL)
        l->ant = novo;

    return novo; // O NOVO EH O INICIO DA LISTA
}
// IMPRIME A LISTA DO INICIO PARA O FIM
void imprime_frente(Lista2 *l)
{
    printf("LISTA DO INICIO AO FIM:\n");
    for (Lista2 *p = l; p != NULL; p = p->prox)
    {
        printf("%d  ", p->info);
    }
    printf("\n");
}

// IMPRIME A LISTA DO FIM PARA O INICIO
void imprime_tras(Lista2 *l)
{
    if (l == NULL)
    {
        printf("Lista vazia.\n");
        return;
    }

    // VAI ATE O ULTIMO ELEMENTO
    Lista2 *p = l;
    while (p->prox != NULL)
    {
        p = p->prox;
    }

    // AGORA VOLTA IMPRIMINDO
    printf("LISTA DO FIM AO INICIO:\n");
    for (; p != NULL; p = p->ant)
    {
        printf("%d ", p->info);
    }
    printf("\n");
}

// FUNCAO PRINCIPAL PARA TESTAR
int main(void)
{
    Lista2 *lista = NULL; // LISTA COMECA FAZIA

    // INSERE ALGUNS VALORES
    lista = insere(lista, 10);
    lista = insere(lista, 20);
    lista = insere(lista, 30);
    lista = insere(lista, 40);

    imprime_frente(lista); // DEVE MOSTRAR : 40 30 20 10
    imprime_tras(lista);   // DEVE MOSTRAR : 10 20 30 40

    return 0;
}
