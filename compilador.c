#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TAMANHO_MAXIMO 100
#define TAMANHO_MAXIMO_SIMBOLOS 1000

/******   DEFINIÇÃO DAS ESTRUTURAS DE DADOS    *****/
typedef struct
{
  char nomeToken[10];
  char valor[100];
} Token;

typedef struct
{
  Token tabela[TAMANHO_MAXIMO_SIMBOLOS];
  int tamanho;
} TabelaSimbolos;

typedef struct
{
  int topo;
  char itens[TAMANHO_MAXIMO];
} Pilha;

/*****    FUNÇÕES PILHA    *****/
void inicializa_pilha(Pilha *p)
{
  p->topo = -1;
}

void empilha(Pilha *p, char item)
{
  p->itens[++(p->topo)] = item;
}

void desempilha(Pilha *p)
{
  if (p->topo >= 0)
  {
    (p->topo)--;
  }
}

/*****    FUNÇÕES ARQUIVOS    *****/
FILE *abrirArquivo(char *nomeArquivo)
{
  FILE *arquivo = fopen(nomeArquivo, "r");

  if (arquivo == NULL)
  {
    perror("Erro ao abrir o arquivo");
    return NULL;
  }

  return arquivo;
}

void fecharArquivo(FILE *arquivo)
{
  if (arquivo != NULL)
  {
    fclose(arquivo);
  }
}

/*****    FUNÇÕES TABELA DE SIMBOLOS    *****/
void inicializarTabelaSimbolos(TabelaSimbolos *tabela)
{
  tabela->tamanho = 0;
}

int inserirSimbolo(TabelaSimbolos *tabela, char *nomeToken, char *tipo)
{
  if (tabela->tamanho < 1000)
  {
    strcpy(tabela->tabela[tabela->tamanho].nomeToken, nomeToken);
    strcpy(tabela->tabela[tabela->tamanho].valor, tipo);
    tabela->tamanho++;
  }
  else
  {
    printf("Erro: Tabela de símbolos cheia.\n");
  }
  return tabela->tamanho;
}

int buscarSimbolo(TabelaSimbolos *tabela, char *nomeToken, char *valor)
{
  for (int i = 0; i < tabela->tamanho; i++)
  {
    if (strcmp(tabela->tabela[i].valor, valor) == 0 && strcmp(tabela->tabela[i].nomeToken, nomeToken) == 0)
    {
      return i;
    }
  }
  return -1;
}

/*****    FUNÇÕES ANALISADOR LEXICO    *****/
char lerProximoChar(FILE *arquivo)
{
  int caractere = fgetc(arquivo);

  if (caractere == EOF)
  {
    return EOF;
  }
  return caractere;
}

int tratarErroLexico()
{
  printf("Erro na analise lexica\n");
  return 0;
}

int tratarLookahead()
{
  return 1;
}

