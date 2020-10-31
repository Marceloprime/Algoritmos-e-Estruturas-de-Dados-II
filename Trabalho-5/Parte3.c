#include "Parte3.h"

/*Trabalho 3 - Dupla
NOME: Marcelo Augusto dos Reis
Nusp: 10844309
NOME: João Vitor Monteiro
Nusp: 10691932
*/



//Funcao alterei o nome para apenas binarioNaTela
void binarioNaTela(FILE *ponteiroArquivoBinario) {

	/* Escolha essa função se você ainda tem o ponteiro de arquivo 'FILE *' aberto.
	*  Lembrando que você tem que ter aberto ele no fopen para leitura também pra funcionar (exemplo: rb, rb+, wb+, ...) */
	unsigned char *mb;
	unsigned long i;
	size_t fl;
	fseek(ponteiroArquivoBinario, 0, SEEK_END);
	fl = ftell(ponteiroArquivoBinario);
	fseek(ponteiroArquivoBinario, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, ponteiroArquivoBinario);
	for(i = 0; i < fl; i += sizeof(unsigned char)) {
		printf("%02X ", mb[i]);
		if((i + 1) % 16 == 0){
			printf("\n");
		}

	}
	free(mb);
}
///////////////////////////////////////////////////////////////////////////////////
/*Essa funcao verificar se a string passada pode ser usada como nomeEscola de arquivo
binario, ou seja se possui .bin*/

