#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//FUNCAO GENERICA PARA GERAR E SALVAR OS NUMEROS
void gerar_arquivo(char *nome_arquivo, int quantidade){
    FILE *arquivo;
    int i;

    //ABRE O ARQUIVO PARA ESCRITA ("W"  - Write)
    arquivo = fopen(nome_arquivo, "w");

    //VERIFICA SE HOUVE ERRO NA ABERTURA
    if (arquivo == NULL){
        printf("[Erro] ao criar o arquivo: %s\n", nome_arquivo);
        exit(1); //ENCERRA O PROGRAMA COM ERRO
    }
    printf("Gerando %d numeros em '%s'...\n", quantidade, nome_arquivo);

    //LOOP PARA GERAR OS NUMEROS ALEATORIos
    for (i = 0; i < quantidade; i++){
        //GERA UM NUMERO ALEATORIO ENTRE ZERO E 999999
        int numero = rand() % 1000000;

        //ESCREVE NO ARQUIVO. O \n COLOCA UM NUMERO POR LINHA
        fprintf(arquivo, "%d\n", numero);
    }
    //FECHA O ARQUIVO PARA SALVAR OS DADOS NO DISCO
    fclose(arquivo);
    printf("Concluido!\n");
}
int main(){
    //INICIALIZA A SEMENTE ALEATORIA 
    //SEM ISSO, OS NUMEROS SERIAM OS MESMO TODA VEZ QUE RODASSE O PROGRAMA
    srand((unsigned)time(NULL));

    printf("--- INICIANDO GERACAO DE ARQUIVOS ---\n");

    //CHAMADAS DA FUNCAO PARA CADA REQUISITO
    gerar_arquivo("numeros_100.txt", 100);
    gerar_arquivo("numeros_1000.txt", 1000);
    gerar_arquivo("numeros_10000.txt", 10000);
    gerar_arquivo("numeros_100000.txt", 100000);

    printf("\nTodos os arquivos foram gerados com sucesso.\n");
    printf("Verifique a pasta do projeto.\n");

    return 0;
}
