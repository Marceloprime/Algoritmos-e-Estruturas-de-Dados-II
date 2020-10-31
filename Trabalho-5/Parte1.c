#include "Parte1.h"


// Essa funcao e reponsavel por Preencher o cabecalho
Cabecalho_de_arquivo *Preencher_cabecalho(char string[]){
    Cabecalho_de_arquivo *cabecalho;
    cabecalho = (Cabecalho_de_arquivo*) malloc (sizeof(Cabecalho_de_arquivo));
    cabecalho->status = '1';//1 indica que arquivo não foi corrompido e 0 o oposto
    cabecalho->topo_pilha_RRN = -1;
    //Tags
    cabecalho->tagCampo1 = '1';
    cabecalho->tagCampo2 = '2';
    cabecalho->tagCampo3 = '3';
    cabecalho->tagCampo4 = '4';
    cabecalho->tagCampo5 = '5';

    int j,k,cont;


    for(j = 0, k=0;string[j] != ',';j++,k++){
        cabecalho->desCampo1[k] = string[j];//Número de inscricao
    }
    cabecalho->desCampo1[k] = '\0';

    for(cont = k+1; cont < 55;cont++){
        cabecalho->desCampo1[cont] = '@';
    }

    /////////////////////////////////////////////////////
    for(j = j+1, k=0;string[j] != ',';j++,k++){
        cabecalho->desCampo2[k] = string[j];//Nota do aluno
    }
    cabecalho->desCampo2[k] = '\0';

    for(cont = k+1; cont < 55;cont++){
        cabecalho->desCampo2[cont] = '@';
    }
    //////////////////////////////////////////////////////
    for(j = j+1, k=0;string[j] != ',';j++,k++){
        cabecalho->desCampo3[k] = string[j];//data
    }
    cabecalho->desCampo3[k] = '\0';

    for(cont = k+1; cont < 55;cont++){
        cabecalho->desCampo3[cont] = '@';
    }
    /////////////////////////////////////////////////////
    for(j = j+1,k=0;string[j] != ',';j++,k++){
        cabecalho->desCampo4[k] = string[j];//Cidade
    }

    cabecalho->desCampo4[k] = '\0';

    for(cont = k+1; cont < 55;cont++){
        cabecalho->desCampo4[cont] = '@';
    }
    /////////////////////////////////////////////////////
    for(j = j+1,k=0;string[j] != '0';j++,k++){
        cabecalho->desCampo5[k] = string[j];//Nome da escola
    }

    cabecalho->desCampo5[k] = '\0';

    for(cont = k+1; cont < 55;cont++){
        cabecalho->desCampo5[cont] = '@';
    }


    return cabecalho;
}

/////////////////////////////////////////////////////////////////////////////////

