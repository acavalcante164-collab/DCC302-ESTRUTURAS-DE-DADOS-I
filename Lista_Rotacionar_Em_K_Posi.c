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

int vazia (Lista* l)
{
    return (l == NULL);
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

/*
 * Rotaciona uma lista encadeada à esquerda em k posições.
 * Retorna o ponteiro para a nova cabeça da lista.
 */
Lista* rotate_list(Lista *L, int k) {
    // 1. Lida com casos de borda
    // Se a lista está vazia, ou tem 1 nó, ou k=0, não há rotação.
    if (vazia(L) || L->prox == NULL || k == 0) {
        return L;
    }

    // 2. Encontrar o tamanho da lista (n) e a cauda original
    int n = 1;
    Lista* cauda_original = L;
    while (cauda_original->prox != NULL) {
        cauda_original = cauda_original->prox;
        n++;
    }

    // 3. Normalizar o k
    // Se k > n (ex: k=7, n=5), é o mesmo que k = (k % n) (k=2)
    k = k % n;
    
    // Se k normalizado for 0, não há rotação
    if (k == 0) {
        return L;
    }

    // 4. Encontrar o novo fim (k-ésimo nó)
    Lista* novo_fim = L;
    // Precisamos andar k-1 passos para chegar no k-ésimo nó
    for (int i = 1; i < k; i++) {
        novo_fim = novo_fim->prox;
    }

    // 5. Identificar a nova cabeça (o nó *após* o novo_fim)
    Lista* nova_cabeca = novo_fim->prox;

    // 6. Fazer a rotação
    
    // a) Liga a cauda original (5) na cabeça original (1)
    // Lista se torna: 1 -> 2 -> 3 -> 4 -> 5 -> (aponta para 1)
    cauda_original->prox = L; 

    // b) Quebra a lista no novo fim (o nó 2)
    // O prox do nó 2 se torna NULL
    novo_fim->prox = NULL;
    
    // A lista agora é: 3 -> 4 -> 5 -> 1 -> 2 -> NULL

    // 7. Retorna a nova cabeça
    return nova_cabeca;
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
    Lista* l = inicializa(); 
    l = insere_no_fim(l, 1);
    l = insere_no_fim(l, 2);
    l = insere_no_fim(l, 3);
    l = insere_no_fim(l, 4);
    l = insere_no_fim(l, 5);

    printf("--- Lista Original ---\n");
    imprime(l);
    /* Saída:
    info = 1
    info = 2
    info = 3
    info = 4
    info = 5
    */

    int k = 2;
    printf("\n--- Rotacionando %d posicoes a esquerda ---\n", k);
    
    // A variável 'l' de main PRECISA ser atualizada com o retorno
    l = rotate_list(l, k);

    imprime(l);
    /* Saída:
    info = 3
    info = 4
    info = 5
    info = 1
    info = 2
    */

    // Teste com k maior que o tamanho
    k = 8; // 8 % 5 = 3. Deve rotacionar mais 3.
    printf("\n--- Rotacionando mais %d posicoes (total 5) ---\n", k);
    l = rotate_list(l, k); // A lista agora é 3->4->5->1->2
                           // Rotacionar 3: nova cabeça será 1
    
    imprime(l);
    /* Saída:
    info = 1
    info = 2
    info = 3
    info = 4
    info = 5
    */


    libera(l);
    return 0;
}