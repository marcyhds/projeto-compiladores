#include <stdio.h>
#include <stdlib.h>
#include "compilador.h"

int main()
{   
    // Token token;

    // char *nomeArquivo = "teste.txt";
    // FILE *arquivo = abrirArquivo(nomeArquivo);
    // if (arquivo == NULL)
    //     return -1;
    
    // TabelaSimbolos tabela;
    // inicializarTabelaSimbolos(&tabela);

    // while(ftell(arquivo)!=-1){
    //     printf("<%s,%s>\n", token.nomeToken, token.valor);
    //     token = analisadorLexico(arquivo, &tabela);
    // }

    // fecharArquivo(arquivo);

    char *nomeArquivo = "teste.txt";
    analisadorSintatico(nomeArquivo);

    return 0;
}
