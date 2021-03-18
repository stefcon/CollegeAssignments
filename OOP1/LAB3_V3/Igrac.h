#ifndef _igrac_h_
#define _igrac_h_

#include <iostream>
#include <string>
using namespace std;

class Igrac {
	string naziv;
	int vrednost;
public:
	Igrac(string n, int vr = 1000) : naziv(n), vrednost(vr) {}

	string dohvNaziv() const { return naziv; }

	int dohvVrednost() const { return vrednost; }

	Igrac& promenaVr(int procenat) {
		vrednost = vrednost * (100 + procenat) / 100;
		return *this;
	}

	friend bool operator==(const Igrac& igr1, const Igrac& igr2) {
		return igr1.naziv == igr2.naziv && igr1.vrednost == igr2.vrednost;
	}

	friend ostream& operator<<(ostream& os, const Igrac& igr) {
		return os << igr.naziv << "#" << igr.vrednost;
	}

};
#endif // !_igrac_h_

