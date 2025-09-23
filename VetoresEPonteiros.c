#include <stdio.h>
#include <stdlib.h>

int main(){
    int v[3] = {5,10,15};

    printf("%d %d\n", v, &v[0]);
    printf("%d %d\n", v+1, &v[1]);
    printf("%d %d\n", v+2, &v[2]);

    printf("%d %d\n", *v, v[0]);
    printf("%d %d\n", *(v+1), v[1]);
    printf("%d %d\n", *(v+2), v[2]);
}