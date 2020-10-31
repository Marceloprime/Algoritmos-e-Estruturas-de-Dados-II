//Nome: Marcelo Augusto dos Reis nUSP: 10844309 - Sistemas da Informacao
/*Trabalho 4 - Dupla
NOME: Marcelo Augusto dos Reis
Nusp: 10844309
NOME: João Vitor Monteiro
Nusp: 10691932
*/
#include "Parte4.h"


int main(){
    //variavel para guarda a opcao
    int opcao;
    int acessos;
    //variaveis de entrada
    char nome_de_arquivo[50],nome_campo[50],valor[50],arquivo_de_Indices[50];
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
            funcionalidade3(nome_de_arquivo,nome_campo,valor,&acessos);
        }
        else if(opcao == 4){
            int RRN;
            scanf("%s",nome_de_arquivo);
            scanf(" %d",&RRN);
            //Essa opcao realizar busca atraves do RRN
            funcionalidade4(nome_de_arquivo,RRN);
        }
        else if(opcao == 5){
            int n_vezes;
            scanf("%s",nome_de_arquivo);
            scanf("%d",&n_vezes);
            //Essa opcao realizar a remocao logica dos registro utilizado
            //a abordagem dinamica com pilha
            funcionalidade5(nome_de_arquivo,n_vezes);
        }
        else if(opcao == 6){
            int n_vezes;
            scanf("%s ",nome_de_arquivo);
            scanf("%d",&n_vezes);
            //Essa opcao realizar a insercao dos registro utilizado
            //a abordagem dinamica com pilha
            funcionalidade6(nome_de_arquivo,n_vezes);

        }
        else if(opcao == 7){
            int RRN;
            int n_vezes;
            scanf("%s ",nome_de_arquivo);
            scanf("%d",&n_vezes);
            //Essa opcao realizar a atualizacao no documento atraves do campo
            funcionalidade7(nome_de_arquivo,n_vezes);
        }
        else if(opcao == 8){
            /*Trabalho 3 - Dupla
            NOME: Marcelo Augusto dos Reis
            Nusp: 10844309
            NOME: João Vitor Monteiro
            Nusp: 10691932
            */
            char arquivodesaida[80];
            scanf("%s ",nome_de_arquivo);
            scanf(" %s",arquivodesaida);
            funcionalidade8(nome_de_arquivo,arquivodesaida);

        }
        else if(opcao == 9){
            char arquivodesaida[80];
            char arquivo2[80];
            scanf("%s ",nome_de_arquivo);
            scanf("%s",arquivo2);
            scanf(" %s",arquivodesaida);
            funcionalidade9(nome_de_arquivo,arquivo2,arquivodesaida);

        }
        else if(opcao == 10){
            char arquivodesaida[80];
            char arquivo2[80];
            scanf("%s ",nome_de_arquivo);
            scanf("%s ",arquivo2);
            scanf("%s",arquivodesaida);
            funcionalidade10(nome_de_arquivo,arquivo2,arquivodesaida);

        }
        else if(opcao == 11){
            /*Trabalho 4 - Dupla
            NOME: Marcelo Augusto dos Reis
            Nusp: 10844309
            NOME: João Vitor Monteiro
            Nusp: 10691932
            */
            char arquivodesaida[80];
            scanf("%s ",nome_de_arquivo);
            scanf(" %s",arquivodesaida);
            //Essa funcao gera um arquivo de indicie,com o campo
            //nomeEscola com indicie secundario fortemente ligado
            funcionalidade11(nome_de_arquivo,arquivodesaida);
        }
        else if(opcao == 12){
            scanf("%s ",nome_de_arquivo);
            scanf("%s ",arquivo_de_Indices);
            scanf("%s ",nome_campo);
            scan_quote_string(valor);
            //Essa funcao realizar a busca usado o nome escola como chave
            //de busca e um arquivo de indicie para realizar
            //busca de um registros
            funcionalidade12(nome_de_arquivo,arquivo_de_Indices,nome_campo,valor,&acessos);
        }
        else if(opcao == 13){
            int n_vezes;
            scanf("%s ",nome_de_arquivo);
            scanf("%s ",arquivo_de_Indices);
            scanf("%d",&n_vezes);
            //Essa opcao realizar a remocao logica dos registro utilizado
            //a abordagem dinamica com pilha e arquivoIndices para a busca
            funcionalidade13(nome_de_arquivo,arquivo_de_Indices,n_vezes);
        }
        else if(opcao == 14){
            int n_vezes;
            scanf("%s ",nome_de_arquivo);
            scanf("%s ",arquivo_de_Indices);
            scanf("%d",&n_vezes);
            //Essa opcao realizar a insercao dos registro utilizado
            //a abordagem dinamica com pilha e arquivo de indicies
            funcionalidade14(nome_de_arquivo,arquivo_de_Indices,n_vezes);

        }
        else if(opcao == 15){
            scanf("%s ",nome_de_arquivo);
            scanf("%s ",arquivo_de_Indices);
            scanf("%s ",nome_campo);
            scan_quote_string(valor);
            //Realizar uma comparacao de desempenho entre a funcionalidade3 e a
            //funcionalidade12
            funcionalidade15(nome_de_arquivo,arquivo_de_Indices,nome_campo,valor);
        }

    return 0;
}
