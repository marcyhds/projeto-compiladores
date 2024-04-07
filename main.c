#include <stdio.h>
#include <stdlib.h>
#include "compilador.h"

int main()
{   
    // char **tabelaProducoes = malloc(5 * sizeof(char *));
    // for (int i = 0; i < 5; i++) {
    //     tabelaProducoes[i] = malloc(4 * sizeof(char));
    // }

    // // Preencha a tabela de análise
    // tabelaProducoes[0][0] = ' '; // Exemplo, preencha conforme sua tabela real
    // // ...
    // tabelaProducoes[4][3] = ' ';

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
    // for (int i = 0; i < 5; i++) {
    //     free(tabelaProducoes[i]);
    // }
    // free(tabelaProducoes);

    char *nomeArquivo = "teste.txt";
    analisadorSintatico(nomeArquivo);

    return 0;
}
