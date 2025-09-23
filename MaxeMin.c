#include <stdio.h>

void MaxMix(int *vet, int tam, int*max, int *min){
    //INICIALIZA MAX E MIN COM O PRIMEIRO ELEMENTO DO VETOR
    *max = vet[0];
    *min = vet[0];

    //PERCORRE O VETOR A PARTIR DO SEGUNDO ELEMENTO (INDICE 1)
    for( int i = 1; i < tam; i++){
        if (vet[i] > *max){
            *max = vet[i]; //ATUALIZA O MAXIMO
        }
        if (vet[i] < *min){
            *min = vet[i]; //ATUALIZA O MINIMO
        }
    }
}
int main(){
    int meuVetor[] = {5,2,8,1,9,4};
    int tamanho = sizeof(meuVetor) / sizeof(meuVetor[0]);
    int valorMax, valorMin;

    MaxMix(meuVetor, tamanho, &valorMax, &valorMin);

    printf("Valor maximo: %d\n", valorMax);
    printf("valor minimo: %d\n", valorMin);

    return 0;
}
/*

Explicação do Código
void encontrarMaxMin(int *vet, int tam, int *max, int *min):
Esta é a função que encontra o máximo e o mínimo.

int *vet: Recebe um ponteiro para o início do vetor. 

int tam: O número de elementos no vetor. 

int *max, int *min: Ponteiros para as variáveis onde os valores máximo e mínimo serão armazenados, permitindo que a função os altere. 

*max = vet[0]; e *min = vet[0];:
Inicializamos as variáveis max e min com o primeiro elemento do vetor. Isso é crucial para que as comparações subsequentes funcionem corretamente. 

for (int i = 1; i < tam; i++):
O ciclo for percorre o vetor a partir do segundo elemento (índice 1), já que o primeiro já foi usado na inicialização. 

if (vet[i] > *max) e if (vet[i] < *min):
Dentro do ciclo, cada elemento vet[i] é comparado com o max e o min atuais. 

Se o elemento for maior que o máximo atual, ele se torna o novo máximo. 
Se o elemento for menor que o mínimo atual, ele se torna o novo mínimo. 

main():
Declara um vetor de exemplo meuVetor. 
Calcula o tamanho do vetor. 
Declara as variáveis valorMax e valorMin.
Chama a função encontrarMaxMin, passando o vetor, o seu tamanho e os endereços das variáveis valorMax e valorMin (usando o operador &). 
Imprime os valores encontrados. 

int tamanho = sizeof(meuVetor) / sizeof(meuVetor[0]);

sizeof(meuVetor)

O operador sizeof retorna o tamanho em bytes ocupado pela variável.

Como meuVetor é um array de 6 inteiros, e geralmente int ocupa 4 bytes (depende do compilador/arquitetura), o resultado é:

6 elementos * 4 bytes = 24 bytes

sizeof(meuVetor[0])

Aqui pegamos o tamanho de um elemento do vetor.

Como meuVetor[0] é um int, o resultado normalmente é 4 bytes.

Divisão:

sizeof(meuVetor) / sizeof(meuVetor[0]) = 24 / 4 = 6


Isso dá a quantidade de elementos no vetor.

 Ou seja:
O código calcula dinamicamente o tamanho do vetor (quantos elementos ele tem), sem precisar contar manualmente.

*/