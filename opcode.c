#include <stdio.h>

// Definição da Struct ---
typedef struct {
    int RegWrite;
    int MemRead;
    int MemWrite;
    int ALUSrc;
    int Branch;
    int MemtoReg;
    int RegDst;
    int ALUOp; // 2 bits
} ControlSignals;

// Hardware simulado (variáveis globais) ---
int estadoAtual = 0; // Guarda o estado da FSM
int pc = 0;          // Program Counter
int instrucao_atual = 0; // Instruction Register (IR)
int running = 1;     // Flag para parar o simulador

// --- Memória de Instruções (Nosso Programa) ---
// Vamos simular um programa com 3 instruções:
// 0: add $t1, $t2, $t3 (Opcode 0x00, Tipo-R)
// 1: lw $t0, 0($t0)    (Opcode 0x23, Load Word)
// 2: HALT (instrução inválida para parar)
int instruction_memory[] = {
    0x014B4820, // add $t1, $t2, $t3
    0x8D080000, // lw $t0, 0($t0)
    0xFFFFFFFF  // "HALT" - Sinal para parar
};

// --- Nossos Estados da FSM (como você tinha) ---
#define ESTADO_BUSCA 0
#define ESTADO_DECODE 1
#define ESTADO_MEM_ADDR 2 // Para lw/sw
#define ESTADO_MEM_READ 3 // Para lw
#define ESTADO_MEM_WRITE_BACK 4 // Para lw
#define ESTADO_EXEC_RTYPE 5 // Para Tipo-R
#define ESTADO_RTYPE_WRITE_BACK 6 // Para Tipo-R
#define ESTADO_HALT 99 // Estado de parada

// --- Função para zerar os sinais ---
// É crucial zerar os sinais a cada novo ciclo!
void reset_signals(ControlSignals* signals) {
    signals->RegWrite = 0;
    signals->MemRead  = 0;
    signals->MemWrite = 0;
    signals->ALUSrc   = 0;
    signals->Branch   = 0;
    signals->MemtoReg = 0;
    signals->RegDst   = 0;
    signals->ALUOp    = 0;
}

// --- Função para printar (como você tinha) ---
void print_signals(ControlSignals* signals) {
    printf("--- Sinais de Controle (Flegs) ---\n");
    printf("  RegWrite: %d   MemRead: %d   MemWrite: %d\n", signals->RegWrite, signals->MemRead, signals->MemWrite);
    printf("  ALUSrc:   %d   Branch:  %d   MemtoReg: %d\n", signals->ALUSrc, signals->Branch, signals->MemtoReg);
    printf("  RegDst:   %d   ALUOp:   %d\n", signals->RegDst, signals->ALUOp);
    printf("----------------------------------\n");
}

