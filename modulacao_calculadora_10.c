#include <stdio.h>

// FUNCAO QUE REALIZA A OPERACAO COM BASE NO SIMBOLO INFORMADO
float calcular(float num1, float num2, char operador)
{
    float resultado;

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
        if (num2 != 0)
            resultado = num1 / num2;
        else
        {
            printf("Erro: divisao por zero!\n");
            resultado = 0;
        }
        break;

    default:
        printf("Operador invalido.\n");
        resultado = 0;
    }
    return resultado;
}

int main()
{
    float valor1, valor2, resultado;
    char operacao;

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