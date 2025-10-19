#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


int main(){
    Pilha prato;

    CriaPilha(&prato);
    printf("Pilha inicializada");

    printf("\n EMPILHANDO: 10, 20, 25 ... \n");
    empilha(&prato, 10);
    empilha(&prato, 20);
    empilha(&prato, 25);
    empilha(&prato, 30);    
    

    printf("\n--- Pilha atual ---\n");
    imprimir(&prato);
    return 0;
}
