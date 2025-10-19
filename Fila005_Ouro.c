#include <stdio.h>
#include <stdlib.h>

#define N 7 // Tamanho do nosso labirinto 7x7, conforme a imagem

// Estrutura para armazenar uma coordenada (linha, coluna)
typedef struct {
    int linha;
    int coluna;
} Ponto;

// Sua estrutura de Fila, agora adaptada para armazenar Pontos
typedef struct fila {
    int comeco;
    int final;
    int quantidade;
    Ponto VETOR[N * N]; // A fila pode ter no máximo todos os pontos do labirinto
} Fila;
// Função para criar a fila
Fila* cria_fila() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    if (f != NULL) {
        f->comeco = 0;
        f->final = 0;
        f->quantidade = 0;
    }
    return f;
}

// Funções para verificar estado
int esta_vazia(Fila* f) {
    return (f->quantidade == 0);
}

// Função para inserir um Ponto na fila
int inserir(Fila* f, Ponto p) {
    if (f->quantidade == N * N) { // Fila cheia
        return 0;
    }
    f->VETOR[f->final] = p;
    f->final = (f->final + 1) % (N * N);
    f->quantidade++;
    return 1;
}

// Função para retirar um Ponto da fila
// É mais prático retornar o Ponto diretamente
Ponto retirar(Fila* f) {
    Ponto p = f->VETOR[f->comeco];
    f->comeco = (f->comeco + 1) % (N * N);
    f->quantidade--;
    return p;
}

// Libera a memória da fila
void liberaFila(Fila* f) {
    free(f);
}
// Função que percorre o labirinto e conta o ouro
int encontrarOuro(int labirinto[N][N], Ponto ponto_inicial) {
    int ouro_encontrado = 0;
    
    // 1. Matriz para marcar posições já visitadas
    int visitado[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            visitado[i][j] = 0; // Inicializa tudo como não visitado
        }
    }

    // 2. Cria a fila para a busca
    Fila* fila = cria_fila();

    // 3. Coloca na fila a posição inicial e marca como visitada
    // (Verificamos se o ponto inicial é válido antes)
    if (labirinto[ponto_inicial.linha][ponto_inicial.coluna] == -1) {
        printf("Erro: Ponto inicial e um obstaculo!\n");
        liberaFila(fila);
        return 0;
    }
    inserir(fila, ponto_inicial);
    visitado[ponto_inicial.linha][ponto_inicial.coluna] = 1;

    // 4. Enquanto a fila não está vazia...
    while (!esta_vazia(fila)) {
        // 4.1. Remove a posição do início da fila
        Ponto atual = retirar(fila);
        
        // 4.2. Verifica se encontrou ouro nesta posição
        if (labirinto[atual.linha][atual.coluna] == 1) {
            ouro_encontrado++;
            printf("Ouro encontrado na posicao (%d, %d)!\n", atual.linha, atual.coluna);
        }

        // 4.3. Para cada posição vizinha... (Cima, Baixo, Esquerda, Direita)
        int movimentos_linha[] = {-1, 1, 0, 0}; // Cima, Baixo
        int movimentos_coluna[] = {0, 0, -1, 1}; // Esquerda, Direita

        for (int i = 0; i < 4; i++) {
            int vizinho_linha = atual.linha + movimentos_linha[i];
            int vizinho_coluna = atual.coluna + movimentos_coluna[i];
            
            // 4.3.1. ...verifique se é acessível...
            // Condição 1: Está dentro dos limites do labirinto?
            if (vizinho_linha >= 0 && vizinho_linha < N && vizinho_coluna >= 0 && vizinho_coluna < N) {
                // Condição 2: Não é um obstáculo e ainda não foi visitada?
                if (labirinto[vizinho_linha][vizinho_coluna] != -1 && !visitado[vizinho_linha][vizinho_coluna]) {
                    
                    // 4.3.2. ...coloque na fila e marque como visitada.
                    visitado[vizinho_linha][vizinho_coluna] = 1;
                    Ponto vizinho = {vizinho_linha, vizinho_coluna};
                    inserir(fila, vizinho);
                }
            }
        }
    }

    liberaFila(fila); // Não se esqueça de liberar a memória
    return ouro_encontrado;
}
int main() {
    // Definindo o labirinto com base na imagem
    int labirinto[N][N] = {
        {-1, -1, -1, -1, -1, -1, -1},
        {-1,  0,  0, -1,  0, -1, -1},
        {-1,  0,  0,  0,  0,  1, -1}, // Ouro em (2, 5)
        {-1, -1, -1,  0,  0,  0, -1},
        {-1,  1, -1,  0, -1,  0, -1}, // Ouro em (4, 1)
        {-1,  0,  0,  0, -1,  0, -1},
        {-1, -1, -1, -1, -1, -1, -1}
    };
    
    // Ponto inicial da busca. Pode ser qualquer ponto livre.
    // Vamos começar perto de um dos ouros, em (1, 1).
    Ponto ponto_inicial = {1, 1}; 
    
    printf("Iniciando a busca por ouro no labirinto a partir de (%d, %d)...\n", 
            ponto_inicial.linha, ponto_inicial.coluna);
            
    int total_de_ouro = encontrarOuro(labirinto, ponto_inicial);
    
    printf("\nBusca finalizada!\n");
    printf("Total de ouro encontrado: %d\n", total_de_ouro);
    
    return 0;
}