#include <stdio.h>

struct lado{
    int l1;
    int l2;
};
int main(){
    struct lado l;

    printf("Digite os dois lado: ");
    scanf(" %d %d", &l.l1, &l.l2);

    printf("os dois lados fornecidos foram: %d  /  %d\n", l.l1, l.l2);

    return 0;

}