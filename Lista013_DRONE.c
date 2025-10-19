#include <stdio.h>
#include <stdlib.h>
#include <string.h> //NECESSARIO PARA "strcpy"
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#define PAUSA_SEGUNDOS(s) Sleep(s * 1000)
#else
#include <unistd.h>
#define PAUSA_SEGUNDOS(s) Sleep(s)
#endif

//PARAMETRO DA SIMULACAO
#define CAPACIDADE_DRONE 10
#define TOTAL_PASSOS_SIMULACAO 5
#define PROBABILIDADE_CHEGADA 60 //CHANCE (EM %) DE UM NOVO PEDIDO CHEGAR A CADA PASSO
#define TEMPO_PAUSA 1 //SEGUNDO DE PAUSA ENTRE OS PASSOS

//DEFINICOES GLOBAIS
#define MAX_FILA 50 //TAMANHO MAXIMO DA FILA DE ESPERA

//--- ESTRUTURA DOS DADOS ---
typedef struct {
    int id;
    int peso;
    char endereco[50]; //ARRAY PARA ARMAZENAR O NOME DA RUA
} Pedido;

//FILA CIRCULAR PARA ARMAZENAR OS PEDIDOS
typedef struct {
    int comeco;
    int final;
    int quantidade;
    Pedido vetor[MAX_FILA]; //A FILA AGORA ARMAZENA "PEDIDO"
} Fila;

// --- FUNCOES DA FILA CIRCULAR (PARA PEDIDO) ---

Fila* cria_fila(){
    Fila* f = (Fila*)malloc(sizeof(Fila));
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
void inserir(Fila* f, Pedido p) {
    if (f->quantidade == MAX_FILA) {
        printf("AVISO: FILA DE PEDIDOS ESTA CHEIA!\n");
        return;
    }
    f->vetor[f->final] = p;
    f->final = (f->final + 1) % MAX_FILA;
    f->quantidade++;
}
Pedido retirar (Fila* f){
    Pedido p = f->vetor[f->comeco];
    f->comeco = (f->comeco + 1) % MAX_FILA;
    f->quantidade--;
    return p;
}
void libera_fila(Fila* f){
    free(f);
}
//FUNCAO PARA EXIBIR O CONTEUDO DA FILA DE PEDIDOS 
void imprimir_fila(Fila* f){
    if (esta_vazia(f)){
        printf("[]\n");
        return;
    }
    printf("[\n");
    int i = f->comeco;
    for(int count = 0; count < f->quantidade; count++){
        printf("    ID %d - %dkg - %s\n", f->vetor[i].id, f->vetor[i].peso, f->vetor->endereco);
        i = (i + 1) % MAX_FILA;
    }
    printf("]\n");
}
// --- MOTOR DA SIMULACAO ---
int main(){
    //1. INICIALIZACAO
    srand(time(NULL)); // ESSENCIAL PARA GERAR NUMEROS ALEATORIOS

    Fila* fila_pedidos = cria_fila();

    //LISTA DE ENDERECO PARA GERAR PEDIDOS ALEATORIOS
    const char* ruas[] = {"Rua A", "Avenida B", "Praca C", "Travessa D", "Alameda E"};
    int num_ruas = 5;

    printf("--- SIMULACAO DE ENTREGA POR DRONE ---\n");
    printf("CAPACIDADE DO DRONE: %dkg\n", CAPACIDADE_DRONE);
    printf("-----------------------------------------\n");

    //2. LOOP PRINCIPAL DA SIMULACAO
    for(int passo = 1; passo <= TOTAL_PASSOS_SIMULACAO; passo++){
        printf("\n--- PASSO DE SIMULACAO %d ---\n", passo);

        //A. CHEGADA ALEATORIA DE NOVOS PEDIDOS
        if (rand() % 100 < PROBABILIDADE_CHEGADA){
            Pedido novo_pedido;
            novo_pedido.id = 100 + rand() % 900;
            novo_pedido.peso = 1 + rand() % 15;  //GERA PESO ENTRE 1kg e 15Kg
            strcpy(novo_pedido.endereco, ruas[rand() % num_ruas]);

            printf("NOVO PEDIDO RECEBIDO: ID %d, PESO %dkg, ENDERECO: %s\n", novo_pedido.id, novo_pedido.peso, novo_pedido.endereco);
            inserir(fila_pedidos, novo_pedido);
        }

        //B. EXIBICAO DO ESTADO DA FILA
        printf("\nFILA DE ENTREGAS:\n");
        imprimir_fila(fila_pedidos);

        //LOGICA DE ENTREGA DO DRONE
        if(!esta_vazia(fila_pedidos)){
            //PEGA O PROXIMO PEDIDO DA FILA PARA AVALIACAO
            Pedido proximo_pedido = retirar(fila_pedidos);

            printf("\nDRONE SAIU PARA ENTREGA DO PEDIDO %d.\n", proximo_pedido.id);
            PAUSA_SEGUNDOS(TEMPO_PAUSA);

            //VERIFICA SE O DRONE CONSEGUE CARREGAR O PEDIDO
            if (proximo_pedido.peso <= CAPACIDADE_DRONE){
                printf("PEDIDO %d ENTREGUE COM SUCESSO!\n", proximo_pedido.id);
            } else {
                printf("FALHA: PEDIDO %d (PESO %dkg) EXCEDE A CAPACIDADE DO DRONE (%dkg) E FOI RETORNADO.\n", proximo_pedido.id, proximo_pedido.peso, CAPACIDADE_DRONE);   
            }
            printf("DRONE RETORNOU A BASE.\n");
        } else {
            printf("\nNENHUM PEDIDO NA FILA. DRONE AGUARDANDO NA BASE.\n");
        }
        PAUSA_SEGUNDOS(TEMPO_PAUSA);
    }
    //3.FINALIZACAO
    printf("\n\n--- FIM DA SIMULACAO ---\n");
    libera_fila(fila_pedidos);

    return 0;
}
