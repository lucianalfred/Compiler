// analisador_semantico
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analisador_lexico.h"
#include "analisador_semantico.h"

//variaveis semanticas
int token_atual;
char nome_token_atual[MAX_TOKEN_NAME];
char lexema_atual[MAX_LEXEMA];

//

void consumir() {
    analex();
}


void erro(const char *esperado) {
    printf("Erro de sintaxe na linha %d: esperado '%s', encontrado '%s'\n",
           linha, esperado, nome_token_atual);
    exit(1);
}

void combinar(int esperado) {
    if (token_atual == esperado) {
        consumir();
    } else {
        erro("token esperado não encontrado");
    }
}

void tipo() {
    if (strcmp(nome_token_atual, "TOKEN_INT") == 0 ||
        strcmp(nome_token_atual, "TOKEN_FLOAT") == 0 ||
        strcmp(nome_token_atual, "TOKEN_CHAR") == 0) {
        consumir();
    } else {
        erro("tipo (int, float ou char)");
    }
}

void declaracao() {
    tipo();
    if (token_atual == TOKEN_IDENTIFICADOR) {
        consumir();
        if (strcmp(nome_token_atual, "TOKEN_SEMICOLON") == 0) {
            combinar(TOKEN_DELIMITADOR);
        } else {
            erro("ponto e vírgula");
        }
    } else {
        erro("identificador");
    }
}

void lista_de_declaracoes() {
    while (strcmp(nome_token_atual, "TOKEN_INT") == 0 ||
           strcmp(nome_token_atual, "TOKEN_FLOAT") == 0 ||
           strcmp(nome_token_atual, "TOKEN_CHAR") == 0) {
        declaracao();
    }
}

void programa() {
    consumir();  // inicializa primeiro token
    lista_de_declaracoes();

    if (token_atual != FIM_DE_ARQUIVO) {
        erro("fim do arquivo");
    } else {
        printf("Análise sintáctica concluída com sucesso.\n");
    }
}
