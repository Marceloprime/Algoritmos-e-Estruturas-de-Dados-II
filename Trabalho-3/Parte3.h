#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*Trabalho 3 - Dupla
NOME: Marcelo Augusto dos Reis
Nusp: 10844309
NOME: João Vitor Monteiro
Nusp: 10691932
*/
typedef struct{
    char status;
    int pilha;
    char resto[15995];
}Cabecalho_leitura;

typedef struct{
    char removido;
    int encadeamento;
    int nroInscricao;
    double nota;
    char data[10];
    int indicador_Tam;
    char tagCampo;
    char *cidade;
    int indicador_Tam2;
    char tagCampo2;
    char *nomeEscola;
    char *lixo;
}Registros_leitura;



void funcionalidade8(char nome_de_arquivo[], char arquivodesaida[]);
void funcionalidade9(char nome_de_arquivo[], char arquivo2[],char arquivodesaida[]);
void funcionalidade10(char nome_de_arquivo[], char arquivo2[],char arquivodesaida[]);
