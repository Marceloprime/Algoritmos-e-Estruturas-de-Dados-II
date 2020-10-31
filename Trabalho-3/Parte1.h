//Bibliotecas utilizadas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct usadas para o cabecalho
typedef struct{
    char status;
    int topo_pilha_RRN;

    //Tag dos campos
    char tagCampo1;
    char tagCampo2;
    char tagCampo3;
    char tagCampo4;
    char tagCampo5;

    //Descricao dos campos
    char desCampo1[55];
    char desCampo2[55];
    char desCampo3[55];
    char desCampo4[55];
    char desCampo5[55];

}Cabecalho;

//struct usada para os dados
typedef struct{
    //  Campos de tamanho fixo
    char removido;
    int encadeamento;
    int nroInscricao;
    float nota;
    char data[10];
    // Campos de tamanho variavel
    int indicador_Tam_cidade;
    char tagCampo4;
    char *cidade;
    int indicador_Tam_nomeEscola;
    char tagCampo5;
    char *nomeEscola;
    //auxiliador na contagem de bytes do registro
    int aux_pag;

}Registro_de_Dados;


//Funcoes do Trabalho 1
void funcionalidade1(char nome_de_arquivo[]);
void funcionalidade2(char nome_de_arquivo[]);
void funcionalidade3(char arquivo[], char nome_campo[], char valor[]);
void funcionalidade4(char arquivo[], int RRN);

//Funcoe do Trabalho 2
