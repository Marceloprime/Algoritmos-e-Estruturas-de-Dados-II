//.h das funcionalidades utilizadas
#include "Parte1.h"
#include "Parte2.h"
#include "Parte3.h"

//Bibliotecas utilizadas
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Stucts do arquivo de indicies
typedef struct {
    char status;
    int nroRegistros;
    char resto[15995];
}Cabecalho_do_arquivo_indice;


typedef struct {
    char chave[28];
    int RRN;
}Indices;


//Assinaturas de funcoes, que usam arquivo de indicies
void funcionalidade11(char nome_de_arquivo[],char arquivodesaida[]);//Criacao de arquivo de indicies
void funcionalidade12(char nome_de_arquivo[],char arquivo_de_Indices[],char nome_campo[],char valor[],int *acessos);//Busca
void funcionalidade13(char nome_de_arquivo[],char arquivo_de_Indices[],int n_vezes);//Remocao
void funcionalidade14(char nome_de_arquivo[], char arquivo_de_Indices[], int n_vezes);//insercao
void funcionalidade15(char nome_de_arquivo[],char arquivo_de_Indices[],char nome_campo[],char valor[]);//compacao
