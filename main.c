#include <stdio.h>
#include <stdlib.h>
#include "analisador_lexico.h"
#include "analisador_sintatico.h"

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

    programa(); 

    imprimir_tabela_simbolos();     
    liberar_tabela_simbolos();  

    fclose(arquivo);
    return 0;
}
