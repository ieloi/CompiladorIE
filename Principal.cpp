#include "funcoes_e_variaveis.h"
#include "lexico.h"
#include "funcoes_sintatico.h"

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

	/*
	if(erro == true)
	{
		cout << endl << msg << endl;
	}
	else
	{
		cout << endl << msg << endl;
	}
	*/
	
	cout << endl << msg << endl;

	return 0;
}
