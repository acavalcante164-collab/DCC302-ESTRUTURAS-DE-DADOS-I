#include <stdio.h>
#include <stdlib.h>

void troca1(int *a, int* b) {
	int aux = *a;
	*a = *b;
	*b = aux;
	printf("--------------------------------------------\n");	
	printf(" A = %d (end. %p) e B = %d (end. %p)\n", *a, a, *b, b);
	printf("--------------------------------------------\n");	
}

void troca2(int *a, int *b) {
	int* aux = a;
	a = b;
	b = aux;
	printf("--------------------------------------------\n");
	printf(" A = %d (end. %p) e B = %d (end. %p)\n", *a, a, *b, b);
    printf("--------------------------------------------\n");
}

void troca3(int **a, int **b) {
	int* aux = *a;
	*a = *b;
	*b = aux;
	printf("--------------------------------------------\n");	
	printf(" A = %d (end. %p) e B = %d (end. %p)\n", **a, *a, **b, *b);
	printf("--------------------------------------------\n");	
}

int main(int argc, char** argv)
{
	int* x = (int *) malloc(sizeof(int));
	int* y = (int *) malloc(sizeof(int));
	
	*x = 10;
	*y = 11;
	printf("ANTES:\n");
	printf(" X = %d (end. %p) e Y = %d (end. %p)\n", *x, x, *y, y);
	
	troca1(x, y);
	//troca2(x, y);
	//troca3(&x, &y);
	printf("DEPOIS:\n");	
	printf(" X = %d (end. %p) e Y = %d (end. %p)\n", *x, x, *y, y);
	
	free(x);
	free(y);	
	
	system("pause");
    return 0;
}
