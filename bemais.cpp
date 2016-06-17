#ifndef _BEMAIS_
#define _BEMAIS_
#include "bemais.h"
using namespace std;

ull hashFunction(char *str) { //funcao hash djb2
    ull hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

void leituraArquivo(vind &indices, int nChar, int atributo, FILE *entrada){
    int tamanho, i, j, virgula;
    char linha[MAXLINHA], aux[nChar+1];
    ull hash = 0;
    ll offsetAux;

    while (offsetAux = ftell(entrada), fgets(linha, MAXLINHA, entrada)) {
        virgula = atributo - 1;
        linha[strlen(linha)-1] = '\0';
        //passa o atributo pro aux
        for (i = 0, tamanho = strlen(linha); i < tamanho && virgula; i++)
            if (linha[i] == ',') virgula--;
        for (j = 0; j < nChar && linha[i] != '\0' && linha[i] != '\n' && linha[i] != ','; i++)
            if (linha[i] != '"') aux[j++] = linha[i];
        aux[j] = '\0';
        printf("%s\n", aux);

        //faz hash
        hash = hashFunction(aux);

        //empurra no vetor
        indices.push_back(index_t(hash, offsetAux));
        printf("%llu %lld\n", hash, offsetAux);
    }

    //ordena de acordo com as hashs
    sort(indices.begin(), indices.end(), compareIndex);
}

FILE* abrirArquivo(char arquivoEntrada[]){
    FILE *entrada;
    entrada = fopen(arquivoEntrada, "a+"); //abre o arquivo de entrada que vai ser passado de parametro quando executar o programa
    if (!entrada) { printf("Não abriu entrada\n"); exit(1); }
    fseek(entrada, 0, SEEK_SET); //retorna o buffer pro começo (so pra garantir)
    return entrada;
}

bool compareIndex(const index_t &_a, const index_t &_b) {
  return _a.hash < _b.hash;
}

#endif
