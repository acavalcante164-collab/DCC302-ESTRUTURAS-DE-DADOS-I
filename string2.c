//MANIPULANDO STRING
/*

Em C, não existe uma função "pronta" na biblioteca padrão que converte a string inteira de uma vez (como string.lower() em Python).

Você precisa fazer isso manualmente, caractere por caractere, usando um loop.

Para facilitar, usamos a biblioteca <ctype.h>, que possui a função tolower() (to lower = para minúscula). Ela pega uma letra e a transforma em minúscula.

O Passo a Passo
Importe <ctype.h>.

Crie um loop (geralmente for ou while) para percorrer a string.

Aplique tolower() em cada posição do vetor.

Exemplo Prático
Aqui está como transformar "Ola MUNDO" em "ola mundo":

Criando sua própria função
Para deixar seu código organizado, o ideal é criar uma função utilitária para isso, assim você pode reutilizá-la sempre que precisar.

*/
#include <stdio.h>
#include <string.h>
#include <ctype.h> //NECESSARIO PARA O  tolower()

// Função que recebe a string e modifica ela diretamente
void paraMinuscula(char* str) {
    for(int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

int main(){
    char texto[] = "Ola MUNDO 123!";
    int i;

    char nome[50];
    printf("Digite seu nome (): ");
    fgets(nome, 50, stdin);

    //chamada de funcao
    paraMinuscula(nome);
    printf("seu nome normalizado: %s", nome);


    printf("Original: %s\n", texto);

    //LOOP QUE PERCORRE ATE ENCONTRAR O FIM DA STRING (\0)
    for(i = 0; texto[i] != '\0'; i++){
        texto[i] = tolower(texto[i]);
    }
    printf("Minuscula: %s\n", texto);

    return 0;
}