#ifndef _TABLAHASH_
#define _TABLAHASH_

#include <list>
#include <string>
#include <vector>
#include <algorithm>

#define TAM 33533

using namespace std;

class TablaHash{

	private:
		list<string> tabla[TAM]; //dispersion abierta estatica
		int numPalabras;
		bool esConsome (string palabra, string iterador);
		bool esVocal (char c);
		bool encontrarSigConsonante (string cadena, int &i);

		vector<int> numerizarCesar (string cadena);
		bool vectoresIguales (vector<int> v, vector<int> u);

		vector<int> numerizarJuana (string cadena); 

	public:	
		int hash (string palabra, int n);
		int hashConsome (string palabra);
		int hashCesar (string palabra);
		int hashJuana (string palabra);		
		TablaHash ();
		void insertar(string palabra, int n);
		bool consultar (string palabra);
		void vaciar(void);
		int numElem(void) {return numPalabras;};
		string consome (string palabra);		
		string cesar (string palabra);		
		string juanagrama (string palabra);

};

#endif 
