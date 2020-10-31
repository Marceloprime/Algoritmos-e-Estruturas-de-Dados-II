#include "Parte4.h"

/*Trabalho 4 - Dupla
NOME: Marcelo Augusto dos Reis
Nusp: 10844309
NOME: João Vitor Monteiro
Nusp: 10691932
*/

//Assinatura de funcoes utilizadas
void escrever_cabecalho_de_indicies(FILE *arquivoIndicie);//Escreve o cabecalho do arquivo de indicies
Indices *gerador_de_indices(FILE *arquivo,int *qtd);//Transforma o arquivo de dados em um vetor de indicies
Indices *arquivo_de_Indices_para_vetor(FILE *arquivo,int *tam);//Transforma arquivoIndices em vetor
void escrever_indicies(FILE *arquivoIndicie,Indices *vetor,int qtd);//Escreve indicies no arquivo
int compare(const void * left, const void * right);//Funcao usada pelo qsort da stdlib.h
void binarioNaTela4(FILE *ponteiroArquivoBinario);//Funcao de impressao
void busca_por_campo(char chave[],FILE *arquivo,FILE *arquivoIndicie,int qtd_indices,int *acessos);//Busca
void impressao_de_registro_pelo_rrn(FILE *arquivo,int RRN);//imprimir um registro
int buscaBinaria (int n, Indices v[],char valor[]);//Busca binaria
void shiftamento(Indices *vector,int pos,int qtd);//shitar um vetor
void insertion_sort(Indices *a, int MAX);//insertion sort para indicies
void insertionSort(int arr[], int n);//insertion Sort para int
///////////////////////////////////////////////////////////////////////////////////////////
//Criacao do arquivo  de Indices
void funcionalidade11(char nome_de_arquivo[],char arquivodesaida[]){
    //Variaveis utilizadas
    FILE *arquivo;
    FILE *arquivoIndicie;
    Indices *vetor;
    int qtd;
    char status;
    char status2 = '1';


    //Abertura de arquivo
    arquivo = fopen(nome_de_arquivo,"rb+");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    fseek(arquivo,0,SEEK_SET);
    fread(&status,sizeof(char),1,arquivo);
    if(status == '0'){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    arquivoIndicie = fopen(arquivodesaida,"wb+");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    /////////////////////////////////////////////////
    //Escreve o cabecalho no arquivoIndices
    escrever_cabecalho_de_indicies(arquivoIndicie);
    //Criacao dos indicies
    vetor = gerador_de_indices(arquivo,&qtd);
    //Ordenacao
    qsort(vetor,qtd,sizeof(Indices),compare);
    //Escrita no arquivo de indicies
    escrever_indicies(arquivoIndicie,vetor,qtd);

    //atualizacao de Informacoes do arquivo de indicies
    fseek(arquivoIndicie,0,SEEK_SET);
    fwrite(&status2,sizeof(char),1,arquivoIndicie);//para consistente
    fwrite(&qtd,sizeof(int),1,arquivoIndicie);//qtd de registros

    //impressao na tela
    binarioNaTela4(arquivoIndicie);

    //Fechamento dos arquivos
    fclose(arquivo);
    fclose(arquivoIndicie);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Busca usando o arquivo de indicies
void funcionalidade12(char nome_de_arquivo[],char arquivo_de_Indices[],char nome_campo[],char valor[],int *acessos){
    //Variaveis utilizadas
    FILE *arquivo;
    FILE *arquivoIndicie;
    char status;
    int qtd_indices;

    //Abertura de arquivos
    arquivo = fopen(nome_de_arquivo,"rb+");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    arquivoIndicie = fopen(arquivo_de_Indices,"rb+");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    //Verificar se o status esta inconsistente
    fseek(arquivoIndicie,0,SEEK_SET);
    fread(&status,sizeof(char),1,arquivoIndicie);
    if(status == '0'){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    fseek(arquivo,0,SEEK_SET);
    fread(&status,sizeof(char),1,arquivo);
    if(status == '0'){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    ///////////////////////////////////////////////
    //qtd de registro presentes no arquivo
    fread(&qtd_indices,sizeof(int),1,arquivo);
    ///////////////////////////////////////////////////
    //Confere se o campo eh valido segundo a politica de chave de busca
    if(strcmp(nome_campo,"nomeEscola") == 0){
        busca_por_campo(valor,arquivo,arquivoIndicie,qtd_indices,acessos);
    }
    else{
        printf("Registro inexistente.\n");
        return;
    }

    //fechamento de arquivo
    fclose(arquivo);
    fclose(arquivoIndicie);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Realizar a remocao utilizado arquivo de indicies para realizar a busca
void funcionalidade13(char nome_de_arquivo[],char arquivo_de_Indices[],int n_vezes){
    //Variaveis
    FILE *arquivoIndicie;
    char status;
    char status2 = '1';
    Indices *vector;
    int tam;
    FILE *arquivo;
    int aux_regis = 0;
    char nomeEscola[500];
    char cidade[500];
    int registro = 1, aux_registro = 0;
    int flag = 0,entrou = 0;
    int indicador_Tam2;
    int contador = 0;
    char nome_campo[100];
    char valor[100];
    int RRN_removido = -1;
    int Atual_pilha = -1;
    int k = 0;
    int qtd_registros;
    char buffer;
    char removido;
    int encadeamento;
    int inscricao;
    int valor1;
    char lixo[75];
    double nota;
    double valor2;
    int posicao;
    char data[10],aux_data[10];
    int indicador_Tam;
    char tagCampo;
    char lixo_buffer;


    //Abertura de arquivos
    arquivoIndicie = fopen(arquivo_de_Indices,"rb+");
    if(arquivoIndicie == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    fseek(arquivoIndicie,0,SEEK_SET);
    fread(&status,sizeof(char),1,arquivoIndicie);
    if(status == '0'){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    //carregamento do arquivoIndices para a RAM
    vector = arquivo_de_Indices_para_vetor(arquivoIndicie,&tam);

	//Verificao se o arquivo eh inconsistente
	arquivo = fopen(nome_de_arquivo,"rb+");
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo.bin\n");
		return;
	}
	//Verificar status
	if(verifcar_status(arquivo) == 0){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    fclose(arquivoIndicie);

	//Inicia o uso do arquivos
	arquivo_em_uso(arquivo);

	//Calcular a qtd de registros
	fseek(arquivo,0,SEEK_END);
	qtd_registros = (int) (ftell(arquivo)-16000)/80;

	//n_vezes eh quantidade de registro a serem removidos
	//solicitados pelo usuario
	while (contador < n_vezes){
		//Verificao do topo da pilha
		fseek(arquivo,1,SEEK_SET);
	   	fread(&Atual_pilha,sizeof(int),1,arquivo);

		//Pular o cabecalho
	   	fseek(arquivo,16000,SEEK_SET);

		//Leitura de dados
	   	scanf("%s ",nome_campo);
		scan_quote_string(valor);

		k = 0;//contador de registros

		//leitura de todos os registros
	    while(k < qtd_registros){
			//posicao inicial do registro
			posicao = ftell(arquivo);
	   		RRN_removido++;//O RRN e atualizado
	       	//Caso o arquivo estaja removido ele pular para o  proximo
			//registro
			fread(&removido,sizeof(char),1,arquivo);
			if(removido != '-'){
	           fseek(arquivo,79,SEEK_CUR);
				k++;
				continue;
	        }
		    ////////////////////////////////////////////////
			//O ponteiro avanca os bytes do encadeamento
            fread(&encadeamento,sizeof(int),1,arquivo);
        	//////////////////////////////////////////////
	        if(strcmp(nome_campo,"nroInscricao") == 0){
	            //Conversao da string para int
                valor1 = atoi(valor);
	       		//leitura da inscricao
	            fread(&inscricao,sizeof(int),1,arquivo);
				//Se o valo dos nroInscricao forem iguais
	            if(inscricao == valor1){
					Atual_pilha = remocao_preenchimento(arquivo,posicao,Atual_pilha,RRN_removido);
                    shiftamento(vector,Atual_pilha,tam);
                    tam--;
	                break;
				}
			}
	        else{
	           	//Caso nao seja o campo desejado, o codigo
	           	//continua normalmente
	           	fread(&inscricao,sizeof(int),1,arquivo);
	        }
	        ///////////////////////////////////////////////
			//se o campo for nota
		    if(strcmp(nome_campo,"nota") == 0){
				//o falor eg conventida para double
				valor2 = atof(valor);
				//A nota do registro eh lida
            	fread(&nota,sizeof(double),1,arquivo);
				//se nota for igual
				if(nota == valor2){
					//a pilha eh atualizada
					Atual_pilha = remocao_preenchimento(arquivo,posicao,Atual_pilha,RRN_removido);
                    shiftamento(vector,Atual_pilha,tam);
                    tam--;
					//Avanca para o proximo registro
					fseek(arquivo,posicao+80,SEEK_SET);
					k++;
					continue;
            	}
        	}
			else{
            	fread(&nota,sizeof(double),1,arquivo);
			}

            ///////////////////////////////////////////////
        	//Apartir daqui nao eh mais necessario realizar
        	//transformacoes, as string sao comparadas diretamente
        	if(strcmp(nome_campo,"data") == 0){
            	fread(&data,sizeof(char),10,arquivo);
				//comparacao da data
                if(data[0] == valor[0] && data[1] == valor[1]){
                    if(data[2] == valor[2] && data[3] == valor[3]){
                        if(data[4] == valor[4] && data[5] == valor[5]){
                            if(data[6] == valor[6] && data[7] == valor[7]){
                                if(data[8] == valor[8] && data[9] == valor[9]){
									//se todos os caracteres baterem entao a pilha eh atualizado
									Atual_pilha = remocao_preenchimento(arquivo,posicao,Atual_pilha,RRN_removido);
                                    shiftamento(vector,Atual_pilha,tam);
                                    tam--;
									fseek(arquivo,posicao+80,SEEK_SET);
									k++;
									continue;
                                }
                            }
                        }
                    }
                }
            }
	        else{
				//Caso data nao seja o campo
	            fread(&data,sizeof(char),10,arquivo);
	        }
			/////////////////////////////////////////////////
			//Campos com tamanho variavel
	        //Primeiro eh lido o indicador_Tamanho
	        fread(&indicador_Tam,sizeof(int),1,arquivo);

	       	//Em seguida eh lido a tag
	        fread(&tagCampo,sizeof(char),1,arquivo);
        	//Se a tag for do campo 4 ela entra
	        if(tagCampo == '4'){
				//Se for o campo 4
	            if(strcmp(nome_campo,"cidade") == 0){
	                fread(&cidade,sizeof(char),indicador_Tam-1,arquivo);
	                if(strcmp(valor,cidade) == 0){
						//Se as strings forem iguais
						Atual_pilha = remocao_preenchimento(arquivo,posicao,Atual_pilha,RRN_removido);
                        shiftamento(vector,Atual_pilha,tam);
                        tam--;
						fseek(arquivo,posicao+80,SEEK_SET);
						k++;
						continue;
	                }
	             }
	             else{
					 //Se o campo nao for cidade
	               	fread(&cidade,sizeof(char),indicador_Tam-1,arquivo);
	             }
				 //Leitura do segundo campo caso ele exista
	             fread(&indicador_Tam2,sizeof(int),1,arquivo);

	             fread(&tagCampo,sizeof(char),1,arquivo);

	          		if(tagCampo == '5'){
						//Se o campo for nomeEscola
	             		if(strcmp(nome_campo,"nomeEscola") == 0){
					    	fread(&nomeEscola,sizeof(char),indicador_Tam2-1,arquivo);
	                    	if(strcmp(valor,nomeEscola) == 0){
								//Se a string for encontrada
								Atual_pilha = remocao_preenchimento(arquivo,posicao,Atual_pilha,RRN_removido);
                                shiftamento(vector,Atual_pilha,tam);
                                tam--;

								fseek(arquivo,posicao+80,SEEK_SET);
								k++;
								continue;
	                    	}
	                	}
	                	else{
							//Caso nao seja o campo 5
	                    	fread(&nomeEscola,sizeof(char),indicador_Tam2-1,arquivo);
				        }
	             	}
				}
	            else if(tagCampo == '5'){
	            	//Se for o campo 5
	                if(strcmp(nome_campo,"nomeEscola") == 0){
	                    fread(&nomeEscola,sizeof(char),indicador_Tam-1,arquivo);
	                    if(strcmp(valor,nomeEscola) == 0){
							//se as strings forem iguais
							Atual_pilha = remocao_preenchimento(arquivo,posicao,Atual_pilha,RRN_removido);
                            shiftamento(vector,Atual_pilha,tam);
                            tam--;
							fseek(arquivo,posicao+80,SEEK_SET);
							k++;
							continue;
	                    }
	                }
	                else{
						//Caso nao seja o campo nomeEscola
	                    fread(&nomeEscola,sizeof(char),indicador_Tam-1,arquivo);
	                }

	            }
				// leitura do Lixo
				fread(&lixo_buffer,sizeof(char),1,arquivo);
				int i = 0;
				while(lixo_buffer == '@'){
					i++;
					fread(&lixo_buffer,sizeof(char),1,arquivo);
					if(i > 80){
						break;
					}
				}
				//volt uma posicao, pois entro no novo registro
	            fseek(arquivo,-1,SEEK_CUR);
				k++;//atualizacao do nro de registros
            }

			//RRN e reninicializdo
			RRN_removido = -1;
			contador++;//uma busca ou remocao realizada
    	}
		//Fechamento do uso do arquivo
		fim_de_uso(arquivo);
        arquivoIndicie = fopen(arquivo_de_Indices,"wb");
        if(arquivoIndicie == NULL){
            printf("Falha no processamento do arquivo.\n");
            return;
        }
        //atualizacao do arquivo de Indices
        escrever_cabecalho_de_indicies(arquivoIndicie);
        escrever_indicies(arquivoIndicie,vector,tam);
        fseek(arquivoIndicie,0,SEEK_SET);
        fwrite(&status2,sizeof(char),1,arquivoIndicie);
        fwrite(&tam,sizeof(int),1,arquivoIndicie);
        fclose(arquivoIndicie);

        //Abertura para a leitura
        arquivoIndicie = fopen(arquivo_de_Indices,"rb");
        if(arquivoIndicie == NULL){
            printf("Falha no processamento do arquivo.\n");
            return;
        }
		//impressao de hexadecimal na tela
		binarioNaTela1(arquivoIndicie);

		//Fechamento do arquivo;
		fclose(arquivo);
}
// ///////////////////////////////////////////////////////////////////////////////////////
void funcionalidade14(char nome_de_arquivo[], char arquivo_de_Indices[], int n_vezes){
    //Variaveis utilizadas
    FILE *arquivo;
    FILE *arquivoIndices;
    Indices *vetor;
    int contador = 0;//numero de insercoes
    int RRN_pilha;
    int novo_topo;
    char *nota;
    double ins_nota;
    int ins_inscricao;
    char *data;
    char *cidade;
    char *nomeEscola;
    int indicador_Tam_cidade;
    int indicador_Tam_nomeEscola;
    char removido;
    int tamanho;
    int encadeamento;
    int tam;
    char valor[28];
    int i;
    int flag;
    char status2 = '1';
    int qtd;

    //Abertura do arquivo;
    arquivo = fopen(nome_de_arquivo,"rb+");
    if(arquivo == NULL){
        //Caso nao seja possivel abrir o arquivo
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    arquivoIndices = fopen(arquivo_de_Indices,"rb");
    if(arquivo == NULL){
        //Caso nao seja possivel abrir o arquivo
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    //Verificar status
    if(verifcar_status(arquivo) == 0){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    if(verifcar_status(arquivoIndices) == 0){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    //Calcular a quantidade de registros
    fseek(arquivo,0,SEEK_END);
    qtd = (int) (ftell(arquivo)-16000)/80;
    fseek(arquivo,0,SEEK_SET);
    //Leitura para a RAM
    vetor = arquivo_de_Indices_para_vetor(arquivoIndices,&tam);
    //Ordenacao
    qsort(vetor,tam,sizeof(Indices),compare);

    fclose(arquivoIndices);
    //inicio do uso do arquivo
    arquivo_em_uso(arquivo);
    //Realizar a busca e remocao Enquanto for menor que o numero de n_vezes
    //solicitado pelo usuario
    while (contador < n_vezes){
        //leitura
        scanf("%d",&ins_inscricao);

        nota = (char*) malloc (10*sizeof(char));

        scan_quote_string(nota);

        //campo data
        data = (char*) malloc (10*sizeof(char));

        scan_quote_string(data);
        /////////////////////////////////////////////
        //campo cidade

        cidade = (char*) malloc (75*sizeof(char));
        scan_quote_string(cidade);
        indicador_Tam_cidade =(int) strlen(cidade);

        ////////////////////////////////////////////
        //campo nomeEscola
        nomeEscola = (char*) malloc (75*sizeof(char));
        scan_quote_string(nomeEscola);
        indicador_Tam_nomeEscola =(int) strlen(nomeEscola);

        /////////////////////////////////////////////
        //Sertar na pilha do arquivo
        fseek(arquivo,1,SEEK_SET);
        // leitura da pilha
        fread(&RRN_pilha,sizeof(int),1,arquivo);

        tamanho = 0;//contador de bytes
        if(RRN_pilha == -1){

            /*For igual a -1 inserer no final*/
            fseek(arquivo,0,SEEK_END);

            //O status de nao removido eh escrito
            removido = '-';
            fwrite(&removido,sizeof(char),1,arquivo);
            tamanho++;

            encadeamento = -1;
            fwrite(&encadeamento,sizeof(int),1,arquivo);
            tamanho += 4;

            ////////////////////////////////////////////
            //ID dos registros
            fwrite(&ins_inscricao,sizeof(int),1,arquivo);
            tamanho += 4;
            ////////////////////////////////////////////
            if(strlen(nota) == 0){//nota nula
                ins_nota = -1.0;
                fwrite(&ins_nota,sizeof(double),1,arquivo);
            }
            else{
                ins_nota = atof(nota);
                fwrite(&ins_nota,sizeof(double),1,arquivo);
            }
            tamanho += 8;

            /////////////////////////////////////////////////////
            if (strlen(data) == 0) {
                //Se a data for nula
                data[0] = '\0';
                for(int i=1;i<10;i++){
                    data[i] = '@';
                }
                fwrite(data,sizeof(char),10,arquivo);
            }
            else{
                //Se nao
                fwrite(data,sizeof(char),10,arquivo);
            }
            tamanho += 10;
            /////////////////////////////////////////////////////
            //Se o campo cidade nao for nulo
            if(strlen(cidade) != 0){

                char tagCampo4 = '4';
                int aux_int = indicador_Tam_cidade + 2;

                fwrite(&aux_int,sizeof(int),1,arquivo);
                tamanho += 4;
                fwrite(&tagCampo4,sizeof(char),1,arquivo);
                tamanho++;
                fwrite(cidade,sizeof(char),indicador_Tam_cidade+1,arquivo);

                tamanho += indicador_Tam_cidade+1;

            }
            ////////////////////////////////////////////////////////
            if(strlen(nomeEscola) != 0){
                //Se o campo nomeEscola nao for nulo
                char tagCampo5 = '5';
                int aux_ind_esc = indicador_Tam_nomeEscola + 2;

                fwrite(&aux_ind_esc,sizeof(int),1,arquivo);
                tamanho += 4;
                fwrite(&tagCampo5,sizeof(char),1,arquivo);
                tamanho++;

                fwrite(nomeEscola,sizeof(char),indicador_Tam_nomeEscola+1,arquivo);
                //Criacao do Indices
                tamanho += indicador_Tam_nomeEscola+1;
                strcpy(vetor[tam].chave,nomeEscola);
                vetor[tam].RRN = qtd;
                tam++;
            }
            ///////////////////////////////////////////////////////////////////
            //O resto do arquivo eh prenchido com lixo
            char lixo[80-tamanho];
            for(int i=0;i< 80-tamanho;i++){
                lixo[i] = '@';
            }
            fwrite(lixo,sizeof(char),(80-tamanho),arquivo);
        }
        else{
            ///Caso a pilha nao esteja vazia E haja registro removidos

            //busca do registro
            fseek(arquivo,(16000+(RRN_pilha*80)),SEEK_SET);

            removido = '-';
            fwrite(&removido,sizeof(char),1,arquivo);
            tamanho++;

            //o atual encadeamento vai para o topo da pilha
            fread(&novo_topo,sizeof(int),1,arquivo);
            fseek(arquivo,-4,SEEK_CUR);

            //e eh inscrito o novo encadeamento
            encadeamento = -1;
            fwrite(&encadeamento,sizeof(int),1,arquivo);
            tamanho += 4;

            ////////////////////////////////////////////
            //ID dos registros
            fwrite(&ins_inscricao,sizeof(int),1,arquivo);
            tamanho += 4;
            ////////////////////////////////////////////
            if(strlen(nota) == 0){//nota nula
                ins_nota = -1.0;
                fwrite(&ins_nota,sizeof(double),1,arquivo);
            }
            else{
                ins_nota = atof(nota);
                fwrite(&ins_nota,sizeof(double),1,arquivo);
            }
            tamanho += 8;

            /////////////////////////////////////////////////////
            if (strlen(data) == 0) {
                //Se data for nula
                data[0] = '\0';
                for(int i=1;i<10;i++){
                    data[i] = '@';
                }
                fwrite(data,sizeof(char),10,arquivo);
            }
            else{
                //Se nao
                fwrite(data,sizeof(char),10,arquivo);

            }
            tamanho += 10;
            /////////////////////////////////////////////////////
            //Se o campo cidade nao for nulo
            if(strlen(cidade) != 0){

                char tagCampo4 = '4';
                int aux_int = indicador_Tam_cidade + 2;

                fwrite(&aux_int,sizeof(int),1,arquivo);
                tamanho += 4;
                fwrite(&tagCampo4,sizeof(char),1,arquivo);
                tamanho++;
                fwrite(cidade,sizeof(char),indicador_Tam_cidade+1,arquivo);

                tamanho += indicador_Tam_cidade+1;

                if(strlen(nomeEscola) != 0){//Se o campo nao for nulo
                    char tagCampo5 = '5';
                    int aux_ind_esc = indicador_Tam_nomeEscola + 2;

                    fwrite(&aux_ind_esc,sizeof(int),1,arquivo);
                    tamanho += 4;
                    fwrite(&tagCampo5,sizeof(char),1,arquivo);
                    tamanho++;

                    fwrite(nomeEscola,sizeof(char),indicador_Tam_nomeEscola+1,arquivo);
                    //Criacao do Indices
                    tamanho += indicador_Tam_nomeEscola+1;
                    strcpy(vetor[tam].chave,nomeEscola);
                    vetor[tam].RRN = RRN_pilha;
                    tam++;
                }
            }
            else if(strlen(nomeEscola) != 0){//Se o campo nao for nulo
                char tagCampo5 = '5';
                int aux_ind_esc = indicador_Tam_nomeEscola + 2;

                fwrite(&aux_ind_esc,sizeof(int),1,arquivo);
                tamanho += 4;
                fwrite(&tagCampo5,sizeof(char),1,arquivo);
                tamanho++;

                fwrite(nomeEscola,sizeof(char),indicador_Tam_nomeEscola+1,arquivo);

                tamanho += indicador_Tam_nomeEscola+1;
                flag = 0;
                //Criacao do Indices
                strcpy(vetor[tam].chave,nomeEscola);
                vetor[tam].RRN = RRN_pilha;
                tam++;
            }
            ///////////////////////////////////////////////////////////////////
            char lixo[80-tamanho];
            for(int i=0;i< 80-tamanho;i++){
                lixo[i] = '@';
            }
            fwrite(lixo,sizeof(char),(80-tamanho),arquivo);

            //o novo topo da pilha eh atualizado
            fseek(arquivo,1,SEEK_SET);
            fwrite(&novo_topo,sizeof(int),1,arquivo);
        }
        qtd++;
        contador++;
    }

    //Processo de Ordenacao
    qsort(vetor,tam,sizeof(Indices),compare);
    insertion_sort(vetor,tam);

    //fechamento do uso do arquivo
    fim_de_uso(arquivo);
    arquivoIndices = fopen(arquivo_de_Indices,"wb");
    if(arquivoIndices == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    //atualizacao do arquivo Indices
    escrever_cabecalho_de_indicies(arquivoIndices);
    escrever_indicies(arquivoIndices,vetor,tam);
    fseek(arquivoIndices,0,SEEK_SET);
    fwrite(&status2,sizeof(char),1,arquivoIndices);
    fwrite(&tam,sizeof(int),1,arquivoIndices);
    fclose(arquivoIndices);

    //Abertura para a leitura
    arquivoIndices = fopen(arquivo_de_Indices,"rb");
    if(arquivoIndices == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    //impressao de hexadecimal na tela
    binarioNaTela1(arquivoIndices);

    fclose(arquivo);
    fclose(arquivoIndices);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Nessa funcao eh realizada a comparacao entre  a funcionalidade 3 e a funcionalidade 12
void funcionalidade15(char nome_de_arquivo[],char arquivo_de_Indices[],char nome_campo[],char valor[]){
    //variaveis utilizadas
    FILE *arquivo;
    FILE *arquivoIndices;
    char status;
    int acessos1;
    int acessos2;

    //Abertura do arquivo;
    arquivo = fopen(nome_de_arquivo,"rb+");
    if(arquivo == NULL){
        //Caso nao seja possivel abrir o arquivo
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    arquivoIndices = fopen(arquivo_de_Indices,"rb");
    if(arquivo == NULL){
        //Caso nao seja possivel abrir o arquivo
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    //Verificar status
    if(verifcar_status(arquivo) == 0){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    if(verifcar_status(arquivoIndices) == 0){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    //Fechamento de arquivos
    fclose(arquivo);
    fclose(arquivoIndices);

    printf("*** Realizando a busca sem o auxílio de índice\n");

    funcionalidade3(nome_de_arquivo,nome_campo,valor,&acessos1);
    printf("\n");
    printf("*** Realizando a busca com o auxílio de um índice secundário fortemente ligado\n");

    funcionalidade12(nome_de_arquivo,arquivo_de_Indices,nome_campo,valor,&acessos2);
    printf("\n");
    printf("Diferença no número de páginas de disco acessadas: %d",((acessos1) - acessos2));

}
//////////////////////////////////////////////////////////////////////////////////////////
/*Escreve o cabecalho do arquivo de indicie, porem sem a quantidade de registos*/
void escrever_cabecalho_de_indicies(FILE *arquivoIndicie) {
    //Variaveis utilizadas
    Cabecalho_do_arquivo_indice cab;
    int i;

    cab.status = '0';//eh inicialidado como inconsistente
    cab.nroRegistros = -1;//sera alteradado para o valor real ao fim da funcionalidade11
    //a string resto eh prenchida com @ ate completa uma pagina de disco de 16000 bytes
    for(i=0;i<15995;i++){
        cab.resto[i] = '@';
    }

    //Escrita no arquivo
    fseek(arquivoIndicie,0,SEEK_SET);
    fwrite(&cab.status,sizeof(char),1,arquivoIndicie);
    fwrite(&cab.nroRegistros,sizeof(int),1,arquivoIndicie);
    fwrite(&cab.resto,sizeof(char),15995,arquivoIndicie);

}
/////////////////////////////////////////////////////////////////////////////////////////
/*Essa funcao ler o arquivo guarda o campo nomeEscola e o seu RRN*/
Indices *gerador_de_indices(FILE *arquivo,int *qtd){
    //Variaveis utilizadas
    Indices *vetor;
    int qtd_registros;
    int cont = 0;
    char removido;
    char tagCampo;
    int indicador_Tam;
    char nomeEscola[28];//tamanho estabelecido segundo os criterios do Trabalho
    int pos = 0;
    long int posicao;
    //calculado do nroRegistros
    fseek(arquivo,0,SEEK_END);
    qtd_registros = (int) (ftell(arquivo)-16000)/80;
    //alocacao do vetor
    vetor = (Indices*) malloc (sizeof(Indices)*qtd_registros);
    //Cabecalho eh pulado
    fseek(arquivo,16000,SEEK_SET);
    while (cont < qtd_registros) {
        posicao = ftell(arquivo);
        fread(&removido,sizeof(char),1,arquivo);
        if(removido != '-'){
            fseek(arquivo,79,SEEK_CUR);
            cont++;
            continue;
        }
        //Se o registro nao for removido
        //o encadeamento,nroInscricao,nota e data e pulado
        fseek(arquivo,26,SEEK_CUR);

        fread(&indicador_Tam,sizeof(int),1,arquivo);
        fread(&tagCampo,sizeof(char),1,arquivo);
        if(tagCampo == '4'){
            //pula a cidade
            fseek(arquivo,indicador_Tam-1,SEEK_CUR);
            //ler o proximo campo
            fread(&indicador_Tam,sizeof(int),1,arquivo);
            fread(&tagCampo,sizeof(char),1,arquivo);
            if(tagCampo == '5'){
                fread(nomeEscola,sizeof(char),indicador_Tam-1,arquivo);
                vetor[pos].RRN = cont;
                strcpy(vetor[pos].chave,nomeEscola);
                pos++;
            }
        }
        else if(tagCampo == '5'){
            fread(nomeEscola,sizeof(char),indicador_Tam-1,arquivo);
            vetor[pos].RRN = cont;
            strcpy(vetor[pos].chave,nomeEscola);
            pos++;
        }
        //Pular o lixo
        fseek(arquivo,posicao+80,SEEK_SET);
        cont++;
    }
    //A quantidade eh passada por referencia
    *qtd = pos;

    return vetor;//retorna o ponteiro
}
//////////////////////////////////////////////////////////////////////////////////
//Escreve o vetor de indicies no arquivoIndices
void escrever_indicies(FILE *arquivoIndicie,Indices *vetor,int qtd){
    //variaveis utilizadas
    int cont = 0;
    char *lixo;
    int tam;
    int i;
    //pular o cabecalho
    fseek(arquivoIndicie,16000,SEEK_SET);

    while (cont < qtd) {
        //Pega o tamanho da string de chave
        tam = strlen(vetor[cont].chave)+1;
        if(tam < 28){
            //o resto da string eh preenchida com @
            lixo = (char*) malloc (sizeof(char)*(28-tam));
            for(i=0;i<28-tam;i++){
                lixo[i] = '@';
            }
            //Escrita no arquivo
            fwrite(vetor[cont].chave,sizeof(char),(strlen(vetor[cont].chave))+1,arquivoIndicie);
            fwrite(lixo,sizeof(char),28-tam,arquivoIndicie);
            fwrite(&vetor[cont].RRN,sizeof(int),1,arquivoIndicie);

        }
        else{
            //Caso a string tenha tamanho de 28 bytes
            //Escrita no arquivo
            fwrite(vetor[cont].chave,sizeof(char),(strlen(vetor[cont].chave))+1,arquivoIndicie);
            fwrite(&vetor[cont].RRN,sizeof(int),1,arquivoIndicie);

        }
        cont++;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//Funcao compara do qsort
int compare(const void * left, const void * right) {
    const Indices * a = (const Indices *) left;
    const Indices * b = (const Indices *) right;
    int i = 0;
    //Ordenacao alfabetica
    while(i < 28){
        int c = a->chave[i];
        int d = b->chave[i];
        if (c < d) {
            return -1;
        } else if (c > d) {
            return 1;
        } else {
            i++;
        }
    }
    //Desemparte de RRN
    int e = a->RRN;
    int f = b->RRN;
    if (e < f) {
        return -1;
    }
    else if (e > f) {
        return 1;
    }
    else {
          return 0;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//impressao hexadecimal
void binarioNaTela4(FILE *ponteiroArquivoBinario) {

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
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void busca_por_campo(char chave[],FILE *arquivo,FILE *arquivoIndicie,int qtd_indices,int *acessos){
    //Variaveis utilizadas
    char campo[28];
    char valor[28];
    int cont = 0;
    long int posicao;
    long int posicaoArquivo;
    long int posicao2;
    long int posicaoArquivo2;
    int i;
    int pos;
    int aux = 0;
    int aux2 = 0;
    int inicio;
    int meio;
    int fim;
    int RRN;
    int flag  = 0;
    Indices *vetor;
    int esq = 0, dir = 0;
    int contador_paginas = 1;
    int impressor[10000];

    //Passa arquivoIndices para a RAM
    vetor = arquivo_de_Indices_para_vetor(arquivoIndicie,&fim);
    posicao2 = 1+ftell(arquivoIndicie)/16000;
    //Sertar o fim do arquivo
    fseek(arquivoIndicie,0,SEEK_END);
    posicaoArquivo = ftell(arquivoIndicie);
    fseek(arquivoIndicie,16000,SEEK_SET);
    //Preencher o resto da string com lixo
    for (i = strlen(chave); i < 28; i++) {
        if(flag == 0){
            chave[i] = '\0';
            flag++;
        }
        else{
            chave[i] = '@';
        }
    }
    ////////////////////////////////////////
    flag = 0;
    pos = buscaBinaria(fim,vetor,chave);
    cont = 0;
    aux = 0;
    ////////////////////////////////////////
    //Verificar se ha mais campos que conresponde a chave
    if(pos != -1){
        while (1) {
            if(strcmp(vetor[pos-aux].chave,chave) == 0){//Verificar se ha antes
                impressor[cont] = vetor[pos-aux].RRN;//guarda no vetor
                cont++;
            }
            else{
                break;//se a Informacao de diferente termina o while
            }
            aux++;
        }
        aux = 1;//para nao ler o mesmo campo
        while (1) {
            if(strcmp(vetor[pos+aux].chave,chave) == 0){//Verificar depois
                impressor[cont] = vetor[pos+aux].RRN;//Guarda no vetor
                cont++;
            }
            else{
                break;//se a Informacao de diferente termina o while
            }
            aux++;
       }

    }
    //Ordenacao do vetor de RRN
    insertionSort(impressor,cont);
    contador_paginas = -1;
    aux;
    int cont2 = 0;
    //Sistema de contagem de acessos a discos
    if(cont > 0){
        flag = 0;
        while (flag < cont) {
            impressao_de_registro_pelo_rrn(arquivo,impressor[flag]);//impressao do registros
            aux = (int) (ftell(arquivo)/16000)+1;
            if(contador_paginas != aux){//atualizacao do acessos
                contador_paginas = aux;
                cont2++;
            }
            flag++;
        }
        printf("Número de páginas de disco para carregar o arquivo de índice: %ld\n",posicao2);
        printf("Número de páginas de disco para acessar o arquivo de dados: %d\n",cont2+1);
    }
    else{
        printf("Registro inexistente.\n");
    }
    *acessos = cont2+1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void impressao_de_registro_pelo_rrn(FILE *arquivo,int RRN){
    //Variaveis utilizadas
    int encadeamento;
    int inscricao;
    double nota;
    char data[10];
    int indicador_Tam;
    char tagCampo;
    char nomeEscola[30];
    char cidade[30];
    char removido;
    char lixo;

    fseek(arquivo,(16000)+(RRN*80),SEEK_SET);

    fread(&removido,sizeof(char),1,arquivo);
    fread(&encadeamento,sizeof(int),1,arquivo);
    //////////////////////////////////////////////
    fread(&inscricao,sizeof(int),1,arquivo);
    printf("%d",inscricao);
    ///////////////////////////////////////////////
    fread(&nota,sizeof(double),1,arquivo);
    if(nota > 0){
        printf(" %.1lf",nota);
    }
    ///////////////////////////////////////////////
    fread(&data,sizeof(char),10,arquivo);
    if(data[0] != '\0'){
        printf(" ");
        for(int k = 0;data[k] != '\0',k<10;k++){
            printf("%c",data[k]);
        }
    }
    /////////////////////////////////////////
    fread(&indicador_Tam,sizeof(int),1,arquivo);

    fread(&tagCampo,sizeof(char),1,arquivo);

    //Caso haja um campo nulo, ele verifica com a tag qual campo eh;
    if(tagCampo == '4'){
        //Se for o campo 4
        fread(&cidade,sizeof(char),indicador_Tam-1,arquivo);
        printf(" %d",indicador_Tam-2);
        printf(" %s",cidade);
        fread(&indicador_Tam,sizeof(int),1,arquivo);
        fread(&tagCampo,sizeof(char),1,arquivo);

        if(tagCampo == '5'){
            printf(" %d",indicador_Tam-2);


            fread(&nomeEscola,sizeof(char),indicador_Tam-1,arquivo);
            printf(" %s",nomeEscola);
        }
    }
    else if(tagCampo == '5'){
        //Se for o campo 5
        printf(" %d",indicador_Tam-2);
        fread(&nomeEscola,sizeof(char),indicador_Tam-1,arquivo);
        printf(" %s",nomeEscola);

    }
    //Leitura do lixo
    fread(&lixo,sizeof(char),1,arquivo);
    while(lixo == '@'){
        fread(&lixo,sizeof(char),1,arquivo);
    }
    fseek(arquivo,-1,SEEK_CUR);
    printf("\n");
}
//////////////////////////////////////////////////
Indices *arquivo_de_Indices_para_vetor(FILE *arquivo,int *tam){
    //variaves utilizadas
    Indices *vetor;
    int qtd;
    int cont = 0;
    long int posicao;

    vetor = (Indices*) malloc (sizeof(Indices)*100000);
    if(vetor == NULL){
        printf("Falha no processamento do arquivo.\n");
        return NULL;
    }
    fseek(arquivo,0,SEEK_END);
    posicao = ftell(arquivo);
    fseek(arquivo,16000,SEEK_SET);
    //Ate o fim do arquivo
    while (1) {
        if(posicao == ftell(arquivo)){
            break;
        }
        fread(vetor[cont].chave,sizeof(char),28,arquivo);
        fread(&vetor[cont].RRN,sizeof(int),1,arquivo);
        cont++;
        if(cont == 100000){
            printf("Falha no processamento do arquivo.\n");
            break;
        }
    }
    *tam = cont;
    return vetor;
}
///////////////////////////////////////////////////////////////////////////////////
int  buscaBinaria(int n,Indices vector[],char valor[]){
    int ini =0;
    int fim = n-1;
    int meio;
    int i = 0;
    while(ini < fim){
        meio = (ini + fim)/2;

        if(strcmp(valor,vector[meio].chave) < 0){
            fim = meio-1;

        }
        else if(strcmp(valor,vector[meio].chave) > 0){
            ini = meio+1;

        }
        else if(strcmp(valor,vector[meio].chave) == 0){

            return meio;
        }

    }

    return -1;//caso o elemento nao seja encontrado

}
////////////////////////////////////////////////////////////////////////////////
void shiftamento(Indices *vector,int pos,int qtd){
    //variaveis utilizadas
    int i,j;

    for(i=0;i<qtd;i++){
        if(vector[i].RRN == pos){
            for(j=i;j<qtd;j++){
                strcpy(vector[j].chave,vector[j+1].chave);
                vector[j].RRN = vector[j+1].RRN;
            }
            break;
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////
//Para a Ordenacao de indicies
void insertion_sort(Indices *a, int MAX){
 int i, j;
 Indices tmp;

 for(i = 1; i < MAX; i++){
     strcpy(tmp.chave,a[i].chave);
     tmp.RRN = a[i].RRN;
     for(j = i-1; j >= 0; j--){
         if(strcmp(tmp.chave,a[j].chave) > 0){
             break;
         }
         else if(strcmp(tmp.chave,a[j].chave) == 0){
             if(tmp.RRN > a[j].RRN){
                 break;
             }
         }

         strcpy(a[j+1].chave,a[j].chave);
         a[j+1].RRN = a[j].RRN;
     }
     strcpy(a[j+1].chave,tmp.chave);
     a[j+1].RRN = tmp.RRN;
 }

}
///////////////////////////////////////////////////////////////////////////////
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
 //////////////////////////////////////////////////////////////////////////////
