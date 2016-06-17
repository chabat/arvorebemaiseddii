#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

#define MAXLINHA 1123

using namespace std;

typedef long long int ll;
typedef unsigned long long int ull;

typedef struct index_t{
    unsigned long int hash;
    long long int offset;

    index_t(long long int _h, unsigned long int _o) : hash(_h), offset(_o) {}
}index_t;

typedef struct offsets_t{    //lista encadeada dos offsets
    ll offset;
    struct offsets_t *prox;
}offsets_t;

typedef struct nodo_t{
    nodo_t **filhos, *prox, *pai;
    offsets_t **offsets;
    ull *keys;
    int quantidadeKeys, quantidadeFilhos;
    bool folha;

    nodo_t(int ordem, bool folha){ //construtor
        if(!folha){
            filhos = NULL;
            filhos = (nodo_t**)malloc(sizeof(nodo_t*)*ordem);
            if (!filhos) printf("Erro inicializando vetor dos filhos\n");
        }
        else{
            folha = true;
            offsets = NULL;
            offsets = (offsets_t**)malloc(sizeof(offsets_t*)*(ordem-1));
        }
        keys = NULL;
        keys = (ull*)malloc(sizeof(ull)*(ordem-1));
        if (!keys) printf("Erro inicializando vetor das chaves\n");
        quantidadeKeys = quantidadeFilhos = 0;
        prox = pai = NULL;
    }

    /*~nodo_t() { //deconstrutor
        free(keys);
        free(filhos);
    }*/
}nodo_t;

typedef vector<index_t> vind;

ull hashFunction(char *str);
FILE* abrirArquivo(char arquivoEntrada[]);
bool compareIndex(const index_t &_a, const index_t &_b);
void leituraArquivo(vind &indices, int nChar, int atributo, FILE *entrada);
nodo_t* bulk_loading(nodo_t* arvore, vind &indices, int ordem);
