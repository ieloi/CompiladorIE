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

void declara_tipo(ifstream& arq){
	do
	{
		busca_token(arq);
		if(novo_token.tipo_token_formado != "identificador")
		{
			msg = " identificador esperado ";
			cout << endl << msg << endl;
			exit(0);
		}
		busca_token(arq);
		if(novo_token.token_formado != "=")
		{
			msg = " = esperado ";
			cout << endl << msg << endl;
			exit(0);
		}
		busca_token(arq);
		if(novo_token.tipo_token_formado != "identificador")
		{
			msg = " identificador esperado ";
			cout << endl << msg << endl;
			exit(0);
		}
		busca_token(arq);
		if(novo_token.token_formado != ";")
		{
			msg = " ; esperado ";
			cout << endl << msg << endl;
			exit(0);
		}
		busca_token(arq);
	} while(novo_token.tipo_token_formado == "identificador");
}

void bloco(ifstream& arq){
	if(novo_token.token_formado == "tipo")
	{
		declara_tipo(arq);
	} 
}

void sintatico(ifstream& arq) {
	busca_token(arq);
	if(novo_token.token_formado != "programa")
	{
		msg = "programa esperado na linha ";
		cout << endl << msg << endl;
		exit(0);
	}
	
	busca_token(arq);
	if(novo_token.tipo_token_formado != "identificador")
	{
		msg = "identificador esperado na linha ";
		cout << endl << msg << endl;
		exit(0);
	}
	
	busca_token(arq);
	if(novo_token.token_formado != ";")
	{
		msg = "; esperado na linha ";
		cout << endl << msg << endl;
		exit(0);
	}
	
	busca_token(arq);
	bloco(arq);
	
	busca_token(arq);
	if(novo_token.token_formado != ".")
	{
		msg = ". esperado na linha ";
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