int verifcar_arquivo_binario(char arquivo[]){
    int flag = 0;
    int aux;

	//todos os caractere da string eh analisados
    for(int i=0;i<strlen(arquivo);i++){
        if(arquivo[i] == '.'){//se houver ponto ele guardar a posicao
            aux = i+1;
            flag++;
        }
    }
    if(flag == 1){// se a flag for verdade
        if(arquivo[aux] == 'b' && arquivo[aux+1] == 'i' && arquivo[aux+2] == 'n'){
            return 1;
        }
    }
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////
/*O Cabecalho  do arquivo ehh guardado em uma struct
e a retornado a struct*/
Cabecalho_leitura leitura_cabecalho(FILE *arquivo){
    //variaveis utilizadas
    char status;
    int pilha;
    char buffer;
    char resto[15995];

    //ponteiro no inicio do  arquivo
    fseek(arquivo,0,SEEK_SET);

    //Leitura
    fread(&status,sizeof(char),1,arquivo);
    fread(&pilha,sizeof(int),1,arquivo);
    fread(resto,sizeof(char),15995,arquivo);

    //Salvamento de Informacoes
    Cabecalho_leitura cab_arquivo;

	//eh guardado na struct
    cab_arquivo.status = status;
    cab_arquivo.pilha = pilha;
    for(int i=0;i<15995;i++){
        cab_arquivo.resto[i] = resto[i];
    }

    return cab_arquivo;
}

///////////////////////////////////////////////////////////////////////////////
/*Todos os arquivos sao guardados em um vetor sao retornadaos*/
Registros_leitura *leitura_de_registros(FILE *arquivo, int *qtd_final){
    //Variaveis utilizadas
    int qtd_registros;
    Registros_leitura *registros;
    long int posicao_final;
    char nomeEscola[80];
    char cidade[80];
    int cont = 0, cont2 = 0;
    int tam = 0;
    char removido;
    int encadeamento;
    int inscricao;
    double nota;
    char data[10];
    int indicador_Tam;
    char tagCampo;

	//a qtd de registros eh calculadar(incluir o removidos tambem)
    fseek(arquivo,0,SEEK_END);
    qtd_registros = (int) (ftell(arquivo)-16000)/80;
    posicao_final = ftell(arquivo);
    fseek(arquivo,16000,SEEK_SET);

	//O vetor eh alocado
    registros = (Registros_leitura*) malloc ((qtd_registros+1)*sizeof(Registros_leitura));

	//enquanto cont for menor que o numero de registos
    while(cont < qtd_registros){
            tam = 0;
            //eh usado o fread para ler o documento
            fread(&removido,sizeof(char),1,arquivo);
			//se for removido pular para o proximo registro
            if(removido != '-'){
                fseek(arquivo,79,SEEK_CUR);
                cont++;
                continue;
            }
            //////////////////////////
            //////////////////////////
            registros[cont2].removido = removido;
            tam++;
            ////////////////////////////////////////////////
            fread(&encadeamento,sizeof(int),1,arquivo);
            registros[cont2].encadeamento = encadeamento;
            tam+=4;
            //////////////////////////////////////////////

            fread(&inscricao,sizeof(int),1,arquivo);
            registros[cont2].nroInscricao = inscricao;
            tam+=4;
            ///////////////////////////////////////////////
            fread(&nota,sizeof(double),1,arquivo);
            registros[cont2].nota = nota;
            tam+=8;
            ///////////////////////////////////////////////
            fread(&data,sizeof(char),10,arquivo);
            memcpy(registros[cont2].data,data,10);
            tam+=10;
            /////////////////////////////////////////
            fread(&indicador_Tam,sizeof(int),1,arquivo);

            fread(&tagCampo,sizeof(char),1,arquivo);

            //Caso haja um campo nulo, ele verifica com a tag qual campo eh;
            if(tagCampo == '4'){
                //Se for o campo 4
                registros[cont2].indicador_Tam = indicador_Tam;
                registros[cont2].tagCampo = '4';
                fread(cidade,sizeof(char),indicador_Tam-1,arquivo);
                registros[cont2].cidade = (char*) malloc (sizeof(char)*indicador_Tam-1);
                strcpy(registros[cont2].cidade,cidade);

                ///////////////////////////
                tam+=4;
                tam+=indicador_Tam;

                fread(&indicador_Tam,sizeof(int),1,arquivo);
                fread(&tagCampo,sizeof(char),1,arquivo);
                if(tagCampo == '5'){
                    //Se o campo 4 existir e o 5 tambem
                    registros[cont2].indicador_Tam2 = indicador_Tam;
                    registros[cont2].tagCampo2 = '5';
                    fread(nomeEscola,sizeof(char),indicador_Tam-1,arquivo);
                    registros[cont2].nomeEscola = (char*) malloc (sizeof(char)*indicador_Tam-1);
                    strcpy(registros[cont2].nomeEscola,nomeEscola);

                    tam+=4;
                    tam+=indicador_Tam;
                }
                else{
					//se campo escola nao existir
                    fseek(arquivo,-(sizeof(int) + sizeof(char)), SEEK_CUR);

                    registros[cont2].tagCampo2 = 'x';
                    registros[cont2].indicador_Tam2 = 6;
                    registros[cont2].nomeEscola = (char*) malloc (sizeof(char)*5);
                    strcpy(registros[cont2].nomeEscola,"NULO");
                }
            }
            else if(tagCampo == '5'){
                //Se for o campo 5 e o 4 nao existir
                registros[cont2].tagCampo = 'x';
                registros[cont2].indicador_Tam = 6;
                registros[cont2].cidade = (char*) malloc (sizeof(char)*5);
                strcpy(registros[cont2].cidade,"NULO");

                registros[cont2].indicador_Tam2 = indicador_Tam;
                registros[cont2].tagCampo2 = '5';
                fread(nomeEscola,sizeof(char),indicador_Tam-1,arquivo);
                registros[cont2].nomeEscola = (char*) malloc (sizeof(char)*indicador_Tam-1);
                strcpy(registros[cont2].nomeEscola,nomeEscola);
                tam+=4;
                tam+=indicador_Tam;
            }
            else{
				//se ambos os campos nao existirem
                fseek(arquivo,-(sizeof(int) + sizeof(char)), SEEK_CUR);

                registros[cont2].tagCampo = 'x';
                registros[cont2].indicador_Tam = 6;
                registros[cont2].cidade = (char*) malloc (sizeof(char)*5);
                strcpy(registros[cont2].cidade,"NULO");
                registros[cont2].tagCampo2 = 'x';
                registros[cont2].indicador_Tam2 = 6;
                registros[cont2].nomeEscola = (char*) malloc (sizeof(char)*5);
                strcpy(registros[cont2].nomeEscola,"NULO");


            }

            //Lixo eh calculado
            int i = 0;
            while ((i+tam) < 80){
                i++;
            }
			//alocacao
            registros[cont2].lixo = (char*) malloc (sizeof(char)*(i));
            for(int k=0;k<i;k++){
                registros[cont2].lixo[k] ='@';
            }

            fseek(arquivo,i,SEEK_CUR);

            cont2++;
            cont++;
            //Posicao
    }
    *qtd_final = cont2;
    return registros;
}

/////////////////////////////////////////////////////////////////////////////
//escreve um cabecalho
void escrever_no_arquivo(FILE *arquivo,Cabecalho_leitura cab, Registros_leitura *registros, int qtd_registros){
    //variaveis utilizadas
    int cont = 0;
    int tam = 0;
    fseek(arquivo,0,SEEK_SET);
    //Escrita do cabecalho
    fwrite(&cab.status,sizeof(char),1,arquivo);
    fwrite(&cab.pilha,sizeof(int),1,arquivo);
    fwrite(&cab.resto,sizeof(char),15995,arquivo);
    //Escrita dos registros
    while(cont < qtd_registros){
            tam = 0;
            char removido = registros[cont].removido;
            fwrite(&removido,sizeof(char),1,arquivo);
            tam++;
            ////////////////////////////////////////////////
            int encadeamento = registros[cont].encadeamento;
            fwrite(&encadeamento,sizeof(int),1,arquivo);
            tam +=4;
            //////////////////////////////////////////////
            int nroInscricao = registros[cont].nroInscricao;
            fwrite(&nroInscricao,sizeof(int),1,arquivo);
            tam +=4;
            ///////////////////////////////////////////////
            double nota = registros[cont].nota;
            fwrite(&nota,sizeof(double),1,arquivo);
            tam +=8;
            ///////////////////////////////////////////////
            char data[10];
            if(registros[cont].data[0] == '\0'){
                for(int i=0;i<10;i++){
                    data[i] = '@';
                }
                data[0] = '\0';
                fwrite(data,sizeof(char),10,arquivo);
            }
            else{
                fwrite(registros[cont].data,sizeof(char),10,arquivo);
            }
            tam +=10;
            //Caso haja um campo nulo, ele verifica com a tag qual campo eh;
            if(registros[cont].tagCampo == '4'){
                //Se o campo 4 existir
                fwrite(&registros[cont].indicador_Tam,sizeof(int),1,arquivo);
                fwrite(&registros[cont].tagCampo,sizeof(char),1,arquivo);
                fwrite(registros[cont].cidade,sizeof(char),registros[cont].indicador_Tam-1,arquivo);
                tam +=4;
                tam +=registros[cont].indicador_Tam;
            }
            if(registros[cont].tagCampo2 == '5'){
				//Se o campo 5 existir
                fwrite(&registros[cont].indicador_Tam2,sizeof(int),1,arquivo);
                fwrite(&registros[cont].tagCampo2,sizeof(char),1,arquivo);
                fwrite(registros[cont].nomeEscola,sizeof(char),registros[cont].indicador_Tam2-1,arquivo);
                tam +=4;
                tam +=registros[cont].indicador_Tam2;
            }

            fwrite(registros[cont].lixo,sizeof(char),(80-tam),arquivo);
            cont++;
            //Posicao
    }


}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//Funcao compara do quick_sort
/*
int compare(const void * left, const void * right) {
    const Registros_leitura * a = (const Registros_leitura *) left;
    const Registros_leitura * b = (const Registros_leitura *) right;
    if (a->nroInscricao < b->nroInscricao) {
        return -1;
    } else if (a->nroInscricao > b->nroInscricao) {
        return 1;
    } else {
        return 0;
    }
}*/
//////////////////////////////////////////////////////////////////////////////////////////////////////
void funcionalidade8(char nome_de_arquivo[], char arquivodesaida[]){
    //variaveis utilizadas
    FILE *arquivo;
    FILE *arquivos;
    char status;
    Cabecalho_leitura cab_arquivo;
    Registros_leitura *registros;
    int qtd_registros;


    //Abertura de arquivo
    arquivo = fopen(nome_de_arquivo,"rb");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    //verifcarcao do status
    fread(&status,sizeof(char),1,arquivo);
    if(status == '0'){
        printf("Falha no processamento do arquivo.\n");
        return;//arquivo inconsistente
    }

    //leitura de cabecalho
    cab_arquivo = leitura_cabecalho(arquivo);
    registros = leitura_de_registros(arquivo,&qtd_registros);

    fseek(arquivo,0,SEEK_SET);

	//Abertura do arquivo de saida
    arquivos = fopen(arquivodesaida,"wb+");
    if(arquivos == NULL){
        return;
    }

	//ordenacao com o quick_sort do stdlib
    //qsort(registros,qtd_registros,sizeof(Registros_leitura),compare);

	//Escuta no arquivo o vetor de arquivos e a struct do cabecalho
	escrever_no_arquivo(arquivos,cab_arquivo,registros,qtd_registros);

	//Impressao na tela
    binarioNaTela(arquivos);

	//Fechamento dos arquivos
	fclose(arquivo);
	fclose(arquivos);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//escreve o cabecalho no arquivo
void escrever_cabecalho(FILE *arquivo,Cabecalho_leitura cab){
	//O ponteiro eh sertada no inicio
	fseek(arquivo,0,SEEK_SET);
    //Escrita do cabecalho
    fwrite(&cab.status,sizeof(char),1,arquivo);
    fwrite(&cab.pilha,sizeof(int),1,arquivo);
    fwrite(&cab.resto,sizeof(char),15995,arquivo);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Escreve apenas um registro no arquivo
void escrever_um_registro(FILE *arquivo, Registros_leitura *registros,int pos,int posicao_de_arquivo){
    //variaveis utilizadas
    int cont = pos;
    int tam = 0;
    char lixo = '@';
    //Escrita dos registros
    tam = 0;
    fseek(arquivo,posicao_de_arquivo,SEEK_SET);
    char removido = registros[cont].removido;
    fwrite(&removido,sizeof(char),1,arquivo);
    tam++;
    ////////////////////////////////////////////////
    int encadeamento = registros[cont].encadeamento;
    fwrite(&encadeamento,sizeof(int),1,arquivo);
    tam +=4;
    //////////////////////////////////////////////
    int nroInscricao = registros[cont].nroInscricao;
    fwrite(&nroInscricao,sizeof(int),1,arquivo);
    tam +=4;
    ///////////////////////////////////////////////
    double nota = registros[cont].nota;
    fwrite(&nota,sizeof(double),1,arquivo);
    tam +=8;
    ///////////////////////////////////////////////
    char data[10];
    if(registros[cont].data[0] == '\0'){
        for(int i=0;i<10;i++){
            data[i] = '@';
        }
        data[0] = '\0';
        fwrite(data,sizeof(char),10,arquivo);
    }
    else{
        fwrite(registros[cont].data,sizeof(char),10,arquivo);
    }
    tam +=10;
    //Caso haja um campo nulo, ele verifica com a tag qual campo eh;
    if(registros[cont].tagCampo == '4'){
        //Se for o campo 4
        fwrite(&registros[cont].indicador_Tam,sizeof(int),1,arquivo);
        fwrite(&registros[cont].tagCampo,sizeof(char),1,arquivo);
        fwrite(registros[cont].cidade,sizeof(char),registros[cont].indicador_Tam-1,arquivo);
        tam +=4;
        tam +=registros[cont].indicador_Tam;
    }
    if(registros[cont].tagCampo2 == '5'){
		//Se for o campo 5
        fwrite(&registros[cont].indicador_Tam2,sizeof(int),1,arquivo);
        fwrite(&registros[cont].tagCampo2,sizeof(char),1,arquivo);
        fwrite(registros[cont].nomeEscola,sizeof(char),registros[cont].indicador_Tam2-1,arquivo);
        tam +=4;
        tam +=registros[cont].indicador_Tam2;
    }

	//Escrita do lixo
    for(int i = tam; i < 80; i++){
        fwrite(&lixo,sizeof(char),1,arquivo);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//Essa funcao realizar merge em arquivos ordenados
void funcionalidade9(char nome_de_arquivo[], char nome_de_arquivo2[],char arquivodesaida[]){
    //variaveis utilizadas
    FILE *arquivo;
    FILE *arquivo2;
    FILE *arquivo_de_saida;
    char status;
    Cabecalho_leitura cab;
    Registros_leitura *arquivo1_registros;
    Registros_leitura *arquivo2_registros;
    int qtd_registros;
    int qtd_registros2;
    int cont = 0;
    int cont2 = 0;
    int posicao_de_arquivo = 16000;
    //Abertura de arquivo_de_saida
    arquivo = fopen(nome_de_arquivo,"rb+");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    arquivo2 = fopen(nome_de_arquivo2,"rb+");
    if(arquivo2 == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    if(verifcar_arquivo_binario(arquivodesaida) == 0){
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    arquivo_de_saida = fopen(arquivodesaida,"wb+");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    ////////////////////////////////////////////////////////

    //Verificao de verifcao de status
    fseek(arquivo,0,SEEK_SET);
    fread(&status,sizeof(char),1,arquivo);
    if(status == '0'){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    fseek(arquivo2,0,SEEK_SET);
    fread(&status,sizeof(char),1,arquivo);
    if(status == '0'){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    ///////////////////////////////////////////////////////
	//leitura dos arquivos
	//Os registros sao passados para um vetor
    cab = leitura_cabecalho(arquivo);
    arquivo1_registros = leitura_de_registros(arquivo,&qtd_registros);
    arquivo2_registros = leitura_de_registros(arquivo2,&qtd_registros2);

	//escreve o cabecalho no arquivo
    escrever_cabecalho(arquivo_de_saida,cab);

    while(cont < qtd_registros){
		//se o arquivo 2 termina
        if(cont2 == qtd_registros2){
            escrever_um_registro(arquivo_de_saida, arquivo1_registros,cont,posicao_de_arquivo);
            posicao_de_arquivo+=80;
        }
        while (cont2 < qtd_registros2) {
			//Se a inscricao do arquivo1 for maior que a inscricao do arquivo 2
            if(arquivo1_registros[cont].nroInscricao > arquivo2_registros[cont2].nroInscricao){
                escrever_um_registro(arquivo_de_saida, arquivo2_registros,cont2,posicao_de_arquivo);
                cont2++;
                posicao_de_arquivo+=80;
            }
            else if(arquivo1_registros[cont].nroInscricao < arquivo2_registros[cont2].nroInscricao){
				//Se a inscricao do arquivo1 for menor que a inscricao do arquivo 2
                escrever_um_registro(arquivo_de_saida, arquivo1_registros,cont,posicao_de_arquivo);
                posicao_de_arquivo+=80;
                cont2++;
                break;
            }
            else{
				//Se a inscricao do arquivo1 for igual que a inscricao do arquivo 2
                escrever_um_registro(arquivo_de_saida, arquivo1_registros,cont,posicao_de_arquivo);
                posicao_de_arquivo+=80;
                cont2++;
                break;
            }
        }
        cont++;
    }

    binarioNaTela(arquivo_de_saida);

    //Fechar os arquivos
    fclose(arquivo);
    fclose(arquivo2);
    fclose(arquivo_de_saida);
}
///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
/*Essa funcao escreve apenas os registros presentes em dois arquivos , ou em outras palavras
realizar a interssecção dos arquivos*/
void funcionalidade10(char nome_de_arquivo[], char nome_de_arquivo2[],char arquivodesaida[]){
    //variaveis utilizadas
    FILE *arquivo;
    FILE *arquivo2;
    FILE *arquivo_de_saida;
    char status;
    Registros_leitura *arquivo1_registros;
    Registros_leitura *arquivo2_registros;
    Cabecalho_leitura cab;
    int qtd_registros;
    int qtd_registros2;
    int posicao_de_arquivo;
    int cont = 0;
    int cont2 = 0;


    //Abertura de arquivo_de_saida
    arquivo = fopen(nome_de_arquivo,"rb+");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    arquivo2 = fopen(nome_de_arquivo2,"rb+");
    if(arquivo2 == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    arquivo_de_saida = fopen(arquivodesaida,"wb+");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    ////////////////////////////////////////////////////////

    //Verificao de verifcao de status
    fseek(arquivo,0,SEEK_SET);
    fread(&status,sizeof(char),1,arquivo);
    if(status == '0'){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    fseek(arquivo2,0,SEEK_SET);
    fread(&status,sizeof(char),1,arquivo);
    if(status == '0'){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    //////////////////////////////////////////////////////
	//Leituras dos arquivos
    cab = leitura_cabecalho(arquivo);
    arquivo1_registros = leitura_de_registros(arquivo,&qtd_registros);
    arquivo2_registros = leitura_de_registros(arquivo2,&qtd_registros2);

	//Escrita do cabecalho
    escrever_cabecalho(arquivo_de_saida,cab);
	//Pular o cabecalho
    posicao_de_arquivo = 16000;

	//arquivo1
    while(cont < qtd_registros){
		//arquivo2
		while (cont2 < qtd_registros2) {
            if(arquivo1_registros[cont].nroInscricao == arquivo2_registros[cont2].nroInscricao){
				//se a intersseccao for encontrada
				escrever_um_registro(arquivo_de_saida, arquivo1_registros,cont,posicao_de_arquivo);
                cont2++;
                posicao_de_arquivo+=80;
                break;

            }
            else if(arquivo1_registros[cont].nroInscricao < arquivo2_registros[cont2].nroInscricao){
				//Se o nroInscricao do arquivo 1 for menor que o a do arquivo2
				break;
            }
            cont2++;
        }
        cont++;
    }

    binarioNaTela(arquivo_de_saida);
    fclose(arquivo_de_saida);
	fclose(arquivo);
	fclose(arquivo2);
}
