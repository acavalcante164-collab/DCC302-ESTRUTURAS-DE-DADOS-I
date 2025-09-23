#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	int num;
	
	int *a;
	int *b;
	
	int **pp;
	int ***ppp;
	
	num = 3;
	
	a = &num;
	
	b = malloc(4);
	
	*b = 5;
	
	pp = &a;
	
	ppp = &pp;
	
	***ppp = 8;
	
	printf("\n num = %d \n", num);
	
	printf("\n *a = %d \n", *a);
	printf("\n *b = %d \n", *b);
	
	printf("\n **pp = %d \n", **pp);
	printf("\n ***ppp = %d \n", ***ppp);
	
	free(b);
	
	system("pause");
	return 0;
}
