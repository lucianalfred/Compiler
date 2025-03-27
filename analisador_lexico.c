#include "analisador_lexico.h"

// Implementação das funções
char ler_caractere() {
    char c = fgetc(arquivo);
    if (c == EOF) {
        return EOF;
    }
    if (c == '\n') {
        linha++;
        coluna = 1;
    } else {
        coluna++;
    }
    return c;
}

void volta_caractere(char c) {
    if (c == EOF) return;
    ungetc(c, arquivo);
    coluna--;
    if (c == '\n') {
        linha--;
    }
}

void gravar_token(int token, const char *lexema) {
    if (indiceTabela < 1000) {
        tabelaSimbolos[indiceTabela].token = token;
        strcpy(tabelaSimbolos[indiceTabela].lexema, lexema);
        indiceTabela++;
    }
}

int e_palavra_reservada(const char *lexema) {
    const char *palavras_reservadas[] = {
        "if", "else", "while", "for", "int", "float", "char", "return", NULL
    };

    for (int i = 0; palavras_reservadas[i] != NULL; i++) {
        if (strcmp(lexema, palavras_reservadas[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void imprimir_tabela_simbolos() {
    printf("Tabela de Símbolos:\n");
    printf("Token\t\tLexema\n");
    printf("----------------------------\n");
    for (int i = 0; i < indiceTabela; i++) {
        printf("%d\t\t%s\n", tabelaSimbolos[i].token, tabelaSimbolos[i].lexema);
    }
}

int analex() {
    char c, lexema[MAX_LEXEMA];
    int pos = 0;
    int estado = 0;

    while (1) {
        c = ler_caractere();

        if (c == EOF) {
            gravar_token(FIM_DE_ARQUIVO, "EOF");
            return FIM_DE_ARQUIVO;
        }

        switch (estado) {
            case 0:
                if (isalpha(c) || c == '_') {
                    lexema[pos++] = c;
                    estado = 1;
                } else if (isdigit(c)) {
                    lexema[pos++] = c;
                    estado = 3;
                } else if (isspace(c)) {
                    // Ignora espaços
                } else {
                    lexema[pos++] = c;
                    lexema[pos] = '\0';
                    gravar_token(CARACTER_ESPECIAL, lexema);
                    pos = 0;
                    return CARACTER_ESPECIAL;
                }
                break;

            case 1:
                if (isalnum(c) || c == '_') {
                    lexema[pos++] = c;
                } else {
                    volta_caractere(c);
                    lexema[pos] = '\0';
                    pos = 0;

                    if (e_palavra_reservada(lexema)) {
                        gravar_token(PALAVRA_RESERVADA, lexema);
                        return PALAVRA_RESERVADA;
                    } else {
                        gravar_token(IDENTIFICADOR, lexema);
                        return IDENTIFICADOR;
                    }
                }
                break;

            case 3:
                if (isdigit(c)) {
                    lexema[pos++] = c;
                } else {
                    volta_caractere(c);
                    lexema[pos] = '\0';
                    pos = 0;
                    gravar_token(NUMERO_INTEIRO, lexema);
                    return NUMERO_INTEIRO;
                }
                break;
        }
    }
}