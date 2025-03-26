#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEXEMA 100

//Definicao dos Tokens
#define PALAVRA_RESERVADA 1
#define IDENTIFICADOR 2
#define NUMERO_INTEIRO 3
#define OPERADOR_RELACIONAL 5
#define CARACTER_ESPECIAL 6
#define PONTUACAO 7
#define OPERADOR_ARITMETICO 8
#define FIM_DE_ARQUIVO 9 


//Tabela de Simbolos
typedef struct{
    int token;
    char lexema[MAX_LEXEMA];
}EntradaTabela;

EntradaTabela tabelaSimbolos[1000];
int indiceTabela  = 0;


FILE *arquivo;
int linha = 1, coluna = 1;

//funcao ler caractere
char ler_caractere()
{
    char c = fgetc(arquivo);
    if(c == '\n')
    {
        linha++;
        coluna = 1;
    }else{
        coluna++;
    }
    return (c);
}

void volta_caractere(char c)
{
    ungetc(c, arquivo);
    coluna--;
    if(c == '\n')
    {
        linha--;
    }
}

void gravar_token(int token, const char *lexema)
{
    if (indiceTabela < 1000)
    {
        tabelaSimbolos[indiceTabela].token = token;
        strcpy(tabelaSimbolos[indiceTabela].lexema, lexema);
        indiceTabela++;
    }
}

