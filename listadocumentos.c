#include "listadocumentos.h"
#include "documento.h"
#include <stdlib.h>

struct listadocumentos {
    Documento *info;
    struct listadocumentos *prox;    
};

/* Cria uma lista de documentos vazia
* Entradas: -;
* Saída: Um ponteiro para a lista de documentos vazia criada
* Pós-condições: Uma lista de documentos vazia é criada
*/
ListaDocumentos* initListaDocumentos(){
    return NULL;
}

/* Adiciona um documento ao começo da lista de documentos passada, retornando um ponteiro para a primeira posição
* Entradas: lista - ponteiro para o início da lista que se deseja alterar // documento - ponteiro para o documento que se deseja adiciona na lista;
* Saída: Um ponteiro para o primeiro elemento da lista alterada
* Pós-condições: O documento é adicionado à primeira posição da lista retornada. A lista passada como parâmetro não é alterada diretamente.
*/
ListaDocumentos* adicionaDocumentoLista(ListaDocumentos *lista, Documento *documento){
    //Cria nova célula com o documento passado
    ListaDocumentos *novaCelula = (ListaDocumentos*) malloc(sizeof(ListaDocumentos));
    novaCelula->info = documento;
    //Adiciona a celula nova à lista
    novaCelula->prox = lista;
    
    return novaCelula;   
}

/* Cria uma nova lista que contém todos os documentos contidos nas duas listas passadas
* Entradas: lista1 e lista2 - ponteiros para as listas que se deseja fazer a interseção;
* Saída: Um ponteiro para a nova lista de documentos com a interseção
* Pós-condições: Uma lista de documentos preenchida é criada, sua memória alocada
*/
ListaDocumentos* intercecaoDuasListas(ListaDocumentos *lista1, ListaDocumentos *lista2){
    ListaDocumentos *intersecao = initListaDocumentos();

    //Para cada elemento da lista1, verifica se tem um elemento igual na lista dois
    while(lista1 != NULL){
        Documento *docEmComum = buscaDocumentoPorNome(lista2, retornaNomeDocumento(lista1->info));
        if(docEmComum != NULL){
            adicionaDocumentoLista(intersecao, docEmComum);
        }

        lista1 = lista1->prox;
    }

    return intersecao;
}

/* Passa pela lista, retornando o documento buscado
* Entradas: lista - ponteiro para o início da lista que se deseja buscar o elemento // nome - nome do documento desejado;
* Saída: Um ponteiro para o documento buscado ou NULL se o documento não estiver na lista;
* Pós-condições: Um ponteiro é retornado;
*/
Documento* buscaDocumentoPorNome(ListaDocumentos *lista, char *nome){
    ListaDocumentos *busca = lista;
    while(1){
        if(busca == NULL){
            return NULL;
        }
        if(strcmp(retornaNomeDocumento(busca->info), nome) == 0){
            return busca->info;
        }

        busca = busca->prox;
    }
}

/* Retorna a próxima célula da lista passada
* Entradas: lista - ponteiro para uma célula da lista da qual se deseja saber a próxima célula;
* Saída: Um ponteiro para a próxima célula da lista ou NULL se a lista tiver acabado;
* Pós-condições: A lista não é alterada diretamente, mas retorna um ponteiro para uma posição diferente da entrada;
*/
ListaDocumentos* retornaProximaCelulaLista(ListaDocumentos *lista){
    return lista->prox;
}

/* Retorna o documento contido nesta célula da lista
* Entradas: lista - ponteiro para a célula da lista que se deseja buscar o elemento;
* Saída: Um ponteiro para o documento buscado ou NULL se o documento não estiver na celula;
* Pós-condições: Um ponteiro é retornado;
*/
Documento* retornaElementoDaLista(ListaDocumentos *lista){
    return lista->info;
}

/* Libera toda a memória alocada para a lista
* Entradas: lista - ponteiro para o início da lista que se deseja desalocar;
* Saída: -;
* Pós-condições: A memória ocupada pela lista é liberada. Os documentos que possam estar contidos na lista NÃO são liberados;
*/
void destroiListaDocumentos(ListaDocumentos *lista){
    ListaDocumentos *aux = lista;
    while(aux != NULL){
        lista = aux->prox;
        //Libera aux
        free(aux);
        
        //Passa pro próximo elemento
        aux = lista;
    }
}

/* Libera toda a memória alocada para a lista
* Entradas: lista - ponteiro para o início da lista que se deseja desalocar;
* Saída: -;
* Pós-condições: A memória ocupada pela lista é liberada. Os documentos que possam estar contidos na lista TAMBÉM são liberados;
*/
void destroiListaDocumentosEDocumentos(ListaDocumentos *lista){
    ListaDocumentos *aux = lista;
    while(aux != NULL){
        lista = aux->prox;
        //Libera aux
        destroiDocumento(aux->info);
        free(aux);
        
        //Passa pro próximo elemento
        aux = lista;
    }
}