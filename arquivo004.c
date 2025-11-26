#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
COMO LER UM ARQUIVO TEXTO COM  A FUNCAO FSCANF?
*/
void escrever(char f[]){
    FILE *file = fopen(f, "w");
    char nome[100];
    int opcao, idade;
    float altura;

    if(file){
        printf("=== CADASTRO ===\n");
        do {
           // O fgets permite nomes compostos (com espaços) e é seguro.
           printf("\nDigite o nome: ");
           fgets(nome, 100, stdin);
           nome[strcspn(nome, "\n")] = 0;
           
           printf("Digite idae e altura (ex: 25 1.75): ");
           scanf("%d %f", &idade, &altura);

           fprintf(file, "%s;%d;%.2f\n", nome, idade, altura);

           printf("Digite 1 para inserir outro ou 0 para sair: ");
           scanf("%d", &opcao);

           //LIMPA O BUFFER DO TECLADO
           getchar();
        } while (opcao == 1);
    
        fclose(file);
    } else{
    printf("\nERRO ao abrir arquivo!\n");
    }
}
void ler(char f[]){
    FILE *file = fopen(f, "r");
    char nome[100];
    int idade;
    float altura;

    if (file){
        printf("\n--- Dados Lidos do Arquivo ---\n");
        // 4. MELHORIA: fscanf com Máscara de Leitura
        // O segredo é: "%[^;];%d;%f"
        // %[^;] -> Leia tudo ATÉ encontrar um ponto e vírgula (aceita espaços!)
        // ;     -> Leia e ignore o ponto e vírgula
        // %d    -> Leia o inteiro
        // ;     -> Leia e ignore o ponto e vírgula (opcional, dependendo do formato)
        while(fscanf(file, " %[^;];%d;%f", nome, &idade, &altura) == 3){
            printf("Nome: %-20s | Idade %d | Altura: %.2f\n", nome, idade, altura);
        }
        fclose(file);
    } else{
        printf("\nERRO ao abrir arquivo!\n");
    }
}

int main(){
    char nome []="TesteMelhorado.txt";
    
    escrever(nome);
    ler(nome);
    return 0;
}