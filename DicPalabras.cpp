#include "DicPalabras.h"

DicPalabras::DicPalabras () {

}

void DicPalabras::vaciar (){
	tablaConsome.vaciar();
	tablaCesar.vaciar();	
	tablaJuana.vaciar();	
	arbol.vaciar();
}

bool DicPalabras::consultar (string palabra){
	//return tabla.consultar(palabra);
	return arbol.consultar(palabra);
}

void DicPalabras::insertar (string palabra){
	tablaConsome.insertar(palabra, 0);
	tablaCesar.insertar(palabra, -1);
	tablaJuana.insertar(palabra, +1);
	arbol.insertar(palabra);
}

string DicPalabras::saco (string cad1, string cad2) {
	return arbol.saco (cad1, cad2);

}

string DicPalabras::consome (string palabra){
	return tablaConsome.consome(palabra);
}

string DicPalabras::alargapalabras (string palabra) {

	return arbol.alargapalabras(palabra);
}

string DicPalabras::cesar (string palabra){
	return tablaCesar.cesar(palabra);
}

string DicPalabras::juanagrama (string palabra) {
	return tablaJuana.juanagrama(palabra);
}
