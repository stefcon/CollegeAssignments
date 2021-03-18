#ifndef _sastojak_h_
#define _sastojak_h_

#include "Namirnica.h"

class Sastojak {
	Namirnica namirnica;
	double kolicina;
public:
	Sastojak(const Namirnica& nam, double kol) : namirnica(nam), kolicina(kol) {}

	double dohvKolicinu() const { return kolicina; }

	Namirnica dohvNamirnicu() const { return namirnica; }

	Nutritivna_vrednost dohvNutrVr() const;

	double dohvKalorije() const;

	friend ostream& operator<<(ostream& os, const Sastojak& s) {
		return os << "[" << s.dohvKalorije() << " kcal] " << s.kolicina << " x " << s.namirnica;
	}


};


#endif // !_sastojak_h_

