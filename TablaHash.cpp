#include "TablaHash.h"

int TablaHash::hash (string c, int n) {
	if (n == 0)
		return hashConsome(c);
	if (n < 0)
		return hashCesar(c);
	return hashJuana(c);
}

//Iterativo Consome
int TablaHash::hashConsome (string c) {
	int result = 31;
	int base = 761;
	int i = 0;
	int longitudCadena = c.length();
	while (i < longitudCadena-1) {
		if ( !( ((c[i] == (char) 0xC3) && (c[i+1] == (char) 0x9C))
		|| (esVocal(c[i])) ) ) {
		int x = (int) c[i];
		result *= base;
		result = result xor x*x*x;
		}
		else if (!esVocal(c[i]))
			++i;
		++i;
	}
	
	if ( (i < longitudCadena) && (!esVocal(c[longitudCadena-1])) ){
		int x = (int) c[longitudCadena-1];
		result *= base;
		result = result xor x*x*x;
	}

	result = result % TAM;
	
	if (result < 0)
		result += TAM;

	return result;
}

TablaHash::TablaHash(){
	numPalabras =0;
}


void TablaHash::vaciar(){
	numPalabras=0;
	for(int i=0; i<TAM;i++)
		tabla[i].clear();
}

void TablaHash::insertar(string palabra, int n){
	int codHash = hash(palabra, n);
	
	list<string>::iterator it;
	it = tabla[codHash].begin();
	while (it != tabla[codHash].end() && *it < palabra) it++;
	if (it == tabla[codHash].end() || *it != palabra) {
		tabla[codHash].insert(it,palabra);
		numPalabras++;
	}
	
	
}

bool TablaHash::consultar(string palabra){
	int codHash = hashConsome(palabra);		//Consome por defecto

	list<string>::iterator it;
	it = tabla[codHash].begin();
	while (it != tabla[codHash].end() && *it < palabra)
		it++;
	return (it != tabla[codHash].end() && *it == palabra );
}

bool TablaHash::esVocal (char c) {
	return ((c=='A') || (c=='E') || (c=='I') || (c=='O') || (c=='U'));
}

bool TablaHash::encontrarSigConsonante (string cadena, int &i) {
	int longCadena = cadena.length();	
	while ( (i < longCadena - 1) &&
	( ((cadena[i] == (char) 0xC3) && (cadena[i+1] == (char) 0x9C))
	|| (esVocal(cadena[i])) ) ){
	
	if(!esVocal(cadena[i]))
		++i;	
	++i;
	
	}
	if ((i >= longCadena) || (esVocal(cadena[i])))
		return false;
	return true;
}

bool TablaHash::esConsome (string palabra, string iterador){
		int longPalabra = palabra.length();
		int longIterador = iterador.length();
		int i = 0;	//iterador
		int j = 0;	//palabra

		while ((i<longIterador) && (j<longPalabra))  {
			bool bpalabra = encontrarSigConsonante(palabra,j);	
			bool biterador = encontrarSigConsonante(iterador,i);
			if ( (biterador && !bpalabra) || (!biterador && bpalabra ) )
				return false;
			else if ( !biterador && !bpalabra )
				return true;
			if (iterador[i] != palabra[j]) return false;
			i++;
			j++;			
		}
		if (j>=longPalabra) 
			return !encontrarSigConsonante (iterador, i);
		if (i>=longIterador)
			return !encontrarSigConsonante (palabra, j);
}


string TablaHash::consome (string palabra) {
	int codHash = hashConsome(palabra);
	string resultado;
	list<string>::iterator it;
	it = tabla[codHash].begin();
	while (it != tabla[codHash].end()) {
		if (esConsome(palabra, *it))
			resultado += " " + *it;
		it++;
	}
	return resultado;
}


//////////cesar

