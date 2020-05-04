#ifndef _INTERPRETE_
#define _INTERPRETE_

#include "DicPalabras.h"

using namespace std;

class Interprete{

	private:
		DicPalabras dic;
		string normalizar (string cadena);
	public:
		Interprete ();
		void VACIAR ();
		void INSERTAR ();
		void BUSCAR ();
		void SALIR ();
		void PARTIDAS ();
		void ALOCADO ();
		void JUANAGRAMA ();
		void CESAR ();
		void CONSOME ();
		void ALARGAPALABRAS ();
		void SACO ();
		void INTERPRETE (string comando);


};
#endif
