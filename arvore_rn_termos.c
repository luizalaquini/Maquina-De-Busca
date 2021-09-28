#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "arvore_rn_termos.h"
#include "documento.h"
#include "listadocumentos.h"

#define RED 1
#define BLACK 0


struct node {
    char* key;
    RBTdocs* documentos;
    int color;
    RBT *l, *r;
};


/* Cria um node da árvore.
* Entradas: key - a palavra, type - o inteiro que significa a cor, doc - o documento 
* Saída: Um node da árvore;
* Pós-condições: A árvore agora tem um node;
*/
RBT* create_node(char* key, int type, Documento *doc){
    RBT* node = malloc(sizeof(RBT));
    node->key = strdup(key);
    node->color = type;
    node->documentos = RBTdocs_insert(NULL, doc);
    node->l = NULL;
    node->r = NULL;

    return node;
}

/* Retorna 1 se a cor da ávore  vermelha e retorna 0 se a árvore for NULL
* Entradas: x - a árvore a ser destruida;
* Saída: Um inteiro que significa a cor da árvore;
* Pós-condições: -;
*/
int is_red (RBT *x) {
    if (x == NULL) return BLACK;
    return x->color; //RED == true
}

/* 
* Entradas: h - a árvore;
* Saída: 
* Pós-condições: 
*/
RBT* rotate_left(RBT *h) {
    RBT *x = h->r;
    h->r = x->l;
    x->l = h;
    x->color = x->l->color;
    x->l->color = RED;
    return x;
}

/* .
* Entradas: h - a árvore;
* Saída: 
* Pós-condições: 
*/
RBT* rotate_right(RBT *h) {
    RBT *x = h->l;
    h->l = x->r;
    x->r = h;
    x->color = x->r->color;
    x->r->color = RED;
    return x;
}

/* Troca a cor da árvore da direita com a cor da árvore da esquerda.
* Entradas: h - a árvore;
* Saída: -;
* Pós-condições: As cores da árvore da direita e da esquerda foram trocadas;
*/
void flip_colors(RBT *h) {
    h->color = RED;
    h->l->color = BLACK;
    h->r->color = BLACK;
}

/* Compara uma string com outra
* Entradas: key1 - string, key2 - string;
* Saída: Um inteiro indicando se as strings são iguais ou não;
* Pós-condições: -;
*/
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
        //Adicionar o documento na árvore de documentos do termo
        h->documentos = RBTdocs_insert(h->documentos, doc);
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

ListaDocumentos* retornaListaRBT(RBT* h){
    if(h)
        return criaListaAPartirRBTdocs(h->documentos, NULL);
    return NULL;
}

void destroiRBT(RBT* h) {
    if(h == NULL){
        return;
    }

    free(h->key);

    if (h->l != NULL) destroiRBT(h->l);
    if (h->r != NULL) destroiRBT(h->r);

    destroiRBTdocs(h->documentos);
    free(h);
}


RBTdocs* retornaRBTDocumentos(RBT* h){
    return h->documentos;
}

