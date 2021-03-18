#ifndef _destinacija_h_
#define _destinacija_h_

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Destinacija {
	string naziv, opis;
	double prosek = 0, br_ocena = 0;
public:
	Destinacija(string n, string o) : naziv(n), opis(o) {}

	string dohvNaziv() const { return naziv; }

	string dohvOpis() const { return opis; }

	double dohvProsek() const { return prosek; }

	Destinacija& oceni(int ocena);

	friend bool operator>(const Destinacija& d1, const Destinacija& d2) {
		return d1.prosek > d2.prosek;
	}

	friend ostream& operator<<(ostream& os, const Destinacija& d) {
		return os << "[" << setprecision(2) << d.prosek << "] " << d.naziv << " (" << d.opis << ")" << setprecision(6);
	}
};

#endif // !_destinacija_h_

