#include<stdio.h>
#include<stdlib.h>
int main(){
    int* e;
    e = malloc(sizeof(int));

    if (e == NULL){
        printf("Memoria cheia");
        exit(1);
    }
    *e = 10;

    printf("e = %p e contem %d", e, *e);

    free(e);
    return 0;
}
