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

Documento** procuraDocumentos(char* args, ListaDocumentos *todosDocumentos, RBT *rbtWords){
    char s[2] = " ";
    char* token = strtok(args, s);

    ListaDocumentos *intersecaoDocumentos;
    if(token != NULL){
        //Busca na árvore a lista de documentos
        intersecaoDocumentos = retornaListaRBT(RBT_search(rbtWords, token));
        intersecaoDocumentos = intersecaoDuasListas(intersecaoDocumentos, intersecaoDocumentos);
    }    

    ListaDocumentos *aux = NULL;
    token = strtok(NULL, s);
    while (token != NULL) {
        //printf("%s\n", token);
        //Busca na árvore a lista de documentos
        ListaDocumentos *documentosTermo = retornaListaRBT(RBT_search(rbtWords, token));

        //compara com a lista de documentos que contém todos os termos até agora
        //Passa por todos os elementos em intersecao, se um documento não estiver presente em documentosTermo, removemos ele de interseção
        aux = intersecaoDuasListas(intersecaoDocumentos, documentosTermo);
        destroiListaDocumentos(intersecaoDocumentos);
        intersecaoDocumentos = aux;        
    
        
        token = strtok(NULL, s);
    }

    //Passar a lista para um vetor, para ordenar a saída
    int i = 0, numElementos = numDocumentosLista(intersecaoDocumentos);
    Documento** vet = (Documento**)malloc(sizeof(Documento*)*(numElementos+1));//LIBERAR
    ListaDocumentos *p = intersecaoDocumentos;

    for(p = intersecaoDocumentos; p != NULL; p = retornaProximaCelulaLista(p)){
       vet[i] = retornaElementoDaLista(p);
       i++;
    }
    vet[i]=NULL;

    qsort(vet, numElementos, sizeof(Documento*), comparaDocumento);
    destroiListaDocumentos(intersecaoDocumentos);

    return vet; 
}

/*

search:abacate ruim
pages:c.txt b.txt
pr:0.74067344 0.09541328

tar -xzvf 2004209608.tar.gz
make
./trab3 /tmp/data/

*/


void imprimeResultado(Documento **resultado, char *args){
    int i=0;
    printf("\npages:");
    for(i=0; resultado[i] != NULL; i++){
        printf("%s ", retornaNomeDocumento(resultado[i]));
    }
    printf("\npr:");
    for(i=0; resultado[i] != NULL; i++){
        printf("%lf ", retornaPageRank(resultado[i]));
    }
    printf("\n");
}

///////////////////////Funções de testes///////////////////////
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
    RBT* rbtWords = lePaginas(todosDocumentos, rbtStop, nomePasta);

    //Cálculo do page rank de todas as páginas (documentos)
    calculaPageRank(todosDocumentos, numDocs);

    char leitura[1000]; //Perguntar pro giovanni tamanho das entradas
    while(scanf("%[^\n]s\n", leitura) == 1){
        //Imprime a pesquisa
        printf("search:%s", leitura);
        Documento **resultado = procuraDocumentos(leitura, todosDocumentos, rbtWords);
        //Imprime o resultado dessa busca
        imprimeResultado(resultado, leitura);

        free(resultado);
    }

    ////////////////////////////
    ///// TESTES ///////////////

    //ImprimeLista(todosDocumentos);
    /*printf("\n\nSTOP:\n");
    imprimeRBT(rbtStop);
    printf("\n\nWORD:\n");
    imprimeRBT(rbtWords);*/


    //Libera as estruturas
    destroiListaDocumentosEDocumentos(todosDocumentos); 
    destroiRBT(rbtStop);
    destroiRBT(rbtWords);

    return 0;
}