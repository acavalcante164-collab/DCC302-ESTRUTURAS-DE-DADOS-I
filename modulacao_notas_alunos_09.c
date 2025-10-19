#include <stdio.h>

// FUNCAO QUE CALCULA A MEDA CONFORME O TIPO ('A' OU 'P')
float calcularMedia(float n1, float n2, float n3, char tipo)
{
    float media;

    if (tipo == 'A' || tipo == 'a')
    {
        media = (n1 + n2 + n3) / 3.0;
    }
    else if (tipo == 'P' || tipo == 'p')
    {
        media = (n1 * 5 + n2 * 3 + n3 * 2) / 10.0;
    }
    else
    {
        printf("Tipo invalido. Retornando 0.\n");
        media = 0.0;
    }

    return media;
}

int main()
{
    float nota1, nota2, nota3;
    char tipo;

    printf("Digite as 3 notas do aluno: ");
    scanf("%f %f %f", &nota1, &nota2, &nota3);

    printf("Digite o tipo de media ('A' para aritimetica, 'P' para ponderada): ");
    scanf(" %c", &tipo); // ESPACO ANTES DO %C PARA IGNORA LIXO DE BUFFER

    float media = calcularMedia(nota1, nota2, nota3, tipo);

    printf("A media do aluno eh: %.2f\n", media);

    return 0;
}