#include <stdio.h>



//Pag 75
typedef struct aluno *PAluno;

#define MAX 100
PAluno tab[MAX];

void inicializa (void){
    int i;
    for (i = 0; i < MAX; i++)
        tab[i] = NULL;

void preeche (int i){
    if (tab[i == NULL])
        tab[i] = (PAluno)malloc(sizeof(Aluno));

    printf("Entre com o nome: ");
    scanf(" %80[^\n]", tab[i]->nome);
    printf("Entre com a matricula: ");
    scanf("%d", &tab[i]->mat);
    printf("Entre com o endereco: ");
    scanf(" %120[^\n]", tab[i]->end);
    printf("Entre com o telefone: ");
    scanf(" %20[^\n]", tab[i]->tel);
}
}

