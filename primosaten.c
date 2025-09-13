//Todos os primos ate n
#include <stdio.h>
#include <stdbool.h>  // habilita o tipo bool
#include <math.h>



int main(void){
    int n;
    printf("Digite um numero: ");
    scanf("%d", &n);

    for (int num = 2; num <= n; num++){
        bool primo = true; //assume que eh priomo ate provar contrario
        int limite = sqrt(num);

        for (int d = 2; d <= limite; d++){
            if (num % d == 0){
                primo = false;
                break; //Ja achou um divisor, nao precisa continuar
            }
        }

        if (primo){
            printf("%d\n", num);
        }
    }

    return 0;
}

