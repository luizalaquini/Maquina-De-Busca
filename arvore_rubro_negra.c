#include <stdlib.h>
#include <string.h>

#include "arvore_rubro_negra.h"
#include "documento.h"
#include "listadocumentos.h"

#define RED 1
#define BLACK 0

struct node {
    char* key;
    ListaDocumentos* listaDoc;
    int color;
    RBT *l, *r;
};

RBT* create_node(char* key, int type, Documento *doc){
    RBT* node = malloc(sizeof(RBT));
    node->key = strdup(key);
    node->color = type;
    node->listaDoc = initListaDocumentos();
    node->listaDoc = adicionaDocumentoLista(node->listaDoc, doc);
    node->l = NULL;
    node->r = NULL;

    return node;
}

int is_red (RBT *x) {
    if (x == NULL) return BLACK;
    return x->color; //RED == true
}

RBT* rotate_left(RBT *h) {
    RBT *x = h->r;
    h->r = x->l;
    x->l = h;
    x->color = x->l->color;
    x->l->color = RED;
    return x;
}

RBT* rotate_right(RBT *h) {
    RBT *x = h->l;
    h->l = x->r;
    x->r = h;
    x->color = x->r->color;
    x->r->color = RED;
    return x;
}

void flip_colors(RBT *h) {
    h->color = RED;
    h->l->color = BLACK;
    h->r->color = BLACK;
}

int compare(char* key1, char* key2) {
    return strcmp(key1, key2);
}

RBT* RBT_insert(RBT *h, char *key, Documento *doc) {
    // Insert at bottom and color it red.
    if (h == NULL) { 
        return create_node(key, RED, doc); 
    }

    int cmp = compare(key, h->key);
    
    if (cmp < 0) { 
        h->l = RBT_insert(h->l, key, doc); 
    }
    else if (cmp > 0) { 
        h->r = RBT_insert(h->r, key, doc); 
    }
    else /*cmp == 0*/ { 
        //Adicionar o documento na lista do termo
        h->listaDoc = adicionaDocumentoLista(h->listaDoc, doc);
    }

    // Lean left.
    if (is_red(h->r) && !is_red(h->l)) { 
        h = rotate_left(h); 
    }
    // Balance 4-node.
    if (is_red(h->l) && is_red(h->l->l)) { 
        h = rotate_right(h); 
    }
    // Split 4-node.
    if (is_red(h->l) && is_red(h->r)) { 
        flip_colors(h); 
    }
    return h;
}

RBT* RBT_search(RBT *n, char* key) {
    while (n != NULL) {
        int cmp;
        cmp = compare(key, n->key);
        if (cmp < 0) n = n->l;
        else if (cmp > 0) n = n->r;
        else return n;
    }
    return NULL;
}

void imprimeRBT(RBT* h){
    if(h == NULL){
        return;
    }

    printf("%s: ", h->key);
    ListaDocumentos *lista = h->listaDoc;
    while(lista != NULL){
        Documento *doc = retornaElementoDaLista(lista);
        printf("%s ", retornaNomeDocumento(doc)); 

        lista = retornaProximaCelulaLista(lista);
    }
    printf("\n");

    if (h->l != NULL) imprimeRBT(h->l);
    if (h->r != NULL) imprimeRBT(h->r);

    

}

void destroiRBT(RBT* h) {
    if(h == NULL){
        return;
    }

    free(h->key);

    if (h->l != NULL) destroiRBT(h->l);
    if (h->r != NULL) destroiRBT(h->r);

    destroiListaDocumentos(h->listaDoc);
    free(h);
}

