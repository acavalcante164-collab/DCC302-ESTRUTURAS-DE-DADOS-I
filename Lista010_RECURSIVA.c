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
int main (void) {
 Lista* l; /* declara uma lista não iniciada */
 l = inicializa(); /* inicia lista vazia */
 l = insere_ordenado(l, 23); /* insere na lista o elemento 23 */
 l = insere_ordenado(l, 45); /* insere na lista o elemento 45 */
 l = insere_ordenado(l, 56); /* insere na lista o elemento 56 */
 l = insere_ordenado(l, 78); /* insere na lista o elemento 78 */
 imprime_rec(l); /* imprimirá: 78 56 45 23 */
 l = retira_rec(l, 78);
 imprime_rec(l); /* imprimirá: 56 45 23 */
 l = retira_rec(l, 45);
 imprime_rec(l); /* imprimirá: 56 23 */
 libera_rec(l);
 return 0;
}
