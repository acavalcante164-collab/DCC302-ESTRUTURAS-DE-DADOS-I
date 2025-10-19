#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Para a função sleep() ser compatível com Windows e Linux/macOS
#ifdef _WIN32
#include <windows.h>
#define PAUSA_SEGUNDOS(s) Sleep(s * 1000)
#else
#include <unistd.h>
#define PAUSA_SEGUNDOS(s) sleep(s)
#endif

// --- PARÂMETROS DA SIMULAÇÃO (fáceis de alterar) ---
#define CAPACIDADE_PONTE 10
#define TOTAL_PASSOS_SIMULACAO 40
#define PROBABILIDADE_CHEGADA 50 // Chance (em %) de um carro novo chegar a cada passo
#define TEMPO_PAUSA 1            // Segundos de pausa entre os passos

// --- DEFINIÇÕES GLOBAIS ---
#define NORTE 0
#define SUL 1
#define MAX_FILA 50 // Tamanho máximo das filas de espera

// --- ESTRUTURAS DE DADOS ---

// Estrutura para cada veículo
typedef struct {
    int id;
    int direcao; // NORTE (0) ou SUL (1)
} Veiculo;

// Estrutura da Fila Circular de Veículos
typedef struct {
    int comeco;
    int final;
    int quantidade;
    Veiculo vetor[MAX_FILA];
} Fila;

// --- FUNÇÕES DA FILA CIRCULAR ---

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

void inserir(Fila* f, Veiculo v) {
    if (f->quantidade == MAX_FILA) {
        printf("AVISO: Fila de espera esta cheia!\n");
        return;
    }
    f->vetor[f->final] = v;
    f->final = (f->final + 1) % MAX_FILA;
    f->quantidade++;
}

Veiculo retirar(Fila* f) {
    Veiculo v = f->vetor[f->comeco];
    f->comeco = (f->comeco + 1) % MAX_FILA;
    f->quantidade--;
    return v;
}

void libera_fila(Fila* f) {
    free(f);
}

// Função para exibir o conteúdo de uma fila de espera
void imprimir_fila(Fila* f) {
    if (esta_vazia(f)) {
        printf("[]");
        return;
    }
    printf("[");
    int i = f->comeco;
    for (int count = 0; count < f->quantidade; count++) {
        printf("%d", f->vetor[i].id);
        if (count < f->quantidade - 1) {
            printf(", ");
        }
        i = (i + 1) % MAX_FILA;
    }
    printf("]");
}

// --- MOTOR DA SIMULAÇÃO ---

int main() {
    // 1. INICIALIZAÇÃO
    srand(time(NULL)); // Essencial para gerar números realmente aleatórios

    Fila* fila_norte = cria_fila(); // Fila para veículos indo para o Norte
    Fila* fila_sul = cria_fila();   // Fila para veículos indo para o Sul

    printf("--- SIMULACAO DE TRAFEGO EM PONTE DE MAO UNICA ---\n");
    printf("Capacidade da Ponte: %d veiculos por vez.\n", CAPACIDADE_PONTE);
    printf("--------------------------------------------------\n");
    PAUSA_SEGUNDOS(2);

    // 2. LOOP PRINCIPAL DA SIMULAÇÃO
    for (int passo = 1; passo <= TOTAL_PASSOS_SIMULACAO; passo++) {
        printf("\n\n--- PASSO %d ---\n", passo);

        // A. CHEGADA ALEATÓRIA DE VEÍCULOS
        if (rand() % 100 < PROBABILIDADE_CHEGADA) {
            Veiculo novo_veiculo;
            novo_veiculo.id = 100 + rand() % 900;
            novo_veiculo.direcao = rand() % 2; // 0 (NORTE) ou 1 (SUL)

            if (novo_veiculo.direcao == NORTE) {
                printf(">> Chegada: Veiculo %d chegou indo para o NORTE.\n", novo_veiculo.id);
                inserir(fila_norte, novo_veiculo);
            } else {
                printf(">> Chegada: Veiculo %d chegou indo para o SUL.\n", novo_veiculo.id);
                inserir(fila_sul, novo_veiculo);
            }
        }

        // B. EXIBIÇÃO DO ESTADO DAS FILAS DE ESPERA
        printf("FILAS DE ESPERA ATUAIS:\n");
        printf("  - Aguardando (NORTE): ");
        imprimir_fila(fila_norte);
        printf("\n");
        printf("  - Aguardando (SUL):   ");
        imprimir_fila(fila_sul);
        printf("\n\n");

        // C. LÓGICA DE TRAVESSIA DA PONTE
        // Decide qual direção tem prioridade (a fila mais longa)
        int direcao_da_vez = -1; // -1 significa que ninguém atravessa
        if (fila_norte->quantidade > fila_sul->quantidade && !esta_vazia(fila_norte)) {
            direcao_da_vez = NORTE;
        } else if (fila_sul->quantidade > 0) {
            direcao_da_vez = SUL;
        } else if (fila_norte->quantidade > 0) { // Caso de empate ou se a fila sul está vazia
             direcao_da_vez = NORTE;
        }

        // Se há veículos para atravessar, inicia o processo
        if (direcao_da_vez != -1) {
            printf("PONTE ABERTA NA DIRECAO: %s\n", (direcao_da_vez == NORTE) ? "NORTE" : "SUL");

            Fila* fila_da_vez = (direcao_da_vez == NORTE) ? fila_norte : fila_sul;
            
            // Calcula quantos veículos podem atravessar neste lote
            int veiculos_para_atravessar = fila_da_vez->quantidade;
            if (veiculos_para_atravessar > CAPACIDADE_PONTE) {
                veiculos_para_atravessar = CAPACIDADE_PONTE;
            }

            // Simula a travessia
            for (int i = 0; i < veiculos_para_atravessar; i++) {
                Veiculo v = retirar(fila_da_vez);
                printf("  <- Veiculo %d atravessou a ponte.\n", v.id);
                PAUSA_SEGUNDOS(TEMPO_PAUSA / 2); // Pausa menor para cada carro
            }
            printf("PONTE LIVRE.\n");
        } else {
            printf("Nenhum veiculo aguardando. Ponte permanece livre.\n");
        }
        
        PAUSA_SEGUNDOS(TEMPO_PAUSA);
    }

    // 3. FINALIZAÇÃO
    printf("\n\n--- FIM DA SIMULACAO ---\n");
    libera_fila(fila_norte);
    libera_fila(fila_sul);

    return 0;
}