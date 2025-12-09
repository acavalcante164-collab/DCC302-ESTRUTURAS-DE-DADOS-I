#include <stdio.h>
#include <stdlib.h>

int buscaSequencial(int vetor[], int TAM, int valor) {
    for (int i = 0 ; i < TAM ; i++){
        if (vetor[i] == valor){
            return i; //Retorna o indice do valor encontrad
        }
    }
    return -1; //Valor nao encontrado
}

int main () {
    int v [] = {1,6,7,9,4};
    int tamanho = 5;
    int valorBuscado;

    printf("Digite um valor para buscar no vetor: ");
    scanf("%d", &valorBuscado);

    //CHAMADA DA FUNCAO E CAPTURA DO RETORNO
    int resultado = buscaSequencial(v, tamanho, valorBuscado);

    if (resultado == -1) {
        printf("Valor %d NAO encontrado no vetor.\n", valorBuscado);
    } else{
        printf("Valor %d encotrado na posicao %d.\n", valorBuscado, resultado);
    }
    return 0;
}