#include "Arbol.h"

Nodo::Nodo (string elem) {
	this->elem = elem;
	izq = NULL;
	der = NULL;
	altura = 0;
}

int Nodo::maximo(int n, int m){
	if (m<n) return n;
	return m;
}

int Nodo::Altura(Nodo *n){
	if(n== NULL) return -1;
	return n->altura;
}


void Nodo::RSI(Nodo *&n){
	Nodo *m = n->izq;
	n->izq = m->der;
	m->der = n;
	n->altura = 1+maximo(Altura(n->izq), Altura(n->der));
	m->altura = 1+maximo(Altura(m->izq), n->altura);
	n = m;
}

void Nodo::RSD(Nodo *&n){
	Nodo *m = n->der;
	n->der = m->izq;
	m->izq = n;
	n->altura = 1+maximo(Altura(n->izq), Altura(n->der));
	m->altura = 1+maximo(Altura(m->der), n->altura);
	n = m;
}

void Nodo::RDI(Nodo *&n){
	RSD(n->izq);
	RSI(n);	
}

void Nodo::RDD(Nodo *&n){
	RSI(n->der);
	RSD(n);

}

bool Nodo::insertarR (Nodo *&n, string cadena) {
	bool insertado = false;
	if (n == NULL) {
		n = new Nodo(cadena);
		insertado = true;
	}

	else {
		if (cadena < n->elem) {
			insertado = insertarR(n->izq, cadena);
			if (Altura(n->izq) - Altura(n->der)>1){
				if (cadena < n->izq->elem)
					RSI(n);
				else
					RDI(n);
			}
			else
				n->altura = 1+maximo(Altura(n->izq), Altura(n->der));		
		}
		else 
			if (cadena > n->elem){
				insertado = insertarR(n->der,cadena);
				if (Altura(n->der) - Altura(n->izq)>1){
					if (cadena < n->der->elem)
						RDD(n);
					else
						RSD(n);
				}		
				else
					n->altura = 1+maximo(Altura(n->izq), Altura(n->der));			
			}
	}
	return insertado;
}

bool Nodo::consultarR(Nodo *n, string palabra){
	
	if(n==NULL) return false;
	if(n->elem == palabra) return true;
	if (palabra > n->elem)
		return consultarR(n->der, palabra);
	return consultarR(n->izq, palabra);
	
};

void Nodo::sacoR (Nodo *n, string cad1, string cad2, string &resultado) {	
	if (n != NULL) { 
		if (n->elem <= cad1)
			sacoR(n->der, cad1, cad2, resultado);	
		else if (n->elem >= cad2)
			sacoR(n->izq, cad1, cad2, resultado);
		
		else	{
			sacoR(n->izq, cad1, cad2, resultado);
			resultado += " " + n->elem;
			sacoR(n->der, cad1, cad2, resultado);
		}
	}
}

//cadena1 empieza por cadena2?
bool Nodo::empiezaPor (string cad1, string cad2) {
	if (cad1.length() < cad2.length())
		return false;

	int i = 0;
	while ((cad1[i] == cad2[i]) && (cad2.length() > i))
		++i;
	return (i >= cad2.length());
}

//Cuenta letras segun Alargapalabras (Ñ u Ü cuentan 1)
int Nodo::cuentaLetras (string c) {
	int longitudCadena = c.length();	
	int i = 0;	//recorrido
	int contador = 0;
	while (i < longitudCadena){
		if ( !((c[i] == (char) 0xC3) && (i != longitudCadena - 1) &&			
		((c[i+1] == (char) 0x9C) || (c[i+1] == (char) 0x91))) )
			++contador;				//Caso de no-Ü y no-Ñ
	
			++i;
	}
	
	return contador;
}

void Nodo::alargapalabrasR(Nodo *n, string palabra, string &resultado) {
	if (n!=NULL) {
		if (n->elem < palabra)
			alargapalabrasR(n->der, palabra, resultado);

		else if (!empiezaPor(n->elem, palabra))
			alargapalabrasR(n->izq, palabra, resultado);
		
		else {
			alargapalabrasR(n->izq, palabra, resultado);
			if (cuentaLetras(n->elem) > cuentaLetras(resultado))	//Recorremos ordenadamente (inorden), luego es estricto
				resultado = n->elem;
			alargapalabrasR(n->der, palabra, resultado);
		}
	}
}


void Nodo::listarInordenR (Nodo *n) {
	if (n != NULL) {
		listarInordenR(n->izq);
		cout << " " + n->elem;
		listarInordenR(n->der);
	}
}

void Nodo::listarPreordenR (Nodo *n) {
	if (n != NULL) {
		cout << " " + n->elem;
		listarPreordenR(n->izq);
		listarPreordenR(n->der);
	}
}

void Nodo::listarPostordenR (Nodo *n) {
	if (n != NULL) {
		listarPostordenR(n->izq);
		listarPostordenR(n->der);
		cout << " " + n->elem;
	}
}

//-----------------------ARBOL----------------------//



Arbol::Arbol () {
	raiz = NULL;
	nElem = 0;
}


void Arbol::insertar (string palabra) {
	if (Nodo::insertarR(raiz, palabra))
		nElem++;

}

void Arbol::vaciar(){
	nElem = 0;
	delete raiz;
	raiz = NULL;
}


bool Arbol::consultar(string palabra){
	return Nodo::consultarR(raiz, palabra);
}


void Arbol::listarInorden () {

	Nodo::listarInordenR (raiz);

}

void Arbol::listarPreorden () {

	Nodo::listarPreordenR (raiz);

}

void Arbol::listarPostorden () {

	Nodo::listarPostordenR (raiz);

}

string Arbol::saco (string cad1, string cad2) {
	string resultado = "";
	Nodo::sacoR(raiz, cad1, cad2, resultado);
	return resultado;
}

string Arbol::alargapalabras (string palabra) {
	string resultado = "";
	Nodo::alargapalabrasR (raiz, palabra, resultado);
	if (resultado != "")
		resultado = " " + resultado;
	return resultado;
}
