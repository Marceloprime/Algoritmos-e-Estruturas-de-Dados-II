#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


///Funcoes do trabalho 2
void funcionalidade5(char nome_de_arquivo[], int n_vezes);
void funcionalidade6(char nome_de_arquivo[], int n_vezes);
void funcionalidade7(char nome_de_arquivo[], int n_vezes);
void scan_quote_string(char *str);
void binarioNaTela1(FILE *ponteiroArquivoBinario);
void arquivo_em_uso(FILE *arquivo);
int verifcar_status(FILE *arquivo);
void arquivo_em_uso(FILE *arquivo);
void fim_de_uso(FILE *arquivo);
int remocao_preenchimento(FILE *arquivo,int posicao,int Atual_pilha,int RRN_removido);
