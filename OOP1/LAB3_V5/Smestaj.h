#ifndef _smestaj_h_
#define _smestaj_h_

#include "Destinacija.h"
#include <exception>

class GZvezdice : public exception {
public:
	GZvezdice() : exception("*** Greska pri zadavanju broja zvezdica! ***") {}
};

enum struct TipSmestaja { HOTEL, APARTMAN };

class Smestaj {
	Destinacija dest;
	TipSmestaja tip;
	string naziv;
	int br_zvezdica;
	double cena_po_danu;
public:
	Smestaj(const Destinacija& d, TipSmestaja t, string n, int bz, double c) : dest(d) {
		if (bz < 1 || bz > 5) throw GZvezdice();
		tip = t;
		naziv = n;
		br_zvezdica = bz;
		cena_po_danu = c;
	}


	Destinacija dohvDest() const { return dest; }

	TipSmestaja dohvTip() const { return tip; }

	string dohvNaziv() const { return naziv; }

	int dohvBrZvezdica() const { return br_zvezdica; }

	double dohvCenu() const { return cena_po_danu; }

	friend ostream& operator<<(ostream& os, const Smestaj& s);


};
#endif // !_smestaj_h_