Token analisadorLexico(FILE *arquivo, TabelaSimbolos *tabela)
{
  Token token;

  char proxChar, lexema[100000];

  int estadoAtual = 0, lookahead = 0, index = 0;

  while (!feof(arquivo))
  {
    switch (estadoAtual)
    {
    case 0:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
      {
        lookahead = !lookahead;
        lexema[0] = '\0';
      }
      strncat(lexema, &proxChar, 1);
      if (proxChar == 'p')
        estadoAtual = 1;
      else if (proxChar == 's')
        estadoAtual = 11;
      else if (proxChar == 'e')
        estadoAtual = 15;
      else if (proxChar == 'r')
        estadoAtual = 42;
      else if (proxChar == 'a')
        estadoAtual = 50;
      else if (proxChar == 'f')
        estadoAtual = 36;
      else if (proxChar == 'i')
        estadoAtual = 97;
      else if (proxChar == 'c')
        estadoAtual = 110;
      else if (proxChar == '(')
        estadoAtual = 55;
      else if (proxChar == ')')
        estadoAtual = 57;
      else if (proxChar == '/')
        estadoAtual = 59;
      else if (proxChar == '*')
        estadoAtual = 62;
      else if (proxChar == ';')
        estadoAtual = 65;
      else if (proxChar == ',')
        estadoAtual = 67;
      else if (proxChar == '<')
        estadoAtual = 69;
      else if (isspace(proxChar))
        estadoAtual = 79;
      else if (proxChar == '%')
        estadoAtual = 75;
      else if (proxChar == '-')
        estadoAtual = 72;
      else if (proxChar == '+')
        estadoAtual = 82;
      else if (proxChar == '^')
        estadoAtual = 86;
      else if (proxChar == '=')
        estadoAtual = 92;
      else if (proxChar == '>')
        estadoAtual = 93;
      else if (proxChar == '>')
        estadoAtual = 93;
      else if (isdigit(proxChar))
        estadoAtual = 122;
      else if (isalpha(proxChar))
        estadoAtual = 132;
      else
        tratarErroLexico();
      break;
    case 1:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'r')
        estadoAtual = 2;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 2:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'o')
        estadoAtual = 3;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 3:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'g')
        estadoAtual = 4;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 4:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'r')
        estadoAtual = 5;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 5:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'a')
        estadoAtual = 6;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 6:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'm')
        estadoAtual = 7;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 7:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'a')
        estadoAtual = 8;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 8:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 9;
      break;
    case 9:
      lookahead = tratarLookahead();
      lexema[0] = '\0';
      strcpy(token.nomeToken, "programa");
      strcpy(token.valor, "NULL");
      return token;
      break;
    case 11:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'e')
        estadoAtual = 12;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 12:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'n')
        estadoAtual = 21;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 13;
      break;
    case 13:
      lookahead = tratarLookahead();
      lexema[0] = '\0';
      strcpy(token.nomeToken, "se");
      strcpy(token.valor, "NULL");
      return token;
      break;
    case 21:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'a')
        estadoAtual = 22;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 22:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'o')
        estadoAtual = 23;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 23:
      lookahead = tratarLookahead();
      lexema[0] = '\0';
      strcpy(token.nomeToken, "senao");
      strcpy(token.valor, "NULL");
      return token;
      break;
    case 15:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'n')
        estadoAtual = 16;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 16:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'q')
        estadoAtual = 28;
      else if (proxChar == 't')
        estadoAtual = 17;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 17:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'a')
        estadoAtual = 18;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 18:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'o')
        estadoAtual = 19;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 19:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 20;
      break;
    case 20:
      lookahead = tratarLookahead();
      lexema[0] = '\0';
      strcpy(token.nomeToken, "entao");
      strcpy(token.valor, "NULL");
      return token;
      break;
    case 28:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'u')
        estadoAtual = 29;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 29:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'a')
        estadoAtual = 30;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 30:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'n')
        estadoAtual = 31;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 31:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 't')
        estadoAtual = 32;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 32:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'o')
        estadoAtual = 33;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 33:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 34;
      break;
    case 34:
      lookahead = tratarLookahead();
      lexema[0] = '\0';
      strcpy(token.nomeToken, "enquanto");
      strcpy(token.valor, "NULL");
      return token;
      break;
    case 42:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'e')
        estadoAtual = 43;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 43:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'p')
        estadoAtual = 44;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 44:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'i')
        estadoAtual = 45;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 45:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 't')
        estadoAtual = 46;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 46:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'a')
        estadoAtual = 47;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 47:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 48;
      break;
    case 48:
      lookahead = tratarLookahead();
      lexema[0] = '\0';
      strcpy(token.nomeToken, "repita");
      strcpy(token.valor, "NULL");
      return token;
      break;
    case 50:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 't')
        estadoAtual = 51;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 51:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'e')
        estadoAtual = 52;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 52:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 53;
      break;
    case 53:
      lookahead = tratarLookahead();
      lexema[0] = '\0';
      strcpy(token.nomeToken, "ate");
      strcpy(token.valor, "NULL");
      return token;
      break;
    case 36:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'a')
        estadoAtual = 37;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 37:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'c')
        estadoAtual = 38;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 38:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'a')
        estadoAtual = 39;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 39:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 40;
      break;
    case 40:
      lookahead = tratarLookahead();
      lexema[0] = '\0';
      strcpy(token.nomeToken, "faca");
      strcpy(token.valor, "NULL");
      return token;
      break;
    case 116:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'o')
        estadoAtual = 117;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 117:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'a')
        estadoAtual = 118;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 118:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 't')
        estadoAtual = 119;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 119:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 120;
      break;
    case 120:
      lookahead = tratarLookahead();
      lexema[0] = '\0';
      strcpy(token.nomeToken, "tipo");
      strcpy(token.valor, "FLOAT");
      return token;
      break;
    case 97:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'n')
        estadoAtual = 98;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 98:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 't')
        estadoAtual = 99;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 99:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 100;
      break;
    case 100:
      lookahead = tratarLookahead();
      lexema[0] = '\0';
      strcpy(token.nomeToken, "tipo");
      strcpy(token.valor, "INT");
      return token;
      break;
    case 110:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'h')
        estadoAtual = 111;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 111:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'a')
        estadoAtual = 112;
      else if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 113:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 114;
      break;
    case 114:
      lookahead = tratarLookahead();
      lexema[0] = '\0';
      strcpy(token.nomeToken, "tipo");
      strcpy(token.valor, "CHAR");
      return token;
      break;
    case 55:
      lexema[0] = '\0';
      strcpy(token.nomeToken, "pesq");
      strcpy(token.valor, "NULL");
      return token;
      break;
    case 57:
      lexema[0] = '\0';
      strcpy(token.nomeToken, "pdir");
      strcpy(token.valor, "NULL");
      return token;
      break;
    case 59:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == '*')
        estadoAtual = 60;
      else
        estadoAtual = 85;
      break;
    case 60:
      lexema[0] = '\0';
      strcpy(token.nomeToken, "besq");
      strcpy(token.valor, "NULL");
      return token;
      break;
    case 85:
      lookahead = tratarLookahead();
      lexema[0] = '\0';
      strcpy(token.nomeToken, "oparit");
      strcpy(token.valor, "NULL");
      return token;
      break;
    case 62:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == '/')
        estadoAtual = 63;
      else
        estadoAtual = 84;
      break;
    case 63:
      lexema[0] = '\0';
      strcpy(token.nomeToken, "bdir");
      strcpy(token.valor, "NULL");
      return token;
      break;
    case 84:
      lookahead = tratarLookahead();
      lexema[0] = '\0';
      strcpy(token.nomeToken, "oparit");
      strcpy(token.valor, "MUL");
      return token;
      break;
    case 65:
      lexema[0] = '\0';
      strcpy(token.nomeToken, "ptvgl");
      strcpy(token.valor, "NULL");
      return token;
      break;
    case 67:
      lexema[0] = '\0';
      strcpy(token.nomeToken, "vgl");
      strcpy(token.valor, "NULL");
      return token;
      break;
    case 69:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == '-')
        estadoAtual = 70;
      else if (proxChar == '=')
        estadoAtual = 89;
      else if (proxChar == '>')
        estadoAtual = 90;
      else
        estadoAtual = 91;
      break;
    case 70:
      lexema[0] = '\0';
      strcpy(token.nomeToken, "atr");
      strcpy(token.valor, "NULL");
      return token;
      break;
    case 89:
      lexema[0] = '\0';
      strcpy(token.nomeToken, "relop");
      strcpy(token.valor, "LE");
      return token;
      break;
    case 90:
      lexema[0] = '\0';
      strcpy(token.nomeToken, "relop");
      strcpy(token.valor, "NE");
      return token;
      break;
    case 91:
      lookahead = tratarLookahead();
      lexema[0] = '\0';
      strcpy(token.nomeToken, "relop");
      strcpy(token.valor, "LT");
      return token;
      break;
    case 79:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      // if (proxChar == '\n' || proxChar == ' ' || proxChar == '\t')
      if (isspace(proxChar))
        estadoAtual = 79;
      else
        estadoAtual = 80;
      break;
    case 80:
      estadoAtual = 0;
      lookahead = tratarLookahead();
      break;
    case 75:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == '%')
        estadoAtual = 77;
      else
        estadoAtual = 76;
      break;
    case 76:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == '%')
        estadoAtual = 77;
      else
        estadoAtual = 76;
    case 77:
      estadoAtual = 0;
      break;
    case 72:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == '>')
        estadoAtual = 73;
      else
        estadoAtual = 83;
      break;
    case 73:
      lexema[0] = '\0';
      strcpy(token.nomeToken, "vr");
      strcpy(token.valor, "NULL");
      return token;
      break;
    case 83:
      lookahead = tratarLookahead();
      lexema[0] = '\0';
      strcpy(token.nomeToken, "oparit");
      strcpy(token.valor, "SUB");
      return token;
      break;
    case 82:
      lexema[0] = '\0';
      strcpy(token.nomeToken, "oparit");
      strcpy(token.valor, "SUM");
      return token;
      break;
    case 86:
      lexema[0] = '\0';
      strcpy(token.nomeToken, "oparit");
      strcpy(token.valor, "POW");
      return token;
      break;
    case 92:
      lexema[0] = '\0';
      strcpy(token.nomeToken, "relop");
      strcpy(token.valor, "EQ");
      return token;
      break;
    case 93:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == '=')
        estadoAtual = 94;
      else
        estadoAtual = 95;
      break;
    case 94:
      lexema[0] = '\0';
      strcpy(token.nomeToken, "relop");
      strcpy(token.valor, "GE");
      return token;
      break;
    case 95:
      lexema[0] = '\0';
      strcpy(token.nomeToken, "relop");
      strcpy(token.valor, "GT");
      return token;
      break;
    case 122:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == '.')
        estadoAtual = 123;
      else if (isdigit(proxChar))
        estadoAtual = 122;
      else if (proxChar == 'E')
        estadoAtual = 125;
      else
        estadoAtual = 128;
      break;
    case 123:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (isdigit(proxChar))
        estadoAtual = 124;
      else
        tratarErroLexico();
      break;
    case 124:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == 'E')
        estadoAtual = 125;
      else if (isdigit(proxChar))
        estadoAtual = 124;
      else
        estadoAtual = 129;
      break;
    case 125:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (proxChar == '+' || proxChar == '-')
        estadoAtual = 126;
      else if (isdigit(proxChar))
        estadoAtual = 127;
      else
        tratarErroLexico();
      break;
    case 126:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (isdigit(proxChar))
        estadoAtual = 127;
      else
        tratarErroLexico();
      break;
    case 127:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (isdigit(proxChar))
        estadoAtual = 127;
      else
        estadoAtual = 130;
      break;
    case 128:
      lookahead = tratarLookahead();
      lexema[strlen(lexema) - 1] = '\0';
      index = buscarSimbolo(tabela, "id", lexema);
      if (index == -1)
        index = inserirSimbolo(tabela, "num", lexema);

      lexema[0] = '\0';
      strcpy(token.nomeToken, "num");
      snprintf(token.valor, sizeof(token.valor), "%d", index);
      return token;
      break;
    case 129:
      lookahead = tratarLookahead();
      lexema[strlen(lexema) - 1] = '\0';
      index = buscarSimbolo(tabela, "id", lexema);
      if (index == -1)
        index = inserirSimbolo(tabela, "num", lexema);

      lexema[0] = '\0';
      strcpy(token.nomeToken, "num");
      snprintf(token.valor, sizeof(token.valor), "%d", index);
      return token;
      break;
    case 130:
      lookahead = tratarLookahead();
      lexema[strlen(lexema) - 1] = '\0';
      index = buscarSimbolo(tabela, "id", lexema);
      if (index == -1)
        index = inserirSimbolo(tabela, "num", lexema);

      lexema[0] = '\0';
      strcpy(token.nomeToken, "num");
      snprintf(token.valor, sizeof(token.valor), "%d", index);
      return token;
      break;
    case 132:
      if (!lookahead)
        proxChar = lerProximoChar(arquivo);
      else
        lookahead = !lookahead;
      strncat(lexema, &proxChar, 1);

      if (isalpha(proxChar) || isdigit(proxChar) || proxChar == '_')
        estadoAtual = 132;
      else
        estadoAtual = 133;
      break;
    case 133:
      lookahead = tratarLookahead();
      lexema[strlen(lexema) - 1] = '\0';
      index = buscarSimbolo(tabela, "id", lexema);
      if (index == -1)
        index = inserirSimbolo(tabela, "id", lexema);

      lexema[0] = '\0';
      strcpy(token.nomeToken, "id");
      snprintf(token.valor, sizeof(token.valor), "%d", index);
      return token;
      break;
    default:
      strcpy(token.nomeToken, "EOF");
      strcpy(token.valor, "NULL");
      return token;
      break;
    }
  }

  fecharArquivo(arquivo);
}

