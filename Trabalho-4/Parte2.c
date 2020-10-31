#include "Parte2.h"


//Funcoes propostas pela professora
void binarioNaTela1(FILE *ponteiroArquivoBinario) {

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
void trim(char *str) {

	/*
	*	Essa função arruma uma string de entrada "str".
	*	Manda pra ela uma string que tem '\r' e ela retorna sem.
	*	Ela remove do início e do fim da string todo tipo de espaçamento (\r, \n, \t, espaço, ...).
	*	Por exemplo:
	*
	*	char minhaString[] = "    \t TESTE  DE STRING COM BARRA R     \t  \r\n ";
	*	trim(minhaString);
	*	printf("[%s]", minhaString); // vai imprimir "[TESTE  DE STRING COM BARRA R]"
	*
	*/

	size_t len;
	char *p;

	for(len = strlen(str); len > 0 && isspace(str[len - 1]); len--); // remove espaçamentos do fim
	str[len] = '\0';
	for(p = str; *p != '\0' && isspace(*p); p++); // remove espaçamentos do começo
	len = strlen(p);
	memmove(str, p, sizeof(char) * (len + 1));
}




void scan_quote_string(char *str) {

	/*
	*	Use essa função para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada está da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
	*/

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então...
		str[0] = R;
		scanf("%s", &str[1]);
	} else { // EOF
		strcpy(str, "");
	}
}

////////////////////////////////////////////////////////////////////////////////
//Verificar se o arquivo eh inconsistente
int verifcar_status(FILE *arquivo){
	char status;
	fseek(arquivo,0,SEEK_SET);
	fread(&status,sizeof(char),1,arquivo);
	if(status == '1'){
		return 1;
	}
	else{
		return 0;
	}
}

