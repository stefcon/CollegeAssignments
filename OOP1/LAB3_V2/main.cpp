#include "Lista.h"
#include "Sastojak.h"

int main() {
	try {
		Namirnica nam1("jaja", { 0.01, 9.0, 12.6 }, false), nam2("mleko", {60.5, 32.5, 5.5}, false);
		Sastojak s1(nam1, 2), s2(nam2, 0.7);


		Lista<Sastojak> list1;

		list1.dodaj(s1).dodaj(s2);

		for (list1.naPrvi(); list1.postojiTek(); list1.naSled()) {
			cout << list1.dohvTekInfo() << endl;
		}

		list1.dohvTekInfo();

	}
	catch (exception e) {
		cout << e.what() << endl;
	}
	return 0;
}