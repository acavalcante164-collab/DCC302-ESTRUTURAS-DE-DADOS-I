#include <stdio.h>
#include <stdlib.h>

int main(){
     int contador_if = 0;
     int i;

     //LOOP QUE INTERA 10 VEZES
     for (i = 0; i< 10; i++){
        //  o id e executado se i for par
        if ( i % 2 == 0){
            contador_if++;
            printf("A condicao do if foi verdadeira para i = %d\n", i);
        }
     }
     printf("\nO comando IF foi executado com sucesso (condicaoo verdadeira) %d vezes.\n", contador_if);
        return 0;
}