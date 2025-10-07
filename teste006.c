#include <stdio.h>

void printar(int x, int *ptr);
void atualizar(int x, int *ptr);
 
int main(){

    int x = 10;
    int *ptr;

    ptr = &x;
    printar(x, ptr);
    
    *ptr += 1;
    atualizar(x, ptr);

    return 0;
 }
 void printar(int x, int *ptr){
    printf("O valor de x eh = %d\n", x);
    printf("O endereco de x eh %p\n", &x);
    printf("O valor apontado por ptr eh: %d\n", *ptr);
    printf("O endereco de ptr eh: %p\n", ptr);
 }
 void atualizar(int x, int *ptr){
    printf("O valor antigo de X = %d\n", (x-1));
    printf("O NOVO valor de x eh %d", *ptr);
 }