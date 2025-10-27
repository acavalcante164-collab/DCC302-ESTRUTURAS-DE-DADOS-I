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


Lista* insere_inicio (Lista* l, int v)
{
    Lista* novo = cria(v);
    novo->prox = l;
    return novo; // A nova cabeça da lista é o 'novo'
}

void libera (Lista* l)
{
    Lista* p = l;
    while (p != NULL) {
    Lista* t = p->prox; 
    free(p); 
    p = t; 
    }
}


void imprime (const char* nome_lista, Lista* l)
{
    printf("%s: [ ", nome_lista);
    Lista* p; /* variável auxiliar para percorrer a lista */
    for (p = l; p != NULL; p = p->prox) {
        printf("%d ", p->info);
    }
    printf("]\n");
}



void sort_list(Lista *L)
{
    // 1. Verifica casos básicos: lista vazia ou com 1 elemento
    if (L == NULL || L->prox == NULL) {
        return;
    }

    int swapped; // Flag para otimização
    Lista *p;    // Ponteiro para percorrer a lista

    do {
        swapped = 0; // Reseta a flag no início de cada passagem
        p = L;

        // 2. Percorre a lista comparando elementos adjacentes
        while (p->prox != NULL) {
            
            // 3. Compara o nó atual com o próximo
            if (p->info > p->prox->info) {
                
                // 4. Se fora de ordem, troca os DADOS (info)
                int temp = p->info;
                p->info = p->prox->info;
                p->prox->info = temp;
                
                // 5. Marca que uma troca ocorreu
                swapped = 1;
            }
            // Avança para o próximo nó
            p = p->prox;
        }
        // 6. Repete o processo se qualquer troca foi feita nesta passagem
    } while (swapped);
}


int main (void) {
    Lista* l; 
    l = inicializa(); 

  // Vamos criar uma lista DESORDENADA usando insere_inicio
  // A lista será: 10 -> 56 -> 23 -> 45
    l = insere_inicio(l, 45); 
    l = insere_inicio(l, 23); 
    l = insere_inicio(l, 56); 
    l = insere_inicio(l, 10); 

    imprime("Lista Original ", l);
  
    printf("\n--- Ordenando a lista ---\n");
    sort_list(l);
  
    imprime("Lista Ordenada ", l);

    libera(l);
    return 0;
}