#include <stdio.h>
#include <stdlib.h>

/*
Aula 208: Como escrever em arquivo texto com a função fputc?
Modos de abertura de arquivos:
w-> Escrita
r -> leitura
a -> anexar
r+ -> leitura e escrita
w+ -> leitura e escrita (apaga o conteúdo caso o arquivo exista)
a+ -> leitura e escrita (adiciona ao final do arquivo)
*/
void escrever(char f[]){
    FILE *file = fopen(f, "w");
    char letra;

    if(file){
        printf("\nDigite um texto e pressione o ENTER ao Finalizar! ");
        scanf("%c", &letra);
        while(letra != '\n'){
            fputc(letra, file);
            scanf("%c", &letra);
        } 
        fclose(file);       
    }
    else
        printf("\nERRO ao abrir arquivo!\n");
}
void leitura(char f[]){
    FILE *file = fopen(f, "r");
    char letra;

    if(file){
        printf("\n\tTEXTO LIDO DO ARQUIVO:\n");
        while(!feof(file)){
            letra = fgetc(file);
            printf("%c", letra);
        }

        fclose(file);
    }
    else
        printf("\n\t--> ERRO ao abrir arquivo!\n");
}
int main (){

    char nome[]  = ("conto.txt");
    
    escrever(nome);
    leitura(nome);

    return 0;
}