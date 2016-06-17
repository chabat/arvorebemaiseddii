#include <cstdio>
#include <cstdlib>
#include "bemais.h"

int main(int argc, char *argv[]) { //{nome do programa, atributo, n char, ordem, arq entrada}
    FILE *entrada = NULL;
    int nChar = atoi(argv[2]), atributo = atoi(argv[1]);
    vind indices;
    
    entrada = abrirArquivo(argv[4]); //passa o nome do arquivo
    leituraArquivo(indices, nChar, atributo, entrada);

    fclose(entrada);
    return 0;
}
