#ifndef _ARBOL_
#define _ARBOL_

#include <string>
#include <iostream>

using namespace std;

class Nodo {
	private:
		string elem;
		Nodo *izq;
		Nodo *der;
		int altura;

		static int maximo(int n, int m);
		static int Altura(Nodo *n);
		static bool empiezaPor (string cad1, string cad2);
		static int cuentaLetras (string c);
	public:
		Nodo(string elem);
		~Nodo() { delete izq;	delete der; }
		string clave () { return this->elem; };
		static bool insertarR(Nodo *&n, string cadena);
		static bool consultarR(Nodo *n, string palabra);
		static void RSI (Nodo *&n);
		static void RDI (Nodo *&n);
		static void RSD (Nodo *&n);	
		static void RDD (Nodo *&n);
		static void listarInordenR (Nodo *n);
		static void listarPreordenR (Nodo *n);
		static void listarPostordenR (Nodo *n);
		static void sacoR (Nodo *n, string cad1, string cad2, string &resultado);
		static void alargapalabrasR (Nodo *n, string palabra, string &resultado);

};

class Arbol {

	private:
		Nodo *raiz;
		int nElem;
	public:
		Arbol();
		~Arbol() { delete raiz; }
		void insertar(string palabra);
		bool consultar (string palabra);
		void vaciar(void);
		int numElem(void) {return nElem;};
		void listarInorden (void);
		void listarPreorden (void);
		void listarPostorden (void);
		string saco (string cad1, string cad2);
		string alargapalabras (string palabra);
};

#endif
