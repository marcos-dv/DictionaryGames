a.out:  Arbol.o TablaHash.o DicPalabras.o Interprete.o main.o 
	g++ Arbol.o TablaHash.o DicPalabras.o Interprete.o main.o
main.o: main.cpp Interprete.h
	g++ -c main.cpp
Interprete.o: Interprete.cpp Interprete.h DicPalabras.h
	g++ -c Interprete.cpp
DicPalabras.o: DicPalabras.cpp DicPalabras.h TablaHash.h Arbol.h
	g++ -c DicPalabras.cpp
TablaHash.o: TablaHash.cpp TablaHash.h
	g++ -c TablaHash.cpp
Arbol.o: Arbol.cpp Arbol.h
	g++ -c Arbol.cpp
