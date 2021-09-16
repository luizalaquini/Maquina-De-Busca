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


Documento* initDocumento(char* nomeDocumento){
    Documento *novoDoc = (Documento*) malloc(sizeof(Documento));
    novoDoc->nome = strdup(nomeDocumento);
    novoDoc->in = initListaDocumentos();
    novoDoc->out = initListaDocumentos();
    novoDoc->pageRank = 0;
    novoDoc->pageRankAnterior = 0;

    return novoDoc;
}

char* retornaNomeDocumento(Documento *documento){
    return documento->nome;
}

double retornaPageRank(Documento *documento){
    return documento->pageRank;
}

double retornaPageRankAnterior(Documento *documento){
    return documento->pageRankAnterior;
}

void adicionaLinkOut(Documento *docAtual, Documento *docOut){
    //Adiciona docOut na lista de linksOut do docAtual
    docAtual->out = adicionaDocumentoLista(docAtual->out, docOut);
    //Adiciona docAtual na lista de linksIn do docOut
    docOut->in = adicionaDocumentoLista(docOut->in, docAtual);
}


ListaDocumentos* retornaListaLinksOut(Documento *documento){
    if(documento)
        return documento->out;
    return NULL;
}


ListaDocumentos* retornaListaLinksIn(Documento *documento){
    if(documento)
        return documento->in;
    return NULL;
}

void setPageRankAnterior(Documento *documento, double pagerank){
    documento->pageRankAnterior = pagerank;
}

void setPageRank(Documento *documento, double pagerank){
    documento->pageRank = pagerank;
}


void destroiDocumento(Documento *documento){
    free(documento->nome);
    destroiListaDocumentos(documento->in);
    destroiListaDocumentos(documento->out);
    free(documento);
}
