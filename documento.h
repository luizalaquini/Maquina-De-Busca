#ifndef DOCUMENTO_H
#define DOCUMENTO_H

typedef struct doc Documento;

#include "listadocumentos.h"

/* Cria um documento com o nome passado.
* Entradas: nomeDocumento - ponteiro para string com o nome do documento
* Saída: Um ponteiro para o documento criado;
* Pós-condições: A memória para o documento e para uma cópia do nome é alocada;
*/
Documento* initDocumento(char* nomeDocumento);

/* Adiciona em um documento um link para outro documento, já indicando no outro documento sobre o novo link in
* Entradas: docAtual - ponteiro para o documento origem do link // docOut - ponteiro para o documento destino do link
* Saída: -;
* Pós-condições: Ambos os documentos são alterados, registrando a relação entre eles;
*/
void adicionaLinkOut(Documento *docAtual, Documento *docOut);
/* Retorna o início da lista de links que saem do documento
* Entradas: documento - ponteiro para o documento de que se deseja saber os links out
* Saída: ponteiro para a lista de links saindo do documento;
* Pós-condições: nenhuma estrutura é alterada diretamente;
*/
ListaDocumentos* retornaListaLinksOut(Documento *documento);

/* Retorna o início da lista de links que chegam no documento
* Entradas: documento - ponteiro para o documento de que se deseja saber os links in
* Saída: ponteiro para a lista de links que chegam no documento;
* Pós-condições: nenhuma estrutura é alterada diretamente;
*/
ListaDocumentos* retornaListaLinksIn(Documento *documento);

/* Retorna o nome do documento
* Entradas: documento - ponteiro para o documento de que se deseja saber o nome
* Saída: ponteiro para a string que representa o nome do documento;
* Pós-condições: NÃO é feita a cópia do nome;
*/
char* retornaNomeDocumento(Documento *documento);

/* Libera a memória utilizada pelo documento e seu nome
* Entradas: documento - ponteiro para o documento de que se deseja destruir
* Saída: -;
* Pós-condições: A memória utilizada pelo documento é alocada e as listas destruidas sem destruir os documentos dentro delas;
*/
void destroiDocumento(Documento *documento);

#endif