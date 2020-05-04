#ifndef _DIC_PALABRAS_
#define _DIC_PALABRAS_

#include "TablaHash.h"
#include "Arbol.h"

using namespace std;

class DicPalabras {

	private:
		TablaHash tablaConsome;
		TablaHash tablaCesar;
		TablaHash tablaJuana;
		Arbol arbol;
	public:
		DicPalabras();
		void vaciar();
		void insertar (string palabra);
		bool consultar (string palabra);
		int numElem (void) { return arbol.numElem(); }
		string saco (string cad1, string cad2);
		string consome (string palabra);
		string alargapalabras (string palabra);
		string cesar(string palabra);
		string juanagrama (string palabra);
};
#endif
