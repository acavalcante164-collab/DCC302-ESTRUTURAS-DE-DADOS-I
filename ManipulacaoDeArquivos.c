#include <stdio.h>
#include <string.h>

// Definimos a nossa estrutura
// Nota: Usamos arrays de tamanho fixo (char nome[50]) e não ponteiros (char *nome).
// Isto é CRUCIAL em ficheiros binários para garantir que os dados reais são guardados.
typedef struct {
    char nome[50];
    int nivel;
    float saude;
    int inventario[5]; // Exemplo: IDs dos itens
} Jogador;

// Função para guardar (Serialização)
void guardar_jogo(const char *nome_ficheiro, Jogador *j) {
    FILE *ficheiro = fopen(nome_ficheiro, "wb"); // "wb" = write binary (escrever binário)
    
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro para escrita!\n");
        return;
    }

    // A MÁGICA ACONTECE AQUI:
    // 1. Endereço da variável na memória (&j)
    // 2. Tamanho de UM elemento (sizeof(Jogador))
    // 3. Quantos elementos queremos guardar (1)
    // 4. O ponteiro do ficheiro
    fwrite(j, sizeof(Jogador), 1, ficheiro);

    fclose(ficheiro);
    printf("Jogo guardado com sucesso em '%s'!\n", nome_ficheiro);
}

// Função para carregar (Deserialização)
void carregar_jogo(const char *nome_ficheiro, Jogador *j) {
    FILE *ficheiro = fopen(nome_ficheiro, "rb"); // "rb" = read binary (ler binário)
    
    if (ficheiro == NULL) {
        printf("Ficheiro de jogo não encontrado!\n");
        return;
    }

    // A LEITURA É O INVERSO DA ESCRITA:
    // Lê os bits brutos do ficheiro e despeja diretamente na memória da struct
    fread(j, sizeof(Jogador), 1, ficheiro);

    fclose(ficheiro);
    printf("Jogo carregado!\n");
}

int main() {
    // 1. Criamos um jogador e definimos alguns dados
    Jogador player1;
    strcpy(player1.nome, "Heroi do C");
    player1.nivel = 5;
    player1.saude = 98.5;
    player1.inventario[0] = 10;
    player1.inventario[1] = 22;

    // 2. Guardamos no disco (vai criar um ficheiro ilegível para humanos)
    guardar_jogo("jogo.save", &player1);

    // 3. Vamos limpar a variável para provar que o carregamento funciona
    Jogador player_carregado; // Variável vazia (lixo de memória)
    
    // 4. Carregamos os dados do disco para a nova variável
    carregar_jogo("jogo.save", &player_carregado);

    // 5. Mostramos os dados recuperados
    printf("\n--- DADOS RECUPERADOS ---\n");
    printf("Nome: %s\n", player_carregado.nome);
    printf("Nivel: %d\n", player_carregado.nivel);
    printf("Saude: %.1f\n", player_carregado.saude);
    printf("Item 1: %d\n", player_carregado.inventario[0]);

    return 0;
}