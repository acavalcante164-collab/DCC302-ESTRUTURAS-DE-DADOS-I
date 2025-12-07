#include <stdio.h>

int buscaSequencial(int *lista , int chave, int tamanho){
    int i;
    for(i = 0 ; i < tamanho ; i++){
        if (lista[i] == chave){ //VAI DE POSICAO EM POSICAO PEGUNTANDO SE O INTEM ESTA NAQUELA POSICAO E  == A CHAVE
            return i;
        }
    }
    return -1;
}
void main (){
    int numeros [] = {20 , 5 , 15 , 24 , 67 , 45 , 1 , 76 , 21 , 11};
    int chave , resultado; //O ITEM BUSCADO E ARMAZENAMENTO DO RESULTADO

    printf("Digite o numero a ser buscado: ");
    scanf(" %d", &chave);

    //FUNCAO DE BUSCA
    resultado = buscaSequencial(numeros, chave, 10); //TODO NOME DE VETOR E UM PONTEIRO, SE TIVESSE COM & ESTARIA PASSANDO O ENDERECO DDE MEMORIA ONDE ELE ESTA ALOCADO

    if (resultado != -1){
        printf("O elemento %d foi encontrado no indice %d", chave, resultado);
    }
    else{
        printf("O elemento %d nao foi encontrado.", &chave);
    }
}