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

void lista_de_identificadores(ifstream& arq) //retorna 1 token
{
	if(novo_token.tipo_token_formado != "identificador")
	{
		msg = " identificador esperado (1 posicao lista de identificadores) ";
		cout << endl << msg << countline << endl;
		exit(0);
	}
	busca_token(arq);
	while(novo_token.token_formado == ",")
	{
		if(novo_token.token_formado != ",")
		{
			break;
		}
		busca_token(arq);
		if(novo_token.tipo_token_formado != "identificador")
		{
			msg = " identificador esperado (2 posicao lista de identificadores) ";
			cout << endl << msg << countline << endl;
			exit(0);
		}
		busca_token(arq);
	}
}

void parametros_formais(ifstream& arq) //nao envia token
{
	if(novo_token.token_formado != "(")
	{
		msg = " ( esperado (parametros formais) ";
		cout << endl << msg << countline << endl;
		exit(0);
	}
	busca_token(arq);
	do
	{
		if(novo_token.token_formado == "var")
		{
			busca_token(arq);
		}
		lista_de_identificadores(arq);

		if(novo_token.token_formado != ":")
		{
			msg = " : esperado (parametros formais) ";
			cout << endl << msg << countline << endl;
			exit(0);
		}
		busca_token(arq);
		if(novo_token.tipo_token_formado != "identificador")
		{
			msg = " identificador esperado (parametros formais) ";
			cout << endl << msg << countline << endl;
			exit(0);
		}
		busca_token(arq);
		if(novo_token.token_formado == ";")
		{
			busca_token(arq);
		}
	}
	while(novo_token.token_formado != ")");

	if(novo_token.token_formado != ")")
	{
		msg = " ) esperado (parametros formais) ";
		cout << endl << msg << countline << endl;
		exit(0);
	}
}

void declara_tipo(ifstream& arq) // retorna 1 token
{
	busca_token(arq);
	do
	{
		if(novo_token.tipo_token_formado != "identificador")
		{
			msg = " identificador esperado (declaracao de tipos) ";
			cout << endl << msg << countline << endl;
			exit(0);
		}
		busca_token(arq);
		if(novo_token.token_formado != "=")
		{
			msg = " = esperado (declaracao de tipos) ";
			cout << endl << msg << countline << endl;
			exit(0);
		}
		busca_token(arq);
		// <tipo> -> <identificador>
		if(novo_token.tipo_token_formado != "identificador")
		{
			msg = " identificador esperado (declaracao de tipos) ";
			cout << endl << msg << countline << endl;
			exit(0);
		}
		busca_token(arq);
		if(novo_token.token_formado != ";")
		{
			msg = " ; esperado (declaracao de tipos) ";
			cout << endl << msg << countline << endl;
			exit(0);
		}
		busca_token(arq);
	}
	while(novo_token.tipo_token_formado == "identificador");
}

void definicoes_de_variaveis(ifstream& arq) // retorna 1 token
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
			msg = " : esperado (definicoes de variavel) ";
			cout << endl << msg << countline << endl;
			exit(0);
		}
		busca_token(arq);
		if(novo_token.tipo_token_formado != "identificador")
		{
			msg = " identificador esperado (definicoes de variavel) ";
			cout << endl << msg << countline << endl;
			exit(0);
		}
		busca_token(arq);
		if(novo_token.token_formado != ";")
		{
			msg = " ; esperado (definicoes de variavel) ";
			cout << endl << msg << countline << endl;
			exit(0);
		}
		busca_token(arq);
	}
	while(novo_token.tipo_token_formado == "identificador");
}

void definicao_de_funcao(ifstream& arq) // retorna 1 token
{
	if(novo_token.token_formado != "funcao")
	{
		msg = " funcao esperado (definicao de funcao) ";
		cout << endl << msg << countline << endl;
		exit(0);
	}
	busca_token(arq);
	if(novo_token.tipo_token_formado != "identificador")
	{
		msg = " identificador esperado (definicao de funcao) ";
		cout << endl << msg << countline << endl;
		exit(0);
	}
	busca_token(arq);

	if(novo_token.token_formado == "(")
	{
		parametros_formais(arq);
	}

	busca_token(arq);
	if(novo_token.token_formado != ":")
	{
		msg = " : esperado (definicao de funcao) ";
		cout << endl << msg << countline << endl;
		exit(0);
	}
	busca_token(arq);
	if(novo_token.tipo_token_formado != "identificador")
	{
		msg = " identificador esperado (definicao de funcao) ";
		cout << endl << msg << countline << endl;
		exit(0);
	}
	busca_token(arq);
	if(novo_token.token_formado != ";")
	{
		msg = " ; esperado (definicao de funcao) ";
		cout << endl << msg << countline << endl;
		exit(0);
	}
	busca_token(arq);
}

