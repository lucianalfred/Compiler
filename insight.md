# Análise Léxica para C++ - Projeto de Compiladores

## Visão Geral do Projeto

Você precisa desenvolver um analisador léxico em C para um subconjunto da linguagem C++. O analisador deve ler um arquivo fonte, identificar tokens válidos usando Autômatos Finitos Determinísticos (AFD) e armazenar os tokens e lexemas em uma tabela de símbolos.

## Componentes Principais

### 1. Estruturas Básicas

```c
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEXEMA 100

// Definição dos tokens
#define PALAVRA_RESERVADA 1
#define IDENTIFICADOR 2
#define NUMERO_INTEIRO 3
#define NUMERO_REAL 4
#define OPERADOR_RELACIONAL 5
#define SIMBOLO_ESPECIAL 6
#define PONTUACAO 7
#define OPERADOR_ARITMETICO 8
#define FIM_DE_ARQUIVO 9

// Tabela de símbolos
typedef struct {
    int token;
    char lexema[MAX_LEXEMA];
} EntradaTabelaSimbolos;

EntradaTabelaSimbolos tabelaSimbolos[1000];
int indiceTabela = 0;
```

### 2. Função ler_caractere()

```c
FILE *arquivoFonte;
int linha = 1, coluna = 1;

char ler_caractere() {
    char c = fgetc(arquivoFonte);
    if (c == '\n') {
        linha++;
        coluna = 1;
    } else {
        coluna++;
    }
    return c;
}
```

### 3. Função volta_caractere()

```c
void volta_caractere(char c) {
    ungetc(c, arquivoFonte);
    coluna--;
    if (c == '\n') {
        linha--;
    }
}
```

### 4. Função gravar_token_lexema()

```c
void gravar_token_lexema(int token, const char *lexema) {
    if (indiceTabela < 1000) {
        tabelaSimbolos[indiceTabela].token = token;
        strcpy(tabelaSimbolos[indiceTabela].lexema, lexema);
        indiceTabela++;
    }
}
```

### 5. Função principal analex()

```c
int analex() {
    char c, lexema[MAX_LEXEMA];
    int pos = 0;
    int estado = 0;
    
    while (1) {
        c = ler_caractere();
        
        switch (estado) {
            case 0:
                if (isalpha(c) || c == '_') {
                    lexema[pos++] = c;
                    estado = 1;
                } else if (isdigit(c)) {
                    lexema[pos++] = c;
                    estado = 3;
                } else if (isspace(c)) {
                    // Ignora espaços em branco
                } else {
                    // Outros casos (operadores, símbolos especiais)
                    // Implementar conforme AFD
                }
                break;
                
            case 1: // Identificador ou palavra reservada
                if (isalnum(c) || c == '_') {
                    lexema[pos++] = c;
                } else {
                    volta_caractere(c);
                    lexema[pos] = '\0';
                    pos = 0;
                    
                    // Verificar se é palavra reservada
                    if (eh_palavra_reservada(lexema)) {
                        gravar_token_lexema(PALAVRA_RESERVADA, lexema);
                    } else {
                        gravar_token_lexema(IDENTIFICADOR, lexema);
                    }
                    return 1;
                }
                break;
                
            // Outros estados do AFD...
        }
    }
}
```

## Autômatos Finitos Determinísticos (AFD)

Você precisará implementar AFDs para:
1. Identificadores e palavras reservadas
2. Números inteiros e reais
3. Operadores relacionais (==, !=, <=, >=, etc.)
4. Símbolos especiais e pontuação

## Manual do Programador (MP.DOC)

O manual deve conter:
1. Lista completa de tokens com códigos
2. Expressões regulares para cada categoria léxica
3. Diagramas de transição de estados (AFD)
4. Pseudo-código detalhado de cada função
5. Estrutura de dados utilizadas

## Manual do Usuário (MU.DOC)

O manual deve explicar:
1. Como compilar e executar o analisador
2. Formato do arquivo de entrada
3. Formato da saída (tabela de símbolos)
4. Exemplos de uso
5. Mensagens de erro e como interpretá-las

## Dicas de Implementação

1. Comece com um subconjunto pequeno da linguagem e vá expandindo
2. Teste cada AFD separadamente antes de integrar
3. Use constantes para os tokens para melhor legibilidade
4. Implemente tratamento de erros robusto
5. Documente cada função claramente

## Entrega Final

1. Código fonte completo (arquivo .c e .h)
2. Manual do Programador (mp.doc)
3. Manual do Usuário (mu.doc)
4. Mini-artigo científico explicando as decisões de projeto

Lembre-se que o trabalho é individual e cópias serão penalizadas. Boa sorte com seu analisador léxico!
