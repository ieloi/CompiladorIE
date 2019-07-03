#include <iostream>
#include <fstream>
#include <locale>
#include <string>
#include <stdlib.h>

using namespace std;

struct info_token
{
	string token_formado;
	int estado_token;
	string tipo_token_formado;
};

int estado = 0; // identificador de estado no automato;
int countline = 1; // contador de linhas do arquivo;
string tk_formado = ""; // token formado;
bool tk_encontrado = false; // verifica se foi achado algum token;
bool erro = false; // variavel que verifica se deu algum erro durante a compilação;
string msg = " compilacao bem sucedida "; // mensagem que será mostrada no fim da execução;
char c; // caracter que é lido do arquivo;

info_token novo_token; // token que armazenará temporariamente as informações que serão enviadas ao sintatico

string palavras_reservadas[26] = {"programa", "se", "entao", "senao", "enquanto",
								  "faca", "ate", "repita", "inteiro", "real", "caractere", "caso",
								  "escolha", "fim_escolha", "procedimento",
								  "funcao", "de", "para", "fim_do_se", "inicio", "fim",
								  "tipo", "var", "leia", "imprima", "do"
								 };

int ehMaiusculoOuMinusculo(int c)
{
	return isalpha(c);
}

int ehDigito(int c)
{
	return isdigit(c);
}

int ehSimboloEspecial(int c)
{
	return ispunct(c);
}

int ehLetraOuDigito(int c)
{
	return isalnum(c);
}

int ehMinusculo(int c)
{
	return islower(c);
}

// busca no array de palavras reservadas
int eh_palavra_reservada(string tk_formado)
{
	int res = 0;
	for(int i = 0; i < 26 ; i++)
	{
		if(tk_formado == palavras_reservadas[i])
		{
			res = 1;
			break;
		}
	}
	return res;
}

// guarda as informações do token em uma estrutura
info_token gera_token(string tipo)
{
	novo_token.token_formado = tk_formado;
	novo_token.estado_token = estado;
	novo_token.tipo_token_formado = tipo;

	//cout << " token formado: " << novo_token.token_formado << "\t" << "tipo: " << novo_token.tipo_token_formado << endl;

	estado = 0;
	tk_formado = "";

	return novo_token;
}

//Verifica o estado do token formado e define se ele é reconhecivel ou não
void verificaEstadoToken(int es)
{
	switch(es)
	{
	case 1:
		gera_token("identificador");
		break;
	case 4:
		if(eh_palavra_reservada(tk_formado) == 1)
		{
			gera_token("palavra reservada");
		}
		else
		{
			gera_token("identificador");
		}
		break;
	case 7:
		if(eh_palavra_reservada(tk_formado) == 1)
		{
			gera_token("palavra reservada");
		}
		else
		{
			erro = true;
			msg = "erro de compilacao na linha ";
			break;
		}
		break;
	case 10:
		if(eh_palavra_reservada(tk_formado) == 1)
		{
			gera_token("palavra reservada");
		}
		else
		{
			erro = true;
			msg = "erro de compilacao na linha ";
			break;
		}
		break;
	case 11:
		gera_token("simbolo especial");
		break;
	case 13:
		gera_token("comentario de linha");
		break;
	case 14:
		gera_token("simbolo especial");
		break;
	case 15:
		gera_token("simbolo especial");
		break;
	case 16:
		gera_token("digito");
		break;
	case 18:
		gera_token("digito");
		break;
	case 19:
		gera_token("simbolo especial");
		break;
	case 20:
		gera_token("simbolo especial");
		break;
	case 21:
		gera_token("simbolo especial");
		break;
	case 22:
		gera_token("simbolo especial");
		break;
	case 23:
		gera_token("simbolo especial");
		break;
	case 26:
		gera_token("comentario de varias linhas");
		break;
	default:
		erro = true;
		msg = "erro de compilacao na linha ";
		break;
	}
}

// funcao que delimita o fim de um token
void encontrouFimToken(char c)
{
	if(c == ' ')
	{
		tk_encontrado = true;
	}
	else if(c == '\t')
	{

	}
	else if(tk_formado == "////" || tk_formado == "/##/" || tk_formado == "@@")
	{
		estado = 0;
		tk_formado = "";
		tk_encontrado = false;
	}
	else if(c == '\n' && estado != 0)
	{
		tk_encontrado = true;
	}
	else if(c == '\n' && estado == 0)
	{
		countline++;
	}
	else if(c == '!' || c == '%' || c == '#' || c == '¨' || c == '?' || c == '°' || c == 'º' || c == '~' || c == '§' || c == '[' || c == ']' || c == 'ª')
	{
		verificaEstadoToken(estado);
		erro = true;
		msg = "erro de compilacao na linha ";
	}
	else
	{
		tk_encontrado = true;
	}
}
