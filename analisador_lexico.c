#include "analisador_lexico.h"

EntradaTabela *tabelaSimbolos = NULL;
FILE *arquivo;
int linha = 1;
int coluna = 1;

char ler_caractere() {
    char c = fgetc(arquivo);
    if (c == '\n') {
        linha++;
        coluna = 1;
    } else {
        coluna++;
    }
    return c;
}

void volta_caractere(char c) {
    if (c != EOF) {
        ungetc(c, arquivo);
        coluna--;
        if (c == '\n') linha--;
    }
}

void gravar_token(int token, const char *lexema, const char *token_name) {
    EntradaTabela *novo = (EntradaTabela *) malloc(sizeof(EntradaTabela));
    novo->token = token;
    strcpy(novo->lexema, lexema);
    strcpy(novo->token_name, token_name);
    novo->linha = linha;
    novo->prox = tabelaSimbolos;
    tabelaSimbolos = novo;
}

int e_palavra_reservada(const char *lexema, char *token_name) {
    struct {
        const char *palavra;
        const char *token_name;
        int token_val;
    } palavras[] = {
        {"int", "TOKEN_INT", 1}, {"float", "TOKEN_FLOAT", 1},
        {"char", "TOKEN_CHAR", 1}, {"string", "TOKEN_STRING", 1},
        {"bool", "TOKEN_BOOL", 1}, {"void", "TOKEN_VOID", 1},
        {"if", "TOKEN_IF", 1}, {"else", "TOKEN_ELSE", 1},
        {"while", "TOKEN_WHILE", 1}, {"for", "TOKEN_FOR", 1},
        {"return", "TOKEN_RETURN", 1}, {"break", "TOKEN_BREAK", 1},
        {"continue", "TOKEN_CONTINUE", 1}, {"switch", "TOKEN_SWITCH", 1},
        {"case", "TOKEN_CASE", 1}, {"default", "TOKEN_DEFAULT", 1},
        {"do", "TOKEN_DO", 1}, {"class", "TOKEN_CLASS", 1},
        {"public", "TOKEN_PUBLIC", 1}, {"private", "TOKEN_PRIVATE", 1},
        {"protected", "TOKEN_PROTECTED", 1}, {"static", "TOKEN_STATIC", 1},
        {"const", "TOKEN_CONST", 1}, {"new", "TOKEN_NEW", 1},
        {"this", "TOKEN_THIS", 1}, {"null", "TOKEN_NULL", 1},
        {"true", "TOKEN_TRUE", 1}, {"false", "TOKEN_FALSE", 1},
        {NULL, NULL, 0}
    };

    for (int i = 0; palavras[i].palavra != NULL; i++) {
        if (strcmp(lexema, palavras[i].palavra) == 0) {
            strcpy(token_name, palavras[i].token_name);
            return palavras[i].token_val;
        }
    }
    return 0;
}

void imprimir_tabela_simbolos() {
    printf("Tabela de Símbolos:\n");
    printf("Token\t\tLexema\t\tLinha\n");
    printf("----------------------------------------\n");
    EntradaTabela *atual = tabelaSimbolos;
    while (atual) {
        printf("%s\t\t%s\t\t%d\n", atual->token_name, atual->lexema, atual->linha);
        atual = atual->prox;
    }
}

void liberar_tabela_simbolos() {
    EntradaTabela *atual = tabelaSimbolos;
    while (atual) {
        EntradaTabela *tmp = atual;
        atual = atual->prox;
        free(tmp);
    }
    tabelaSimbolos = NULL;
}

