#include "Aranzman.h"


int main() {
	try {
		Destinacija dest1("Mirijevo", "Fantasticna lokacija sa prelepom prirodom i zanimljvim sadrzajima");
		dest1.oceni(5).oceni(5).oceni(4);

		Smestaj vila1(dest1, TipSmestaja::APARTMAN, "Vila Brankovic", 5, 20);

		cout << vila1 << endl;
		
		Prevoz autobus(dest1, 500);

		Aranzman all_inclusive(dest1, { 2, 4, 2021 }, { 3, 5, 2021 });

		cout << all_inclusive.dohvTrajanje() << endl;

		all_inclusive.dodeliPrevoz(autobus);
		all_inclusive.dodeliSmestaj(vila1);

		Aranzman kopija = all_inclusive;

		cout << kopija << endl;

	}
	catch (exception e) {
		cout << e.what() << endl;
	}


	return 0;
}