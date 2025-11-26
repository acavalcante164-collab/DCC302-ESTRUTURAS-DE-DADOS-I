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

}
void leitura(){

}
int main (){

    FILE *file; //NOME E TIPO
    char letra;

    file = fopen("conto.txt", "w+"); //RECEBE DOIS PARAMETROS NOME DO ARQUIVO e uma DAS LETRAS DE CIMA

    if(file){
        printf("\nDigite um texto e pressione o ENTER ao Finalizar!");
        scanf("%c", &letra);
        while(letra != '\n'){
            fputc(letra, file);
            scanf("%c", &letra);
        }
        rewind(file); //funcao que volta para o  inicio do arquivo

        printf("\n\tTEXTO LIDO DO ARQUIVO:\n");
        while(!feof(file)){
            letra = fgetc(file);
            printf("%c", letra);
        }

        fclose(file);
    }
    else
        printf("\n\t--> ERRO ao abrir o arquivo!\n");

    return 0;
}