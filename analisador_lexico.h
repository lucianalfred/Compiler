#ifndef ANALISADOR_LEXICO_H
#define ANALISADOR_LEXICO_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEXEMA 100

//Definicao dos Tokens
#define PALAVRA_RESERVADA 1
#define IDENTIFICADOR 2
#define NUMERO_INTEIRO 3
#define OPERADOR_LOGICO 4
#define OPERADOR_RELACIONAL 5
#define CARACTER_ESPECIAL 6
#define PONTUACAO 7
#define OPERADOR_ARITMETICO 8
#define FIM_DE_ARQUIVO 9 

typedef struct {
    int token;
    char lexema[MAX_LEXEMA];
    int  linha;
} EntradaTabela;

//externas
extern EntradaTabela tabelaSimbolos[1000];
extern int indiceTabela;
extern FILE *arquivo;
extern int linha;
extern int coluna;

// Protótipos das funções
char ler_caractere();
void volta_caractere(char c);
void gravar_token(int token, const char *lexema);
int analex();
int e_palavra_reservada(const char *lexema);
void imprimir_tabela_simbolos();

#endif