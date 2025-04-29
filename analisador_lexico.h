#ifndef ANALISADOR_LEXICO_H
#define ANALISADOR_LEXICO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEXEMA 100
#define MAX_TOKEN_NAME 50
#define FIM_DE_ARQUIVO 9


typedef struct EntradaTabela {
    int token;
    char lexema[MAX_LEXEMA];
    char token_name[MAX_TOKEN_NAME];
    int linha;
    struct EntradaTabela *prox;
} EntradaTabela;

extern EntradaTabela *tabelaSimbolos;

extern FILE *arquivo;
extern int linha;
extern int coluna;


char ler_caractere();
void volta_caractere(char c);
void gravar_token(int token, const char *lexema, const char *token_name);
int analex();
int e_palavra_reservada(const char *lexema, char *token_name);
void imprimir_tabela_simbolos();
void liberar_tabela_simbolos();

#endif