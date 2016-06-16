#include "bemais.h"
#include <cstdio>
#include <cstdlib>

int main(int argc, char *argv[]) { //{nome do programa, atributo, n char, ordem, entrada
  FILE *entrada = NULL;
  int nChar = atoi(argv[2]), atributo = atoi(argv[1]);
  vind indices;
  entrada = abrirArquivo(argv[4]);
  leituraArquivo(indices, nChar, atributo, entrada);
  printf("saiu\n");
  /*for (int i = 0; i < (int)indices.size(); i++) {
    printf("%lld %llu\n", indices[i].offset, indices[i].hash);
    }*/
  fclose(entrada);
  return 0;
}
