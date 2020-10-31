//Nome: Marcelo Augusto dos Reis nUSP: 10844309 - Sistemas da Informacao
#include "Parte1.h"

int main(){
    //variavel para guarda a opcao
    int opcao;
    //variaveis de entrada
    char nome_de_arquivo[50],nome_campo[50],valor[50];
    scanf("%d",&opcao);

    ///If de opcoes/////
        if(opcao == 1){
            scanf("%s",nome_de_arquivo);
            //Essa opcao gerar um arquivo binario apartir de um arquivo.csv
            funcionalidade1(nome_de_arquivo);
        }
        else if(opcao == 2){
            scanf("%s",nome_de_arquivo);
            //Essa opcao ler um arquivo binario e imprimir na tela
            funcionalidade2(nome_de_arquivo);
        }
        else if(opcao == 3){
            scanf(" %s",nome_de_arquivo);
            scanf(" %s",nome_campo);//Nome do campo a busca
            scanf(" %[^\n\r]s",valor);//Esse valor sera conventida para outro tipo de dado
            //Essa opcao realizar busca no documento atraves do campo
            funcionalidade3(nome_de_arquivo,nome_campo,valor);
        }
        else if(opcao == 4){
            int RRN;
            scanf("%s",nome_de_arquivo);
            scanf(" %d",&RRN);
            //Essa opcao realizar busca atraves do RRN
            funcionalidade4(nome_de_arquivo,RRN);
        }


    return 0;
}
