#include "leitura.h"

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LEITURA 500

//Funções auxiliares

char* stringToLower(char* string){
    int i=0;
    while(string[i] != '\0'){
        if(string[i] >= 'A' && string[i] <= 'Z'){
            string[i] = string[i] + ('a' - 'A');
        }
        i++;
    }
    return string;
}

//Funções de leitura

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
            //printf("DocOut: %s\n", leitura);
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
        stringToLower(leitura);
        //printf("%s\n", leitura);        
        arvore = RBT_insert(arvore, leitura, NULL);
    }
    
    fclose(stopWords);
    return arvore;
}

RBT* lePaginas(ListaDocumentos *todosDocumentos, RBT *stopWords, char *nomePasta){
    RBT *rbtWord = NULL;
    
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

        //Lê as palavras da página
        char leitura[BUFFER_LEITURA];
        while(fscanf(page, "%s", leitura) == 1){
            stringToLower(leitura);
            //printf("%s\n", leitura);
            //Verifica se a palavra está em stopwords
            if(RBT_search(stopWords, leitura) == NULL){
                //Se não está, adiciona na árvore World
                rbtWord = RBT_insert(rbtWord, leitura, documentoAtual);
            }            
        }
        
        fclose(page);
        todosDocumentos = retornaProximaCelulaLista(todosDocumentos);
    }

    return rbtWord;
}