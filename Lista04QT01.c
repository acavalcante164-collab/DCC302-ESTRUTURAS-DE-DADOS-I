/*
 DCC302 - ESTRUTURAS DE DADOS I - T01 (2025.2)
NOME: ALONSO FERNANDES CAVALANTE
MATRICULA: 2024005534

LISTA 04 - EXERCICIO DA AULA 04  08/10/2025 A 19/10/2025
*/

/*

DESCRIÇÃO:

Slide 31 - Aula 07 (Fila)

UMA PONTE ESTREITA, DE MÃO ÚNICA, CONECTA DUAS VILAS. POR QUESTÕES DE SEGURANÇA, A PONTE SÓ PERMITE A PASSAGEM DE VEÍCULOS EM UMA DIREÇÃO POR VEZ. ALÉM DISSO, A PONTE SÓ SUPORTA ATÉ 10 VEÍCULOS DE CADA VEZ. VEÍCULOS QUE CHEGAM QUANDO A PONTE JÁ ESTÁ CHEIA OU QUE ESTÃO INDO NA DIREÇÃO OPOSTA PRECISAM AGUARDAR SUA VEZ. SUA TAREFA É IMPLEMENTAR UM SISTEMA DE CONTROLE QUE GERENCIE O TRÁFEGO DE VEÍCULOS UTILIZANDO UMA FILA CIRCULAR. CADA VEÍCULO TEM UMA IDENTIFICAÇÃO ÚNICA E UMA DIREÇÃO DE TRÂNSITO (NORTE PARA A VILA NO NORTE OU SUL PARA A VILA NO SUL). 

O PROGRAMA DEVE SIMULAR A CHEGADA DE VEÍCULOS DE FORMA ALEATÓRIA (USE RAND() PARA GERAR A DIREÇÃO E A IDENTIFICAÇÃO DOS VEÍCULOS). EXIBA O ESTADO DA PONTE E DA FILA A CADA "PASSO" DA SIMULAÇÃO.

PARA TORNAR O PROGRAMA MAIS INTERESSANTE, IMPLEMENTE UMA PAUSA ENTRE AS OPERAÇÕES (USE SLEEP() OU EQUIVALENTE) PARA SIMULAR O TEMPO QUE OS VEÍCULOS LEVAM PARA ATRAVESSAR. 

EXEMPLO DE SAÍDA: 
PONTE ABERTA NA DIREÇÃO: NORTE 
VEÍCULO 101 CHEGOU INDO PARA NORTE 
VEÍCULO 102 CHEGOU INDO PARA SUL 
VEÍCULO 103 CHEGOU INDO PARA NORTE
VEÍCULO 104 CHEGOU INDO PARA NORTE

FILA ATUAL: 
[NORTE: 101, 103, 104] 
AGUARDANDO (SUL): 102 
VEÍCULO 101 ATRAVESSOU A PONTE. 
VEÍCULO 103 ATRAVESSOU A PONTE. 
VEÍCULO 104 ATRAVESSOU A PONTE. 
PONTE ABERTA NA DIREÇÃO: SUL VEÍCULO 102 ATRAVESSOU A PONTE.

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//FUNCAO SLEEP SER COMPATIVEL
#ifdef _WIN32
#include <windows.h>
#define PAUSA_SEGUNDOS(s) Sleep(s * 1000)
#else
#include <unistd.h>
#define PAUSA_SEGUNDOS(s) sleep(s)
#endif

//PARAMETROS DA SIMULACAO
#define CAPACIDADE_PONTO 10
#define TOTAL_PASSOS_SIMULACAO 30
#define PROBABILIDADE_CHEGADA 50 //CHANCE (EM 5) DE UM CARRO NOVO CHEGAR A CASA PASSO
#define TEMPO_PAUSA 1 //SEGUNDO DE PAUSA ENTRE OS PASSOS

//DEFINE GLOBAIS
#define NORTE 0
#define SUL 1
#define MAX_FILA 50 // TAMANHO MAXIMO DAS FILAS DE ESPERA

//ESTRUTURA DOS DADOS

//CADA VEICULO
typedef struct{
    int id;
    int direcao; //NORTE (0) OU SUL(1)
} Veiculo;

//FILA CIRCULAR
typedef struct {
    int comeco;
    int final;
    int quantidade;
    Veiculo vetor[MAX_FILA];
} Fila;
//PARA CIRCULAR
Fila* cria_fila(){
    Fila* f = (Fila*) malloc(sizeof(Fila));
    if(f != NULL){
        f->comeco = 0;
        f->final = 0;
        f->quantidade = 0;
    }
    return f;
}
int esta_vazia(Fila* f){
    return (f->quantidade == 0);
}
void inserir(Fila* f, Veiculo v){
    if(f->quantidade == MAX_FILA){
        printf("FILA DE ESPERA TA CHEIA\n");
        return;
    }
    f->vetor[f->final] = v;
    f->final = (f->final + 1) % MAX_FILA;
    f->quantidade++;
}
Veiculo retirar(Fila* f){
    Veiculo v = f->vetor[f->comeco];
    f->comeco = (f->comeco +1) % MAX_FILA;
    f->quantidade--;
    return v;
}
void libera_fila(Fila* f){
    free(f);
}
//EXIBIR O CONTEUDO DA FILA DE ESPERA
void imprimir_fila(Fila* f){
    if (esta_vazia(f)){
        printf("[]");
        return;
    }
    printf("[");
    int i = f->comeco;
    for(int count = 0; count < f->quantidade; count++){
        printf("%d", f->vetor[i].id);
        if (count < f->quantidade - 1){
            printf(", ");
        }
        i = (i + 1) % MAX_FILA;
    }
    printf("]");
}
//SIMULACAO PRINCIPAL
int main(){
    //INICIALIZACAO
    srand(time(NULL)); //NUMEROS ALEATORIOS

    Fila* fila_norte = cria_fila(); //FILA PARA VEICULOS INDO PARA O NORTE
    Fila* fila_sul = cria_fila(); //FILA PARA VEICULOS INDO PARA O SUL

    printf("--- PONTE MAO UNICA ---\n");
    printf("CAPACIDADE DA PONTE: %d VEICULOS POR VEZ.\n", CAPACIDADE_PONTO);
    printf("-------------------\n");
    PAUSA_SEGUNDOS(2);

    //LOOP PARA SIMULACAO
    for(int passo = 1; passo <= TOTAL_PASSOS_SIMULACAO; passo++){
        printf("\n\n--- PASSO %d---\n", passo);

        //"CHEGADA" ALEATORIA DE VEICULOS
        if(rand() % 100 < PROBABILIDADE_CHEGADA){
            Veiculo novo_veiculo;
            novo_veiculo.id = 100 + rand() % 900;
            novo_veiculo.direcao = rand() % 2; // 0(NORTE) OU 1(SUL)

            if (novo_veiculo.direcao == NORTE){
                printf(">> CHEGADA: VEICULO %d CHEGOU INDO PARA O NORTE.\n", novo_veiculo.id);
                inserir(fila_norte, novo_veiculo);
            } else {
                printf(">> CHEGADA: VEICULO %d CHEGOU INDO PARA O SUL.\n", novo_veiculo.id);
                inserir(fila_sul, novo_veiculo);
            }             
        }
        //ESTADO DAS FILAS DE ESPERA
        printf("FILAS DE ESPERA ATUAIS:\n");
        printf(" - AGUARDANDO (NORTE): ");
        imprimir_fila(fila_norte);
        printf("\n");
        printf(" - AGUARDANDO (SUL): ");
        imprimir_fila(fila_sul);
        printf("\n\n");

        //TRAVESSIA DA PONTO
        //DECIDE QUAL A DIRECAO TEM PRIORIDADE (A FILA MAIS LONGA)
        int direcao_da_vez = -1; //-1 SIGNIFICA QUE NINGUEM ATRAVESSA
        if(fila_norte->quantidade > fila_sul->quantidade && !esta_vazia(fila_norte)){
            direcao_da_vez = NORTE;
        } else if (fila_sul->quantidade > 0){
            direcao_da_vez = SUL;
        } else if (fila_norte->quantidade > 0){
            direcao_da_vez = NORTE; //EMPATE OU SUL VAZIA
        }
        //SE HA VEICULOS PARA ATRAVESSAR
        if (direcao_da_vez != -1){
            printf("PONTE ABERTA NA DIRECAO: %s\n", (direcao_da_vez == NORTE) ? "NORTE" : "SUL");

            Fila* fila_da_vez = (direcao_da_vez == NORTE) ? fila_norte : fila_sul;

            //CALCULA QUANTOS VEICULOS PODEM ATRAVESSAR NESTE LOCAL
            int veiculos_para_atravessar = fila_da_vez->quantidade;
            if (veiculos_para_atravessar > CAPACIDADE_PONTO){
                veiculos_para_atravessar = CAPACIDADE_PONTO;
            }
            //SIMULA TRAVESSIA
            for (int i = 0; i < veiculos_para_atravessar; i++){
                Veiculo v = retirar(fila_da_vez);
                printf("    <-VEICULO %d ATRAVESSOU A PONTE.\n", v.id);
                PAUSA_SEGUNDOS(TEMPO_PAUSA / 2); //PAUSA MENOR PARA CADA CARRO
            }
            printf("PONTE LIVRE.\n");
        } else {
            printf("NENHUM VEICULO AGUARDANDO. PONTE PERMANECE LIVRE.\n");
        }
        PAUSA_SEGUNDOS(TEMPO_PAUSA);
    }
    //FINALIZACAO
    printf("\n\n--- FIM DA SIMULACAO ---\n");
    libera_fila(fila_norte);
    libera_fila(fila_sul);

    return 0;
}
