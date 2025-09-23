/* inserção no início */
Lista2* insere (Lista2* l, int v)
{
 Lista2* novo = (Lista2*) malloc(sizeof(Lista2));
 novo->info = v;
 novo->prox = l;
 novo->ant = NULL;
 /* verifica se lista não está vazia */
 if (l != NULL)
 l->ant = novo;
 return novo;
}

