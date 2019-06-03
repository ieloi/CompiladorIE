#include "funcoes_e_variaveis.h"
#include "lexico.h"

void busca_token(ifstream& arq)
{
	while(!arq.eof())
	{
		if(erro == true)
		{
			break;
		}
		else
		{
			if(tk_encontrado == true)
			{
				verificaEstadoToken(estado);
				cout << "tk_formado: " << novo_token.token_formado << endl;
				automato(c);
				tk_encontrado = false;
				break;
			}
			arq.get(c);
			automato(c);
		}
	}
}

void lista_de_identificadores(ifstream& arq)
{
	if(novo_token.tipo_token_formado != "identificador")
	{
		msg = " identificador esperado (1 posicao lista de identificadores)";
		cout << endl << msg << endl;
		exit(0);
	}
	busca_token(arq);
	do
	{
		if(novo_token.token_formado != ",")
		{
			break;
		}
		busca_token(arq);
		if(novo_token.tipo_token_formado != "identificador")
		{
			msg = " identificador esperado (2 posicao lista de identificadores)";
			cout << endl << msg << endl;
			exit(0);
		}
		busca_token(arq);
	}
	while(novo_token.token_formado == ",");
}

void definicoes_de_variaveis(ifstream& arq)
{
	busca_token(arq);
	do
	{
		if(novo_token.tipo_token_formado == "identificador")
		{
			lista_de_identificadores(arq);
		}
		
		if(novo_token.token_formado != ":")
		{
			msg = " : esperado (definicoes de variavel)";
			cout << endl << msg << endl;
			exit(0);
		}
		busca_token(arq);
		if(novo_token.tipo_token_formado != "identificador")
		{
			msg = " identificador esperado (definicoes de variavel)";
			cout << endl << msg << endl;
			exit(0);
		}
		busca_token(arq);
		if(novo_token.token_formado != ";")
		{
			msg = " ; esperado (definicoes de variavel)";
			cout << endl << msg << endl;
			exit(0);
		}
		busca_token(arq);
	}
	while(novo_token.tipo_token_formado == "identificador");
}

void declara_tipo(ifstream& arq)
{
	busca_token(arq);
	do
	{
		if(novo_token.tipo_token_formado != "identificador")
		{
			msg = " identificador esperado (declaracao de tipos)";
			cout << endl << msg << endl;
			exit(0);
		}
		busca_token(arq);
		if(novo_token.token_formado != "=")
		{
			msg = " = esperado (declaracao de tipos)";
			cout << endl << msg << endl;
			exit(0);
		}
		busca_token(arq);
		if(novo_token.tipo_token_formado != "identificador")
		{
			msg = " identificador esperado (declaracao de tipos)";
			cout << endl << msg << endl;
			exit(0);
		}
		busca_token(arq);
		if(novo_token.token_formado != ";")
		{
			msg = " ; esperado (declaracao de tipos)";
			cout << endl << msg << endl;
			exit(0);
		}
		busca_token(arq);
	}
	while(novo_token.tipo_token_formado == "identificador");
}

void bloco(ifstream& arq)
{
	if(novo_token.token_formado == "tipo")
	{
		declara_tipo(arq);
	}
	if(novo_token.token_formado == "var")
	{
		definicoes_de_variaveis(arq);
	}
}

void sintatico(ifstream& arq)
{
	busca_token(arq);
	if(novo_token.token_formado != "programa")
	{
		msg = "programa esperado na linha (sintatico)";
		cout << endl << msg << endl;
		exit(0);
	}

	busca_token(arq);
	if(novo_token.tipo_token_formado != "identificador")
	{
		msg = "identificador esperado na linha (sintatico)";
		cout << endl << msg << endl;
		exit(0);
	}

	busca_token(arq);
	if(novo_token.token_formado != ";")
	{
		msg = "; esperado na linha (sintatico)";
		cout << endl << msg << endl;
		exit(0);
	}

	busca_token(arq);
	bloco(arq);

	busca_token(arq);
	if(novo_token.token_formado != ".")
	{
		msg = ". esperado na linha (sintatico)";
		cout << endl << msg << endl;
		exit(0);
	}
}

int main()
{
	ifstream txtFile;

	txtFile.open("teste.txt");

	if(!txtFile)
	{
		cout << "erro de abertura do arquivo";
	}
	else
	{
		sintatico(txtFile);
		txtFile.close();
	}

	if(erro == true)
	{
		cout << endl << msg << endl;
	}
	else
	{
		cout << endl << msg << endl;
	}

	return 0;
}
