#include <stdio.h>
#include "calc.h"

int main() {
    char c;
    float v;
    Calc *calculadora;

    // Cria calculadora com formato de duas casas decimais
    calculadora = calc_cria("%.2f\n");
    
    printf("Digite a expressao pos-fixa (numeros e operadores separados por espaco, termine com '='):\n");
    printf("Exemplo: 5 3 + 8 * = \n");

    // Loop para ler a expressão
    do {
        // lê o próximo caractere não branco
        scanf(" %c", &c);

        // verifica se é um operador válido
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            calc_operador(calculadora, c);
        }
        // Se não for operador, tenta ler como um número
        else {
            // "Devolve" o caractere lido para o buffer de entrada
            ungetc(c, stdin);
            // Tenta ler um número float. Se conseguir (retorno == 1), empilha.
            if (scanf("%f", &v) == 1) {
                calc_operando(calculadora, v);
            }
        }
    } while (c != '='); // Um caractere final para parar a leitura

    // Ao final, o resultado está no topo da pilha
    float resultado_final = calc_resultado(calculadora);
    printf("\nResultado Final: %.2f\n", resultado_final);
    
    // Libera a memória alocada
    calc_libera(calculadora);

    return 0;
}