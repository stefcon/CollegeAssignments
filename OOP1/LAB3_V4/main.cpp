#include "GeneratorPostfiksa.h"

int main() {
	try {
		GeneratorPostfiksa& gen = GeneratorPostfiksa::dohvObjekat();
		Leva_zagrada l;
		Desna_zagrada d;
		Sabiranje p;
		Mnozenje m;
		Operand op1("1"), op2("2"), op3("3");
		Izraz infiks;


		infiks += &op1;
		infiks += &p;
		infiks += &op2;
		infiks += &m;
		infiks += &op3;
		infiks += &m;
		infiks += &l;
		infiks += &op1;
		infiks += &p;
		infiks += &op2;
		infiks += &d;



		cout << infiks << endl;

		Izraz postfiks = gen(infiks);

		cout << postfiks << endl;
		
		-postfiks;

		Izraz postfiks2 = postfiks;
		
		cout << postfiks2 << endl;
	}
	catch (exception e) {
		cout << e.what() << endl;
	}


	return 0;
}