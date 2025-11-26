/*
COMO ESCREVER LINHAS DE TEXTO COM A FUNCAO fputs
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void escrever(char f[]){
    FILE *file = fopen(f, "w");
    char texto[500];

    if(file){
        printf("Digite suas frase:\n");
        printf("Pressione apenas [ENTER] em uma linha vazia para finalizar:\n");
                
        while(fgets(texto, 500, stdin) != NULL){
            // VERIFICAÇÃO DE SAÍDA:
            // O fgets captura o "Enter" (\n). 
            // Se o usuário apertar só Enter, a string será "\n" (tamanho 1).
            // Se o tamanho for 1 (apenas o \n), paramos o loop.
            if(strlen(texto) <= 1 && texto[0] == '\n'){
                break;
            }
            // ESCREVENDO NO ARQUIVO:
            // O fgets já guarda o \n no final da string 'texto'.
            // Por isso, basta usar fputs. Não precisa do fputc('\n', file) extra!
            fputs(texto, file);
        }        
        fclose(file);
        printf("Arquivo salvo com sucesso!\n");
    } else  
        printf("\nERRO ao abrir arquivo!\n");
}
int main(){
    char nome[] = ("teste.txt");
    escrever(nome);
    return 0;
}
