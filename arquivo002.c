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
        printf("Digite suas frase ([ENTER] em uma linha vazia para finalizar):\n");        
                
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
void leitura(char f[]){
    FILE *file = fopen(f, "r");
    char texto[500];

    if(file){
        printf("\n\tTexto lido do arquivo\n");
        while(fgets(texto, 500, file) != NULL){ 
            // O texto já tem o \n do arquivo, então usamos printf simples
            // Se usar printf("\n%s", texto), vai pular duas linhas.           
            printf("Lido: %s", texto);
        }        
        fclose(file);
    }
    else
        printf("\n\t--> ERRO ao abrir arquivo!\n");
}
int main(){
    char nome[] = ("teste.txt");
    // Primeiro escrevemos algo
    escrever(nome);
    // Depois lemos o que foi escrito
    leitura(nome);
    return 0;
}
