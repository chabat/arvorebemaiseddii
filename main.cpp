#include <cstdio>
#include <cstdlib>
#include "bemais.h"

int main(int argc, char *argv[]) { //{nome do programa, atributo, n char, ordem, arq entrada}
    int nChar, atributo, ordem;
    char *nomeArquivo;
    FILE *entrada = NULL;
    vind indices;
    nodo_t *arvore = NULL;

    nChar = atoi(argv[2]); atributo = atoi(argv[1]);
    ordem = atoi(argv[3]); strcpy(nomeArquivo, argv[4]);
    entrada = abrirArquivo(nomeArquivo); //passa o nome do arquivo
    leituraArquivo(indices, nChar, atributo, entrada);
    arvore = bulk_loading(arvore, indices, ordem);

    fclose(entrada);
    return 0;
}
