#include "Interprete.h"

Interprete::Interprete () {
	dic = DicPalabras ();

}

string Interprete::normalizar (string cadena){
	string cadena2 ;
	for (unsigned int i=0; i < cadena.length();i++){
		if (cadena[i] >= 'a' && cadena[i] <= 'z') {
			cadena2 += toupper(cadena[i]); 
		}
		else if (cadena[i] == (char) 0xC3){
			i++;
			switch (cadena[i]){
				case (char) 0xA1 : cadena2+='A'; break;
				case (char) 0xA9 : cadena2+="E"; break;
				case (char) 0xAD : cadena2+="I"; break;
				case (char) 0xB3 : cadena2+="O"; break;
				case (char) 0xBA : cadena2+="U"; break;
				case (char) 0xBC : cadena2+=0xC3; cadena2+=0x9C; break;
				case (char) 0xB1 : cadena2+=0xC3; cadena2+=0x91; break;
				case (char) 0x81 : cadena2+="A"; break;
				case (char) 0x89 : cadena2+="E"; break;
				case (char) 0x8D : cadena2+="I"; break;
				case (char) 0x93 : cadena2+="O"; break;
				case (char) 0x9A : cadena2+="U"; break;
				case (char) 0x9C : cadena2+=0xC3; cadena2+=0x9C; break;
				case (char) 0x91 : cadena2+=0xC3; cadena2+=0x91; break;
				default : cadena2 += 0xC3; cadena2 += cadena[i]; 
			}
		
		} else cadena2 += cadena[i];
	
	}
	return cadena2;
}

void Interprete::INSERTAR(){

	int contadorActual=0;
	do {
		string palabraActual;
		cin >> palabraActual; 
		if (palabraActual == "</insertar>")
			break;
		else{
 		dic.insertar(normalizar(palabraActual));
		++contadorActual;
		}
	} while (true);
	cout << "Insertando: " << contadorActual << " palabras" << endl << "Total diccionario: " << dic.numElem() << " palabras" << endl;

}

void Interprete::VACIAR(){
	
	dic.vaciar();
	cout << "Vaciando" << endl << "Total diccionario: " << dic.numElem() << " palabras" << endl;
}

void Interprete::BUSCAR(){

	string palabraActual;
	cin >> palabraActual;
	palabraActual = normalizar(palabraActual);
	
	cout << "Buscando: " << palabraActual << " -> ";
	if (dic.consultar(palabraActual))
		cout << "Encontrada" << endl;
	else
		cout << "No encontrada" << endl;
}

void Interprete::SALIR (){
	cout << "Saliendo..." << endl;
}

void Interprete::PARTIDAS (){
	cout << "Partidas:";
	do {
		string palabraActual;
		cin >> palabraActual; 
		if (palabraActual == "</partidas>")
			break;
		else
			cout << " " << normalizar(palabraActual);
	} while (true);

	cout << endl << "No implementado" << endl;
}

void Interprete::ALOCADO (){
	string palabraActual;
	cin >> palabraActual;
	cout << "Alocado: " << normalizar(palabraActual) << endl
	<< "No implementado" << endl;
}
 
void Interprete::JUANAGRAMA(){
	string palabraActual;
	cin >> palabraActual;
	palabraActual = normalizar(palabraActual);
	cout << "Juanagrama: " << palabraActual << " ->" << dic.juanagrama(palabraActual) << endl;
}
 
void Interprete::CESAR (){
	string palabraActual;
	cin >> palabraActual;
	palabraActual = normalizar(palabraActual);
	cout << "César: " << palabraActual << " ->" << dic.cesar(palabraActual) << endl;
}
 
void Interprete::CONSOME() {
	string palabraActual;
	cin >> palabraActual;
	palabraActual = normalizar(palabraActual);
	cout << "Consomé: " << palabraActual << " ->" << dic.consome(palabraActual) << endl;
}
 
void Interprete::ALARGAPALABRAS(){
	string palabraActual;
	cin >> palabraActual;
	palabraActual = normalizar(palabraActual); 
	cout << "Alarga: " << palabraActual << " ->" << dic.alargapalabras(palabraActual) << endl;
	
}
 
void Interprete::SACO (){
	string palabraActual1;
	string palabraActual2;
	cin >> palabraActual1 >> palabraActual2;
	palabraActual1 = normalizar(palabraActual1);
	palabraActual2 = normalizar(palabraActual2);
	cout << "Saco: " << palabraActual1 << " " << palabraActual2 << " ->" << dic.saco(palabraActual1, palabraActual2) << endl;

}
 
void Interprete::INTERPRETE (string comando){
	if (comando == "<insertar>")
		INSERTAR();
	else if (comando == "<vaciar>")
		VACIAR();
	else if (comando == "<buscar>")
		BUSCAR();
	else if (comando == "<partidas>")
		PARTIDAS();
	else if (comando == "<alocado>")
		ALOCADO();
	else if (comando == "<juanagra>")
		JUANAGRAMA();
	else if (comando == "<césar>")
		CESAR();
	else if (comando == "<consomé>")
		CONSOME();
	else if (comando == "<alarga>")
		ALARGAPALABRAS();
	else if (comando == "<saco>")
		SACO();
	else if (comando == "<exit>")
		SALIR();

}

