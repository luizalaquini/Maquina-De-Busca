#ifndef LISTA_DOCS_H
#define LISTA_DOCS_H

typedef struct listadocumentos ListaDocumentos;

#include <string.h>

#include "documento.h"

/* Cria uma lista de documentos vazia
* Entradas: -;
* Saída: Um ponteiro para a lista de documentos vazia criada
* Pós-condições: Uma lista de documentos vazia é criada
*/
ListaDocumentos* initListaDocumentos();

/* Retorna a próxima célula da lista passada
* Entradas: lista - ponteiro para uma célula da lista da qual se deseja saber a próxima célula;
* Saída: Um ponteiro para a próxima célula da lista ou NULL se a lista tiver acabado;
* Pós-condições: A lista não é alterada diretamente, mas retorna um ponteiro para uma posição diferente da entrada;
*/
ListaDocumentos* retornaProximaCelulaLista(ListaDocumentos *lista);

/* Retorna o documento contido nesta célula da lista
* Entradas: lista - ponteiro para a célula da lista que se deseja buscar o elemento;
* Saída: Um ponteiro para o documento buscado ou NULL se o documento não estiver na celula;
* Pós-condições: Um ponteiro é retornado;
*/
Documento* retornaElementoDaLista(ListaDocumentos *lista);

/* Adiciona um documento ao começo da lista de documentos passada, retornando um ponteiro para a primeira posição
* Entradas: lista - ponteiro para o início da lista que se deseja alterar // 
*           documento - ponteiro para o documento que se deseja adiciona na lista. NULL se não quiser adicionar documento;
* Saída: Um ponteiro para o primeiro elemento da lista alterada
* Pós-condições: O documento é adicionado à primeira posição da lista retornada. A lista passada como parâmetro não é alterada diretamente.
*/
ListaDocumentos* adicionaDocumentoLista(ListaDocumentos *lista, Documento *documento);

/* Cria uma nova lista que contém todos os documentos contidos nas duas listas passadas
* Entradas: lista1 e lista2 - ponteiros para as listas que se deseja fazer a interseção;
* Saída: Um ponteiro para a nova lista de documentos com a interseção
* Pós-condições: Uma lista de documentos preenchida é criada, sua memória alocada
*/
ListaDocumentos* intercecaoDuasListas(ListaDocumentos *lista1, ListaDocumentos *lista2);

/* Passa pela lista, retornando o documento buscado
* Entradas: lista - ponteiro para o início da lista que se deseja buscar o elemento // nome - nome do documento desejado;
* Saída: Um ponteiro para o documento buscado ou NULL se o documento não estiver na lista;
* Pós-condições: Um ponteiro é retornado;
*/
Documento* buscaDocumentoPorNome(ListaDocumentos *lista, char *nome);

/* Libera toda a memória alocada para a lista
* Entradas: lista - ponteiro para o início da lista que se deseja desalocar;
* Saída: -;
* Pós-condições: A memória ocupada pela lista é liberada. Os documentos que possam estar contidos na lista NÃO são liberados;
*/
void destroiListaDocumentos(ListaDocumentos *lista);

/* Libera toda a memória alocada para a lista
* Entradas: lista - ponteiro para o início da lista que se deseja desalocar;
* Saída: -;
* Pós-condições: A memória ocupada pela lista é liberada. Os documentos que possam estar contidos na lista TAMBÉM são liberados;
*/

int numDocumentosLista(ListaDocumentos *documento);

void destroiListaDocumentosEDocumentos(ListaDocumentos *lista);

#endif