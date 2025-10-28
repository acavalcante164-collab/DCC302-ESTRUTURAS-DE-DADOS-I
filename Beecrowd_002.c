#include <stdio.h>
#include <stdlib.h>

// Tipo de dados para armazenar as dimensões de um presente
typedef struct {
    int a, b, c;
} Present;

// Tipo de dados para uma orientação específica (altura, largura, profundidade)
typedef struct {
    int h, w, d;
} Orientation;

// Tabela DP: dp[i][j] = altura máxima da pilha 1..i, com presente i na orientação j
// Usamos long long para garantir que a soma das alturas não estoure
long long dp[100005][3];

// Array para armazenar os N presentes
Present presents[100005];

// Função auxiliar para encontrar o máximo de dois long longs
long long max(long long a, long long b) {
    return (a > b) ? a : b;
}

// Retorna a orientação 'k' (0, 1, ou 2) para um dado presente 'p'
Orientation get_orientation(Present p, int k) {
    Orientation o;
    if (k == 0) {       // Altura A, Base B x C
        o.h = p.a; o.w = p.b; o.d = p.c;
    } else if (k == 1) { // Altura B, Base A x C
        o.h = p.b; o.w = p.a; o.d = p.c;
    } else {             // Altura C, Base A x B
        o.h = p.c; o.w = p.a; o.d = p.b;
    }
    return o;
}

// Verifica se a base2 (w2, d2) cabe na base1 (w1, d1), permitindo rotação
int can_fit(int w1, int d1, int w2, int d2) {
    return (w2 <= w1 && d2 <= d1) || (w2 <= d1 && d2 <= w1);
}

int main() {
    int N;
    // Loop para ler múltiplos casos de teste
    while (scanf("%d", &N) == 1) {
        
        // Lê as dimensões dos N presentes
        for (int i = 0; i < N; i++) {
            scanf("%d %d %d", &presents[i].a, &presents[i].b, &presents[i].c);
        }

        // --- Caso Base (i = 0): Primeiro presente no chão ---
        // Inicializa a tabela DP com 0 para este caso de teste
        for (int i = 0; i < N; i++) {
            dp[i][0] = 0;
            dp[i][1] = 0;
            dp[i][2] = 0;
        }

        dp[0][0] = presents[0].a;
        dp[0][1] = presents[0].b;
        dp[0][2] = presents[0].c;

        // --- Transição da DP (para i de 1 até N-1) ---
        for (int i = 1; i < N; i++) {
            // Para cada orientação 'j' do presente ATUAL 'i'
            for (int j = 0; j < 3; j++) {
                Orientation current_o = get_orientation(presents[i], j);
                
                // Para cada orientação 'k' do presente ANTERIOR 'i-1'
                for (int k = 0; k < 3; k++) {
                    long long prev_height = dp[i-1][k];
                    
                    // Se o estado anterior for 0, é impossível, pule
                    if (prev_height == 0) {
                        continue;
                    }
                    
                    Orientation prev_o = get_orientation(presents[i-1], k);
                    
                    // Verifica se a base atual cabe na base anterior
                    if (can_fit(prev_o.w, prev_o.d, current_o.w, current_o.d)) {
                        long long new_height = prev_height + current_o.h;
                        dp[i][j] = max(dp[i][j], new_height);
                    }
                }
            }
        }

        // --- Resultado Final ---
        // Encontra a altura máxima entre as 3 orientações do último presente (N-1)
        long long max_height = 0;
        max_height = max(dp[N-1][0], dp[N-1][1]);
        max_height = max(max_height, dp[N-1][2]);

        // Se a altura máxima for 0, significa que foi impossível empilhar
        if (max_height == 0) {
            printf("-1\n");
        } else {
            printf("%lld\n", max_height);
        }
    }
    return 0;
}