#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void escrever(char f[]) {
    FILE *file = fopen(f, "w"); // "w" cria ou substitui o arquivo
    char nome[100];
    int opcao, idade;
    float altura;

    if (file) {
        printf("--- Cadastro de Pessoas ---\n");
        
        do {
            // 1. Lendo o Nome
            // O espaço antes do % (" %100...") é um truque do C:
            // ele "come" qualquer Enter ou espaço que tenha sobrado antes de ler o nome.
            printf("\nDigite o NOME: ");
            scanf(" %99[^\n]", nome); 

            // 2. Lendo Idade e Altura
            printf("Digite IDADE e ALTURA (ex: 25 1.75): ");
            scanf("%d %f", &idade, &altura);

            // 3. USANDO O FPRINTF
            // Escreve no arquivo formatado. O \n no final é importante para separar os registros.
            fprintf(file, "Nome: %s | Idade: %d | Altura: %.2f\n", nome, idade, altura);

            // 4. Pergunta se continua
            printf("Digite 1 para inserir outro registro ou 0 para sair: ");
            scanf("%d", &opcao); // CORREÇÃO: Adicionado o &

        } while (opcao == 1);
        
        fclose(file);
        printf("\nDados gravados com sucesso em %s!\n", f);
    } else {
        printf("\nERRO ao abrir o arquivo!\n");
    }
}

int main() {
    char nomeArquivo[] = "TesteDeTexto.txt";
    escrever(nomeArquivo);
    return 0;
}