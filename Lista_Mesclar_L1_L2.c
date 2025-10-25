#include <stdio.h>
#include <stdlib.h>

/*
A estrutura consiste numa seqüência encadeada de elementos, em geral chamados de
nós da lista. A lista é representada por um ponteiro para o primeiro elemento (ou nó).
Do primeiro elemento, podemos alcançar o segundo seguindo o encadeamento, e assim
por diante. O último elemento da lista aponta para NULL, sinalizando que não existe um
próximo elemento.
Para exemplificar a implementação de listas encadeadas em C, vamos considerar um
exemplo simples em que queremos armazenar valores inteiros numa lista encadeada. O
nó da lista pode ser representado pela estrutura abaixo:
Devemos notar que trata-se de uma estrutura auto-referenciada, pois, além do campo
que armazena a informação (no caso, um número inteiro), há um campo que é um
ponteiro para uma próxima estrutura do mesmo tipo. Embora não seja essencial, é uma
boa estratégia definirmos o tipo Lista como sinônimo de struct lista, conforme
ilustrado acima. O tipo Lista representa um nó da lista e a estrutura de lista encadeada
é representada pelo ponteiro para seu primeiro elemento (tipo Lista*).
Considerando a definição de Lista, podemos definir as principais funções necessárias
para implementarmos uma lista encadeada.
*/
struct lista {
 int info;
 struct lista* prox;
};
typedef struct lista Lista;
/* função de inicialização: retorna uma lista vazia
A função que inicializa uma lista deve criar uma lista vazia, sem nenhum elemento.
Como a lista é representada pelo ponteiro para o primeiro elemento, uma lista vazia é representada pelo ponteiro NULL, pois não existem elementos na lista. A função tem
como valor de retorno a lista vazia inicializada, isto é, o valor de retorno é NULL. Uma
possível implementação da função de inicialização é mostrada a seguir:
*/
Lista* inicializa (void)
{
 return NULL;
}
/* função auxiliar: cria e inicializa um nó */
Lista* cria (int v)
{
 Lista* p = (Lista*) malloc(sizeof(Lista));
 p->info = v;
 return p;
}
/* função insere_ordenado: insere elemento em ordem */
Lista* insere_ordenado (Lista* l, int v)
{
 Lista* novo = cria(v); /* cria novo nó */
 Lista* ant = NULL; /* ponteiro para elemento anterior */
 Lista* p = l; /* ponteiro para percorrer a lista*/
 /* procura posição de inserção */
 while (p != NULL && p->info < v) {
 ant = p;
 p = p->prox;
 }
 /* insere elemento */
 if (ant == NULL) { /* insere elemento no início */
 novo->prox = l;
 l = novo;
 }
 else { /* insere elemento no meio da lista */
 novo->prox = ant->prox;
 ant->prox = novo;
 }
 return l;
}
/* função vazia: retorna 1 se vazia ou 0 se não vazia */
/* função vazia: retorna 1 se vazia ou 0 se não vazia */
int vazia (Lista* l)
{
 return (l == NULL);
}
/* função busca: busca um elemento na lista */
Lista* busca (Lista* l, int v)
{
 Lista* p;
 for (p=l; p!=NULL; p=p->prox)
 if (p->info == v)
 return p;
 return NULL; /* não achou o elemento */
}
/* Função retira recursiva
A função para retirar um elemento da lista também pode ser escrita de forma recursiva.
Neste caso, só retiramos um elemento se ele for o primeiro da lista (ou da sub-lista). Se
o elemento que queremos retirar não for o primeiro, chamamos a função recursivamente
para retirar o elemento da sub-lista.
*/
Lista* retira_rec (Lista* l, int v)
{
 if (vazia(l))
 return l; /* lista vazia: retorna valor original */
 /* verifica se elemento a ser retirado é o primeiro */
 if (l->info == v) {
 Lista* t = l; /* temporário para poder liberar */
 l = l->prox;
 free(t);
 }
 else {
 /* retira de sub-lista */
 l->prox = retira_rec(l->prox,v);
 }
 return l;
}
/*
A função para liberar uma lista também pode ser escrita recursivamente, de forma
bastante simples. Nessa função, se a lista não for vazia, liberamos primeiro a sub-lista e
depois liberamos a lista.
*/
void libera_rec (Lista* l)
{
 if (!vazia(l))
 {
 libera_rec(l->prox);
 free(l);
 }
}



/* Função imprime recursiva 
Uma lista pode ser definida de maneira recursiva. Podemos dizer que uma lista
encadeada é representada por:
• uma lista vazia; ou
• um elemento seguido de uma (sub-)lista.
Neste caso, o segundo elemento da lista representa o primeiro elemento da sub-lista.
Com base na definição recursiva, podemos implementar as funções de lista
recursivamente. Por exemplo, a função para imprimir os elementos da lista pode ser reescrita da forma ilustrada abaixo:
*/
void imprime_rec (Lista* l)
{
 if (vazia(l))
 return;
 /* imprime primeiro elemento */

 
 printf("info: %d\n",l->info);
 /* imprime sub-lista */
 imprime_rec(l->prox);
}
int lista_soma_recursiva(Lista *l) {
    // 1. Caso Base: Se a lista está vazia, a soma é 0.
    if (l == NULL) {
        return 0;
    }
    
    // 2. Caso Recursivo: A soma é o valor do nó atual (L->info)
    //    mais a soma do resto da lista (L->prox).
    return l->info + lista_soma_recursiva(l->prox);
}
/*
 * Função que mescla duas listas ordenadas (L1, L2) em uma terceira (L3).
 * VERSÃO RECURSIVA (DESTRUTIVA).
 * Esta função altera L1 e L2, "desmontando-as" para montar a nova lista.
 * Ao final, L1 e L2 não serão mais listas válidas.
 * Apenas a lista retornada (L3) deve ser usada e liberada.
 */
