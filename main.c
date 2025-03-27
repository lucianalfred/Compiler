#include "analisador_lexico.h"

// Definições das variáveis globais
EntradaTabela tabelaSimbolos[1000];
int indiceTabela = 0;
FILE *arquivo = NULL;
int linha = 1;
int coluna = 1;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo_de_entrada>\n", argv[0]);
        return 1;
    }

    arquivo = fopen(argv[1], "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", argv[1]);
        return 1;
    }

    while (analex() != FIM_DE_ARQUIVO) {
        // Continua analisando
    }

    fclose(arquivo);
    imprimir_tabela_simbolos();

    return 0;
}