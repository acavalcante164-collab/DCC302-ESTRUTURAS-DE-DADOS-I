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
/* função auxiliar: cria e inicializa um nó 

No entanto, se desejarmos manter os elementos em ordem, cada novo elemento deve ser
inserido na ordem correta. Para exemplificar, vamos considerar que queremos manter
nossa lista de números inteiros em ordem crescente. A função de inserção, neste caso,
tem a mesma assinatura da função de inserção mostrada, mas percorre os elementos da
lista a fim de encontrar a posição correta para a inserção do novo. Com isto, temos que
saber inserir um elemento no meio da lista. A Figura 9.6 ilustra a inserção de um
elemento no meio da lista.

Conforme ilustrado na figura, devemos localizar o elemento da lista que irá preceder o
elemento novo a ser inserido. De posse do ponteiro para esse elemento, podemos
encadear o novo elemento na lista. O novo apontará para o próximo elemento na lista e
o elemento precedente apontará para o novo. O código abaixo ilustra a implementação
dessa função. Neste caso, utilizamos uma função auxiliar responsável por alocar
memória para o novo nó e atribuir o campo da informação.
*/
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
/* função vazia: retorna 1 se vazia ou 0 se não vazia 
Pode ser útil implementarmos uma função que verifique se uma lista está vazia ou não.
A função recebe a lista e retorna 1 se estiver vazia ou 0 se não estiver vazia. Como
sabemos, uma lista está vazia se seu valor é NULL. Uma implementação dessa função é
mostrada a seguir:

*/
int vazia (Lista* l)
{
 return (l == NULL);
}
/* função busca: busca um elemento na lista
Outra função útil consiste em verificar se um determinado elemento está presente na
lista. A função recebe a informação referente ao elemento que queremos buscar e
fornece como valor de retorno o ponteiro do nó da lista que representa o elemento. Caso
o elemento não seja encontrado na lista, o valor retornado é NULL.
*/
Lista* busca (Lista* l, int v)
{
 Lista* p;
 for (p=l; p!=NULL; p=p->prox)
 if (p->info == v)
 return p;
 return NULL; /* não achou o elemento */
}
/* função retira: retira elemento da lista 
Para completar o conjunto de funções que manipulam uma lista, devemos implementar
uma função que nos permita retirar um elemento. A função tem como parâmetros de
entrada a lista e o valor do elemento que desejamos retirar, e deve retornar o valor
atualizado da lista, pois, se o elemento removido for o primeiro da lista, o valor da lista
deve ser atualizado.
A função para retirar um elemento da lista é mais complexa. Se descobrirmos que o
elemento a ser retirado é o primeiro da lista, devemos fazer com que o novo valor da
lista passe a ser o ponteiro para o segundo elemento, e então podemos liberar o espaço
alocado para o elemento que queremos retirar. Se o elemento a ser removido estiver no
meio da lista, devemos fazer com que o elemento anterior a ele passe a apontar para o
elemento seguinte, e então podemos liberar o elemento que queremos retirar. Devemos
notar que, no segundo caso, precisamos do ponteiro para o elemento anterior para
podermos acertar o encadeamento da lista. As Figuras 9.4 e 9.5 ilustram as operações de
remoção.
*/
Lista* retira (Lista* l, int v) {
 Lista* ant = NULL; /* ponteiro para elemento anterior */
 Lista* p = l; /* ponteiro para percorrer a lista*/
 /* procura elemento na lista, guardando anterior */
 while (p != NULL && p->info != v) {
 ant = p;
 p = p->prox;
 }
 /* verifica se achou elemento */
 if (p == NULL)
 return l; /* não achou: retorna lista original */
 /* retira elemento */
 if (ant == NULL) {
 /* retira elemento do inicio */
 l = p->prox;
 }
 else {
 /* retira elemento do meio da lista */
 ant->prox = p->prox;
 }
 free(p);
 return l;
}
/*
Uma outra função útil que devemos considerar destrói a lista, liberando todos os
elementos alocados. Uma implementação dessa função é mostrada abaixo. A função
percorre elemento a elemento, liberando-os. É importante observar que devemos
guardar a referência para o próximo elemento antes de liberar o elemento corrente (se
liberássemos o elemento e depois tentássemos acessar o encadeamento, estaríamos
acessando um espaço de memória que não estaria mais reservado para nosso uso).
*/
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
/* função soma: retorna a soma dos valores dos elementos */
int lista_soma(Lista *L){
    int soma = 0; //INICIALIZA O ACUMULADOR
    Lista* p;     //PONTEIRO PARA AUXILIAR PERCORRER A LISTA

    //percorre a lista do inicio ao fim
    for (p = L; p!= NULL; p = p->prox){
        //adiciona o valor do no atual ao acumulador
        soma = soma + p->info;        
    }
    return soma;
}
int main (void) {
 Lista* l; /* declara uma lista não iniciada */
 l = inicializa(); /* inicia lista vazia */
 l = insere_ordenado(l, 23); /* insere na lista o elemento 23 */
 l = insere_ordenado(l, 45); /* insere na lista o elemento 45 */
 l = insere_ordenado(l, 56); /* insere na lista o elemento 56 */
 l = insere_ordenado(l, 78); /* insere na lista o elemento 78 */
 
 printf("Elementos da lista:\n");
 imprime(l); 
 
 int soma_total = lista_soma(l);
 printf("A soma de todos os elementos eh: %d\n", soma_total);

 libera(l);
 return 0;
}
