#include "declaracao_funcoes_sintatico.h"

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

void fator(ifstream& arq)
{
	if(novo_token.tipo_token_formado == "identificador")
	{
		
	}
	else if(novo_token.tipo_token_formado == "digito")
	{
		
	}
	else
	{
		msg = " identificador ou digito esperado (fator) ";
		cout << endl << msg << countline << endl;
		exit(0);
	}
}

void termo(ifstream& arq) // retorna 1 token
{
	fator(arq);
	busca_token(arq);
	while(novo_token.token_formado == "*" || novo_token.token_formado == "/" || novo_token.token_formado == "&&")
	{
		if(novo_token.token_formado != "*" && novo_token.token_formado != "/" && novo_token.token_formado != "&&")
		{
			msg = " + ou - ou && esperado (termo) ";
			cout << endl << msg << countline << endl;
			exit(0);
		}
		busca_token(arq);
		fator(arq);
		busca_token(arq);
	}
}

void expressao_simples(ifstream& arq) // retorna 1 token
{
	busca_token(arq);
	if(novo_token.token_formado == "+" || novo_token.token_formado == "-")
	{
		busca_token(arq);
	}
	termo(arq);
	while(novo_token.token_formado == "+" || novo_token.token_formado == "-" || novo_token.token_formado == "||")
	{
		if(novo_token.token_formado != "+" && novo_token.token_formado != "-" && novo_token.token_formado != "||")
		{
			msg = " + ou - ou || esperado (expressao simples) ";
			cout << endl << msg << countline << endl;
			exit(0);
		}
		busca_token(arq);
		termo(arq);
	}
}

void expressao(ifstream& arq)
{
	expressao_simples(arq);

	if(novo_token.token_formado == "=" || novo_token.token_formado == "<>" || novo_token.token_formado == "<" || novo_token.token_formado == "<=" || novo_token.token_formado == ">" || novo_token.token_formado == ">=")
	{
		expressao_simples(arq);
	}
}

void lista_de_expressoes(ifstream& arq)
{
	expressao(arq);
	while(novo_token.token_formado == ";")
	{
		if(novo_token.token_formado != ";")
		{
			msg = " ; esperado (lista de expressoes) ";
			cout << endl << msg << countline << endl;
			exit(0);
		}
		expressao(arq);
	}
}

void comando_leia(ifstream& arq)
{
	while(novo_token.token_formado == "leia")
	{
		busca_token(arq);
		if(novo_token.token_formado != "(")
		{
			msg = " ( esperado (comando leia)";
			cout << endl << msg << countline << endl;
			exit(0);
		}

		busca_token(arq);
		lista_de_identificadores(arq);

		if(novo_token.token_formado != ")")
		{
			msg = " ) esperado (comando leia)";
			cout << endl << msg << countline << endl;
			exit(0);
		}
	}

	busca_token(arq);
}

void comando_imprima(ifstream& arq) // retorna 1 token
{
	while(novo_token.token_formado == "imprima")
	{
		busca_token(arq);
		if(novo_token.token_formado != "(")
		{
			msg = " ( esperado (comando imprima) ";
			cout << endl << msg << countline << endl;
			exit(0);
		}

		//busca_token(arq);
		lista_de_expressoes(arq);

		if(novo_token.token_formado != ")")
		{
			msg = " ) esperado (comando imprima) ";
			cout << endl << msg << countline << endl;
			exit(0);
		}
	}
	busca_token(arq);
}

void comando_repetitivo(ifstream& arq)
{
	expressao(arq);
	
	if(novo_token.token_formado == "do")
	{
		busca_token(arq);
		comando_sem_rotulo(arq);
	}
}

void comando_sem_rotulo(ifstream& arq) // nao retorna token
{
	if(novo_token.token_formado == "leia")
	{
		comando_leia(arq);
	}

	if(novo_token.tipo_token_formado == "identificador")
	{
		busca_token(arq);

		if(novo_token.token_formado == ":=")
		{
			expressao(arq);
		}

		if(novo_token.token_formado == "(")
		{
			lista_de_expressoes(arq);
			if(novo_token.token_formado != ")")
			{
				msg = " ) esperado (comando sem rotulo) ";
				cout << endl << msg << countline << endl;
				exit(0);
			}
			busca_token(arq);
		}
	}
	
	if(novo_token.token_formado == "enquanto")
	{
		comando_repetitivo(arq);
	}

	if(novo_token.token_formado == "imprima")
	{
		comando_imprima(arq);
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

		//busca_token(arq);
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