////////////////////////////////////////////////////////////////////////////////
//Alterar o status quando alteracoes forem realizadas no arquivo
void arquivo_em_uso(FILE *arquivo){
	char status = '0';

	fseek(arquivo,0,SEEK_SET);
	fwrite(&status,sizeof(char),1,arquivo);

	return;
}
////////////////////////////////////////////////////////////////////////////////
//Alterar os status apos o uso dos arquivos
void fim_de_uso(FILE *arquivo){
	char status = '1';

	fseek(arquivo,0,SEEK_SET);
	fwrite(&status,sizeof(char),1,arquivo);

	return;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*realizar a remocao do registro preenchedo com o atual topo da Pilha e prechendo o resto do registro com '@'*/
int remocao_preenchimento(FILE *arquivo,int posicao,int Atual_pilha,int RRN_removido){
	//variaveis utilizadas
	char removido = '*';
	char lixo[75];
	int encadeamento;

	fseek(arquivo,posicao,SEEK_SET);
	fwrite(&removido,sizeof(char),1,arquivo);
	////////////////////////////////////////////////
	//atualizacao da pilha e do encadeamento
	encadeamento = Atual_pilha;
	Atual_pilha = RRN_removido;

	//O encadeamento eh atualizado
	fwrite(&encadeamento,sizeof(int),1,arquivo);

	//O resto do registro e prenchido com @
	for(int i=0;i<75;i++){
		lixo[i] = '@';
	}
	fwrite(&lixo,sizeof(char),75,arquivo);

	//Topo da pilha eh atualizado
	fseek(arquivo,1,SEEK_SET);
	fwrite(&Atual_pilha,sizeof(int),1,arquivo);

	return Atual_pilha;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Realizar busca e a remocao dos registros com abordadegem dinamica utilizada o conceito de pilha*/
void funcionalidade5(char nome_de_arquivo[], int  n_vezes){

	//variaveis utilizadas
	FILE *arquivoTrab1si;
	int aux_regis = 0;
    char nomeEscola[500];
    char cidade[500];
    int registro = 1, aux_registro = 0;
    int flag = 0,entrou = 0;
    int indicador_Tam2;
	int contador = 0;
	char *nome_campo;
	char *valor;
	int RRN_removido = -1;
	int Atual_pilha = -1;
	int k = 0;
	char status;
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

	//Verificao se o arquivo eh inconsistente
	arquivoTrab1si = fopen(nome_de_arquivo,"rb+");
	if(arquivoTrab1si == NULL){
		printf("Erro ao abrir o arquivo.bin\n");
		return;
	}

	//Alocacao de variaveis
	nome_campo = (char*) malloc (100*sizeof(char));
	valor = (char*) malloc (100*sizeof(char));

	//Verificar status
	if(verifcar_status(arquivoTrab1si) == 0){
        printf("Falha no processamento do arquivo.\n");
        return;
    }

	//Inicia o uso do arquivos
	arquivo_em_uso(arquivoTrab1si);

	//Calcular a qtd de registros
	fseek(arquivoTrab1si,0,SEEK_END);
	qtd_registros = (int) (ftell(arquivoTrab1si)-16000)/80;

	//n_vezes eh quantidade de registro a serem removidos
	//solicitados pelo usuario
	while (contador < n_vezes){
		//Verificao do topo da pilha
		fseek(arquivoTrab1si,1,SEEK_SET);
	   	fread(&Atual_pilha,sizeof(int),1,arquivoTrab1si);

		//Pular o cabecalho
	   	fseek(arquivoTrab1si,16000,SEEK_SET);

		//Leitura de dados
	   	scanf("%s ",nome_campo);
		trim(nome_campo);
		scan_quote_string(valor);

		k = 0;//contador de registros

		//leitura de todos os registros
	    while(k < qtd_registros){
			//posicao inicial do registro
			posicao = ftell(arquivoTrab1si);
	   		RRN_removido++;//O RRN e atualizado
	       	//Caso o arquivo estaja removido ele pular para o  proximo
			//registro
			fread(&removido,sizeof(char),1,arquivoTrab1si);
			if(removido != '-'){
	           fseek(arquivoTrab1si,79,SEEK_CUR);
				k++;
				continue;
	        }
		    ////////////////////////////////////////////////
			//O ponteiro avanca os bytes do encadeamento
            fread(&encadeamento,sizeof(int),1,arquivoTrab1si);
        	//////////////////////////////////////////////
	        if(strcmp(nome_campo,"nroInscricao") == 0){
	            //Conversao da string para int
                valor1 = atoi(valor);
	       		//leitura da inscricao
	            fread(&inscricao,sizeof(int),1,arquivoTrab1si);
				//Se o valo dos nroInscricao forem iguais
	            if(inscricao == valor1){
					remocao_preenchimento(arquivoTrab1si,posicao,Atual_pilha,RRN_removido);
	                break;
				}
			}
	        else{
	           	//Caso nao seja o campo desejado, o codigo
	           	//continua normalmente
	           	fread(&inscricao,sizeof(int),1,arquivoTrab1si);
	        }
	        ///////////////////////////////////////////////
			//se o campo for nota
		    if(strcmp(nome_campo,"nota") == 0){
				//o falor eg conventida para double
				valor2 = atof(valor);
				//A nota do registro eh lida
            	fread(&nota,sizeof(double),1,arquivoTrab1si);
				//se nota for igual
				if(nota == valor2){
					//a pilha eh atualizada
					Atual_pilha = remocao_preenchimento(arquivoTrab1si,posicao,Atual_pilha,RRN_removido);
					//Avanca para o proximo registro
					fseek(arquivoTrab1si,posicao+80,SEEK_SET);
					k++;
					continue;
            	}
        	}
			else{
            	fread(&nota,sizeof(double),1,arquivoTrab1si);
			}

            ///////////////////////////////////////////////
        	//Apartir daqui nao eh mais necessario realizar
        	//transformacoes, as string sao comparadas diretamente
        	if(strcmp(nome_campo,"data") == 0){
            	fread(&data,sizeof(char),10,arquivoTrab1si);
				//comparacao da data
                if(data[0] == valor[0] && data[1] == valor[1]){
                    if(data[2] == valor[2] && data[3] == valor[3]){
                        if(data[4] == valor[4] && data[5] == valor[5]){
                            if(data[6] == valor[6] && data[7] == valor[7]){
                                if(data[8] == valor[8] && data[9] == valor[9]){
									//se todos os caracteres baterem entao a pilha eh atualizado
									Atual_pilha = remocao_preenchimento(arquivoTrab1si,posicao,Atual_pilha,RRN_removido);
									fseek(arquivoTrab1si,posicao+80,SEEK_SET);
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
	            fread(&data,sizeof(char),10,arquivoTrab1si);
	        }
			/////////////////////////////////////////////////
			//Campos com tamanho variavel
	        //Primeiro eh lido o indicador_Tamanho
	        fread(&indicador_Tam,sizeof(int),1,arquivoTrab1si);

	       	//Em seguida eh lido a tag
	        fread(&tagCampo,sizeof(char),1,arquivoTrab1si);
        	//Se a tag for do campo 4 ela entra
	        if(tagCampo == '4'){
				//Se for o campo 4
	            if(strcmp(nome_campo,"cidade") == 0){
	                fread(&cidade,sizeof(char),indicador_Tam-1,arquivoTrab1si);
	                if(strcmp(valor,cidade) == 0){
						//Se as strings forem iguais
						Atual_pilha = remocao_preenchimento(arquivoTrab1si,posicao,Atual_pilha,RRN_removido);
						fseek(arquivoTrab1si,posicao+80,SEEK_SET);
						k++;
						continue;
	                }
	             }
	             else{
					 //Se o campo nao for cidade
	               	fread(&cidade,sizeof(char),indicador_Tam-1,arquivoTrab1si);
	             }
				 //Leitura do segundo campo caso ele exista
	             fread(&indicador_Tam2,sizeof(int),1,arquivoTrab1si);

	             fread(&tagCampo,sizeof(char),1,arquivoTrab1si);

	          		if(tagCampo == '5'){
						//Se o campo for nomeEscola
	             		if(strcmp(nome_campo,"nomeEscola") == 0){
					    	fread(&nomeEscola,sizeof(char),indicador_Tam2-1,arquivoTrab1si);
	                    	if(strcmp(valor,nomeEscola) == 0){
								//Se a string for encontrada
								Atual_pilha = remocao_preenchimento(arquivoTrab1si,posicao,Atual_pilha,RRN_removido);
								fseek(arquivoTrab1si,posicao+80,SEEK_SET);
								k++;
								continue;
	                    	}
	                	}
	                	else{
							//Caso nao seja o campo 5
	                    	fread(&nomeEscola,sizeof(char),indicador_Tam2-1,arquivoTrab1si);
				        }
	             	}
				}
	            else if(tagCampo == '5'){
	            	//Se for o campo 5
	                if(strcmp(nome_campo,"nomeEscola") == 0){
	                    fread(&nomeEscola,sizeof(char),indicador_Tam-1,arquivoTrab1si);
	                    if(strcmp(valor,nomeEscola) == 0){
							//se as strings forem iguais
							Atual_pilha = remocao_preenchimento(arquivoTrab1si,posicao,Atual_pilha,RRN_removido);
							fseek(arquivoTrab1si,posicao+80,SEEK_SET);
							k++;
							continue;
	                    }
	                }
	                else{
						//Caso nao seja o campo nomeEscola
	                    fread(&nomeEscola,sizeof(char),indicador_Tam-1,arquivoTrab1si);
	                }

	            }
				// leitura do Lixo
				fread(&lixo_buffer,sizeof(char),1,arquivoTrab1si);
				int i = 0;
				while(lixo_buffer == '@'){
					i++;
					fread(&lixo_buffer,sizeof(char),1,arquivoTrab1si);
					if(i > 80){
						break;
					}
				}
				//volt uma posicao, pois entro no novo registro
	            fseek(arquivoTrab1si,-1,SEEK_CUR);
				k++;//atualizacao do nro de registros
            }

			//RRN e reninicializdo
			RRN_removido = -1;
			contador++;//uma busca ou remocao realizada
    	}
		//Fechamento do uso do arquivo
		fim_de_uso(arquivoTrab1si);

		//impressao de hexadecimal na tela
		binarioNaTela1(arquivoTrab1si);


		//Fechamento do arquivo;
		fclose(arquivoTrab1si);
}

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/*Realizar a insercao utilizado abordadegem dinamica*/
void funcionalidade6(char nome_de_arquivo[], int n_vezes){
	//Variaveis utilizadas
	FILE *arquivo;
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

	//Abertura do arquivo;
	arquivo = fopen(nome_de_arquivo,"rb+");
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

				tamanho += indicador_Tam_nomeEscola+1;
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

				if(strlen(nomeEscola) != 0){
					char tagCampo5 = '5';
					int aux_ind_esc = indicador_Tam_nomeEscola + 2;

					fwrite(&aux_ind_esc,sizeof(int),1,arquivo);
					tamanho += 4;
					fwrite(&tagCampo5,sizeof(char),1,arquivo);
					tamanho++;

					fwrite(nomeEscola,sizeof(char),indicador_Tam_nomeEscola+1,arquivo);

					tamanho += indicador_Tam_nomeEscola+1;
				}
			}
			else if(strlen(nomeEscola) != 0){
				char tagCampo5 = '5';
				int aux_ind_esc = indicador_Tam_nomeEscola + 2;

				fwrite(&aux_ind_esc,sizeof(int),1,arquivo);
				tamanho += 4;
				fwrite(&tagCampo5,sizeof(char),1,arquivo);
				tamanho++;

				fwrite(nomeEscola,sizeof(char),indicador_Tam_nomeEscola+1,arquivo);

				tamanho += indicador_Tam_nomeEscola+1;
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

		contador++;
	}
	//fechamento do uso do arquivo
	fim_de_uso(arquivo);

	//impressao na tela
	binarioNaTela1(arquivo);

	fclose(arquivo);
}


///////////////////////////////////////////////////////////////////////
/*Essa funcionalidade realizar a atualizacao dos campos de reistro fixo*/
void funcionalidade7(char nome_de_arquivo[], int n_vezes){
	//Declaracao de variaveis utilizadas
	char nomeEscola[500];
	char cidade[500];
	char status;
	int RRN;
	int i = 0;
	char *nome_campo;
	char *valor;
	char buffer;
	char removido;
	int encadeamento;
	int inscricao;
	char data[10];
	double nota,nota_leitura;
	int posicao;
	int indicador_Tam;
	int indicador_Tam2;
	char tagCampo;
	char tagCampo2;
	int qtd_registros;
	char lixo;
	char limpeza[75];
	int contador = 0;
	FILE *arquivo;
	int aux_int;
	long int fim;

	//Abertura de arquivo
    arquivo = fopen(nome_de_arquivo,"rb+");
    if(arquivo == NULL){
		printf("Falha no processamento do arquivo.\n");
        return;
    }

	//Verificar se o arquivo eh inconsistente
	if(verifcar_status(arquivo) == 0){
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	//Alterar do status do arquivos
	arquivo_em_uso(arquivo);

	//Alocacao das variaveis de leitura
	nome_campo = (char*) malloc (30*sizeof(char));
	valor = (char*) malloc (30*sizeof(char));
	for(int i=0;i<75;i++){
		limpeza[i] = '@';
	}

	//O numero de registro eh calculado
	fseek(arquivo,0,SEEK_END);
	qtd_registros = (int) (ftell(arquivo)-16000)/80;
	fim = ftell(arquivo);


	//Enquanto o contador for menor que o numero de opcoes
	while(contador < n_vezes) {
		//A cada ciclo um novo campo eh atualizado
		scanf("%d ",&RRN);//RRN do campo
		scanf("%s",nome_campo);//nome do campo desejado
		scanf("%c",&buffer);//ler o espaco entre a string nome_campo e valor
		scan_quote_string(valor);//tratamento das aspas

		//RRN maior que o numero de registro presentes no  arquivos

		//O RRN eh buscado
		fseek(arquivo,(16000+(RRN*80)),SEEK_SET);
		if(fim == ftell(arquivo)){
			contador++;
			continue;
		}
		///////////////////////////////////////////////////////////////////////
		//Leitua do registro
		///////////////////////////////////////////////////////////////////////
		posicao = (int) ftell(arquivo);
		//eh usado o fread para ler o documento
		fread(&removido,sizeof(char),1,arquivo);
		if(removido != '-'){
			contador++;
			continue;
		}
		////////////////////////////////////////////////
		fread(&encadeamento,sizeof(int),1,arquivo);
		//////////////////////////////////////////////
		fread(&inscricao,sizeof(int),1,arquivo);
		///////////////////////////////////////////////
		fread(&nota_leitura,sizeof(double),1,arquivo);
		////////////////////////////////////////////////
		fread(&data,sizeof(char),10,arquivo);
		///////////////////////////////////////////////
		fread(&indicador_Tam,sizeof(int),1,arquivo);
		///////////////////////////////////////////////
		fread(&tagCampo,sizeof(char),1,arquivo);
		////////////////////////////////////////////////

		if(tagCampo == '4'){
			//Se for o campo 4
			fread(&cidade,sizeof(char),indicador_Tam-1,arquivo);
			///////////////////////////
			//Campo nomeEscola
			fread(&indicador_Tam2,sizeof(int),1,arquivo);
			fread(&tagCampo2,sizeof(char),1,arquivo);

			if(tagCampo2 == '5'){
				//Se o campo 4 existir e o 5 tambem
				fread(&nomeEscola,sizeof(char),indicador_Tam2-1,arquivo);
			}
		}
		else if(tagCampo == '5'){
			//Se o campo nao existir
			fread(&nomeEscola,sizeof(char),indicador_Tam-1,arquivo);
		}

		//Lixo
		fread(&lixo,sizeof(char),1,arquivo);
		int i = 0;
		while(lixo == '@'){
			i++;
			fread(&lixo,sizeof(char),1,arquivo);
			if(i > 80){
				break;
			}
		}
		fseek(arquivo,-1,SEEK_CUR);

		///////////////////////////////////////////////////////////////////////
		//atualizacao
		//////////////////////////////////////////////////////////////////////
		fseek(arquivo,posicao+5,SEEK_SET);
		fwrite(limpeza,sizeof(char),75,arquivo);
		fseek(arquivo,posicao+5,SEEK_SET);

		if(strcmp(nome_campo,"nroInscricao") == 0){
			//Se sim a string valor e transformada em int
			inscricao = atoi(valor);
			//atualizacao
			fwrite(&inscricao,sizeof(int),1,arquivo);

		}
		else{
			//Caso nao seja o campo escolhido
			fwrite(&inscricao,sizeof(int),1,arquivo);
		}
		///////////////////Nota////////////////////////////
		//Nesse caso notas negativas sao consideradas campo nulo
		if(strcmp(nome_campo,"nota") == 0){
			//Se o campo for nulo
			if(strlen(valor) == 0){
				nota = -1.0;
				fwrite(&nota,sizeof(double),1,arquivo);
			}
			else{
				//Caso o campo nao seja nula
				nota = atof(valor);
				fwrite(&nota,sizeof(double),1,arquivo);

			}
		}
		else{
			//Se o campo nao e o da nota
			fwrite(&nota_leitura,sizeof(double),1,arquivo);
		}

		///////////////////Data////////////////////////////

		if(strcmp(nome_campo,"data") == 0){
			//Se o campo data for nulo
			if(strlen(valor) == 0){
				for(int i=0;i<10;i++){
					data[i] = '@';
				}
				data[0] ='\0';
				fwrite(data,sizeof(char),10,arquivo);
			}
			else{
				//Caso o campo data nao seja nulo
				for(int i=0;i<10;i++){
					data[i] = valor[i];
				}
				fwrite(data,sizeof(char),10,arquivo);
			}
		}
		else{
			fwrite(&data,sizeof(char),10,arquivo);
		}
		posicao = (int) ftell(arquivo);
		////////////////Cidade e nome de escola/////////////////////////
		//Se campo for cidade
		if(strcmp(nome_campo,"cidade") == 0){
			//Verificar a que campo a tag petencer
			if(tagCampo == '4'){
				if(strlen(valor) != 0){
					fseek(arquivo,posicao,SEEK_SET);
					indicador_Tam = strlen(valor)+2;
					fwrite(&indicador_Tam,sizeof(int),1,arquivo);
					tagCampo = '4';
					fwrite(&tagCampo,sizeof(char),1,arquivo);
					fwrite(valor,sizeof(char),(indicador_Tam-1),arquivo);
				}
					//nomeEscola
				if(tagCampo2 == '5'){
					indicador_Tam2 = (int) strlen(nomeEscola)+2;
					fwrite(&indicador_Tam2,sizeof(int),1,arquivo);

					fwrite(&tagCampo2,sizeof(char),1,arquivo);

					fwrite(nomeEscola,sizeof(char),(indicador_Tam2-1),arquivo);

				}

			}
			else if(tagCampo == '5'){
				//Cidade
				if(strlen(valor) != 0){
					fseek(arquivo,posicao,SEEK_SET);
					indicador_Tam2 = strlen(valor)+2;
					fwrite(&indicador_Tam2,sizeof(int),1,arquivo);

					tagCampo = '4';
					fwrite(&tagCampo,sizeof(char),1,arquivo);

					fwrite(valor,sizeof(char),(indicador_Tam2-1),arquivo);
				}
				//Escola
				fwrite(&indicador_Tam,sizeof(int),1,arquivo);

				tagCampo = '5';
				fwrite(&tagCampo,sizeof(char),1,arquivo);

				fwrite(nomeEscola,sizeof(char),(indicador_Tam-1),arquivo);
			}
			else{
				//Nao tem nenhum campo
				//cidade
				if(strlen(valor) != 0){
					fseek(arquivo,posicao,SEEK_SET);
					indicador_Tam2 = strlen(valor)+2;
					fwrite(&indicador_Tam2,sizeof(int),1,arquivo);

					tagCampo = '4';
					fwrite(&tagCampo,sizeof(char),1,arquivo);

					fwrite(valor,sizeof(char),(indicador_Tam2-1),arquivo);
				}
			}
		}
		else if(strcmp(nome_campo,"nomeEscola") == 0){
			if(tagCampo == '4'){
					fseek(arquivo,posicao,SEEK_SET);

					fwrite(&indicador_Tam,sizeof(int),1,arquivo);

					fwrite(&tagCampo,sizeof(char),1,arquivo);

					fwrite(cidade,sizeof(char),(indicador_Tam-1),arquivo);

					//Escola
					if(strlen(valor) != 0){
						indicador_Tam2 = (int) strlen(valor)+2;
						fwrite(&indicador_Tam2,sizeof(int),1,arquivo);

						fwrite(&tagCampo2,sizeof(char),1,arquivo);

						fwrite(valor,sizeof(char),(indicador_Tam2-1),arquivo);
					}
			}
			else if(tagCampo == '5'){
				if(strlen(valor) != 0){
					fseek(arquivo,posicao,SEEK_SET);
					indicador_Tam2 = strlen(valor)+2;
					fwrite(&indicador_Tam2,sizeof(int),1,arquivo);

					tagCampo = '5';
					fwrite(&tagCampo,sizeof(char),1,arquivo);

					fwrite(valor,sizeof(char),(indicador_Tam2-1),arquivo);
				}
			}
		}
		else{
			//caso nao seja nem o campo cidade e nem o campo nomeEscola
			if(tagCampo == '4'){
					fseek(arquivo,posicao,SEEK_SET);
					indicador_Tam = strlen(cidade)+2;
					fwrite(&indicador_Tam,sizeof(int),1,arquivo);
					tagCampo = '4';
					fwrite(&tagCampo,sizeof(char),1,arquivo);
					fwrite(cidade,sizeof(char),(indicador_Tam-1),arquivo);

					if(tagCampo2 == '5'){
						indicador_Tam2 = (int) strlen(nomeEscola)+2;
						fwrite(&indicador_Tam2,sizeof(int),1,arquivo);

						fwrite(&tagCampo2,sizeof(char),1,arquivo);

						fwrite(nomeEscola,sizeof(char),(indicador_Tam2-1),arquivo);
					}
			}
			else if(tagCampo == '5'){
				indicador_Tam2 = (int) strlen(nomeEscola)+2;
				fwrite(&indicador_Tam2,sizeof(int),1,arquivo);

				fwrite(&tagCampo,sizeof(char),1,arquivo);

				fwrite(nomeEscola,sizeof(char),(indicador_Tam2-1),arquivo);
			}

		}

		contador++;
	}

	fim_de_uso(arquivo);
	binarioNaTela1(arquivo);
    fclose(arquivo);
}
