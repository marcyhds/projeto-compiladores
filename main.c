#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

int main()
{

    Token token;

    char *nomeArquivo = "teste.txt";
    FILE *arquivo = abrirArquivo(nomeArquivo);
    if (arquivo == NULL)
        return -1;
    
    TabelaSimbolos tabela;
    inicializarTabelaSimbolos(&tabela);

    printf("tam %d\n", tabela.tamanho);

    while(!feof(arquivo)){ 
        token = analisadorLexico(arquivo, &tabela);
        printf("<%s,%s>\n", token.nomeToken, token.valor);
    }

    fecharArquivo(arquivo);

    return 0;
}
