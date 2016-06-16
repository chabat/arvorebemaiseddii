#include "bemais.h"
#include <cstdio>
#include <cstdlib>

#define DEBP

int main(int argc, char *argv[]) { //{nome do programa, atributo, n char, ordem, entrada
  FILE *entrada = NULL;
  int nChar = atoi(argv[2]), atributo = atoi(argv[1]);
  vind indices;
  char str[MAXTUPLA];
  entrada = abrirArquivo(argv[4]);
  leituraArquivo(indices, nChar, atributo, entrada);

#ifdef DEBP
  for (int i = 0; i < (int)indices.size(); i++) {
    fseek(entrada, indices[i].offset, SEEK_SET);
    fgets(str, MAXTUPLA, entrada);
    printf("%s", str);
  }
#endif

  fclose(entrada);
  return 0;
}
