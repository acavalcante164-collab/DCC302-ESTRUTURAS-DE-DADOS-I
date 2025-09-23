/*
 DCC302 - ESTRUTURAS DE DADOS I - T01 (2025.2)
NOME: ALONSO FERNANDES CAVALANTE
MATRICULA: 2024005534

EXERCICIO DA AULA 01  10/09/2025 A 17/09/2025
*/

/*

DESCRIÇÃO:
Função de inserção

*/
#include <stdio.h>
#include <stdlib.h>  // MALLOC E FREE

//DEFINICAO DE ESTRUTURA DE NO DA LISTA
struct lista2 {
    int info;               //VALOR ARMAZENADO
    struct lista2* ant;     //PONTEIRO PARA O NO ANTERIOR
    struct lista2* prox;    // PONTEIRO PARA O PRIXIMO NO
};

typedef struct lista2 Lista2;

//FUNCAO PARA INSERIR ELEMENTO NO INICIO DA LISTA
Lista2* insere(Lista2* l, int v){
    Lista2* novo = (Lista2*) malloc(sizeof(Lista2)); //CRIA NOVO NO
    novo->info =v; //GUARDA O VALOR
    novo->prox = l; //O PROXIMMO DO NOVO NO EH O ANTIGO PRIMEIRO
    novo->ant = NULL; //COMO EH O PRIMEIRO, NAO TEM ANTERIOR

    //SE A LISTA NAO ERA VAZIA, O ANTIGO PRIMEIRO DEVE APONTAR PARA O NOVO
    if (l != NULL)
        l->ant = novo;
    

        return novo; //O NOVO EH O INICIO DA LISTA
}
//FUNCAO PARA IMPRIMIR A LISTA DO INCIO AO FIM
void imprime(Lista2* l) {
    Lista2* p;
    printf("Lista: ");
    for (p = l; p != NULL; p = p->prox) {
        printf("%d ", p->info);
    }
    printf("\n");
}
//FUNCAO PARA LIMPAR A MEMORIA DA LISTA
void libera(Lista2* l) {
    Lista2* p = l;
    while (p != NULL) {
        Lista2* temp = p->prox; //GUARDA O PROXIMO
        free(p); //LIBERA O ATUAL
        p = temp;
    }
}

int main() {
    Lista2* lista = NULL; //COMECA COM LISTA VAZIA

    //INSERE ALGUNS ELEMENTOS
    lista = insere(lista,10);
    lista = insere(lista, 5);
    lista = insere(lista, 20);

    //IMPRIME A LISTA
    imprime(lista);

    //LIBERA A MEMORIA
    libera(lista);

    return 0;
}
