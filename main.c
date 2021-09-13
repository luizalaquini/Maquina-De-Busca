#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arvore_rubro_negra.h"
#include "documento.h"
#include "listadocumentos.h"

#define BUFFER_LEITURA 500

ListaDocumentos* leIndex(char* nomePasta, int *numDocs){
    //Cria arquivo
    char caminhoIndex[BUFFER_LEITURA];
    strcpy(caminhoIndex, nomePasta);
    strcat(caminhoIndex, "/index.txt");
    FILE *index = fopen(caminhoIndex, "r");

    //Lê o index e cria a lista
    ListaDocumentos *listaDocs = initListaDocumentos();
    char leitura[BUFFER_LEITURA];
    while(fscanf(index, "%s\n", leitura) == 1){
        printf("%s\n", leitura);
        Documento *novoDoc = initDocumento(leitura);
        listaDocs = adicionaDocumentoLista(listaDocs, novoDoc);
    }
    
    fclose(index);
    return listaDocs;
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

    //StopWords
    RBT* rbtStop = NULL;

    //Pages
    RBT* rbtWorld = NULL;




    //Libera as estruturas
    destroiListaDocumentosEDocumentos(todosDocumentos);    

    return 0;
}