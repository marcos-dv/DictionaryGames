#include "Interprete.h"   

using namespace std; 

int main(){

	string comando;
	cin >> comando;
	Interprete inter = Interprete();
	do{
		inter.INTERPRETE (comando);
	} while ((comando != "<exit>") && (cin >> comando));

	return 0;

}

// Pruebas rapidas (ej 300)
// rm DicPalabras.o main.o TablaHash.o Arbol.o Interprete.o; make; clear; echo -n "Tiempo Transcurrido:"; time ./a.out < 200a.in > salida300
