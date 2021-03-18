#ifndef _namirnica_h_
#define _namirnica_h_

#include "Nutritivna_vrednost.h"

class Namirnica {
	string naziv;
	Nutritivna_vrednost nutr_vr;
	bool posna;
public:
	Namirnica(string ime, const Nutritivna_vrednost& vrednost, bool posno) : naziv(ime), nutr_vr(vrednost), posna(posno) {}

	friend bool operator==(const Namirnica& namirnica1, const Namirnica& namirnica2) {
		return namirnica1.naziv == namirnica2.naziv;
	}

	string dohvNaziv() const { return naziv; }

	Nutritivna_vrednost dohvNutrVr() const { return nutr_vr; }

	bool jePosna() const { return posna; }

	friend ostream& operator<<(ostream& os, const Namirnica& namirnica) {
		return os << namirnica.naziv << "-" << namirnica.nutr_vr;
	}
};

#endif // !_namirnica_h_

