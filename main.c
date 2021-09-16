#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arvore_rubro_negra.h"
#include "documento.h"
#include "listadocumentos.h"

#define BUFFER_LEITURA 500

ListaDocumentos* leIndex(char* nomePasta, int *numDocs){
    //Abre arquivo
    char caminhoIndex[BUFFER_LEITURA];
    strcpy(caminhoIndex, nomePasta);
    strcat(caminhoIndex, "/index.txt");
    FILE *index = fopen(caminhoIndex, "r");

    //Lê o index e cria a lista
    ListaDocumentos *listaDocs = initListaDocumentos();
    char leitura[BUFFER_LEITURA];
    *numDocs = 0;
    while(fscanf(index, "%s\n", leitura) == 1){
        //printf("%s\n", leitura);
        Documento *novoDoc = initDocumento(leitura);
        listaDocs = adicionaDocumentoLista(listaDocs, novoDoc);
        (*numDocs)++;
    }
    
    fclose(index);
    return listaDocs;
}

void leGrafo(ListaDocumentos *todosDocumentos, char *nomePasta){
    //Abre arquivo
    char caminhoGrafo[BUFFER_LEITURA];
    strcpy(caminhoGrafo, nomePasta);
    strcat(caminhoGrafo, "/graph.txt");
    FILE *graph = fopen(caminhoGrafo, "r");

    //Lê o grafo 
    char leitura[BUFFER_LEITURA];
    int nLinks=0;
    while(fscanf(graph, "%s", leitura) == 1){
        //printf("%s ", leitura);
        //Encontra documento com nome lido
        Documento *docAtual = buscaDocumentoPorNome(todosDocumentos, leitura);
        //Lê quantos links de saída tem no documento
        fscanf(graph, "%d", &nLinks);
        //printf("%d ", nLinks);
        //Lê os links de saída
        for(int i=0; i<nLinks; i++){
            fscanf(graph, "%s", leitura);
            //printf("%s ", leitura);
            Documento *docOut = buscaDocumentoPorNome(todosDocumentos, leitura);
            adicionaLinkOut(docAtual, docOut);
        }
        //printf("\n");
    }
    
    fclose(graph);
}

RBT* leStopWords(RBT* arvore, char* nomePasta){
    //Abre arquivo
    char caminhoSW[BUFFER_LEITURA];
    strcpy(caminhoSW, nomePasta);
    strcat(caminhoSW, "/stopwords.txt");
    FILE *stopWords = fopen(caminhoSW, "r");

    //Lê as Stop Words e cria a árvore rubro negra
    char leitura[BUFFER_LEITURA];
    while(fscanf(stopWords, "%s\n", leitura) == 1){
        //printf("%s\n", leitura);        
        arvore = RBT_insert(arvore, leitura, NULL);
    }
    
    fclose(stopWords);
    return arvore;
}

RBT* lePaginas(ListaDocumentos *todosDocumentos, RBT *stopWords, char *nomePasta){
    RBT *rbtWorld = NULL;
    
    //Abre arquivo
    char caminhoPaginas[BUFFER_LEITURA];
    strcpy(caminhoPaginas, nomePasta);
    strcat(caminhoPaginas, "/pages/");

    while(todosDocumentos != NULL){
        Documento *documentoAtual = retornaElementoDaLista(todosDocumentos);

        char caminhoPagina[BUFFER_LEITURA];
        strcpy(caminhoPagina, caminhoPaginas);
        strcat(caminhoPagina, retornaNomeDocumento(documentoAtual));
        //printf("\n\n%s :\n", caminhoPagina);
        FILE *page = fopen(caminhoPagina, "r");

        //Lê  
        char leitura[BUFFER_LEITURA];
        while(fscanf(page, "%s", leitura) == 1){
            //printf("%s\n", leitura);
            //Verifica se a palavra está em stopwords
            if(RBT_search(stopWords, leitura) == NULL) continue;

            //Se não está, adiciona na árvore World
            rbtWorld = RBT_insert(rbtWorld, leitura, documentoAtual);
        }
        
        fclose(page);
        todosDocumentos = retornaProximaCelulaLista(todosDocumentos);
    }

    return rbtWorld;
}


///////////////////////Funções de testes
///////////////////////
void ImprimeLista(ListaDocumentos *lista){
    printf("Imprimindo lista:\n");
    while(lista != NULL){
        Documento *doc = retornaElementoDaLista(lista);
        printf("%s IN: ", retornaNomeDocumento(doc));
        ListaDocumentos *links = retornaListaLinksIn(doc);
        while(links != NULL){
            Documento *docIn = retornaElementoDaLista(links);
            printf("%s ", retornaNomeDocumento(docIn)); 

            links = retornaProximaCelulaLista(links);
        }

        links = retornaListaLinksOut(doc);
        printf(" // OUT: ");
        while(links != NULL){
            Documento *docIn = retornaElementoDaLista(links);
            printf("%s ", retornaNomeDocumento(docIn)); 

            links = retornaProximaCelulaLista(links);
        }

        printf("\n");
        lista = retornaProximaCelulaLista(lista);
    }
}

int main(int argc, char** argv){
    //Verifica se passou o nome da pasta
    if(argc != 2){
        printf("Erro! Passe o nome da pasta com a entrada\n");
        return 1;
    }
    char* nomePasta = argv[1];

    //Index
    int numDocs = 0;
    ListaDocumentos *todosDocumentos = leIndex(nomePasta, &numDocs);

    //Graph
    leGrafo(todosDocumentos, nomePasta);

    //StopWords
    RBT* rbtStop = NULL;
    rbtStop = leStopWords(rbtStop, nomePasta);

    //Pages
    RBT* rbtWorld = lePaginas(todosDocumentos, rbtStop, nomePasta);

    ////////////////////////////
    ///// TESTES ///////////////

    ImprimeLista(todosDocumentos);


    //Libera as estruturas
    destroiListaDocumentosEDocumentos(todosDocumentos); 
    destroiRBT(rbtStop);
    destroiRBT(rbtWorld);

    return 0;
}