Lista* merge_sorted_lists(Lista *L1, Lista *L2) {
    // 1. Casos Base: Se uma das listas estiver vazia, retorne a outra.
    if (vazia(L1)) {
        return L2;
    }
    if (vazia(L2)) {
        return L1;
    }

    // 2. Passo Recursivo:
    Lista* L3_cabeca = NULL; // Ponteiro para a cabeça da lista mesclada

    // Compara os nós da cabeça de L1 e L2
    if (L1->info <= L2->info) {
        // A cabeça de L1 é menor, então ela é a cabeça de L3
        L3_cabeca = L1;
        
        // O próximo de L3_cabeca será o resultado da mesclagem 
        // do resto de L1 (L1->prox) com a L2 inteira.
        L3_cabeca->prox = merge_sorted_lists(L1->prox, L2);
    } 
    else {
        // A cabeça de L2 é menor, então ela é a cabeça de L3
        L3_cabeca = L2;

        // O próximo de L3_cabeca será o resultado da mesclagem
        // da L1 inteira com o resto de L2 (L2->prox).
        L3_cabeca->prox = merge_sorted_lists(L1, L2->prox);
    }

    // Retorna a cabeça da nova lista mesclada
    return L3_cabeca;
}
/*
INTERCALA DUAS LISTAS L1 E L2 de form DESTRUTIVA
A LISTA RETORNADA EH A CABEÇA DA NOVA LISTA INTERCALADA

*/
Lista* intercalate_lists(Lista *L1, Lista * L2){
    //caso base
    //se tiver fazia nao tem nada para intercalar
    //o resultado eh o que sobrar de l2
    if(vazia(L1)){
        return L2;
    }
    //SE L2 ESTIVER VAZIA, NAO TEM NADA DE L2 PARA COLOCAR
    if (vazia(L2)){
        return L1;
    }
    // 1. Guardamos as "caudas" de L1 e L2
    Lista* cauda_L1 = L1->prox;
    Lista* cauda_L2 = L2->prox;
    // 2. A cabeça da lista final será a cabeça de L1
    Lista* cabeca_final = L1;
    // 3. O próximo da cabeça (L1) será a cabeça de L2
    cabeca_final->prox = L2;
    // 4. O próximo de L2 será o resultado da intercalação
    //    das *caudas* que guardamos.
    //
    //    Chamamos a função recursivamente para:
    //    L1 = cauda_L1 (o resto de L1)
    //    L2 = cauda_L2 (o resto de L2)
    L2->prox = intercalate_lists(cauda_L1, cauda_L2);

    return cabeca_final;
}
// Função auxiliar para inserir no FIM (necessária para o teste)
Lista* insere_no_fim(Lista* l, int v) {
    Lista* novo = cria(v); 
    novo->prox = NULL;
    if (vazia(l)) {
        return novo;
    }
    Lista* p = l;
    while (p->prox != NULL) {
        p = p->prox;
    }
    p->prox = novo;
    return l; 
}

int main (void) {
    // Teste 1: Listas de tamanhos diferentes
    Lista* l1 = inicializa();
    l1 = insere_no_fim(l1, 1);
    l1 = insere_no_fim(l1, 3);
    l1 = insere_no_fim(l1, 5);

    Lista* l2 = inicializa();
    l2 = insere_no_fim(l2, 2);
    l2 = insere_no_fim(l2, 4);
    l2 = insere_no_fim(l2, 6);
    l2 = insere_no_fim(l2, 7);
    l2 = insere_no_fim(l2, 8); // L2 é maior

    printf("--- Lista 1 Original ---\n");
    imprime_rec(l1);
    printf("--- Lista 2 Original ---\n");
    imprime_rec(l2);

    // Como é destrutivo, l1 e l2 não serão mais válidas.
    Lista* l_intercalada = intercalate_lists(l1, l2);
    
    printf("\n--- Lista Intercalada (L2 maior) ---\n");
    imprime_rec(l_intercalada);
    /* Saída:
    info = 1
    info = 2
    info = 3
    info = 4
    info = 5
    info = 6
    info = 7
    info = 8
    */

    libera_rec(l_intercalada); // Libera todos os nós (de l1 e l2)

    // --- Teste 2 (L1 maior) ---
    l1 = inicializa();
    l1 = insere_no_fim(l1, 10);
    l1 = insere_no_fim(l1, 30);
    l1 = insere_no_fim(l1, 50);
    l1 = insere_no_fim(l1, 60);

    l2 = inicializa();
    l2 = insere_no_fim(l2, 20);
    l2 = insere_no_fim(l2, 40);

    printf("\n--- Lista 1 Original ---\n");
    imprime_rec(l1);
    printf("--- Lista 2 Original ---\n");
    imprime_rec(l2);

    l_intercalada = intercalate_lists(l1, l2);
    
    printf("\n--- Lista Intercalada (L1 maior) ---\n");
    imprime_rec(l_intercalada);
    /* Saída:
    info = 10
    info = 20
    info = 30
    info = 40
    info = 50
    info = 60
    */

    libera_rec(l_intercalada);
    return 0;
}
