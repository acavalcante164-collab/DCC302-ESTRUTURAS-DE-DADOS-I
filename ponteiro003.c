#include <stdio.h>

void printar(int x, int* ptr);
void atualizar (int x, int* ptr);

int main(){
    int x = 100;
    int *ptr; //    conteudo do endereço apontado por ptr, quando se declara um ponteiro ele vai conter o valor do conteudo apontado por alguma coisa
    
    ptr = &x; //ptr vai receber o endereço de x

    printar(x, ptr);
    
    *ptr = *ptr + 1;

    atualizar(x, ptr);

    return 0;
}
void printar (int x, int* ptr){

    printf("\n\n");
    printf("O conteudo de x = %d\n", x);
    printf("O endereco de x = %p\n", &x);
    printf("o conteudo apontador por ptr = %d\n", *ptr);
    printf("endereco apontado por ptr = %p", ptr);

}
void atualizar(int x, int *ptr){
    printf("\n\n");
    printf("Update de x = %d\n", x);
    printf("O endereco de x = %p\n", &x);
    printf("o NOVO conteudo apontador por ptr = %d\n", *ptr);
    printf("endereco apontado por ptr = %p", ptr);
    
}
