#ifndef ARVORE_RUBRO_NEGRA_DOCUMENTOS_H
#define ARVORE_RUBRO_NEGRA_DOCUMENTOS_H

#include "documento.h"
#include "listadocumentos.h"

typedef struct node RBTdocs;


/* Insere um node na árvore.
* Entradas: h - a árvore, doc - o documento a ser inserido
* Saída: A árvore atualizada;
* Pós-condições: A árvore foi atualizada;
*/
RBTdocs* RBTdocs_insert(RBTdocs *h, Documento *doc);

/* Cria uma lista com os documentos da árvore passada
* Entradas: h - Raiz da árvore que se deseja transformar em lista // lista - ponteiro para uma lista já existente para dar append ou NULL para criar uma nova;
* Saída: lista de documentos dos documentos contidos em h;
* Pós-condições: É alocada memória para a lista criada;
*/
ListaDocumentos* criaListaAPartirRBTdocs(RBTdocs *docs, ListaDocumentos *lista);

/* Libera a memória da árvore.
* Entradas: h - a árvore a ser destruida;
* Saída: -;
* Pós-condições: A árvore foi destruida;
*/
void destroiRBTdocs(RBTdocs* h);


void imprimeRBT(RBTdocs *h);

#endif