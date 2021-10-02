#ifndef ARVORE_RUBRO_NEGRA_TERMOS_H
#define ARVORE_RUBRO_NEGRA_TERMOS_H

#include "documento.h"
#include "arvore_rn_documentos.h"
#include "listadocumentos.h"

typedef struct node RBT;


/* Insere um node na árvore.
* Entradas: h - a árvore, key - a palavra a ser inserida, doc - de qual documento é a palavra
* Saída: A árvore atualizada;
* Pós-condições: A árvore foi atualizada;
*/
RBT* RBT_insert(RBT *h, char *key, Documento *doc);

/* Procura na árvore uma palavra.
* Entradas: n - a árvore, key - a palavra a ser procurada;
* Saída: ?;
* Pós-condições: -;
*/
RBT* RBT_search (RBT *n, char* key);

/* Libera a memória da árvore.
* Entradas: h - a árvore a ser destruida;
* Saída: -;
* Pós-condições: A árvore foi destruida;
*/
void destroiRBT(RBT* h);

/* Cria uma lista com os documentos do termo passado
* Entradas: h - Nó da árvore com termo que se deseja a lista;
* Saída: lista de documentos do termo contido em h;
* Pós-condições: É alocada memória para a lista criada;
*/
ListaDocumentos* retornaListaRBT(RBT* h);

RBTdocs* retornaRBTDocumentos(RBT* h);

#endif