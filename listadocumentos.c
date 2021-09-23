#include "listadocumentos.h"
#include "documento.h"
#include <stdlib.h>
#include <stdio.h>

struct listadocumentos {
    Documento *info;
    struct listadocumentos *prox;    
};


ListaDocumentos* initListaDocumentos(){
    return NULL;
}

ListaDocumentos* retornaProximaCelulaLista(ListaDocumentos *lista){
    return lista->prox;
}


Documento* retornaElementoDaLista(ListaDocumentos *lista){
    return lista->info;
}

ListaDocumentos* adicionaDocumentoLista(ListaDocumentos *lista, Documento *documento){
    if(documento == NULL){
        return lista;
    }

    if(buscaDocumentoPorNome(lista, retornaNomeDocumento(documento)) != NULL) return lista;
    
    //Cria nova célula com o documento passado
    ListaDocumentos *novaCelula = (ListaDocumentos*) malloc(sizeof(ListaDocumentos));
    novaCelula->info = documento;
    //Adiciona a celula nova à lista
    novaCelula->prox = lista;
    
    return novaCelula;   
}


ListaDocumentos* intersecaoDuasListas(ListaDocumentos *lista1, ListaDocumentos *lista2){
    ListaDocumentos *intersecao = initListaDocumentos();

    //Para cada elemento da lista1, verifica se tem um elemento igual na lista dois
    while(lista1 != NULL){
        Documento *docEmComum = buscaDocumentoPorNome(lista2, retornaNomeDocumento(lista1->info));
        if(docEmComum != NULL){
            intersecao = adicionaDocumentoLista(intersecao, docEmComum);
        }

        lista1 = lista1->prox;
    }

    return intersecao;
}


Documento* buscaDocumentoPorNome(ListaDocumentos *lista, char *nome){
    if(lista == NULL) return NULL;
    ListaDocumentos *busca = lista;
    while(1){
        if(busca == NULL){
            return NULL;
        }
        if(strcmp(retornaNomeDocumento(busca->info), nome) == 0){
            return busca->info;
        }

        busca = busca->prox;
    }
}


void destroiListaDocumentos(ListaDocumentos *lista){
    ListaDocumentos *aux = lista;
    while(aux != NULL){
        lista = aux->prox;
        //Libera aux
        free(aux);
        
        //Passa pro próximo elemento
        aux = lista;
    }
}

int numDocumentosLista(ListaDocumentos *documentos){
    int count = 0;
    ListaDocumentos* aux = documentos;

    while(aux != NULL){
        aux = aux->prox;
        count++;
    }
    return count;
}

void destroiListaDocumentosEDocumentos(ListaDocumentos *lista){
    ListaDocumentos *aux = lista;
    while(aux != NULL){
        lista = aux->prox;
        //Libera aux
        destroiDocumento(aux->info);
        free(aux);
        
        //Passa pro próximo elemento
        aux = lista;
    }
}