vector<int> TablaHash::numerizarCesar (string cadena) {
	int longitudCadena = cadena.length();	
	vector<int> v (longitudCadena, 0);
	int i = 0;
	int j = 0;
	while (i < longitudCadena){
		if ((cadena[i] == (char) 0xC3) && (i != longitudCadena - 1) &&			
		((cadena[i+1] == (char) 0x9C) || (cadena[i+1] == (char) 0x91))) {	//Caso de Ñ o Ü
			if (cadena[i+1] == (char) 0x9C)	
				v[j] = (int) ('V'-'A');		//'V' en vez de 'U', porque 'U' > 'O'
			else
				v[j] = (int) ('O'-'A');
			++i;
		}
		else {
			v[j] = (int) (cadena[i] - 'A');
			if (cadena[i] >= 'O')
				v[j] += 1;			//Espacio de la ñ

		}
		++i;
		++j;
	}
	//v.resize(j);		EL TAMANYO DEL VECTOR ES 'j'
	for(int i = 0; i < j-1; ++i) {
		v[i] -= v[i+1];			//Factor clave
		if (v[i] < 0)
			v[i] += 27;		//Abecedario
	}
	v.resize(j-1);
	return v;
}

int TablaHash::hashCesar (string palabra) {
	vector<int> v = numerizarCesar(palabra);
	int longVector = v.size();
	int resultado = 29;
	int base = 823;

	for (int i = 0; i < longVector; ++i){	//hash iterativo
		resultado *= base;
		resultado = resultado xor v[i]*v[i];
	}

	resultado = resultado % TAM;
	if (resultado < 0)
		resultado += TAM;
	return resultado;
}

string TablaHash::cesar (string palabra) {
	int codHash = hashCesar(palabra);
	string resultado;

	list<string>::iterator it;
	it = tabla[codHash].begin();
	while (it != tabla[codHash].end()) {
		if (vectoresIguales(numerizarCesar(palabra), numerizarCesar(*it)))	//"Condicion Cesar"
			resultado += " " + *it;
		it++;
	}
	return resultado;	
}

///////////juana


bool TablaHash::vectoresIguales (vector<int> v, vector<int> u) {
	int n = v.size();
	int m = u.size();	
	if (n != m )
		return false;

	int i = 0;	
	while ((i < n) && (v[i] == u[i]))
		++i;
	return (i>=n);

}

vector<int> TablaHash::numerizarJuana (string cadena) {
	int longitudCadena = cadena.length();	
	vector<int> v (longitudCadena, 0);
	int i = 0;
	int j = 0;
	while (i < longitudCadena){
		if ((cadena[i] == (char) 0xC3) && (i != longitudCadena - 1) &&			
		((cadena[i+1] == (char) 0x9C) || (cadena[i+1] == (char) 0x91))) {
			if (cadena[i+1] == (char) 0x9C)	
				v[j] = 1 + (int) 'Z';		//Caso Ü
			else
				v[j] = 2 + (int) 'Z';		//Caso Ñ
			++i;
		}
		else 
			v[j] = (int) (cadena[i] - 'A');
		++i;
		++j;
	}
	v.resize(j);
	sort (v.begin(), v.end());		//Todos los anagramas, al ordenarse, deben ser equivalentes
	return v;
}

int TablaHash::hashJuana (string palabra) {
	vector<int> v = numerizarJuana(palabra);
	int longVector = v.size();
	int resultado = 29;
	int base = 823;

	for (int i = 0; i < longVector; ++i){	//hash iterativo
		resultado *= base;
		resultado = resultado xor v[i]*v[i];
	}

	resultado = resultado % TAM;
	if (resultado < 0)
		resultado += TAM;
	return resultado;
}

string TablaHash::juanagrama (string palabra) {
	int codHash = hashJuana(palabra);
	list<string>::iterator it;
	it = tabla[codHash].begin();

	while ( it != tabla[codHash].end() && !vectoresIguales(numerizarJuana(palabra), numerizarJuana(*it)) )	//Condicion "Juanagrama"
		it++;
	if ( it != tabla[codHash].end() )
		return " " + *it;	
	return "";
}