void definicao_de_procedimento(ifstream& arq) // retorna 1 token
{
	if(novo_token.token_formado != "procedimento")
	{
		msg = " procedimento esperado (definicao de procedimento) ";
		cout << endl << msg << countline << endl;
		exit(0);
	}
	busca_token(arq);
	if(novo_token.tipo_token_formado != "identificador")
	{
		msg = " identificador esperado (definicao de procedimento) ";
		cout << endl << msg << countline << endl;
		exit(0);
	}
	busca_token(arq);

	if(novo_token.token_formado == "(")
	{
		parametros_formais(arq);
	}

	busca_token(arq);
	if(novo_token.token_formado != ";")
	{
		msg = "; esperado (definicao de procedimento) ";
		cout << endl << msg << countline << endl;
		exit(0);
	}
	busca_token(arq);
}

void comando_sem_rotulo(ifstream& arq) // nao retorna token
{
	while(novo_token.token_formado == "leia")
	{
		busca_token(arq);
		if(novo_token.token_formado != "(")
		{
			msg = " ( esperado (comando sem rotulo) ";
			cout << endl << msg << countline << endl;
			exit(0);
		}

		busca_token(arq);
		lista_de_identificadores(arq);

		if(novo_token.token_formado != ")")
		{
			msg = " ) esperado (comando sem rotulo) ";
			cout << endl << msg << countline << endl;
			exit(0);
		}
	}
}

void comando_composto(ifstream& arq) // nao retorna token
{
	if(novo_token.token_formado != "inicio")
	{
		msg = " inicio esperado (comando composto) ";
		cout << endl << msg << countline << endl;
		exit(0);
	}
	busca_token(arq);

	while(novo_token.token_formado != "fim")
	{
		comando_sem_rotulo(arq);

		busca_token(arq);
		if(novo_token.token_formado != ";")
		{
			msg = "; esperado (comando composto) ";
			cout << endl << msg << countline << endl;
			exit(0);
		}

		busca_token(arq);
	}

	if(novo_token.token_formado != "fim")
	{
		msg = " fim esperado (comando composto) ";
		cout << endl << msg << countline << endl;
		exit(0);
	}
}

void bloco(ifstream& arq) // nao retorna token
{
	if(novo_token.token_formado == "tipo")
	{
		declara_tipo(arq);
	}
	if(novo_token.token_formado == "var")
	{
		definicoes_de_variaveis(arq);
	}
	while(novo_token.token_formado == "funcao" || novo_token.token_formado == "procedimento")
	{
		do
		{
			if(novo_token.token_formado == "funcao")
			{
				definicao_de_funcao(arq);
			}
			else
			{
				definicao_de_procedimento(arq);
			}
		}
		while(novo_token.token_formado == "funcao" || novo_token.token_formado == "procedimento");
	}
	comando_composto(arq);
}

void sintatico(ifstream& arq)
{
	busca_token(arq);
	if(novo_token.token_formado != "programa")
	{
		msg = "programa esperado na linha (sintatico) ";
		cout << endl << msg << countline << endl;
		exit(0);
	}

	busca_token(arq);
	if(novo_token.tipo_token_formado != "identificador")
	{
		msg = "identificador esperado na linha (sintatico) ";
		cout << endl << msg << countline << endl;
		exit(0);
	}

	busca_token(arq);
	if(novo_token.token_formado != ";")
	{
		msg = "; esperado na linha (sintatico) ";
		cout << endl << msg << countline << endl;
		exit(0);
	}

	busca_token(arq);
	bloco(arq);

	busca_token(arq);
	if(novo_token.token_formado != ".")
	{
		msg = ". esperado na linha (sintatico)";
		cout << endl << msg << countline << endl;
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
