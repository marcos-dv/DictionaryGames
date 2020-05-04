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