int analex() {
    char c, lexema[MAX_LEXEMA];
    int pos = 0;
    char token_name[MAX_TOKEN_NAME];

    while (1) {
        c = ler_caractere();

        if (c == EOF) {
            gravar_token(9, "EOF", "FIM_DE_ARQUIVO");
            return 9;
        }

        if (isspace(c)) continue;

        // Identificadores e palavras-chave
        if (isalpha(c) || c == '_') {
            lexema[pos++] = c;
            while (isalnum(c = ler_caractere()) || c == '_') {
                lexema[pos++] = c;
            }
            volta_caractere(c);
            lexema[pos] = '\0';
            pos = 0;

            if (e_palavra_reservada(lexema, token_name)) {
                gravar_token(1, lexema, token_name); // PALAVRA_RESERVADA
                return 1;
            } else {
                gravar_token(2, lexema, "TOKEN_IDENTIFIER"); // IDENTIFICADOR
                return 2;
            }
        }

        // Números inteiros ou ponto flutuante
        if (isdigit(c)) {
            lexema[pos++] = c;
            int ponto = 0;
            while (isdigit(c = ler_caractere()) || (c == '.' && !ponto)) {
                if (c == '.') ponto = 1;
                lexema[pos++] = c;
            }
            volta_caractere(c);
            lexema[pos] = '\0';
            pos = 0;

            if (ponto) {
                gravar_token(2, lexema, "TOKEN_FLOAT_LITERAL");
            } else {
                gravar_token(3, lexema, "TOKEN_INTEGER_LITERAL");
            }
            return 3;
        }

        // Literais de caractere
        if (c == '\'') {
            lexema[pos++] = c;
            c = ler_caractere();
            lexema[pos++] = c;
            c = ler_caractere();
            if (c == '\'') {
                lexema[pos++] = c;
                lexema[pos] = '\0';
                gravar_token(2, lexema, "TOKEN_CHAR_LITERAL");
                return 2;
            }
        }

        // Literais de string
        if (c == '"') {
            lexema[pos++] = c;
            while ((c = ler_caractere()) != '"' && c != EOF) {
                lexema[pos++] = c;
            }
            lexema[pos++] = '"';
            lexema[pos] = '\0';
            gravar_token(2, lexema, "TOKEN_STRING_LITERAL");
            return 2;
        }

        // Comentários
        if (c == '/') {
            char next = ler_caractere();
            if (next == '/') {
                // comentário de uma linha
                while ((c = ler_caractere()) != '\n' && c != EOF);
                continue;
            } else if (next == '*') {
                // comentário de múltiplas linhas
                char prev = 0;
                while ((c = ler_caractere()) != EOF) {
                    if (prev == '*' && c == '/') break;
                    prev = c;
                }
                continue;
            } else {
                volta_caractere(next);
                gravar_token(8, "/", "TOKEN_DIVIDE");
                return 8;
            }
        }

        // Operadores relacionais e lógicos
        switch (c) {
            case '+':
                if ((c = ler_caractere()) == '+') {
                    gravar_token(8, "++", "TOKEN_INCREMENT");
                } else if (c == '=') {
                    gravar_token(8, "+=", "TOKEN_ADD_ASSIGN");
                } else {
                    volta_caractere(c);
                    gravar_token(8, "+", "TOKEN_PLUS");
                }
                return 8;

            case '-':
                if ((c = ler_caractere()) == '-') {
                    gravar_token(8, "--", "TOKEN_DECREMENT");
                } else if (c == '=') {
                    gravar_token(8, "-=", "TOKEN_SUB_ASSIGN");
                } else {
                    volta_caractere(c);
                    gravar_token(8, "-", "TOKEN_MINUS");
                }
                return 8;

            case '*':
                if ((c = ler_caractere()) == '=') {
                    gravar_token(8, "*=", "TOKEN_MUL_ASSIGN");
                } else {
                    volta_caractere(c);
                    gravar_token(8, "*", "TOKEN_MULTIPLY");
                }
                return 8;

            case '%':
                if ((c = ler_caractere()) == '=') {
                    gravar_token(8, "%=", "TOKEN_MOD_ASSIGN");
                } else {
                    volta_caractere(c);
                    gravar_token(8, "%", "TOKEN_MODULO");
                }
                return 8;

            case '=':
                if ((c = ler_caractere()) == '=') {
                    gravar_token(5, "==", "TOKEN_EQUAL");
                } else {
                    volta_caractere(c);
                    gravar_token(8, "=", "TOKEN_ASSIGN");
                }
                return 8;

            case '!':
                if ((c = ler_caractere()) == '=') {
                    gravar_token(5, "!=", "TOKEN_NOT_EQUAL");
                } else {
                    volta_caractere(c);
                    gravar_token(4, "!", "TOKEN_NOT");
                }
                return 4;

            case '<':
                if ((c = ler_caractere()) == '=') {
                    gravar_token(5, "<=", "TOKEN_LESS_EQUAL");
                } else {
                    volta_caractere(c);
                    gravar_token(5, "<", "TOKEN_LESS");
                }
                return 5;

            case '>':
                if ((c = ler_caractere()) == '=') {
                    gravar_token(5, ">=", "TOKEN_GREATER_EQUAL");
                } else {
                    volta_caractere(c);
                    gravar_token(5, ">", "TOKEN_GREATER");
                }
                return 5;

            case '&':
                if ((c = ler_caractere()) == '&') {
                    gravar_token(4, "&&", "TOKEN_AND");
                    return 4;
                }
                break;

            case '|':
                if ((c = ler_caractere()) == '|') {
                    gravar_token(4, "||", "TOKEN_OR");
                    return 4;
                }
                break;

            // Delimitadores e separadores
            case ';': gravar_token(6, ";", "TOKEN_SEMICOLON"); return 6;
            case ',': gravar_token(6, ",", "TOKEN_COMMA"); return 6;
            case '.': gravar_token(6, ".", "TOKEN_DOT"); return 6;
            case ':': gravar_token(6, ":", "TOKEN_COLON"); return 6;
            case '(': gravar_token(6, "(", "TOKEN_OPEN_PAREN"); return 6;
            case ')': gravar_token(6, ")", "TOKEN_CLOSE_PAREN"); return 6;
            case '{': gravar_token(6, "{", "TOKEN_OPEN_BRACE"); return 6;
            case '}': gravar_token(6, "}", "TOKEN_CLOSE_BRACE"); return 6;
            case '[': gravar_token(6, "[", "TOKEN_OPEN_BRACKET"); return 6;
            case ']': gravar_token(6, "]", "TOKEN_CLOSE_BRACKET"); return 6;

            default:
                // caractere não reconhecido
                lexema[0] = c;
                lexema[1] = '\0';
                gravar_token(6, lexema, "TOKEN_UNKNOWN");
                return 6;
        }
    }
}