// --- A Unidade de Controle FSM (Atualizada) ---
// Agora ela também simula a ação do Datapath (buscar PC)
void Multiciclo_ControlUnit(ControlSignals* signals) {
    
    // Zera todos os sinais no início do ciclo
    reset_signals(signals);
    
    // Pega o opcode da instrução ARMAZENADA (exceto no estado de busca)
    int opcode = (instrucao_atual >> 26) & 0x3F;

    // O switch da Máquina de Estados Finitos
    switch (estadoAtual) {
        
        case ESTADO_BUSCA:
            printf("Estado: BUSCA\n");
            // 1. Sinais: Ler memória (de instrução), usar ULA para PC+4
            signals->MemRead = 1;
            signals->ALUSrc = 0;
            
            // 2. Ação do Datapath (simulada):
            instrucao_atual = instruction_memory[pc]; // IR = Mem[PC]
            pc = pc + 1; // PC = PC + 4 (aqui simplificado para +1)
            printf("  Acao: Buscando instrucao 0x%X do PC=%d\n", instrucao_atual, pc-1);
            
            // 3. Próximo estado:
            if (instrucao_atual == 0xFFFFFFFF) {
                estadoAtual = ESTADO_HALT;
            } else {
                estadoAtual = ESTADO_DECODE;
            }
            break;
            
        case ESTADO_DECODE:
            printf("Estado: DECODE (Analisando Opcode 0x%X)\n", opcode);
            // 1. Sinais: Nenhum sinal principal
            
            // 2. Próximo estado (depende do opcode!)
            switch (opcode) {
                case 0x00: // Tipo-R (O "tipo 0" que você mencionou!)
                    estadoAtual = ESTADO_EXEC_RTYPE;
                    break;
                case 0x23: // lw
                    estadoAtual = ESTADO_MEM_ADDR;
                    break;
                // case 0x2B: // sw
                // case 0x04: // beq
                default:
                    printf("  Erro: Opcode 0x%X nao suportado!\n", opcode);
                    estadoAtual = ESTADO_BUSCA; // Volta ao início
                    break;
            }
            break;

        case ESTADO_EXEC_RTYPE:
            printf("Estado: EXEC_RTYPE\n");
            // 1. Sinais: ULA usa 2 registradores, operação Tipo-R
            signals->ALUSrc = 0;
            signals->ALUOp = 2; // "10"
            // 2. Próximo estado:
            estadoAtual = ESTADO_RTYPE_WRITE_BACK;
            break;

        case ESTADO_RTYPE_WRITE_BACK:
            printf("Estado: RTYPE_WRITE_BACK\n");
            // 1. Sinais: Escrever no registrador, dado vem da ULA, no registrador 'rd'
            signals->RegWrite = 1;
            signals->MemtoReg = 0;
            signals->RegDst = 1;
            // 2. Próximo estado:
            estadoAtual = ESTADO_BUSCA; // Fim da instrução
            break;
            
        case ESTADO_MEM_ADDR: // Para lw/sw
            printf("Estado: MEM_ADDR (lw/sw)\n");
            // 1. Sinais: ULA usa imediato, operação de SOMA
            signals->ALUSrc = 1;
            signals->ALUOp = 0; // "00"
            // 2. Próximo estado:
            estadoAtual = ESTADO_MEM_READ; // Assumindo lw
            break;

        case ESTADO_MEM_READ: // Apenas para lw
            printf("Estado: MEM_READ (lw)\n");
            // 1. Sinais: Ler da memória de *dados*
            signals->MemRead = 1;
            // 2. Próximo estado:
            estadoAtual = ESTADO_MEM_WRITE_BACK;
            break;

        case ESTADO_MEM_WRITE_BACK: // Apenas para lw
            printf("Estado: MEM_WRITE_BACK (lw)\n");
            // 1. Sinais: Escrever no registrador, dado vem da MEMÓRIA, no registrador 'rt'
            signals->RegWrite = 1;
            signals->MemtoReg = 1;
            signals->RegDst = 0;
            // 2. Próximo estado:
            estadoAtual = ESTADO_BUSCA; // Fim da instrução
            break;

        case ESTADO_HALT:
            printf("Estado: HALT. Simulacao terminada.\n");
            running = 0; // Para o loop principal
            break;
    }
}

// --- O Loop Principal do Simulador ---
int main() {
    int ciclo = 1;
    ControlSignals sinais; // Nossas "flegs"

    while (running) {
        printf("\n=== CICLO DE CLOCK: %d ===\n", ciclo);
        
        // A FSM decide os sinais E o próximo estado
        Multiciclo_ControlUnit(&sinais);
        
        // Printa os sinais para este ciclo
        print_signals(&sinais); 
        
        ciclo++;
        if (ciclo > 20) { // Limite de segurança
            printf("Limite de ciclos atingido!\n");
            running = 0;
        }
    }
    return 0;
}

/*
0x014B4820  → add $t1, $t2, $t3
0x8D080000  → lw $t0, 0($t0)
0xFFFFFFFF  → HALT


=== CICLO DE CLOCK: 1 ===
Estado: BUSCA
  Acao: Buscando instrucao 0x14B4820 do PC=0

--- Sinais de Controle ---
MemRead=1, ALUSrc=0 ...
----------------------------------
Estado: DECODE
  Opcode 0x0 -> Tipo-R

Estado: EXEC_RTYPE
Estado: RTYPE_WRITE_BACK

Estado: BUSCA
  Acao: Buscando instrucao 0x8D080000 do PC=1

Estado: DECODE
  Opcode 0x23 -> lw

Estado: MEM_ADDR
Estado: MEM_READ
Estado: MEM_WRITE_BACK
Estado: BUSCA

  Acao: Buscando instrucao 0xFFFFFFFF do PC=2
Estado: HALT. Simulacao terminada.


*/