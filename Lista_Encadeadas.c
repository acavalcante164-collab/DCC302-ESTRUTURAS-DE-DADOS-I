#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int valor;
    struct  nodo* prox;
} Nodo;

typedef struct fila{
    Nodo* ini;
    Nodo* Fim;
    int Tam;
} Fila;

int remover(Fila*, int);
int tamanho(Fila*);


int inserir (Fila* f, int v){
    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
    if(novo != NULL){
        novo->prox = NULL;
        novo-> valor = v;
        if (!esta_vazia(f))
            f->Fim->prox = novo;
        else
            f->ini = novo;
    f->Fim = novo;
    f->Tam++;
    return 1;
    }
    return 0;
}
void imprimir(Fila* f){
    // Crie um ponteiro auxiliar do tipo Nodo, não Fila.
    Nodo* p = f->ini;

    if (esta_vazia(f)) {
        printf("Fila vazia!\n");
        return;
    }

    printf("Fila: [ ");
    // Percorra a lista até o ponteiro ser NULO (fim da lista)
    while (p != NULL) {
        printf("%d ", p->valor); // Imprima o valor do nodo atual
        p = p->prox;             // Avance para o próximo nodo
    }
    printf("]\n");
}

Fila* criafila() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    if (f != NULL) {
        f->ini = NULL;
        f->Fim = NULL;
        f->Tam = 0;
    }
    return f;
}

int esta_vazia(Fila* f) {
    // Uma fila está vazia se seu início (ou fim) for NULO.
    return (f->ini == NULL);
}

void destroi_fila(Fila* f) {
    Nodo* p = f->ini;
    while (p != NULL) {
        Nodo* temp = p; // Guarda o nodo atual
        p = p->prox;    // Avança para o próximo
        free(temp);     // Libera o nodo anterior
    }
    free(f); // Libera a estrutura da fila
}

int main(){
    // 1. Crie a fila e inicialize seus ponteiros
    Fila* FF = criafila();
    if (FF == NULL) {
        printf("Erro ao alocar memoria para a fila!\n");
        return 1; // Termina o programa se não houver memória
    }

    // 2. Agora sim, insira os elementos
    inserir(FF, 23);
    inserir(FF, 10);
    inserir(FF, 7);

    // 3. Imprima a fila para ver o resultado
    imprimir(FF);

    // 4. Libere a memória no final
    destroi_fila(FF);

    return 0;
}
int remover (Fila* f, int v){
    if(!esta_vazia(f)){
        f->Tam--;
        *v = f->ini->valor;
        Nodo* p = f->ini;
        f->ini = f->ini->prox;
        free(p);
        return 1;
    }
    return 0;
}