#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

#define MAXTUPLA 1123

struct nodo_t {
  nodo_t *filhos;
  unsigned long int *keys;
  int quantidadeKeys, quantidadeFilhos;
  
  nodo_t(int ordem) { //construtor
  filhos = NULL;
  filhos = (nodo_t*)malloc(sizeof(nodo_t)*ordem);
  if (!filhos) printf("Erro inicializando nodo_t\n");
  keys = NULL;
  keys = (unsigned long int*)malloc(sizeof(unsigned long int)*(ordem-1));
    if (!keys) printf("Erro inicializando nodo_t. Parte 2\n");
    quantidadeKeys = quantidadeFilhos = 0;
}
  
  ~nodo_t() { //deconstrutor
    free(keys);
    free(filhos);
  } 
};

struct index_t {
  unsigned long int hash;
    long long int offset;
  
index_t(long long int _h, unsigned long int _o) : hash(_h), offset(_o) {}
  
};

typedef long long int ll;
typedef unsigned long long int ull;
typedef struct index_t index_t;
typedef std::vector<index_t> vind;
typedef struct nodo_t nodo_t;

ull hashFunction(char *str);
void leituraArquivo(vind &indices, int nChar, int atributo, FILE *entrada);
FILE* abrirArquivo(char arquivoEntrada[]);
bool compareIndex(const index_t &_a, const index_t &_b);
