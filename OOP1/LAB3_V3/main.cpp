#include "Mec.h"

int main() {
	try {
		Igrac igrac1("Messi", 9000), igrac2("Dusko Tosic", 1069), igrac3("Ronaldo", 8999), igrac4("Marcelo", 7000);

		Tim tim1("Barcelona", 2);
		tim1.staviNaPoz(igrac1, 0);
		tim1.staviNaPoz(igrac2, 1);

		cout << tim1 << endl;

		Privilegovani tim2("Real Madrid", 2, 5000);
		tim2.staviNaPoz(igrac3, 0);
		tim2.staviNaPoz(igrac4, 1);

		const Igrac* igrac = tim2[0];

		igrac = new Igrac(igrac1);

		cout << *igrac << endl;

		cout << tim2 << endl;

		Mec el_classico1(tim1, tim2);
		el_classico1.odigrajMec();
		cout << el_classico1 << endl;

		Par<int,int> poeni = el_classico1.dohvPoene();
		cout << poeni << endl;

		Mec el_classico2(tim1, tim2);
		el_classico2.dohvPoene();
	}
	catch (exception e) {
		cout << e.what() << endl;
	}



	return 0;
}