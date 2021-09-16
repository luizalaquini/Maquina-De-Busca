#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arvore_rubro_negra.h"
#include "documento.h"
#include "listadocumentos.h"
#include "leitura.h"

#define alpha 0.85


double calculaMudancaPageRank(ListaDocumentos *todosDocumentos, int numDocumentos){
    double mudanca = 0;
    while(todosDocumentos != NULL){
        Documento *doc = retornaElementoDaLista(todosDocumentos);
        double diferenca = retornaPageRank(doc) - retornaPageRankAnterior(doc);
        if(diferenca < 0.0) diferenca = -diferenca;
        mudanca += diferenca;

        todosDocumentos = retornaProximaCelulaLista(todosDocumentos);
    }
    return mudanca/numDocumentos;
}

//Função para cálculo do pagerank
void calculaPageRank(ListaDocumentos *todosDocumentos, int numDocumentos){
    //Inicializa todos os documentos com pagerank 1/n
    ListaDocumentos *lista = todosDocumentos;
    while(lista != NULL){
        Documento *doc = retornaElementoDaLista(lista);
        setPageRankAnterior(doc, 0);
        setPageRank(doc, (1.0/numDocumentos));
        lista = retornaProximaCelulaLista(lista);
    }

    //Laço computando o pagerank até que o erro seja menor que 
    while(calculaMudancaPageRank(todosDocumentos, numDocumentos) > 0.000001){
        //Atualiza o pagerank anterior com o pagerank da última iteração
        lista = todosDocumentos;
        while(lista != NULL){
            Documento *doc = retornaElementoDaLista(lista);
            setPageRankAnterior(doc, retornaPageRank(doc));
            lista = retornaProximaCelulaLista(lista);
        }

        //Calcula os pageranks atuais com base nos pageranks anteriores
        lista = todosDocumentos;
        while(lista != NULL){
            Documento *doc = retornaElementoDaLista(lista);
            
            double pageRank = (1 - alpha)/numDocumentos;
            double influenciaIn = 0;
            //Calcula influência das páginas que tem link para doc
            ListaDocumentos *paginasIn = retornaListaLinksIn(doc);
            while(paginasIn != NULL){
                influenciaIn += retornaPageRankAnterior(retornaElementoDaLista(paginasIn)) /
                                numDocumentosLista(retornaListaLinksOut(retornaElementoDaLista(paginasIn)));

                paginasIn = retornaProximaCelulaLista(paginasIn);
            }
            pageRank = pageRank + alpha*influenciaIn; 

            //Verifica a condição |Out(i)|=0
            if(retornaListaLinksOut(doc) == NULL){
                pageRank += alpha * retornaPageRankAnterior(doc);
            }

            setPageRank(doc, pageRank); 

            lista = retornaProximaCelulaLista(lista);
        }
    }
}


///////////////////////Funções de testes
///////////////////////
void ImprimeLista(ListaDocumentos *lista){
    printf("Imprimindo lista:\n");
    while(lista != NULL){
        Documento *doc = retornaElementoDaLista(lista);
        printf("%s PR: %lf IN: ", retornaNomeDocumento(doc), retornaPageRank(doc));
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

    //Realização das leituras de arquivos
    //Index
    int numDocs = 0;
    ListaDocumentos *todosDocumentos = leIndex(nomePasta, &numDocs);
    //Graph
    leGrafo(todosDocumentos, nomePasta);
    //StopWords
    RBT* rbtStop = NULL;
    rbtStop = leStopWords(rbtStop, nomePasta);
    //Pages
    RBT* rbtWord = lePaginas(todosDocumentos, rbtStop, nomePasta);

    //Cálculo do page rank de todas as páginas (documentos)
    calculaPageRank(todosDocumentos, numDocs);



    ////////////////////////////
    ///// TESTES ///////////////

    ImprimeLista(todosDocumentos);
    /*printf("\n\nSTOP:\n");
    imprimeRBT(rbtStop);
    printf("\n\nWORD:\n");
    imprimeRBT(rbtWord);*/


    //Libera as estruturas
    destroiListaDocumentosEDocumentos(todosDocumentos); 
    destroiRBT(rbtStop);
    destroiRBT(rbtWord);

    return 0;
}