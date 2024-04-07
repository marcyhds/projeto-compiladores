#include "lex.c"

Token analisadorLexico(FILE *arquivo, TabelaSimbolos *tabela);
void inicializarTabelaSimbolos(TabelaSimbolos *tabela);
FILE *abrirArquivo(char *nomeArquivo);
void fecharArquivo(FILE *arquivo);

