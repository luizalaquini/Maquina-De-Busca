#ifndef LEITURA_H
#define LEITURA_H

#include "listadocumentos.h"
#include "documento.h"
#include "arvore_rubro_negra.h"

//Funções de leitura

/* Muda as strings para lower case
* Entradas: string  a ser mudada
* Saída: a string em lower case;
* Pós-condições: -;
*/
char* stringToLower(char* string);

/* Lê o arquivo index.txt
* Entradas: nomePasta- nome da pasta onde está o arquivo a ser lido, numDocs - número de documentos;
* Saída: Lista de documentos existentes;
* Pós-condições: Lista de documentos existentes foi criada;
*/
ListaDocumentos* leIndex(char* nomePasta, int *numDocs);

/* Lê o arquivo graph.txt
* Entradas: todosDocumentos - lista com todos os documentos existentes, nomePasta- nome da pasta onde está o arquivo a ser lido;
* Saída: -;
* Pós-condições: os links entre as páginas foram inicializados;
*/
void leGrafo(ListaDocumentos *todosDocumentos, char *nomePasta);

/* Lê o arquivo stopwords.txt
* Entradas: arvore - a árvore de stop words, nomePasta- nome da pasta onde está o arquivo a ser lido;
* Saída: A ávore de stop words;
* Pós-condições: A ávore de stop words foi inicializada;
*/
RBT* leStopWords(RBT* arvore, char* nomePasta);

/* Lê os arquivos do diretório pages/
* Entradas: odosDocumentos - lista com todos os documentos existentes, stopWords - a árvore de stop words, nomePasta- nome da pasta onde está o arquivo a ser lido;
* Saída: A árvore de palavras;
* Pós-condições: A árvore de palavras válidasfoi inicializada;
*/
RBT* lePaginas(ListaDocumentos *todosDocumentos, RBT *stopWords, char *nomePasta);

#endif /* LEITURA_H */ 