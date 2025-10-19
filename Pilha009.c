#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*

Crie uma pilha vazia.

Percorra cada caractere da expressão, da esquerda para a direita.

Se o caractere for um (:

Empilhe-o.

Se o caractere for um ):

Verifique se a pilha está vazia. Se estiver, significa que um ) apareceu sem um ( correspondente. A expressão é inválida. Pare tudo.

Se a pilha não estiver vazia, desempilhe um (. (Isso "casa" o par de parênteses).

Ao final do percurso pela expressão:

Verifique se a pilha está vazia. Se estiver, todos os ( foram "casados" com um ). A expressão é válida.

Se a pilha não estiver vazia, significa que sobraram ( sem ) correspondentes. A expressão é inválida.

*/
#define MAX_PILHA 50 //DEFINE UM TAMANHO MAXIMO PAR A NOSSA PILHA

//PILHA DE CARACTERES
typedef struct {
    char VET[MAX_PILHA];
    int topo;
} Pilha;

//CRIAR E INICIALIZAR UMA NOVA PILHA
Pilha* cria_pilha(){
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if(p != NULL){
        p->topo = 0; //A PILHA COMECA FAZIA
    }
    return p;
}
//FUNCAO PARA VERIFICAR SE A PILHA ESTAH VAZIA
int pilha_vazia(Pilha* p){
    return p->topo == 0;
}
//FUNCAO PARA VERIFICAR SE A PILHA ESTAH CHEIA
int pilha_cheia(Pilha* p){
    return p->topo == MAX_PILHA;
}
//FUNCAO PARA EMPILHAR CARACTERE
void empilha(Pilha* p, char c){
    if(!pilha_cheia(p)){
        p->VET[p->topo] = c;
        p->topo++;
    } else {
        printf("Erro: Pilha cheia\n");
    }
}
//FUNCAO PARA DESEMPILHAR 
char desempilha(Pilha* p){
    if(!pilha_vazia(p)){
        p->topo--;
        return p->VET[p->topo];
    } else {
        //INDICA ERRO/PILHA VAZIA
        return '\0';
    }
    
} 
//FUNCAO PRINCIPAL PARA VERIFICACAO
int verifica_balanceamento(const char* expressao){
    int i;
    int tamanho =strlen(expressao);
    Pilha* minha_pilha = cria_pilha();

    //SE NAO CONSEGUIR CRIAR A PILHA, RETORNA ERRO
    if (minha_pilha == NULL){
        return 0; //FALHA
    }
    printf("Verificando expressao: \"%s\"\n", expressao);

    //1. PERCORRE CADA CARACTERE DA EXPRESSAO
    for (i = 0; i < tamanho; i++){
        char caractere_atual = expressao[i];
    
        //2. SE ENCONTROU UM '(' EMPILHA
        if (caractere_atual == '('){
            printf("  Encontrou '(', empilhando\n");
            empilha(minha_pilha, caractere_atual);
        }
        //3.se encontrou um ')' TRATA O FECHAMENTO
        else if (caractere_atual == ')'){
            printf("    Encontrou ')' tentando desempihar\n");
            //SE A PILHA ESTIVER VAZIA, HA UM ')' A MAIS
            if (pilha_vazia(minha_pilha)){
                printf("    Erro: Encontrou ')' mas a pilha esta vazia. expressão invalida");
                free(minha_pilha);
                return 0; //INVALIDO
            }
            //SE NAO ESTAH VAZIA DESEMPILHA PARA CASAR O PARENTESE
            else {
                desempilha(minha_pilha);
                printf("    Sucesso. par fechado");
            }
        }
    }
    //4. AO FINAL VERIFICA SE A PILHA FICOU VAZIA
    if (pilha_vazia(minha_pilha)){
        printf("Fim da expressao. Pilha esta vazia. Expressao valida\n\n");
        free(minha_pilha);
        return 1; //VALIDO
    } else {
        printf("Erro: fim da expressao, mas a pilha nao esta vazia");
        free(minha_pilha);
        return 0 ; //INVALIDO
    }
}
int main(){
    if (verifica_balanceamento("a + ( b * (c - d))")){
        //sucesso
    }
    if (verifica_balanceamento("((a+b)) * c")){
        //SUCESSO
    }
    if (verifica_balanceamento("(a+b(")){
        //falha
    }
    if (verifica_balanceamento(")a+b(")){
        //falha
    }
    if (verifica_balanceamento("(a+b))")){
        //falha
    }
    return 0;
}























