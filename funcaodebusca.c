/*
Função de busca
A função de busca recebe a informação referente ao elemento que queremos buscar e
tem como valor de retorno o ponteiro do nó da lista que representa o elemento. Caso o
elemento não seja encontrado na lista, o valor retornado é NULL.
*/
/* função busca: busca um elemento na lista */
Lista2* busca (Lista2* l, int v)
{
 Lista2* p;
 for (p=l; p!=NULL; p=p->prox)
 if (p->info == v)
 return p;
 return NULL; /* não achou o elemento */
}