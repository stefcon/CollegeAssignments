#ifndef _prevoz_h_
#define _prevoz_h_

#include "Destinacija.h"

class Prevoz {
	Destinacija dest;
	double cena;
public:
	Prevoz(const Destinacija& d, double c) : dest(d), cena(c) {}

	Destinacija dohvDest() const { return dest; }

	double dohvCenu() const { return cena; }
};

#endif // !_prevoz_h_
