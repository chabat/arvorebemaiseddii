#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#define MAXTUPLA 1123

typedef long long int ll;
typedef unsigned long long int ull;

typedef struct index_t {
  ull hash;
  ll offset;
  
index_t(ll _h, ull _o) : hash(_h), offset(_o) {}
  
} index_t;

typedef std::vector<index_t> vind;

ull hashFunction(char *str);
void leituraArquivo(vind &indices, int nChar, int atributo, FILE *entrada);
FILE* abrirArquivo(char arquivoEntrada[]);
int compareIndex(const void *_a, const void *_b);