Registro_de_Dados *Preencher_dados(char string[]){
    Registro_de_Dados *dados;
    dados = (Registro_de_Dados*) malloc (sizeof(Registro_de_Dados));
    //////////////////////////////////////////
    int aux_pag = 0;
    char *aux_Nulo = (char*) malloc (10*sizeof(char));
    strcpy(aux_Nulo,"\0@@@@@@@@@");
    ////////////////////////////////
    dados->removido = '-';
    aux_pag++;
    dados->encadeamento = -1;
    aux_pag += 4;
    ////////////////////////////////

    char *aux;
    aux = (char*) malloc (10*sizeof(char));
    int j,k,flag=0;
    for(j = 0, k=0;string[j] != ',';j++,k++){
        aux[k] = string[j];//Número de inscricao
        flag++;
    }

    if(flag == 0){
        dados->nroInscricao = -1;
    }
    else{
        dados->nroInscricao = atoi(aux);
    }
    flag = 0;
    aux_pag += 4;
    free(aux);
    //////////////////////////////////////////
    char *aux1;
    aux1 = (char*) malloc (80*sizeof(char));
    for(j = j+1,k=0;string[j] != ',';j++,k++){
        aux1[k] = string[j];//Nota;
        flag++;
    }

    if( flag == 0){
        dados->nota = -1.0;
    }
    else{
        dados->nota = atof(aux1);
    }
    flag = 0;
    aux_pag += 8;
    free(aux1);

    ///////////////////////////////////////////////
    for(j = j+1,k=0;string[j] != ',';j++,k++){
        dados->data[k] = string[j];//Data;
        flag++;
    }
    if(flag == 0){
        strcpy(dados->data,aux_Nulo);
    }
    else{
        j++;
    }
    flag = 0;
    aux_pag += 10;

    ////////////////////////////////////////

    dados->tagCampo4 = '4';
    //printf("%c",dados->tagCampo4);
    aux_pag++;

    int indicador_Tam_cid = -1;

    char *aux_cidade;
    aux_cidade = (char*) malloc (80*sizeof(char));
    for(j = j,k=0;string[j] != ',';j++,k++){
        indicador_Tam_cid++;
        aux_pag++;
        aux_cidade[k] = string[j];
    }
    if(indicador_Tam_cid == -1){
        dados->indicador_Tam_cidade = indicador_Tam_cid;
        dados->cidade = (char*) malloc (10*sizeof(char));
        strcpy(dados->cidade,aux_Nulo);
    }
    else{
        dados->indicador_Tam_cidade = indicador_Tam_cid+1;
        dados->cidade = (char*) malloc ((indicador_Tam_cid+1)*sizeof(char));
        strcpy(dados->cidade,aux_cidade);
    }
    free(aux_cidade);
////////////////////////////////////////////////////////////////////////////////

    dados->tagCampo5 = '5';
    aux_pag++;

    int indicador_Tam_nomeEsc = 0;
    char *aux_nomeEscola;

    int aux_cont = 0 ;
    for(aux_cont = j+1;string[aux_cont] != '\0';aux_cont++){
        indicador_Tam_nomeEsc++;
        aux_pag++;
    }

    if(indicador_Tam_nomeEsc == 0){
        dados->indicador_Tam_cidade = -1;
        dados->nomeEscola = (char*) malloc (10*sizeof(char));
        strcpy(dados->nomeEscola,aux_Nulo);
    }
    else{
        dados->indicador_Tam_nomeEscola = indicador_Tam_nomeEsc;
        dados->nomeEscola = (char*) malloc (indicador_Tam_nomeEsc*sizeof(char));
        for(j = j+1,k=0;string[j] != '\0';j++,k++){
            dados->nomeEscola[k] = string[j];
        }

    }
    free(aux_Nulo);
    aux_pag += 4;//indicador de tamanho Cidade
    aux_pag += 4;//indicador de tamanho da Escola

    dados->aux_pag = aux_pag;

    return dados;

}



