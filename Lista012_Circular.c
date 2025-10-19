#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // Para inicializar o rand()
#include <unistd.h> // Para a função sleep()

// --- CONSTANTES DA SIMULACAO (fáceis de alterar) ---
#define CAPACIDADE_PONTE 3     // Quantos carros cabem na ponte ao mesmo tempo
#define NUMERO_DE_PASSOS 30    // Quantos "segundos" a simulação vai durar
#define PROBABILIDADE_CHEGADA 40 // Chance (em %) de um novo carro chegar a cada passo

// --- DEFINICOES GLOBAIS ---
// Direções dos veículos
#define NORTE_SUL 0
#define SUL_NORTE 1
// Estados da ponte
#define LIVRE -1

// Estrutura para armazenar dados dos veiculos (completa)
typedef struct {
    int identificacao;
    int direcao; // 0 para NORTE_SUL, 1 para SUL_NORTE
} Veiculo;

// --- IMPLEMENTACAO DA FILA DE VEICULOS (adaptada do seu código) ---
// Tamanho máximo das filas de espera
#define MAX_FILA 50

typedef struct fila {
    int comeco;
    int final;
    int quantidade;
    Veiculo VETOR[MAX_FILA];
} Fila;

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

int inserir(Fila* f, Veiculo v) {
    if (f->quantidade == MAX_FILA) return 0; // Fila cheia
    f->VETOR[f->final] = v;
    f->final = (f->final + 1) % MAX_FILA;
    f->quantidade++;
    return 1;
}

Veiculo retirar(Fila* f) {
    Veiculo v = f->VETOR[f->comeco];
    f->comeco = (f->comeco + 1) % MAX_FILA;
    f->quantidade--;
    return v;
}

void liberaFila(Fila* f) {
    free(f);
}

// Função para imprimir uma fila de veículos
void imprimir_fila(Fila* f, const char* nome_fila) {
    printf("%s: [ ", nome_fila);
    if (!esta_vazia(f)) {
        int i = f->comeco;
        for (int count = 0; count < f->quantidade; count++) {
            printf("%d ", f->VETOR[i].identificacao);
            i = (i + 1) % MAX_FILA;
        }
    }
    printf("]\n");
}

// --- FUNCAO PRINCIPAL DA SIMULACAO ---
int main() {
    // 1. INICIALIZACAO
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    Fila* fila_ns = cria_fila(); // Fila de veiculos Norte -> Sul
    Fila* fila_sn = cria_fila(); // Fila de veiculos Sul -> Norte

    Veiculo ponte[CAPACIDADE_PONTE];
    int veiculos_na_ponte = 0;
    int estado_ponte = LIVRE; // -1: Livre, 0: Norte->Sul, 1: Sul->Norte

    printf("--- INICIO DA SIMULACAO DA PONTE ---\n");
    printf("Capacidade da Ponte: %d veiculos\n", CAPACIDADE_PONTE);
    printf("--------------------------------------\n");

    // 2. LOOP PRINCIPAL DA SIMULACAO
    for (int tempo = 1; tempo <= NUMERO_DE_PASSOS; tempo++) {
        printf("\n--- TEMPO: %d ---\n", tempo);

        // A. SIMULAR A CHEGADA DE VEICULOS DE FORMA ALEATORIA
        if (rand() % 100 < PROBABILIDADE_CHEGADA) {
            Veiculo novo_veiculo;
            novo_veiculo.identificacao = 100 + rand() % 900; // ID de 100 a 999
            novo_veiculo.direcao = rand() % 2; // 0 ou 1

            if (novo_veiculo.direcao == NORTE_SUL) {
                inserir(fila_ns, novo_veiculo);
                printf("Chegada: Veiculo %d na fila Norte->Sul.\n", novo_veiculo.identificacao);
            } else {
                inserir(fila_sn, novo_veiculo);
                printf("Chegada: Veiculo %d na fila Sul->Norte.\n", novo_veiculo.identificacao);
            }
        }

        // B. GERENCIAR SAIDA DA PONTE (simples: 1 carro sai por passo de tempo)
        if (veiculos_na_ponte > 0) {
            // Para simplificar, consideramos que o veículo líder sai
            printf("Saida: Veiculo %d concluiu a travessia.\n", ponte[0].identificacao);
            // Move os outros veículos para frente na ponte
            for(int i = 0; i < veiculos_na_ponte - 1; i++){
                ponte[i] = ponte[i+1];
            }
            veiculos_na_ponte--;

            // Se a ponte ficou vazia, ela está livre
            if (veiculos_na_ponte == 0) {
                estado_ponte = LIVRE;
                printf("Ponte ficou LIVRE.\n");
            }
        }

        // C. GERENCIAR ENTRADA NA PONTE
        if (veiculos_na_ponte < CAPACIDADE_PONTE) {
            // Se a ponte está livre, decide quem entra (o primeiro que chegar)
            if (estado_ponte == LIVRE) {
                if (!esta_vazia(fila_ns)) {
                    estado_ponte = NORTE_SUL;
                } else if (!esta_vazia(fila_sn)) {
                    estado_ponte = SUL_NORTE;
                }
            }

            // Se a ponte está no sentido Norte->Sul, tenta adicionar mais um carro dessa fila
            if (estado_ponte == NORTE_SUL && !esta_vazia(fila_ns)) {
                Veiculo v = retirar(fila_ns);
                ponte[veiculos_na_ponte++] = v;
                printf("Entrada: Veiculo %d entrou na ponte (Norte->Sul).\n", v.identificacao);
            }
            // Se a ponte está no sentido Sul->Norte, tenta adicionar mais um carro dessa fila
            else if (estado_ponte == SUL_NORTE && !esta_vazia(fila_sn)) {
                Veiculo v = retirar(fila_sn);
                ponte[veiculos_na_ponte++] = v;
                printf("Entrada: Veiculo %d entrou na ponte (Sul->Norte).\n", v.identificacao);
            }
        }

        // D. EXIBIR O ESTADO ATUAL
        printf("\n>>> ESTADO ATUAL:\n");
        imprimir_fila(fila_ns, "Fila Norte->Sul");

        printf("Ponte        : [ ");
        if (veiculos_na_ponte > 0) {
             for(int i = 0; i < veiculos_na_ponte; i++){
                printf("%d ", ponte[i].identificacao);
            }
            printf("] (%s)\n", (estado_ponte == NORTE_SUL) ? "Sentido Norte->Sul" : "Sentido Sul->Norte");
        } else {
            printf("] (LIVRE)\n");
        }

        imprimir_fila(fila_sn, "Fila Sul->Norte");
        printf("--------------------------------------");

        sleep(1); // Pausa por 1 segundo para poder acompanhar a simulação
    }

    // 3. LIMPEZA FINAL
    printf("\n\n--- FIM DA SIMULACAO ---\n");
    liberaFila(fila_ns);
    liberaFila(fila_sn);

    return 0;
}