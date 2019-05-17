#include "funcoes_e_variaveis.h"
#include "lexico.h"

int main() {
	setlocale(LC_ALL, "Portuguese");

	ifstream txtFile;

	txtFile.open("teste.txt");

	if(!txtFile) {
		cout << "erro de abertura do arquivo";
	} else {
		while(!txtFile.eof()) {
			if(erro == true) {
				break;
			} else {
				if(tk_encontrado == true) {
					verificaEstadoToken(estado);
					automato(c);
					tk_encontrado = false;
				} else {
					txtFile.get(c);
					automato(c);
				}
			}
		}
		txtFile.close();
	}

	if(erro == true) {
		cout << endl << msg << countline++ << endl;
	} else {
		cout << endl << msg << endl;
	}

	return 0;
}
