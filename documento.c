#include "documento.h"
#include "listadocumentos.h"
#include <stdlib.h>
#include <string.h>


struct doc{
    char *nome;
    double pageRank;
    double pageRankAnterior;
    ListaDocumentos *out;
    ListaDocumentos *in;
};

/* Cria um documento com o nome passado.
* Entradas: nomeDocumento - ponteiro para string com o nome do documento
* Saída: Um ponteiro para o documento criado;
* Pós-condições: A memória para o documento e para uma cópia do nome é alocada;
*/
Documento* initDocumento(char* nomeDocumento){
    Documento *novoDoc = (Documento*) malloc(sizeof(Documento));
    novoDoc->nome = strdup(nomeDocumento);
    novoDoc->in = initListaDocumentos();
    novoDoc->out = initListaDocumentos();
    novoDoc->pageRank = 0;
    novoDoc->pageRankAnterior = 0;

    return novoDoc;
}

/* Adiciona em um documento um link para outro documento, já indicando no outro documento sobre o novo link in
* Entradas: docAtual - ponteiro para o documento origem do link // docOut - ponteiro para o documento destino do link
* Saída: -;
* Pós-condições: Ambos os documentos são alterados, registrando a relação entre eles;
*/
void adicionaLinkOut(Documento *docAtual, Documento *docOut){
    //Adiciona docOut na lista de linksOut do docAtual
    adicionaDocumentoLista(docAtual->out, docOut);
    //Adiciona docAtual na lista de linksIn do docOut
    adicionaDocumentoLista(docOut->in, docAtual);
}

/* Retorna o início da lista de links que saem do documento
* Entradas: documento - ponteiro para o documento de que se deseja saber os links out
* Saída: ponteiro para a lista de links saindo do documento;
* Pós-condições: nenhuma estrutura é alterada diretamente;
*/
ListaDocumentos* retornaListaLinksOut(Documento *documento){
    if(documento)
        return documento->out;
    return NULL;
}

/* Retorna o início da lista de links que chegam no documento
* Entradas: documento - ponteiro para o documento de que se deseja saber os links in
* Saída: ponteiro para a lista de links que chegam no documento;
* Pós-condições: nenhuma estrutura é alterada diretamente;
*/
ListaDocumentos* retornaListaLinksIn(Documento *documento){
    if(documento)
        return documento->in;
    return NULL;
}

/* Retorna o nome do documento
* Entradas: documento - ponteiro para o documento de que se deseja saber o nome
* Saída: ponteiro para a string que representa o nome do documento;
* Pós-condições: NÃO é feita a cópia do nome;
*/
char* retornaNomeDocumento(Documento *documento){
    return documento->nome;
}

/* Libera a memória utilizada pelo documento e seu nome
* Entradas: documento - ponteiro para o documento de que se deseja destruir
* Saída: -;
* Pós-condições: A memória utilizada pelo documento é alocada e as listas destruidas sem destruir os documentos dentro delas;
*/
void destroiDocumento(Documento *documento){
    free(documento->nome);
    destroiListaDocumentos(documento->in);
    destroiListaDocumentos(documento->out);
    free(documento);
}
