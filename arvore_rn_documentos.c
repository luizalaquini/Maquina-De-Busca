#include <stdlib.h>
#include <string.h>

#include "arvore_rn_documentos.h"
#include "documento.h"
#include "listadocumentos.h"

#define RED 1
#define BLACK 0


struct node {
    Documento* key;
    int color;
    RBTdocs *l, *r;
};

RBTdocs* create_node_docs(int type, Documento *doc){
    RBTdocs* node = malloc(sizeof(RBTdocs));
    node->key = doc;
    node->color = type;
    node->l = NULL;
    node->r = NULL;

    return node;
}

int is_red_docs (RBTdocs *x) {
    if (x == NULL) return BLACK;
    return x->color; //RED == true
}

RBTdocs* rotate_left_docs(RBTdocs *h) {
    RBTdocs *x = h->r;
    h->r = x->l;
    x->l = h;
    x->color = x->l->color;
    x->l->color = RED;
    return x;
}

RBTdocs* rotate_right_docs(RBTdocs *h) {
    RBTdocs *x = h->l;
    h->l = x->r;
    x->r = h;
    x->color = x->r->color;
    x->r->color = RED;
    return x;
}

void flip_colors_docs(RBTdocs *h) {
    h->color = RED;
    h->l->color = BLACK;
    h->r->color = BLACK;
}

int compare_docs(Documento* key1, Documento* key2) {  
    return strcmp(retornaNomeDocumento(key1), retornaNomeDocumento(key2));
}

RBTdocs* RBTdocs_insert(RBTdocs *h, Documento *doc) {
    if(doc == NULL){
        return h;
    }

    // Insert at bottom and color it red.
    if (h == NULL) { 
        return create_node_docs(RED, doc); 
    }

    int cmp = compare_docs(doc, h->key);
    
    if (cmp < 0) { 
        h->l = RBTdocs_insert(h->l, doc); 
    }
    else if (cmp > 0) { 
        h->r = RBTdocs_insert(h->r, doc); 
    }
    else {
        return h;
    }
    

    // Lean left.
    if (is_red_docs(h->r) && !is_red_docs(h->l)) { 
        h = rotate_left_docs(h); 
    }
    // Balance 4-node.
    if (is_red_docs(h->l) && is_red_docs(h->l->l)) { 
        h = rotate_right_docs(h); 
    }
    // Split 4-node.
    if (is_red_docs(h->l) && is_red_docs(h->r)) { 
        flip_colors_docs(h); 
    }
    return h;
}

ListaDocumentos* criaListaAPartirRBTdocs(RBTdocs *docs, ListaDocumentos *lista){
    if(docs == NULL){
        return NULL;
    }
    if(lista == NULL){
        lista = initListaDocumentos();
    }


    if (docs->l != NULL) lista = criaListaAPartirRBTdocs(docs->l, lista);
    if (docs->r != NULL) lista = criaListaAPartirRBTdocs(docs->r, lista);
    
    return adicionaDocumentoLista(lista, docs->key);
}

void destroiRBTdocs(RBTdocs* h) {
    if(h == NULL){
        return;
    }

    if (h->l != NULL) destroiRBTdocs(h->l);
    if (h->r != NULL) destroiRBTdocs(h->r);

    free(h);
}