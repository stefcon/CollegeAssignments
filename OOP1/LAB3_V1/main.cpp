#include "Dinarski_racun.h"

int main() {
	Osoba o1("Janko Jankovic", "0101000696420", { 1,1,2000 });
	Datum d1(1, 1, 2000), d2(1, 2, 1999);
	Dinarski_racun racun(o1, 555333);

	cout << "Ispis osobe;" << endl;
	cout << o1 << endl << endl;

	cout << "Ispis dinarskog racuna: " << endl;
	cout << racun << endl << endl;

	cout << "d1 != d2?" << endl;
	cout << (d1 != d2) << endl << endl;



	return 0;
}