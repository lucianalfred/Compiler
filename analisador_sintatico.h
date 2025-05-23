#ifndef ANALISADOR_SINTATICO_H
#define ANALISADOR_SINTATICO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//

extern int token_atual;
extern char nome_token_atual[MAX_TOKEN_NAME];
extern char lexema_atual[MAX_LEXEMA];


void erro(const char *esperado);
void combinar(int esperado);
void tipo();
void declaracao();
void lista_de_declaracoes();
void programa();

#endif