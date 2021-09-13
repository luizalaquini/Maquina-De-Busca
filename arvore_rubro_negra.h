#ifndef ARVORE_RUBRO_NEGRA_H
#define ARVORE_RUBRO_NEGRA_H

#include "documento.h"
#include "listadocumentos.h"

typedef struct node RBT;

RBT* create_node(char* key, int type, Documento *doc);
int is_red (RBT *x);
RBT* rotate_left(RBT *h);
RBT* rotate_right(RBT *h);
void flip_colors(RBT *h);
int compare(char* key1, char* key2);
ListaDocumentos* RBT_search (RBT *n, char* key);


#endif