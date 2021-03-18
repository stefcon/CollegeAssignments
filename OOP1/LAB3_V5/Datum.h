#ifndef _datum_h_
#define _datum_h_

#include <iostream>
#include <exception>
using namespace std;

class GDatum : public exception {
public:
	GDatum() : exception("*** Neispravan datum ***") {}
};

class Datum {
	int dan, mes, god;
	int izbrojPrestupne() const;
public:
	Datum(int d, int m, int g);
	
	int dohvDan() const { return dan; }

	int dohvMes() const { return mes; }

	int dohvGod() const { return god; }
	
	friend int operator-(const Datum& d1, const Datum& d2);

	friend ostream& operator<<(ostream& os, const Datum& d) {
		return os << d.dan << "." << d.mes << "." << d.god << ".";
	}

};


#endif // !_datum_h_

