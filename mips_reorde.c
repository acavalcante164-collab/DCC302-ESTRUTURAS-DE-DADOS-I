#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/*
Analisa uma lista de instruções.

Verifica dependências de dados (quem escreve em qual registrador).

Tenta reordenar usando um algoritmo "ganancioso" (Greedy): ele procura na lista de espera qualquer instrução que não dependa da instrução imediatamente anterior (para preencher o "slot de atraso" do Load).

Se encontrar, ele reagenda. Se todas as instruções restantes tiverem conflito, ele reporta "Impossível".

Explicação da Lógica
Detecção de Hazard: A função has_hazard verifica se a instrução anterior é um lw (Load) e se a instrução atual tenta ler (src1 ou src2) o registrador que o Load vai escrever (dest). Isso causaria um "Stall" no pipeline.

Algoritmo: Ele tenta preencher a nova lista linha por linha. Para cada linha, ele varre as instruções disponíveis. Se a próxima instrução natural causar conflito, ele "pula" ela e procura mais à frente alguém que não cause conflito (uma instrução independente). Se achar, ele a puxa para cima (reorganização).

Falha: Se todas as instruções restantes na lista dependerem da instrução anterior, o programa imprime "Impossível realocação", pois o hardware será obrigado a parar (Stall) de qualquer jeito.
*/

#define MAX_INSTR 20

// Tipos de Instrução para facilitar a análise
typedef enum { OP_R_TYPE, OP_LOAD, OP_STORE, OP_BRANCH, OP_OTHER } OpType;

// Estrutura para representar uma instrução MIPS simplificada
typedef struct {
    int id;                 // ID original para rastreamento
    char asm_str[50];       // String completa (ex: "lw $t0, 0($t1)")
    char opcode[10];        // ex: "lw", "add"
    OpType type;            // Tipo da operação
    char dest_reg[10];      // Registrador de destino (onde escreve) - ex: "$t0"
    char src_reg1[10];      // Fonte 1 (leitura) - ex: "$t1"
    char src_reg2[10];      // Fonte 2 (leitura) - ex: "$t2"
} Instruction;

// --- Funções Auxiliares ---

// Função simples para definir propriedades da instrução
// Em um compilador real, isso seria um parser complexo
void set_instr(Instruction *i, int id, char *asm_str, char *op, char *dest, char *src1, char *src2) {
    i->id = id;
    strcpy(i->asm_str, asm_str);
    strcpy(i->opcode, op);
    strcpy(i->dest_reg, dest);
    strcpy(i->src_reg1, src1);
    strcpy(i->src_reg2, src2);

    // Identifica o tipo
    if (strcmp(op, "lw") == 0) i->type = OP_LOAD;
    else if (strcmp(op, "sw") == 0) i->type = OP_STORE;
    else if (strcmp(op, "beq") == 0 || strcmp(op, "bne") == 0) i->type = OP_BRANCH;
    else i->type = OP_R_TYPE; // Assume R-type (add, sub) para simplificar
}

// Verifica se há dependência de dados (HAZARD)
// Focamos no LOAD-USE HAZARD: Se a instrução anterior é um LOAD e a atual usa o dado carregado.
// (Assumindo que o processador tem Forwarding para instruções R-Type comuns)
bool has_hazard(Instruction prev, Instruction curr) {
    // Se a anterior não escreve em nada, não há conflito de dados
    if (strlen(prev.dest_reg) == 0) return false;

    // Conflito Load-Use:
    // Se a anterior é LOAD e escreve num registrador que a atual LÊ
    if (prev.type == OP_LOAD) {
        if (strcmp(prev.dest_reg, curr.src_reg1) == 0 || 
            strcmp(prev.dest_reg, curr.src_reg2) == 0) {
            return true; // Hazard detectado!
        }
    }

    // Nota: Se não tivéssemos Forwarding, teríamos que checar R-Type também.
    // Mas o Load-Use é o que exige reordenação de software obrigatoriamente.
    return false;
}

int main() {
    Instruction input[MAX_INSTR];
    Instruction output[MAX_INSTR];
    bool used[MAX_INSTR] = {false};
    int count = 0;

    // ==========================================
    // DEFINA SUAS INSTRUÇÕES AQUI (Entrada)
    // ==========================================
    
    // Exemplo: Conflito de Load-Use ($t1)
    // 1. lw $t1, 0($t0)
    // 2. add $t2, $t1, $t3  <-- Depende de $t1 logo após lw (CONFLITO)
    // 3. sub $t4, $t5, $t6  <-- Independente (Candidata a subir)
    // 4. or $t7, $t1, $t8   <-- Depende de $t1 (OK se estiver longe do lw)

    // Formato: set_instr(&input[i], ID, "Assembly", "Op", "Dest", "Src1", "Src2");
    // Use "" se o registrador não existir na instrução.
    
    set_instr(&input[0], 1, "lw $t1, 0($t0)",    "lw",  "$t1", "$t0", "");
    set_instr(&input[1], 2, "add $t2, $t1, $t3", "add", "$t2", "$t1", "$t3");
    set_instr(&input[2], 3, "sub $t4, $t5, $t6", "sub", "$t4", "$t5", "$t6");
    set_instr(&input[3], 4, "or $t7, $t1, $t8",  "or",  "$t7", "$t1", "$t8");
    count = 4;

    printf("--- Ordem Original ---\n");
    for(int i=0; i<count; i++) printf("%d: %s\n", i+1, input[i].asm_str);
    printf("\nTentando reorganizar para evitar Stalls (Load-Use)...\n\n");

    // ==========================================
    // ALGORITMO DE REORDENAÇÃO
    // ==========================================
    
    int out_idx = 0;
    
    // O primeiro item sempre pode entrar (não tem anterior)
    // Vamos usar uma lógica de busca para preencher slot por slot
    
    // 'last_scheduled' começa vazia/dummy
    Instruction last_scheduled;
    strcpy(last_scheduled.opcode, "nop");
    strcpy(last_scheduled.dest_reg, "");
    last_scheduled.type = OP_OTHER;

    for (int i = 0; i < count; i++) {
        int best_candidate = -1;
        
        // Procura na lista de entrada um candidato válido que não tenha sido usado
        for (int j = 0; j < count; j++) {
            if (!used[j]) {
                // Se não houver conflito com a última agendada, é um candidato
                if (!has_hazard(last_scheduled, input[j])) {
                    best_candidate = j;
                    break; // Pega o primeiro válido que encontrar (preserva ordem original se possível)
                }
            }
        }

        // Se não encontrou ninguém sem conflito...
        if (best_candidate == -1) {
            printf("RESULTADO: Impossivel realocacao (Conflito inevitavel detectado).\n");
            printf("Falha ao tentar agendar instrução para o slot %d.\n", i+1);
            return 1;
        }

        // Agenda o candidato
        output[out_idx++] = input[best_candidate];
        used[best_candidate] = true;
        last_scheduled = input[best_candidate];
    }

    // ==========================================
    // RESULTADO
    // ==========================================
    printf("RESULTADO: Reorganizado com sucesso!\n");
    printf("--- Nova Ordem ---\n");
    for(int i=0; i<count; i++) {
        printf("%d: %s", i+1, output[i].asm_str);
        // Marcador visual para mostrar onde a mudança ocorreu
        if(output[i].id != input[i].id) printf("  <-- Realocado (Era #%d)", output[i].id);
        printf("\n");
    }

    return 0;
}