void funcionalidade1(char nome_de_arquivo[]){
    //Arquivos
    FILE *arquivo;
    FILE *arquivoTrab1si;

    //Abertura dos arquivos
    arquivo = fopen(nome_de_arquivo,"r");
    if(arquivo == NULL){
        printf("Falha no carregamento do arquivo.\n");
        return;
    }
    arquivoTrab1si = fopen("arquivoTrab1si.bin","wb");
    if(arquivoTrab1si == NULL){
        printf("Erro ao abrir o arquivoTrab1si.bin\n");
        return;
    }
    //////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    //String que sera utilizada na leitura dos registro do arquivo csv
    char *string;
    string = (char*) malloc (80*sizeof(char));
    ////////////////////////////////////////////////////////////////////////
    /*Declaracao das structs que serao usadas com aux na leitura do arquivos*/
    Registro_de_Dados *dados;
    dados = (Registro_de_Dados*) malloc (sizeof(Registro_de_Dados));
    Cabecalho_de_arquivo *cab1;
    cab1 = (Cabecalho_de_arquivo*) malloc (sizeof(Cabecalho_de_arquivo));
    ////////////////////////////////////////////////////////////////////////
    int flag = 0,tam = 80;
    while(fgets(string,tam,arquivo)){

        if(flag == 0){
            char status = cab1->status;
            fwrite(&status,sizeof(char),1,arquivoTrab1si);
            int topo_pilha_RRN = cab1->topo_pilha_RRN;
            fwrite(&topo_pilha_RRN,sizeof(int),1,arquivoTrab1si);
            ///////////////////////////////////////////////////////////
            char tagCampo1 = cab1->tagCampo1;
            fwrite(&tagCampo1,sizeof(char),1,arquivoTrab1si);
            char *desCampo1 = (char*) malloc (55*sizeof(char));
            for (int i = 0; i < 55; i++){
                desCampo1[i] = cab1->desCampo1[i];
            }
            free(desCampo1);
            fwrite(&cab1->desCampo1,55*sizeof(char),1,arquivoTrab1si);
            ///////////////////////////////////////////////////////////
            char tagCampo2 = cab1->tagCampo2;
            fwrite(&tagCampo2,sizeof(char),1,arquivoTrab1si);
            char *desCampo2 = (char*) malloc (55*sizeof(char));
            for (int i = 0; i < 55; i++){
                desCampo2[i] = cab1->desCampo2[i];
            }
            free(desCampo2);
            fwrite(desCampo2,sizeof(char),55,arquivoTrab1si);
            /////////////////////////////////////////////////////////////
            char tagCampo3 = cab1->tagCampo3;
            fwrite(&tagCampo3,sizeof(char),1,arquivoTrab1si);
            char *desCampo3 = (char*) malloc (55*sizeof(char));
            for (int i = 0; i < 55; i++){
                desCampo3[i] = cab1->desCampo3[i];
            }
            free(desCampo3);
            fwrite(&cab1->desCampo3,sizeof(char),55,arquivoTrab1si);
            /////////////////////////////////////////////////////////////
            char tagCampo4 = cab1->tagCampo4;
            fwrite(&tagCampo4,sizeof(char),1,arquivoTrab1si);
            char *desCampo4 = (char*) malloc (55*sizeof(char));
            for (int i = 0; i < 55; i++){
                desCampo4[i] = cab1->desCampo4[i];
            }
            fwrite(&desCampo4,sizeof(char),55,arquivoTrab1si);
            free(desCampo4);
            /////////////////////////////////////////////////////////////
            char tagCampo5 = cab1->tagCampo5;
            fwrite(&tagCampo5,sizeof(char),1,arquivoTrab1si);
            char *desCampo5 = (char*) malloc (55*sizeof(char));
            for (int i = 0; i < 55; i++){
                desCampo5[i] = cab1->desCampo5[i];
            }
            fwrite(&desCampo5,sizeof(char),55,arquivoTrab1si);
            free(desCampo5);
            ////////////////////////////////////////////////////////////
            for(int i = 0; i < 15715; i++){
                fputc('@',arquivoTrab1si);
            }

            flag++;
            tam += 80;
            free(cab1);
        }
        else{
            dados = Preencher_dados(string);
            char removido = dados->removido;
            fwrite(&removido,sizeof(char),1,arquivoTrab1si);
            int encadeamento = dados->encadeamento;
            fwrite(&encadeamento,sizeof(int),1,arquivoTrab1si);
            int inscricao = dados->nroInscricao;
            fwrite(&dados->nroInscricao,sizeof(int),1,arquivoTrab1si);
            double nota = dados->nota;
            fwrite(&dados->nota,sizeof(double),1,arquivoTrab1si);
            char data[10];
            strcpy(data,dados->data);
            fwrite(data,10*sizeof(char),1,arquivoTrab1si);

            char tagCampo4 = dados->tagCampo4;
            if(tagCampo4 == '4'){
                fwrite(&tagCampo4,sizeof(char),1,arquivoTrab1si);

                int indicador_Tam_cidade = dados->indicador_Tam_cidade;
                fwrite(&indicador_Tam_cidade,sizeof(int),1,arquivoTrab1si);
                char *cidade = (char*) malloc (dados->indicador_Tam_cidade*sizeof(char));
                for (int i = 0; i < dados->indicador_Tam_cidade; i++){
                    cidade[i] = dados->cidade[i];
                }
                fwrite(&cidade,sizeof(char),dados->indicador_Tam_nomeEscola,arquivoTrab1si);
                free(cidade);
            }

            char tagCampo5 = dados->tagCampo5;
            if(tagCampo5 == '5'){
                fwrite(&tagCampo5,sizeof(char),1,arquivoTrab1si);
                int indicador_Tam_nomeEscola = dados->indicador_Tam_cidade;
                fwrite(&indicador_Tam_nomeEscola,sizeof(int),1,arquivoTrab1si);
                char* nomeEscola = (char*) malloc (dados->indicador_Tam_nomeEscola*sizeof(char));
                for (int i = 0; i < dados->indicador_Tam_nomeEscola; i++){
                    nomeEscola[i] = dados->nomeEscola[i];
                }
                fwrite(&nomeEscola,sizeof(char),dados->indicador_Tam_nomeEscola,arquivoTrab1si);
                free(nomeEscola);
            }

            for(int i = dados->aux_pag ; i <= 80; i++){
                fputc('@',arquivoTrab1si);
            }
            tam += 80;
        }
        free(string);
        free(dados);
        string = (char*) malloc (80*sizeof(char));
    }
    printf("arquivoTrab1si.bin");

    //Fechamento de arquivo e liberacao de ponteiro;
    fclose(arquivoTrab1si);
    fclose(arquivo);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

/*Essa funcao receber uma string(nome do arquivo binario) e realizar a leitura do arquivo e
posteriomente a impressao na tela*/
void funcionalidade2(char nome_de_arquivo[]){
    //Abertura do arquivo no modo leitura
    FILE *arquivoTrab1si;
    arquivoTrab1si = fopen(nome_de_arquivo,"rb");
    //Caso nao seja possivel abrir o arquivo
    if(arquivoTrab1si == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    //verifica se o arquivo esta consistente o nao
    char status;
    fread(&status,sizeof(char),1,arquivoTrab1si);
    if(status == '0'){
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    //fseek usado para pular o cabecalho
    fseek(arquivoTrab1si,1,SEEK_SET);
    int pilha;
    fread(&pilha,sizeof(int),1,arquivoTrab1si);

    fseek(arquivoTrab1si,0,SEEK_END);
    int qtd_registros = (int) (ftell(arquivoTrab1si)-16000)/80;
    fseek(arquivoTrab1si,16000,SEEK_SET);
    //string para os campos
    char nomeEscola[80];
    char cidade[80];

/*No while eh iniciado a leitura que ocorre ate quando o  if na parte final do laco,
se acinonado e da break*/
    int cont = 0;
    char removido;

    while(cont < qtd_registros){

            //eh usado o fread para ler o documento
            fread(&removido,sizeof(char),1,arquivoTrab1si);
            if(removido != '-'){
                fseek(arquivoTrab1si,79,SEEK_CUR);
                cont++;
                continue;
            }
            ////////////////////////////////////////////////
            int encadeamento;
            fread(&encadeamento,sizeof(int),1,arquivoTrab1si);
            //////////////////////////////////////////////

            int inscricao;
            fread(&inscricao,sizeof(int),1,arquivoTrab1si);
            printf("%d",inscricao);
            ///////////////////////////////////////////////
            double nota;
            fread(&nota,sizeof(double),1,arquivoTrab1si);
            //tratamento, caso a nota seja nula
            if(nota > 0){
                printf(" %.1lf",nota);
            }
            ///////////////////////////////////////////////
            char data[10];
            fread(&data,sizeof(char),10,arquivoTrab1si);
            //tratamento, caso a data seja nula, nada eh imprinda
            if(data[0] != '\0')
                printf(" %.10s",data);
            /////////////////////////////////////////
            int indicador_Tam;
            fread(&indicador_Tam,sizeof(int),1,arquivoTrab1si);

            char tagCampo;
            fread(&tagCampo,sizeof(char),1,arquivoTrab1si);

            //Caso haja um campo nulo, ele verifica com a tag qual campo eh;
            if(tagCampo == '4'){
                //Se for o campo 4
                printf(" %d ",indicador_Tam-2);
                fread(&cidade,sizeof(char),indicador_Tam-1,arquivoTrab1si);
                for(int i=0;i<indicador_Tam-2;i++){
                    printf("%c",cidade[i]);
                }
                ///////////////////////////
                fread(&indicador_Tam,sizeof(int),1,arquivoTrab1si);
                char tagCampo;
                fread(&tagCampo,sizeof(char),1,arquivoTrab1si);

                if(tagCampo == '5'){
                    //Se o campo 4 existir e o 5 tambem
                    printf(" %d ",indicador_Tam-2);
                    fread(&nomeEscola,sizeof(char),indicador_Tam-1,arquivoTrab1si);
                    for(int i=0;i<indicador_Tam-2;i++){
                        printf("%c",nomeEscola[i]);
                    }
                }
            }
            else if(tagCampo == '5'){
                //Se for o campo 5 e o 4 nao existir
                printf(" %d ",indicador_Tam-2);
                fread(&nomeEscola,sizeof(char),indicador_Tam-1,arquivoTrab1si);
                for(int i=0;i<indicador_Tam-2;i++){
                    printf("%c",nomeEscola[i]);
                }
            }
            printf("\n");

            //Lixo
            char lixo;
            fread(&lixo,sizeof(char),1,arquivoTrab1si);
            int i = 0;
            while(lixo == '@'){
                i++;
                fread(&lixo,sizeof(char),1,arquivoTrab1si);
                if(i > 80){
                    break;
                }
            }
            fseek(arquivoTrab1si,-1,SEEK_CUR);

            cont++;
            //Posicao
    }

    printf("Número de páginas de disco acessadas: %ld",((ftell(arquivoTrab1si)/16000)+1));

    fclose(arquivoTrab1si);
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
void impressao_funcionalidade3(FILE *arquivoTrab1si,int RRN) {
        char cidade[80];
        char nomeEscola[80];
        int i;

        fseek(arquivoTrab1si,16000+(RRN*80),SEEK_SET);
        char removido;
        fread(&removido,sizeof(char),1,arquivoTrab1si);
        ////////////////////////////////////////////////
        int encadeamento;
        fread(&encadeamento,sizeof(int),1,arquivoTrab1si);
        //////////////////////////////////////////////
        int inscricao;
        fread(&inscricao,sizeof(int),1,arquivoTrab1si);
        printf("%d",inscricao);
        ///////////////////////////////////////////////
        double nota;
        fread(&nota,sizeof(double),1,arquivoTrab1si);
        //Controlado para nao imprimir elementos nulos
        if(nota > 0){
            printf(" %.1lf",nota);
        }
        ///////////////////////////////////////////////
        char data[10];
        fread(&data,sizeof(char),10,arquivoTrab1si);
        if(data[0] != '\0'){
            printf(" ");
            for(int i=0;i<10;i++){
                printf("%c",data[i]);
            }
        }
        else{
            printf("%s",data);
        }
        /////////////////////////////////////////
        int indicador_Tam;
        fread(&indicador_Tam,sizeof(int),1,arquivoTrab1si);

        char tagCampo;
        fread(&tagCampo,sizeof(char),1,arquivoTrab1si);

        //Caso haja um campo nulo, ele verifica com a tag qual campo eh;
        if(tagCampo == '4'){
            //Se for o campo 4
            printf(" %d",indicador_Tam-2);
            fread(&cidade,sizeof(char),indicador_Tam-1,arquivoTrab1si);
            printf(" %s",cidade);

            //leitura do proximo do indicador e tagCampo
            fread(&indicador_Tam,sizeof(int),1,arquivoTrab1si);
            char tagCampo;
            fread(&tagCampo,sizeof(char),1,arquivoTrab1si);
            if(tagCampo == '5'){
                printf(" %d",indicador_Tam-2);

                fread(&nomeEscola,sizeof(char),indicador_Tam-1,arquivoTrab1si);
                printf(" %s",nomeEscola);
            }
        }
        else if(tagCampo == '5'){
            //Se for o campo 5
            printf(" %d",indicador_Tam-2);
            fread(&nomeEscola,sizeof(char),indicador_Tam-1,arquivoTrab1si);
            printf(" %s",nomeEscola);

        }
        fseek(arquivoTrab1si,16000+(RRN*80)+80,SEEK_SET);
        printf("\n");

}
////////////////////////////////////////////////////////////////////////////////
/*Nessa funcionalidade e passado um campo e um a sttring com o nome de valor
que eh conventida para o tipo de dado do campo que eh buscado*/
void funcionalidade3(char arquivo[], char nome_campo[], char valor[],int *acessos){
    //Abertura do arquivo no modo leitura
    FILE *arquivoTrab1si;
    arquivoTrab1si = fopen(arquivo,"rb+");
    if(arquivoTrab1si == NULL){
        printf("Erro ao abrir o arquivoTrab1si.bin\n");
        return;
    }

    //Cont para contar numeros de paginas
    int cont = 0;
    int qtd;

    //Verificar se o arquivo esta inconsistente
    char status;
    if(status == '0'){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    long int posicao2;
    fseek(arquivoTrab1si,0,SEEK_END);
    posicao2 = ftell(arquivoTrab1si);
    qtd = (int) (ftell(arquivoTrab1si)-16000)/80;
    //Pula o cabecalho
    fseek(arquivoTrab1si,16000,SEEK_SET);

    //Strings e varia auxiliadoras
    char nomeEscola[500];
    char cidade[500];
    int registro = 1;
    int flag = 0;
    int indicador_Tam2;
    int i;
    long int posicao = 15920;
/*A estrategia adotada eh o while roda de maneira 'indeterminada',porem um if na
parte final do arquivo verifica apos ler cada registro se o arquivo chegou
*/
    while(cont < qtd){
            fseek(arquivoTrab1si,posicao+80,SEEK_SET);
            posicao = ftell(arquivoTrab1si);
            if(posicao == posicao2){
                break;
            }
            char removido;
            fread(&removido,sizeof(char),1,arquivoTrab1si);
            //Caso o arquivo estaja removido ele pular para o  proximo
            if(removido != '-'){
                cont++;
                continue;
            }
            ////////////////////////////////////////////////
            int encadeamento;
            fread(&encadeamento,sizeof(int),1,arquivoTrab1si);
            //////////////////////////////////////////////
            //if verifcar se o campo eh o escolhido
            //Se sim transforma a string valor de transforma a String
            //de forma a permitir a compacao
            /*Um ponto importante eh que o numero e inscricao nao
            tem reperticao*/
            if(strcmp(nome_campo,"nroInscricao") == 0){
                //Conversao da string parte
                int valor1 = atoi(valor);
                int inscricao;
                //leitura
                fread(&inscricao,sizeof(int),1,arquivoTrab1si);
                //Se os valores baterem a flag eh acinonada
                if(inscricao == valor1){
//                    impressao_funcionalidade3(arquivoTrab1si,cont);
                    int aux_regis = (int) ftell(arquivoTrab1si)/16000;
                    *acessos = aux_regis;
//                    printf("Número de páginas de disco acessadas: %d\n",aux_regis);
                    return;
                }
            }
            else{
                //Caso nao seja o campo desejado, o codigo
                //continua normalmente
                int inscricao;
                fread(&inscricao,sizeof(int),1,arquivoTrab1si);
            }
            ///////////////////////////////////////////////
            if(strcmp(nome_campo,"nota") == 0){
                double valor2 = atof(valor);
                double nota;
                fread(&nota,sizeof(double),1,arquivoTrab1si);
                if(nota == valor2){
//                    impressao_funcionalidade3(arquivoTrab1si,cont);
                    flag++;
                }
            }
            else{
                double nota;
                fread(&nota,sizeof(double),1,arquivoTrab1si);
            }

            ///////////////////////////////////////////////
            //Apartir daqui nao eh mais necessario realizar
            //transformacoes, as string sao comparadas diretamente
            if(strcmp(nome_campo,"data") == 0){
                char data[10],aux_data[10];
                fread(&data,sizeof(char),10,arquivoTrab1si);
                //tratamento caso o campo seja nulo

                if(data[0] == valor[0] && data[1] == valor[1]){
                    if(data[2] == valor[2] && data[3] == valor[3]){
                        if(data[4] == valor[4] && data[5] == valor[5]){
                            if(data[6] == valor[6] && data[7] == valor[7]){
                                if(data[8] == valor[8] && data[9] == valor[9]){
//                                    impressao_funcionalidade3(arquivoTrab1si,cont);
                                    flag++;
                                }
                            }
                        }
                    }
                }
            }
            else{
                char data[10];
                fread(&data,10*sizeof(char),1,arquivoTrab1si);
            }
            /////////////////////////////////////////

            //Primeiro eh lido o indicador_Tamanho
            int indicador_Tam;
            fread(&indicador_Tam,sizeof(int),1,arquivoTrab1si);

            //Em seguida eh lido a tag
            char tagCampo;
            fread(&tagCampo,sizeof(char),1,arquivoTrab1si);

            //Se a tag for do campo 4 ela entra
            if(tagCampo == '4'){
                //Se for o campo 4
                if(strcmp(nome_campo,"cidade") == 0){
                    fread(cidade,sizeof(char),indicador_Tam-1,arquivoTrab1si);
                    if(strcmp(valor,cidade) == 0){
//                        impressao_funcionalidade3(arquivoTrab1si,cont);
                        flag++;
                    }
                }
                else{
                    fread(cidade,sizeof(char),indicador_Tam-1,arquivoTrab1si);
                }
                fread(&indicador_Tam2,sizeof(int),1,arquivoTrab1si);

                char tagCampo;
                fread(&tagCampo,sizeof(char),1,arquivoTrab1si);

                if(tagCampo == '5'){
                    if(strcmp(nome_campo,"nomeEscola") == 0){
                        fread(nomeEscola,sizeof(char),indicador_Tam2-1,arquivoTrab1si);

                        if(strcmp(valor,nomeEscola) == 0){
//                            impressao_funcionalidade3(arquivoTrab1si,cont);
                            flag++;
                        }
                    }
                    else{
                        fread(nomeEscola,sizeof(char),indicador_Tam2-1,arquivoTrab1si);
                    }

                }
            }
            else if(tagCampo == '5'){
                //Se for o campo 5
                if(strcmp(nome_campo,"nomeEscola") == 0){
                    fread(nomeEscola,sizeof(char),indicador_Tam-1,arquivoTrab1si);

                    if(strcmp(valor,nomeEscola) == 0){
//                        impressao_funcionalidade3(arquivoTrab1si,cont);
                        flag++;
                    }
                }
                else{
                    fread(nomeEscola,sizeof(char),indicador_Tam-1,arquivoTrab1si);
                }

            }
            fseek(arquivoTrab1si,posicao+80,SEEK_SET);
            fread(&removido,sizeof(char),1,arquivoTrab1si);
            if(posicao == ftell(arquivoTrab1si)){
                break;
            }
            cont++;
    }

    if(flag == 0){
//        printf("Registro inexistente.\n");
    }
    else{
        int aux_regis = (int) 1+ftell(arquivoTrab1si)/16000;
        if(aux_regis > 26){
            aux_regis = 26;
        }
        *acessos = aux_regis;
//        printf("Número de páginas de disco acessadas: %d\n",aux_regis);
    }
//////////////////////////////////////////////////////////////////////////////

    //Fechamento do arquivo;
    fclose(arquivoTrab1si);
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*Nessa funcionalidade eh feita a busca usado o RRN, para localizar o registro*/
void funcionalidade4(char arquivo[], int RRN){
    int aux_regis;
    //Verificao se o RRN esta no paramentro existente
    if(RRN > 5000){
        printf("Registro inexistente.\n");

        return;
    }
    else if(RRN < 0){
        printf("Registro inexistente.\n");

        return;
    }
    //Abertura do arquivo
    FILE *arquivoTrab1si;
    arquivoTrab1si = fopen(arquivo,"r+b");
    if(arquivoTrab1si == NULL){
        printf("Erro ao abrir o arquivoTrab1si.bin\n");
        return;
    }
    char nomeEscola[500];
    char cidade[500];
    //O cabecalho eh pulado
    fseek(arquivoTrab1si,16000,SEEK_SET);

    /*O RRN eh multiplicado pelo tamanho do registro*/
    fseek(arquivoTrab1si,(RRN*80),SEEK_CUR);

    char removido;
    fread(&removido,sizeof(char),1,arquivoTrab1si);
    //Verificao se o arquivo esta removido
    if(removido != '-'){
        printf("Registro inexistente.\n");
        return;
    }
    //leitura e impressao do arquivo
    ////////////////////////////////////////////////
    int encadeamento;
    fread(&encadeamento,sizeof(int),1,arquivoTrab1si);
    //////////////////////////////////////////////
    int inscricao;
    fread(&inscricao,sizeof(int),1,arquivoTrab1si);
    printf("%d",inscricao);
    ///////////////////////////////////////////////
    double nota;
    fread(&nota,sizeof(double),1,arquivoTrab1si);
    if(nota > 0){
        printf(" %.1lf",nota);
    }
    ///////////////////////////////////////////////
    char data[10];
    fread(&data,sizeof(char),10,arquivoTrab1si);
    if(data[0] != '\0'){
        printf(" ");
        for(int k = 0;data[k] != '\0',k<10;k++){
            printf("%c",data[k]);
        }
    }
    /////////////////////////////////////////
    int indicador_Tam;
    fread(&indicador_Tam,sizeof(int),1,arquivoTrab1si);

    char tagCampo;
    fread(&tagCampo,sizeof(char),1,arquivoTrab1si);

    //Caso haja um campo nulo, ele verifica com a tag qual campo eh;
    if(tagCampo == '4'){
        //Se for o campo 4
        fread(&cidade,sizeof(char),indicador_Tam-1,arquivoTrab1si);
        printf(" %d",indicador_Tam-2);
        printf(" %s",cidade);
        fread(&indicador_Tam,sizeof(int),1,arquivoTrab1si);
        char tagCampo;
        fread(&tagCampo,sizeof(char),1,arquivoTrab1si);

        if(tagCampo == '5'){
            printf(" %d",indicador_Tam-2);


            fread(&nomeEscola,sizeof(char),indicador_Tam-1,arquivoTrab1si);
            printf(" %s",nomeEscola);
        }
    }
    else if(tagCampo == '5'){
        //Se for o campo 5
        printf(" %d",indicador_Tam-2);
        fread(&nomeEscola,sizeof(char),indicador_Tam-1,arquivoTrab1si);
        printf(" %s",nomeEscola);

    }
    //Leitura do lixo
    char lixo;
    fread(&lixo,sizeof(char),1,arquivoTrab1si);
    while(lixo == '@'){
        fread(&lixo,sizeof(char),1,arquivoTrab1si);
    }
    fseek(arquivoTrab1si,-1,SEEK_CUR);
    printf("\n");
    //Apenas duas paginas sao visitadas
    aux_regis = 2;
    printf("Número de páginas de disco acessadas: %d",aux_regis);
    fclose(arquivoTrab1si);
}
