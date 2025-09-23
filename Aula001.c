/*
 DCC302 - ESTRUTURAS DE DADOS I - T01 (2025.2)
NOME: ALONSO FERNANDES CAVALANTE
MATRICULA: 2024005534

EXERCICIO DA AULA 01  10/09/2025 A 17/09/2025
*/

/*

DESCRIÇÃO:
1.Escreva as funções para inserir e retirar
um elemento de uma lista circular

*/
#include <stdio.h>
#include <stdlib.h>

//ESTRUTURA DO NO DA LISTA CIRCULAR
typedef struct lista {
    int info;
    struct lista* prox;
} Lista;

//FUNCAO PARA INSERIR NO FINAL DA LISTA CIRCULAR
Lista* insere(Lista* l, int valor) {
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    novo->info = valor;

    if (l == NULL) { //LISTA VAZIA
        novo->prox = novo; //APONTA PARA ELE MESMO
        return novo;
    } else {
        Lista* p = l;
        while (p->prox != l) {
            p = p->prox;
        }
        p->prox = novo; //ULTIMO APONTA PARA O NOVO
        novo->prox = l; //NOVO APONTA PARA O INICIO
        return l;
    }
}
//FUNCAO PARA REMOVER UM ELEMENTO DA LISTA CIRCULAR
Lista* retira(Lista* l, int valor) {
    if (l == NULL) return NULL; // LISTA VAZIA

    Lista* atual = l;
    Lista* anterior = NULL;

    //PERCORRE ATE ENCONTRAR O VALOR OU VOLTAR AO INICIO
    do {
        if (atual->info == valor) {
            if (anterior == NULL) { //REMOVE O PRIMEIRO NO
                //CASO A LISTA TENHA APENAS 11 ELEMENTO
                if (atual->prox == atual) {
                    free(atual);
                    return NULL;
                } else {
                    // ENCONTRA O ULTIMO NO PARA CORRIGIR PONTEIRO
                    Lista* ultimo = l;
                    while (ultimo->prox != l) {
                        ultimo = ultimo->prox;
                    }
                    ultimo->prox = atual->prox;
                    l = atual->prox;
                    free(atual);
                    return l;
                }
            } else { //REMOVENDO NO MEIO OU FIM
                anterior->prox = atual->prox;
                free(atual);
                return l;
            }
        }
        anterior = atual;
        atual = atual->prox;
    } while (atual != l);

    printf("Valor %d NAO encontrado na lista.\n", valor);
    return l; //VALOR NAO ENCONTRAD
}

//FUNCAO PARA IMPRIMIR A LISTA CIRCULAR
void imprime(Lista* l) {
    if (l == NULL) {
        printf("Lista Vaziz!\n");
        return;
    }
    Lista* p = l;
    do {
        printf("%d -> ", p->info);
        p = p->prox;
    } while (p != l);
    printf("(Volta ao INICIO)\n");
}

//PROGRAMA PRINCIPAL
int main() {
    Lista* l = NULL;

    //INSERCOES
    l = insere(l, 10);
    l = insere(l, 20);
    l = insere(l,30);
    l = insere(l,40);

    printf("LISTA APOS INSERCOES:\n");
    imprime(l);

    // REMOVER ELEMENTO
    l = retira(l,30);
    printf("\nLISTA APOS REMOVER 30:\n");
    imprime(l);

    //REMOVERE ELEMENTO QUE NAO EXISTE
    l = retira(l, 99);

    //REMOVER O PRIMEIRO
    l = retira(l,10);
    printf("\nLista apos REMOVER 10:\n");
    imprime(l);

    return 0;
}
