#include <stdio.h>
#include <stdlib.h>

#define MAX 10 //DEFINE UMA CONSTANTE
/*
A ESTRUTURA QUE REPRESENTA O TIPO PILHA DEVE, PORTANTO, SER COMPOSTA PELO
VETOR[] E PELO NUMERO DE ELEMENTOS ARMAZENADOS
*/
typedef struct pilha{
    int topo;
    int vetor[MAX];
} Pilha;
/*
- ALOCA MEMORIA PARA A ESTRUTURA FISICA
- INICIALIZA O TOPO DO VETOR = 0
- RETORNA UM PONTEIRO PARA A ESTRUTURA CRIADA
*/
void CriaPilha(Pilha* p){    
    p-> topo = 0;    
}
/*
RECEBE UM '*' PONTEIRO PARA UMA "STRUCT" DO TIPO 'PILHA'
E LIBERA A MEMORIA OCUPADA POR ELA
*/
void LiberaPilha(Pilha* p){
    free(p);
}
/*
O QUE CARACTERIZA UMA PILHA VAZIA ?
O TOPO ESTAH NA POSICAO = O;
*/
int EstahVazia (Pilha* p){
    return (p->topo == 0);
}
/*
O QUE CARACTERIZA UMA PILHA CHEIA ?
O TOPO EH IGUAL AO TAMANHO DO VETOR INTERNO DA PILHA
*/
int EstahCheia(Pilha* p){
    return (p->topo == MAX);
}
/*
- RECEBE UM PONTEIRO PARA UMA ESTRUTURA DO TIPO PILHA E UM VALOR A SER EMPILHADO
-VERIFICA SE A PILHA NAO ESTAH CHEIA
-SE NAO ESTAH, ENTAO ...
    COLOCA O ELEMENTO NA POSICAO INDICADA PELO TOPO
    INCREMENTA O VALOR DO TOPO
A FUCAO EMPILHA() RETORMA 1 SE O VALOR FOI EMPILHADO OU ENTAO REORNA 0 SE NAO FOI POSSIVEL EMPILHAR
*/
int empilha(Pilha* p, int v){
    if(!EstahCheia(p)){
        /* INSERE UM ELEMENTO NA PROXIMA POSICAO LIVRE */
        p->vetor[p->topo] = v;
        p->topo++;
    }
    return 0;    
}
/*
- Recebe um ponteiro para uma estrutura do tipo Pilha e um ponteiro para uma variável inteira;
- Verifica se a pilha ja nao esta vazia;
- Se não está, então ...
    • Retira o elemento da posição logo abaixo do
    topo;
    • Decrementa o valor de topo;
- Afunção desempilha() retorna 1 (um) se o valor
foi desempilhado ou então retorna 0 (zero) se
não foi possível desempilhar;
*/
int desempilha(Pilha* p) {
    if (!EstahCheia(p)) {
        p->topo--; // Primeiro decrementa para apontar para o último elemento
        return p->vetor[p->topo];
    }
    return '\0'; // Retorno de erro/vazio
}
void imprimir(Pilha* p){
    if(EstahVazia(p)){
        printf("\nA Pilha estah VAZIA\n");
        return;
    }
    if (EstahCheia(p)) {
        printf("\nA Pilha estah CHEIA\n");
        return;
    }
    for(int i = p->topo - 1; i >= 0; i--){
        printf(" %d\n", p->vetor[i]);
    }

}
int main(){
    Pilha prato;

    CriaPilha(&prato);
    printf("Pilha inicializada");

    printf("\n EMPILHANDO: 10, 20, 25 ... \n");
    empilha(&prato, 10);
    empilha(&prato, 20);
    empilha(&prato, 25);
    empilha(&prato, 30);    
    

    printf("\n--- Pilha atual ---\n");
    imprimir(&prato);
    return 0;
}
