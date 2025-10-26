#include <stdio.h>
#include <stdlib.h>

struct lista {
    int info;
    struct lista* prox;
};
typedef struct lista Lista;

//INICIALIZA UMA LISTA VAZIA
Lista* inicializa(void){
    return NULL;
}
//CRIA E INICIALIZA UM NO
Lista* cria (int v) {
    Lista* p = (Lista*) malloc (sizeof(Lista));
    p->info = v;
    //p->prox nao e inicializado aqui
    return p;
}
//funcao insere
Lista* insere_ordenado(Lista* l, int v){
    Lista* novo = cria(v); //CRIA NOVO NO
    Lista* ant = NULL; //ELEMENTO ANTERIOR
    Lista* p = l; //percorrer a lista
    //procura posicao
    while(p != NULL && p->info < v){
        ant = p;
        p = p->prox;
    }
    //insere  elementos
    if(ant == NULL) {
        novo->prox = l;
        l = novo;
    }
    else{
        novo -> prox = ant->prox;
        ant->prox = novo;
    }
    return l;
}
//esta vazia
int vazia (Lista* l){
    return (l == NULL);
}
//libera toda a memoria
void libera (Lista* l){
    Lista* p = l;
    while (p != NULL){
    Lista* t = p->prox;
    free(p);
    p = t;
    }
}
void imprime(const char* nome_lista, Lista* l){
    printf("%s: [", nome_lista);
    Lista* p; //AUXILIAR PARA PERCORRER A LISTA
    for (p = l; p != NULL; p = p->prox){
        printf("%d ", p->info);
    }
    printf("]\n");
}
/*
funcao split_lista
DIVIDE A LISTA L EM DUAS NOVAS LISTAS
UMA DE PARES  E UMA DE IMPARES
CRIA COPIAS DO NOS, PRESRVANDO A LISTA L ORIGINAL
*/
void split_list (Lista* l, Lista **even_list, Lista **odd_list){
    //INICIALIZANDO COMO VAZIAS
    *even_list = inicializa();
    *odd_list = inicializa();

    //PONTEIRO PARA O FINAL DE CADA LISTA
    Lista *even_tail = NULL;
    Lista *odd_tail = NULL;

    Lista *p; //PONTEIRO PARA PERCORRER A LISTA ORIGINAL

    for (p = l; p != NULL; p = p->prox){
        Lista *novo = cria(p->info);
        novo->prox = NULL; //O NOVO NO EH SEMPRE O ULTIMO

        //PAR OU IMPAR
        if (novo->info % 2 == 0){
            if (*even_list == NULL){
                *even_list = novo;
            } else {
                even_tail->prox = novo;
            }
            even_tail = novo;
        }
        else{
            if(*odd_list == NULL){
                *odd_list = novo;
            } else {
                odd_tail->prox = novo;
            }
            odd_tail = novo;
        }
    }
}

int main(void){
    Lista* l; //LISTA ORIGINAL
    Lista* l_pares; //NOVA LISTA PARES
    Lista* l_impares; //NOVA LISTA IMPARES

    l  = inicializa(); //INICIALIZA LISTA VAZIA

    l = insere_ordenado(l, 23);
    l = insere_ordenado(l, 45);
    l = insere_ordenado(l, 56);
    l = insere_ordenado(l, 78);
    l = insere_ordenado(l, 10);
    l = insere_ordenado(l, 99);

    imprime("LISTA ORIGINAL: (L)", l);

    //CHAMANDO A FUNCAO PASSANDO OS ENERECOS DE L PARE E IMPARES
    split_list(l, &l_pares, &l_impares);

    imprime("Lista Original", l);
    imprime("Lista PARES        ", l_pares);
    imprime("Lista IMPARES      ", l_impares);

    //LIBERA A MEMORIA DE TODAS AS TRES LISTAS
    libera(l);
    libera(l_pares);
    libera(l_impares);

    return 0;

}