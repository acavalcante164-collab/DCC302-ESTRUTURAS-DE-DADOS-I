#include<stdio.h>
int main(){
    int a;
    int* p;

    a = 10;
    p = &a;
    *p = 5;

    printf("%d", a);
}