/*****    FUNÇÕES ANALISADOR SINTATICO   *****/
int tratarErroSintatico()
{
  printf("Erro na analise sintatica\n");
  return 0;
}

void trataProducao(char X, char producao[])
{
  printf("Producao tratada: %c -> %s\n", X, producao);
}

int hash(const char *str)
{
  int hash = 0;
  while (*str)
  {
    hash += *str++;
  }
  return hash % TAMANHO_MAXIMO;
}

void analisadorSintatico(char *nomeArquivo)
{
  Pilha P;
  Token proxToken;
  char X;
  inicializa_pilha(&P);
  empilha(&P, 'S');

  FILE *arquivo = abrirArquivo(nomeArquivo);
  if (arquivo == NULL)
    return -1;

  TabelaSimbolos tabela;
  inicializarTabelaSimbolos(&tabela);

  proxToken = analisadorLexico(arquivo, &tabela);
  while (P.topo != -1)
  {
    X = P.itens[P.topo];
    int tokenIndex = hash(proxToken.nomeToken);
    if (X == proxToken.nomeToken)
    {
      desempilha(&P);
      proxToken = analisadorLexico(arquivo, &tabela);
    }
    else
    {
      // Tabela de análise sintática
      char tabela[TAMANHO_MAXIMO][TAMANHO_MAXIMO][TAMANHO_MAXIMO];
      // Preencha a tabela com as produções correspondentes
      // Exemplo:
      strcpy(tabela['S']['a'], "aAB");
      strcpy(tabela['S']['b'], "bBC");
      strcpy(tabela['A']['c'], "c");
      strcpy(tabela['B']['d'], "d");
      strcpy(tabela['C']['e'], "e");

      if (strlen(tabela[X][tokenIndex]) == 0)
      {
        tratarErroSintatico();
      }
      else
      {
        trataProducao(X, tabela[X][tokenIndex]);
        desempilha(&P);
        int i = strlen(tabela[X][tokenIndex]) - 1;
        while (i >= 0)
        {
          empilha(&P, tabela[X][tokenIndex][i]);
          i--;
        }
      }
    }
  }

  if (strcmp(proxToken.nomeToken, "EOF") != 0)
  {
    tratarErroSintatico();
  }
  else
  {
    printf("Analise sintatica concluida com sucesso\n");
  }

  fecharArquivo(arquivo);
}