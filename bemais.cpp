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

nodo_t* bulk_loading(nodo_t* arvore, vind &indices, int ordem){
    nodo_t *atual, *raiz = NULL, *paiAtual;
    offsets_t *aux, *novo;
    int i = 0, first = 1;

    raiz = criaNodo(ordem, true);
    paiAtual = raiz;

    while(i < indices.size()){
        atual = criaNodo(ordem, true);

        for(int j = 0; j < ordem && i < indices.size(); i++, j++){ //preenche o nodo atual
            if(j && atual->keys[j-1] == indices[i].hash) j--;
            atual->keys[j] = indices[i].hash;

            novo = (offsets_t *) malloc(sizeof(offsets_t)); //insere offset
            novo->prox = NULL;
            novo->offset = indices[i].offset;
            if(atual->offsets[j]){
                aux = atual->offsets[j];
                while(aux->prox) aux = aux->prox;
                aux->prox = novo;
            }
            else atual->offsets[j] = novo;
        }
        if(paiAtual->quantidadeFilhos >= ordem){
            paiAtual = novoPai(paiAtual, ordem);
        }
        if(!first) paiAtual->keys[paiAtual->quantidadeKeys++] = atual->keys[0];
        paiAtual->filhos[paiAtual->quantidadeFilhos++] = atual;
        atual->pai = paiAtual;
        first = 0;
    }
    return NULL;
}

nodo_t* novoPai(nodo_t *paiAtual, int ordem){
    nodo_t *irmao, *novoPai;
    irmao = criaNodo(ordem, false);
    for(int i = ordem/2, j = 0; i < ordem; i++, j++){
        irmao->keys[j] = paiAtual->keys[i];
        irmao->filhos[j] =  paiAtual->filhos[i];
    }
    paiAtual->quantidadeFilhos--;
    paiAtual->quantidadeKeys--;
    irmao->quantidadeFilhos++;
    irmao->quantidadeKeys++;





    if(!paiAtual->pai){
        novoPai = criaNodo(ordem, false);
    }
}

nodo_t* criaNodo(int ordem, bool folha){
        nodo_t* nodo = (nodo_t *)malloc(sizeof(nodo_t*));
        if(!folha){
            nodo->filhos = NULL;
            nodo->filhos = (nodo_t**)malloc(sizeof(nodo_t*)*ordem);
            if (!nodo->filhos) printf("Erro inicializando vetor dos filhos\n");
        }
        else{
            nodo->offsets = NULL;
            nodo->offsets = (offsets_t**)malloc(sizeof(offsets_t*)*(ordem-1));
        }
        nodo->keys = NULL;
        nodo->keys = (ull*)malloc(sizeof(ull)*(ordem-1));
        if (!nodo->keys) printf("Erro inicializando vetor das chaves\n");
        nodo->quantidadeKeys = nodo->quantidadeFilhos = 0;
        nodo->prox = nodo->pai = NULL;
}

#endif
