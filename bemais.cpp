#ifndef _BEMAIS_
#define _BEMAIS_
#include "bemais.h"


ull hashFunction(char *str) {
  ull hash = 5381;
  int c;
  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}

void leituraArquivo(vind &indices, int nChar, int atributo, FILE *entrada) {
  ll offsetAux;
  char tupla[MAXTUPLA];
  
  while (offsetAux = ftell(entrada), fgets(tupla, MAXTUPLA, entrada)) {
    int tamanho, i, j, virgula = atributo - 1;
    char aux[nChar+1];
    ull hash = 0;
    tupla[strlen(tupla)-1] = '\0';

    //passa o atributo pro aux
    for (i = 0, tamanho = strlen(tupla); i < tamanho && virgula; i++) { if (tupla[i] == ',') virgula--; }
    for (j = 0; j < nChar && tupla[i] != '\0' && tupla[i] != '\n' && tupla[i] != ','; i++) {
      if (tupla[i] != '"') aux[j++] = tupla[i];
    }
    aux[j] = '\0';
    printf("%s\n", aux);
   
    //faz hash
    hash = hashFunction(aux);

    //empurra no vetor
    indices.push_back(index_t(hash, offsetAux));
  }

  //ordena de acordo com as hashs
  qsort(&indices, (int)indices.size(), sizeof(index_t), &compareIndex);
}

FILE* abrirArquivo(char arquivoEntrada[]) {
  FILE *entrada;
  entrada = fopen(arquivoEntrada, "a+"); //abre o arquivo de entrada que vai ser passado de parametro quando executar o programa
  if (!entrada) { printf("Não abriu entrada\n"); exit(1); }
  fseek(entrada, 0, SEEK_SET); //retorna o buffer pro começo (so pra garantir)
  return entrada;
}


int compareIndex(const void *_a, const void *_b) {
  index_t *a = (index_t*)_a, *b = (index_t*)_b;
  if (a < b) return -1;
  if (a > b) return 1;
  return 0;
}

#endif
