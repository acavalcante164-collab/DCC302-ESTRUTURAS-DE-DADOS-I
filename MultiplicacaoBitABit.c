#include <stdio.h>
#include <stdint.h> //NECESSARIO PARA USAR TIPOS DE INTEIROS DE TAMANHO FIXO COMO uint32_t e uint64_t

/*
*FUNCAO QUE REALIZA A MULTIMICACAO BINARIA DE DIS NUMEROS DE 32 BITS SEM SINAL
*BASEADO NO ALGORITMO "SHIFT-AND-ADD" 
*/
uint64_t multiplicacao_binaria(uint32_t multiplicando, uint32_t multiplicador){

    //PRODUTO INICIALIZA EM ZERO
    //PRODUTO PODE SER ATE 64 BITS (32+32), POR ISSO USAMOS uint64+t
    uint64_t produto = 0;

    //CRIAMOS UMA VERSAO DE 64 BITS DO MULTIPLICANDO PARA EVITAR OVERFLOW
    //DURANTE OS DESLOCAMENTOS PARA A ESQUERDA
    uint64_t m_cand_64 = multiplicando;

    //REPETE PARA CADA BIT DO MULTIPLICADOR
    //O LOOP EXECUTA 32 VEZES PARA COBRIR TODOS OS BITS DE UM MULTIPLICADOR DE 32 BITES
    for (int i = 0; i < 32; i++){

        //PASSO1: TESTE DO MULTIPLICADOR0 (TESTA O BIT MENOS SIGNIFICATIVO)
        //USAMOS O OPERADOR BIT-A-BIT  AND (&) COM 1 PARA CHECAR O ULTIMO BIT
        if (multiplicador & 1){
            //PASSO SOME O MULTIPLICANDO AO PRODUTO 
            produto += m_cand_64;
        }

        //PASSO 2 DESLOQUE O REGISTRADOR MULTIPLICANDO 1 BIT A ESQUERDA
        //O OPERADOR <<= DESLOCA OS BITS PARA A ESQUERDA E ATRIBUI O RESULTADO
        m_cand_64 <<= 1;

        //PASSO 3 DESLOQUE O REGISTRADOR MULTIPLICADOR 1 BIT A DIREITA
        //O OPERADOR >>= DESLOCA OS BITS PARA A DIREITA EXPONDO O PROXIMO BIT A SER TESTADO
        multiplicador >>= 1;
    }
    return produto;
}

//FUNCAO PRINCIPAL PARA DEMONSTRAR O USO
int main(){
    uint32_t a = 12; // EM BINARIO: 00...1100
    uint32_t b = 5; // EM BINARIO : 00...0101

    uint64_t resultado = multiplicacao_binaria(a,b);

    printf("MULTIPLICANDO %u por %u\n", a, b);
    printf("O RESULTADO EH: %llu\n", (unsigned long long) resultado); //O RESULTADO ESPERADO EH 60

    printf("\n--- OUTRO EXEMPLO ---\n");
    uint32_t c = 1500;
    uint32_t d = 10000;

    resultado = multiplicacao_binaria(c,d);
    printf("MULTIPLICANDO %u por %u\n", c, d);
    printf("O RESULTADO EH : %llu\n", (unsigned long long)resultado); //O RESULTADO ESPERADO EH 15000000

    return 0;
}
/*

Como o Código Corresponde ao Diagrama:
uint64_t produto = 0;: Corresponde à caixa "Produto" e à inicialização.

uint64_t m_cand_64 = multiplicando;: Representa o registrador "Multiplicando".

uint32_t multiplicador: Representa o registrador "Multiplicador".

if (multiplicador & 1): É o "Teste de controle" que verifica o bit do multiplicador.

produto += m_cand_64;: É a "Unidade aritmética lógica" realizando a soma.

m_cand_64 <<= 1;: É a operação "Deslocamento à esquerda".

multiplicador >>= 1;: É a operação "Deslocamento à direita".

for (int i = 0; i < 32; i++): Garante que o ciclo se repita 32 vezes, como indicado na condição "32ª repetição?".

*/