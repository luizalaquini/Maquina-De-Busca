#ifndef ARVORE_RUBRO_NEGRA_H
#define ARVORE_RUBRO_NEGRA_H

#include "documento.h"
#include "listadocumentos.h"

typedef struct node RBT;

/* Cria um node da árvore.
* Entradas: key - a palavra, type - o inteiro que significa a cor, doc - o documento 
* Saída: Um node da árvore;
* Pós-condições: A árvore agora tem um node;
*/
RBT* create_node(char* key, int type, Documento *doc);

/* Retorna 1 se a cor da ávore  vermelha e retorna 0 se a árvore for NULL
* Entradas: x - a árvore a ser destruida;
* Saída: Um inteiro que significa a cor da árvore;
* Pós-condições: -;
*/
int is_red (RBT *x);

/* 
* Entradas: h - a árvore;
* Saída: 
* Pós-condições: 
*/
RBT* rotate_left(RBT *h);

/* .
* Entradas: h - a árvore;
* Saída: 
* Pós-condições: 
*/
RBT* rotate_right(RBT *h);

/* Troca a cor da árvore da direita com a cor da árvore da esquerda.
* Entradas: h - a árvore;
* Saída: -;
* Pós-condições: As cores da árvore da direita e da esquerda foram trocadas;
*/
void flip_colors(RBT *h);

/* Compara uma string com outra
* Entradas: key1 - string, key2 - string;
* Saída: Um inteiro indicando se as strings são iguais ou não;
* Pós-condições: -;
*/
int compare(char* key1, char* key2);

/* Insere um node na árvore.
* Entradas: h - a árvore, key - a palavra a ser inserida, doc - de qual documento é a palavra(?)
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

void imprimeRBT(RBT* h);

/* Libera a memória da árvore.
* Entradas: h - a árvore a ser destruida;
* Saída: -;
* Pós-condições: A árvore foi destruida;
*/
void destroiRBT(RBT* h);


#endif