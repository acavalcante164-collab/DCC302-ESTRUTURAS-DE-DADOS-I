#include <stdio.h> //Tratamento de entrada/saída.

#include <stdlib.h> /*Implementa funções para diversas operações, 
incluindo conversão,  alocação de memória, controle de processo, 
funções de busca e ordenação.*/

#include <time.h> //Trata de tipos de data e hora.

#define TAM 5341 

/*
Constantes são usadas para armazenar valores que NÃO podem ser modificadas durante a execução de um programa.
Uma constante precisa ser declarada, e para tanto usamos a diretiva de pré-processador #define.
Sintaxe:
#define <nome_da_constante> <valor>
A declaração da constante deve ser feita no início do programa.
É extremamente recomendável utilizar letras maiúsculas ao declarar uma constante.
Declarando as constantes como maiúsculas podemos facilmente diferenciá-las das variáveis que por convenção devem ser declaradas em letras minúsculas.
*/

int main (){
    int Vet[TAM];
    int i, Colisoes, valor;

    //Vai percorrer todos os indices do vetor.
    for (i = 0; i < TAM; i++)
        Vet[i] = - 1;  //atribuicoes
     /*
    vet[i] = -i;
    Aqui você está armazenando o valor negativo do índice dentro da posição i.

    Quando i = 0 → vet[0] = -0 = 0

    Quando i = 1 → vet[1] = -1

    Quando i = 2 → vet[2] = -2

    … e assim por diante.
    */
    
    Colisoes = 0;
    srand((unsigned) time (NULL)); //time(NULL) pega o horário atual do sistema (em segundos desde 1 de janeiro de 1970).
    /*
    Para gerar um número aleatório (randômico) em linguagem C podemos usar a função rand pertencente à biblioteca stdlib.h.
    Gerar sequências de números aleatórios é um problema bastante comum em programação.
    A função rand
    Quando esta função é chamada ela produz um valor aleatório na faixa entre 0 e a constante RAND_MAX. O valor desta constante
    encontra-se definida no arquivo stdlib.h.
    Muitas vezes necessitamos gerar valores dentro de determinada faixa.
    */
    for (i = 0; i < 2000; i++){

        valor = rand() % 1000000 + 1;
        if (Vet[valor%TAM] != -1)
            Colisoes++;
        Vet[valor%TAM] = valor;
    }
    printf("numero de colisoes: %d\n", Colisoes);
    return 0 ;
    /*
    Isso é técnica de espalhamento (hashing):
    O operador % pega o resto da divisão.
    Assim, valor % TAM vai transformar um número enorme (1 até 1.000.000) em um índice válido do vetor Vet, que só tem tamanho TAM.
    Exemplo:
    Se TAM = 1000 → qualquer valor vai cair em uma posição de 0 a 999.
    Isso é como “espalhar” números grandes dentro de uma caixa menor.
    
    Aqui o programa está tentando detectar colisões:
    Se a posição calculada (valor % TAM) já estava ocupada, significa que dois números diferentes caíram na mesma posição.
    Isso é exatamente o que acontece em Tabelas Hash quando duas chaves diferentes têm o mesmo índice.
    4. O que significa Vet[valor % TAM] = valor;
    Ele guarda o valor aleatório naquela posição do vetor.
    Então se outro número cair na mesma posição no futuro, será detectado como colisão.

    5. Em resumo
    Esse código está simulando uma Tabela Hash com tratamento de colisão bem simplificado:
    Sorteia um número aleatório (valor).

    Calcula onde ele deve ser guardado (valor % TAM).

    Verifica se o espaço já estava ocupado.

    Se sim → conta uma colisão.

    Coloca o número naquela posição do vetor.

     Isso é um exemplo prático de como funcionam tabelas de dispersão (hash tables):

    O % é a função de hash.

    O vetor Vet é a tabela.

    Colisoes mede quantos números caíram na mesma posição (colisão de chaves).
    */
    

    }



