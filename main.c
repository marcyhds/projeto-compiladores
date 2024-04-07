#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

int main() {

    Token token;

    char *nomeArquivo = "teste.txt";
    token = analisadorLexico(nomeArquivo);

    printf("<%s,%s>\n", token.nomeToken, token.valor);

    return 0;
}
