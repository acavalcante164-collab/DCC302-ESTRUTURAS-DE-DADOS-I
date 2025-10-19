/*
 DCC302 - ESTRUTURAS DE DADOS I - T01 (2025.2)
NOME: ALONSO FERNANDES CAVALANTE
MATRICULA: 2024005534

LISTA 04 - EXERCICIO DA AULA 04  08/10/2025 A 19/10/2025
*/

/*

DESCRIÇÃO:

Slide 31 - Aula 07 (Fila)

Uma empresa de logística inovadora está usando drones para fazer entregas em uma cidade. Como os drones possuem capacidade limitada de carga e autonomia de voo, eles devem retornar à base após cada entrega para recarregar e pegar a próxima carga. Para gerenciar as entregas de forma eficiente, a empresa utiliza uma fila circular para organizar os pedidos de entrega que chegam. Sua tarefa é implementar um sistema que simule o gerenciamento da fila de entregas e o controle dos drones. Para tanto, você deve:

i) organizar e processar as entregas deforma sequencial, respeitando a capacidade dos drones;
ii) Simular a chegada de novos pedidos de entrega e o retorno dos drones à base.

Cada drone suporta até 10 kg por viagem. Se o próximo pedido na fila ultrapassar o limite, ele deve esperar até que o drone volte e a fila deve avançar para o próximo pedido. Novos pedidos de entrega chegam de forma aleatória durante a simulação. Simule a chegada de novos pedidos com rand() para gerar o peso, o ID e um endereço fictício. Para tornar o programa mais interessante, implemente uma pausa entre as operações (use sleep() ou equivalente) para simular o tempo que os veículos levam para atravessar.

Exemplo de saída:

Novo pedido recebido: ID 101, Peso 5kg, Endereço: Rua A
Novo pedido recebido: ID 102, Peso 7kg, Endereço: Rua B
Novo pedido recebido: ID 103, Peso 4kg, Endereço: Rua C

Fila de entregas:
[ID 101 - 5kg - Rua A, ID 102 - 7kg - Rua B, ID 103 - 4kg - Rua C]

Drone saiu para entrega do pedido 101.
Pedido 101 entregue!

Drone retornou à base.

Drone saiu para entrega do pedido 102.
Pedido 102 não pode ser entregue (excede capacidade restante).

Drone saiu para entrega do pedido 103.
Pedido 103 entregue!

Drone retornou à base.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Necessário para strcpy
#include <time.h>

// FUNCAO SLEEP SER COMPATIVEL COM WINDOWS E LINUX/MACOS
#ifdef _WIN32
#include <windows.h>
#define PAUSA_SEGUNDOS(s) Sleep(s * 1000)
#else
#include <unistd.h>
#define PAUSA_SEGUNDOS(s) sleep(s)
#endif

// PARAMETROS DA SIMULACAO
#define CAPACIDADE_DRONE 10      // Capacidade máxima de peso do drone (em kg)
#define TOTAL_PASSOS_SIMULACAO 5
#define PROBABILIDADE_CHEGADA 60 // Chance (em %) de um novo pedido chegar a cada passo
#define TEMPO_PAUSA 1            // Segundos de pausa entre os passos

// DEFINICOES GLOBAIS
#define MAX_FILA 50 // Tamanho maximo da fila de espera

// --- ESTRUTURA DOS DADOS ---

// Estrutura para representar um Pedido
typedef struct {
    int id;
    int peso;
    char endereco[50]; // Alterado para char array para armazenar o nome da rua
} Pedido;

// Fila Circular para armazenar os Pedidos
typedef struct {
    int comeco;
    int final;
    int quantidade;
    Pedido vetor[MAX_FILA]; // A fila agora armazena 'Pedido'
} Fila;

// --- FUNÇÕES DA FILA CIRCULAR (adaptadas para 'Pedido') ---

Fila* cria_fila() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    if (f != NULL) {
        f->comeco = 0;
        f->final = 0;
        f->quantidade = 0;
    }
    return f;
}

int esta_vazia(Fila* f) {
    return (f->quantidade == 0);
}

void inserir(Fila* f, Pedido p) {
    if (f->quantidade == MAX_FILA) {
        printf("AVISO: Fila de pedidos esta cheia!\n");
        return;
    }
    f->vetor[f->final] = p;
    f->final = (f->final + 1) % MAX_FILA;
    f->quantidade++;
}

Pedido retirar(Fila* f) {
    Pedido p = f->vetor[f->comeco];
    f->comeco = (f->comeco + 1) % MAX_FILA;
    f->quantidade--;
    return p;
}

void libera_fila(Fila* f) {
    free(f);
}

// Função para exibir o conteúdo da fila de pedidos (com mais detalhes)
void imprimir_fila(Fila* f) {
    if (esta_vazia(f)) {
        printf("[]\n");
        return;
    }
    printf("[\n");
    int i = f->comeco;
    for (int count = 0; count < f->quantidade; count++) {
        printf("  ID %d - %dkg - %s\n", f->vetor[i].id, f->vetor[i].peso, f->vetor[i].endereco);
        i = (i + 1) % MAX_FILA;
    }
    printf("]\n");
}

// --- MOTOR DA SIMULAÇÃO ---
int main() {
    // 1. INICIALIZAÇÃO
    srand(time(NULL)); // Essencial para gerar números aleatórios

    Fila* fila_pedidos = cria_fila();
    
    // Lista de endereços para gerar pedidos aleatórios
    const char* ruas[] = {"Rua A", "Avenida B", "Praca C", "Travessa D", "Alameda E"};
    int num_ruas = 5;

    printf("--- SIMULACAO DE ENTREGA POR DRONE ---\n");
    printf("Capacidade do Drone: %dkg\n", CAPACIDADE_DRONE);
    printf("-----------------------------------------\n");

    // 2. LOOP PRINCIPAL DA SIMULAÇÃO
    for (int passo = 1; passo <= TOTAL_PASSOS_SIMULACAO; passo++) {
        printf("\n--- PASSO DE SIMULACAO %d ---\n", passo);

        // A. CHEGADA ALEATÓRIA DE NOVOS PEDIDOS
        if (rand() % 100 < PROBABILIDADE_CHEGADA) {
            Pedido novo_pedido;
            novo_pedido.id = 100 + rand() % 900;
            novo_pedido.peso = 1 + rand() % 15; // Gera peso entre 1kg e 15kg
            strcpy(novo_pedido.endereco, ruas[rand() % num_ruas]);

            printf("Novo pedido recebido: ID %d, Peso %dkg, Endereco: %s\n",
                   novo_pedido.id, novo_pedido.peso, novo_pedido.endereco);
            inserir(fila_pedidos, novo_pedido);
        }

        // B. EXIBIÇÃO DO ESTADO DA FILA
        printf("\nFila de entregas:\n");
        imprimir_fila(fila_pedidos);

        // C. LÓGICA DE ENTREGA DO DRONE
        if (!esta_vazia(fila_pedidos)) {
            // Pega o próximo pedido da fila para avaliação
            Pedido proximo_pedido = retirar(fila_pedidos);
            
            printf("\nDrone saiu para entrega do pedido %d.\n", proximo_pedido.id);
            PAUSA_SEGUNDOS(TEMPO_PAUSA);

            // Verifica se o drone consegue carregar o pedido
            if (proximo_pedido.peso <= CAPACIDADE_DRONE) {
                printf("Pedido %d entregue com sucesso!\n", proximo_pedido.id);
            } else {
                printf("Falha: Pedido %d (Peso: %dkg) excede a capacidade do drone (%dkg) e foi retornado.\n",
                       proximo_pedido.id, proximo_pedido.peso, CAPACIDADE_DRONE);
            }
            printf("Drone retornou a base.\n");

        } else {
            printf("\nNenhum pedido na fila. Drone aguardando na base.\n");
        }

        PAUSA_SEGUNDOS(TEMPO_PAUSA);
    }

    // 3. FINALIZAÇÃO
    printf("\n\n--- FIM DA SIMULACAO ---\n");
    libera_fila(fila_pedidos);

    return 0;
}