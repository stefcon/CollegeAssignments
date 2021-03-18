#ifndef _osoba_h
#define _osoba_h

#include "Datum.h"
#include <string>

class Osoba {
	string ime, mat_broj;
	Datum datum;
public:
	Osoba(string i, string m_br, const Datum& d) : ime(i), mat_broj(m_br), datum(d) {}

	Osoba(const Osoba&) = delete;
	Osoba& operator=(const Osoba&) = delete;

	string dohvIme() const { return ime; }

	string dohvMatBr() const { return mat_broj; }

	Datum dohvDat() const { return datum; }

	friend ostream& operator<<(ostream& os, const Osoba& o) {
		return os << "O(" << o.ime << "," << o.mat_broj << "," << o.datum << ")";
	}

};

#endif // !_osoba_h

