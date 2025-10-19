/*

DCC205 - PROGRAMAÇÃO ESTRUTURADA - T01 (2025.1)
NOME: ALONSO FERNANDES CAVALCANTE
MATRICULA: 2024005534

EXERCÍO DA AULA 08  08/05/2025 A 23/07/2025

*/

/*

DESCRIÇÃO:

10) Escreva uma função que receba dois valores numéricos e um símbolo. Esse símbolo
representará a operação que se deseja efetuar com os números. Assim, se o símbolo
for “ + ”, deverá ser realizada uma adição, se for “ − ”, uma subtração, se for “/”, uma
divisão, e, se for “*”, será efetuada uma multiplicação. Retorne o resultado da operação
para o programa principal.

*/

#include <stdio.h>

// FUNCAO QUE REALIZA A OPERACAO COM BASE NO SIMBOLO INFORMADO
float calcular(float num1, float num2, char operador)
{
    float resultado;

    // USO DO SWITH PARA SIMPLIFICAR O CODIGO E VERIFICACAO DE QUAL ENTRADA VAI SER FEITA PELO USUARIO
    switch (operador)
    {
    case '+':
        resultado = num1 + num2;
        break;
    case '-':
        resultado = num1 - num2;
        break;
    case '*':
        resultado = num1 * num2;
        break;
    case '/':
        // EM CASO DE ZERO
        if (num2 != 0)
            resultado = num1 / num2;
        else
        {
            printf("Erro: divisao por zero!\n");
            resultado = 0;
        }
        break;
    // CASO NENHUMA CONDICAO SEJA ATENDIDA
    default:
        printf("Operador invalido.\n");
        resultado = 0;
    }
    return resultado;
}

// FUNCAO PRINCIPAL
int main()
{
    float valor1, valor2, resultado;
    char operacao;

    // ENTRADA DE DADOS
    printf("Digite o primeiro numero: ");
    scanf("%f", &valor1);

    printf("Digite o segundo numero: ");
    scanf("%f", &valor2);

    printf("Digite a operacao (+, -, *, /): ");
    scanf(" %c", &operacao); // ESPACO ANTES DO %C PARA LIMPAR O BUFFER

    resultado = calcular(valor1, valor2, operacao);

    printf("Resultado: %.2f\n", resultado);

    return 0;
}